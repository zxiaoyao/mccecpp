/*
 * construct_clean_struct.cpp
 *
 * Functions to clean the defined the structures.
 *  Created on: Apr 23, 2014
 *      Author: xzhu
 */

#include <stdlib.h>
#include <string.h>
#include "mcce.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


PROT new_prot()
{
	PROT prot;
	memset(&prot, 0, sizeof(PROT));

	return prot;
}


int cpy_conf(CONF *tgt, CONF *src)
{
	int i;
	ATOM *swap;

	if (src->n_atom != tgt->n_atom) {
		printf("cpy_conf(): conformers do not have same number of atom slots.\n");
		return USERERR;
	}

	/* atom array was already declared, so preserve atoms (number of atoms are the same) */
	swap=tgt->atom;

	/* faithful copy of the conformer */
	memcpy(tgt, src, sizeof(CONF));

	/* copy sublevel contents */
	tgt->atom = swap;
	if (tgt->n_atom && tgt->atom) {
		for (i = 0; i<src->n_atom; i++) tgt->atom[i] = src->atom[i];
	}
	return 0;
}


int cpy_res(RES *tgt, RES *src)
{
	int i_conf;

	/* faithful copy of the residue */
	memcpy(tgt, src, sizeof(RES));

	/* prepare the lower level array */
	tgt->n_conf = 0;
	tgt->conf   = NULL;
	if (src->n_conf) {
		for (i_conf = 0; i_conf<src->n_conf; i_conf++) {
			ins_conf(tgt, i_conf, src->conf[i_conf].n_atom);
			cpy_conf(&tgt->conf[i_conf], &src->conf[i_conf]);
		}
	}

	return 0;
}


int cpy_prot(PROT *tgt, PROT *src)
{
	int i;

	if (tgt->n_res) printf("cpy_prot(): can not copy to a non-empty target .\n");

	/* faithful copy of the residue */
	memcpy(tgt, src, sizeof(PROT));

	/* copy the lower level array */
	if (src->n_res) {
		tgt->res = (RES *) malloc(src->n_res * sizeof(RES));
		for (i = 0; i<src->n_res; i++) cpy_res(&tgt->res[i], &src->res[i]);
	}

	return 0;
}


int del_conf(RES *res_p, int pos)
{
	if (pos >= res_p->n_conf) {
		printf("del_conf(): offrange deletion. residue %3s %c%04d%c, n_conf=%d, delete pos=%d\n",res_p->resName,res_p->chainID,res_p->resSeq,res_p->iCode,res_p->n_conf,pos);
		return USERERR;
	}

	/* free all the lower level data under this conformer */
	if (res_p->conf[pos].atom) {
		free(res_p->conf[pos].atom);
	}

	/* move contents after position "pos" backward by 1 unit */
	memmove(res_p->conf+pos, res_p->conf+pos+1, (res_p->n_conf - pos - 1) * sizeof(CONF));

	/* update number of conformers, shrink the memory */
	res_p->n_conf--;
	res_p->conf = (CONF *) realloc(res_p->conf, res_p->n_conf * sizeof(CONF));

	return pos;
}


int del_res(PROT *prot, int pos)
{
	int i;

	if (pos >= prot->n_res) {
		printf("del_res(): off range deletion.\n");
		return USERERR;
	}

	/* free all the lower level data under this group */

	if (prot->res[pos].n_conf) {
		for (i = 0; i < prot->res[pos].n_conf; i++)
			if (prot->res[pos].conf[i].n_atom) free(prot->res[pos].conf[i].atom);
		free(prot->res[pos].conf);
	}

	/* move contents after position "pos" backward by 1 unit */
	memmove(prot->res+pos, prot->res+pos+1, (prot->n_res - pos - 1) * sizeof(RES));

	/* shrink the memory, update number of atoms */
	prot->n_res--;
	prot->res = (RES *) realloc(prot->res, prot->n_res * sizeof(RES));

	return pos;
}


int del_prot(PROT *prot)
{
	int i, j;

	/* free all the lower level data under this prot */
	if (prot->n_res) {
		for (i=0; i<prot->n_res; i++) {
			if (prot->res[i].n_conf) {
				for (j=0; j<prot->res[i].n_conf; j++) {
					if (prot->res[i].conf[j].n_atom>0) free(prot->res[i].conf[j].atom);/* free atoms */
				}
				free(prot->res[i].conf);	/* free conformers */
			}
		}
		free(prot->res);			/* free residues */
	}

	memset(prot, 0, sizeof(PROT));

	return 0;
}


int ins_conf(RES *res, int ins, int n_atom)
{
	if (ins > res->n_conf)
	{
		printf("ins_conf(): off range insertion.\n");
		return USERERR;
	}

	/*--- increase the conformer list size by 1 */
	if (!(res->conf = (CONF *) realloc(res->conf, (res->n_conf + 1) * sizeof(CONF))))
	{
		printf("ins_conf(): Fails resizing memory\n");
		return USERERR;
	}
	res->n_conf++;

	/* move contents after position "ins" forward by 1 */
	memmove(res->conf+ins+1, res->conf+ins, (res->n_conf - ins - 1) * sizeof(CONF));

	/* initialize the inserted conformer */
	memset(&res->conf[ins], 0, sizeof(CONF));
	res->conf[ins].n_atom = n_atom;
	if (n_atom) {
		if (!(res->conf[ins].atom = (ATOM *) malloc(n_atom*sizeof(ATOM))))
		{
			printf("ins_conf(): Fails allocating memory for atoms.\n");
			return USERERR;
		}
		memset( res->conf[ins].atom, 0, (n_atom * sizeof(ATOM)) );
	}

	return ins;
}


int ins_res(PROT *prot, int ins)
{
	if (ins > prot->n_res) {
		printf("ins_res(): off range insertion.\n");
		return USERERR;
	}

	/*--- increase the residue list size by 1 */
	if (!(prot->res = (RES *) realloc(prot->res, (prot->n_res + 1) * sizeof(RES)))) {
		printf("ins_res(): Fails resizing memory.\n");
		return USERERR;
	}
	prot->n_res++;

	/* move contents after position "ins" forward by 1 */
	memmove(prot->res+ins+1, prot->res+ins, (prot->n_res - ins - 1) * sizeof(RES));

	/* initialize the inserted residue */
	memset(&prot->res[ins], 0, sizeof(RES));

	return ins;
}


int sort_conf(PROT prot)
{
	int i_res;
    int i_conf;
    int j_conf;
    CONF swap_conf;
    STRINGS conflist;
    int  i_conflist;

    for (i_res=0; i_res<prot.n_res; i_res++) {
        if (param_get("CONFLIST", prot.res[i_res].resName, "", &conflist)) {
            printf("sort_conf(): Can't find parameter \"CONFLIST\" of residue \"%s\"\n", prot.res[i_res].resName);
            continue;
        }

        i_conflist = 0;
        for (i_conf=0; i_conf < prot.res[i_res].n_conf; i_conf++) {
            if (i_conflist >= conflist.n) {
               printf("   WARNING: sort_conf(): some conformers in residue \"%s %03d %c\" can not be sorted.\n",
                      prot.res[i_res].resName,
                      prot.res[i_res].resSeq,
                      prot.res[i_res].chainID);
                      break;
            }
            if (!strcmp(prot.res[i_res].conf[i_conf].confName, conflist.strings[i_conflist])) continue;
            /* find the first confomer that can be switched and switch */
            for (j_conf=i_conf+1; j_conf<prot.res[i_res].n_conf; j_conf++) {
               if (!strcmp(prot.res[i_res].conf[j_conf].confName, conflist.strings[i_conflist])) {
                  memcpy(&swap_conf, &prot.res[i_res].conf[j_conf], sizeof(CONF));
                  memmove(&prot.res[i_res].conf[i_conf+1], &prot.res[i_res].conf[i_conf], (j_conf-i_conf)*sizeof(CONF)); /* move instead of switch. Yifan 03/04/01 */
                  memcpy(&prot.res[i_res].conf[i_conf], &swap_conf, sizeof(CONF));
                  break;
               }
            }
            if (j_conf>=prot.res[i_res].n_conf) {
               i_conflist ++;
               i_conf--;
            }
        }
    }
    return 0;
}


int cmp_Eself(const void *a, const void *b)
{
	CONF *A, *B;

	A = (CONF *) a;
	B = (CONF *) b;
	if (A->E_self<B->E_self) return -1;
	else if (A->E_self==B->E_self) return 0;
	else return 1;
}
/*
int cmp_Eself(CONF *A, CONF *B)
{  if (A->E_self<B->E_self) return -1;
   else if (A->E_self==B->E_self) return 0;
   else return 1;
}
*/


int sort_res(PROT prot) {
    int i_res,j_res;
    RES swap_res;

    for (i_res=0; i_res<prot.n_res; i_res++) {
        for (j_res=i_res+1; j_res<prot.n_res; j_res++) {
            if (prot.res[i_res].chainID > prot.res[j_res].chainID) {
                  memcpy(&swap_res, &prot.res[j_res], sizeof(RES));
                  memmove(&prot.res[i_res+1], &prot.res[i_res], (j_res-i_res)*sizeof(RES)); /* move instead of switch. Yifan 03/04/01 */
                  memcpy(&prot.res[i_res], &swap_res, sizeof(RES));
                  j_res = i_res;
            }
        }
    }

    /*
    for (i_res=0; i_res<prot.n_res; i_res++) {
        for (j_res=i_res+1; j_res<prot.n_res; j_res++) {
            if (prot.res[i_res].chainID != prot.res[j_res].chainID) continue;
            if (prot.res[i_res].groupID > prot.res[j_res].groupID) {
                  memcpy(&swap_res, &prot.res[j_res], sizeof(RES));
                  memmove(&prot.res[i_res+1], &prot.res[i_res], (j_res-i_res)*sizeof(RES));  //move instead of switch. Yifan 03/04/01
                  memcpy(&prot.res[i_res], &swap_res, sizeof(RES));
                  j_res = i_res;
            }
        }
    }
    */

    for (i_res=0; i_res<prot.n_res; i_res++) {
        for (j_res=i_res+1; j_res<prot.n_res; j_res++) {
            if ((prot.res[i_res].chainID != prot.res[j_res].chainID)) continue;
            if (prot.res[i_res].resSeq > prot.res[j_res].resSeq) {
                  memcpy(&swap_res, &prot.res[j_res], sizeof(RES));
                  memmove(&prot.res[i_res+1], &prot.res[i_res], (j_res-i_res)*sizeof(RES)); /* move instead of switch. Yifan 03/04/01 */
                  memcpy(&prot.res[i_res], &swap_res, sizeof(RES));
                  j_res = i_res;
            }
        }
    }
    return 0;
}


void id_conf(PROT &prot)
{
	int kr, kc;
	char ins;
	int C;

	for (kr=0; kr<prot.n_res; kr++) {
		C=0;
		if (prot.res[kr].iCode == '\0' || prot.res[kr].iCode == ' ')
			ins = '_';
		else ins = prot.res[kr].iCode;
		for (kc=0; kc<prot.res[kr].n_conf; kc++) {
			sprintf(prot.res[kr].conf[kc].uniqID, "%3s%c%c%c%04d%c%03d", prot.res[kr].resName,
					prot.res[kr].conf[kc].history[0],
					prot.res[kr].conf[kc].history[1],
					prot.res[kr].chainID,
					prot.res[kr].resSeq,
					ins, C);
			prot.res[kr].conf[kc].uniqID[sizeof(prot.res[kr].conf[kc].uniqID)-1] = '\0';
			C++;
		}
	}

	return;
}


int cmp_conf(CONF conf1, CONF conf2, float IDEN_THR) {
	int iatom, jatom,n_on1,n_on2;
	float IDEN_THR2 = IDEN_THR*IDEN_THR;

	//if (strcmp(conf1.confName, conf2.confName)) return -1;
	if (conf1.n_atom != conf2.n_atom) return -1;

	n_on1 = 0;
	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (conf1.atom[iatom].on) n_on1++;
	}
	n_on2 = 0;
	for (jatom = 0; jatom<conf2.n_atom; jatom++) {
		if (conf2.atom[jatom].on) n_on2++;
	}
	if (n_on1 != n_on2) return -2;

	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		for (jatom = 0; jatom<conf2.n_atom; jatom++) {
			if (!conf2.atom[jatom].on) continue;

			if (strncmp(conf1.atom[iatom].name+1, conf2.atom[jatom].name+1, 2) ) continue;
			if (fabs(conf1.atom[iatom].crg - conf2.atom[jatom].crg) > 1e-3) continue;
			if (ddvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz) < IDEN_THR2) break;
		}
		if (jatom == conf2.n_atom) return -1;
	}
	return 0;
}

/** compare two conformers by the distances of the heavy atoms
 * first compare the number of hetero atoms, then distance.
 * return 0, if the two conformers are similar.
 */
int cmp_conf_hv(CONF conf1, CONF conf2, float IDEN_THR)
{
	int iatom, jatom;
	float IDEN_THR2 = IDEN_THR*IDEN_THR;
	int n_hv1=0, n_hv2=0;
	//if (strcmp(conf1.confName, conf2.confName)) return -1;
	//if (conf1.n_atom != conf2.n_atom) return -1;
	/* check if they same number of heavy atoms */
	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		if (conf1.atom[iatom].name[1] == 'H') continue;
		n_hv1++;
	}
	for (jatom = 0; jatom<conf2.n_atom; jatom++) {
		if (!conf2.atom[jatom].on) continue;
		if (conf2.atom[jatom].name[1] == 'H') continue;
		n_hv2++;
	}
	if (n_hv1!=n_hv2) return -1;

	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		if (conf1.atom[iatom].name[1] == 'H') continue;

		for (jatom = 0; jatom<conf2.n_atom; jatom++) {
			if (!conf2.atom[jatom].on) continue;
			if (conf2.atom[jatom].name[1] == 'H') continue;

			if (strncmp(conf1.atom[iatom].name+1, conf2.atom[jatom].name+1, 2) ) continue;
			if (ddvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz) < IDEN_THR2) break;
		}
		if (jatom == conf2.n_atom) return -1;
	}
	return 0;
}

float dist_conf_hv(CONF conf1, CONF conf2) {
	int iatom, jatom;
	float max_dist = 999.;
	float next_test_dist, test_dist2;
	int n_hv1=0, n_hv2=0;

	/* check if they have the same number of heavy atoms */
	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		if (conf1.atom[iatom].name[1] == 'H') continue;
		n_hv1++;
	}
	for (jatom = 0; jatom<conf2.n_atom; jatom++) {
		if (!conf2.atom[jatom].on) continue;
		if (conf2.atom[jatom].name[1] == 'H') continue;
		n_hv2++;
	}
	if (n_hv1!=n_hv2) return 999.;

	next_test_dist = max_dist;
	while (1) {
		test_dist2 = next_test_dist*next_test_dist - 1e-4;
		next_test_dist = 0.;
		for (iatom = 0; iatom<conf1.n_atom; iatom++) {
			if (!conf1.atom[iatom].on) continue;
			if (conf1.atom[iatom].name[1] == 'H') continue;

			for (jatom = 0; jatom<conf2.n_atom; jatom++) {
				if (!conf2.atom[jatom].on) continue;
				if (conf2.atom[jatom].name[1] == 'H') continue;

				if (strncmp(conf1.atom[iatom].name+1, conf2.atom[jatom].name+1, 2) ) continue;
				if (ddvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz) < test_dist2) break;
			}

			if (jatom >= conf2.n_atom) break; /* can't find a jatom within test_dist to match iatom */
			else {
				/* next test threshold is the maximum of all distances btw matched iatom and jatom */
				if (dvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz) > next_test_dist) {
					next_test_dist = dvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz);
				}
			}
		}
		if (iatom < conf1.n_atom) { /* test_dist in the current loop is shorter than the distance btw i and j */
			break;
		}
	}
	return sqrt(test_dist2+1e-4);
}

float rmsd_conf_hv(CONF conf1, CONF conf2) {
	int iatom, jatom;
	int n_hv1=0, n_hv2=0;
	float sum_distsq;

	/* check if they have the same number of heavy atoms */
	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		if (conf1.atom[iatom].name[1] == 'H') continue;
		n_hv1++;
	}
	for (jatom = 0; jatom<conf2.n_atom; jatom++) {
		if (!conf2.atom[jatom].on) continue;
		if (conf2.atom[jatom].name[1] == 'H') continue;
		n_hv2++;
	}
	if (n_hv1!=n_hv2) return 999.;
	if (n_hv1 == 0) return 0.;

	sum_distsq = 0.;
	for (iatom = 0; iatom<conf1.n_atom; iatom++) {
		if (!conf1.atom[iatom].on) continue;
		if (conf1.atom[iatom].name[1] == 'H') continue;

		for (jatom = 0; jatom<conf2.n_atom; jatom++) {
			if (!conf2.atom[jatom].on) continue;
			if (conf2.atom[jatom].name[1] == 'H') continue;

			if (!strcmp(conf1.atom[iatom].name, conf2.atom[jatom].name)) break;
		}
		if (jatom >= conf2.n_atom) return 999.; /* can't find a jatom to match iatom */

		sum_distsq += ddvv(conf1.atom[iatom].xyz, conf2.atom[jatom].xyz);
	}

	return sqrt(sum_distsq/(float) n_hv1);
}


int del_dir(char *dir_name)
{
	struct dirent *dentry;
	DIR *dp;

	if (!(dp = opendir(dir_name))) return -1;

	while ((dentry = readdir(dp))) {
		/*printf("removing ==%s==\n", dentry->d_name);*/
		if (!strcmp(dentry->d_name, ".")) continue;
		if (!strcmp(dentry->d_name, "..")) continue;
		remove(dentry->d_name);
	}
	rmdir(dir_name);

	return 0;
}


/*
 * NAME
 *   free_strings - deallocate the dynamic memory of a STRINGS object
 *
 * SYNOPSIS
 *   #include <mcce.h>
 *
 *   void free_strings(STRINGS *s);
 *
 * DESCRIPTION
 *   The free_strings() function frees memory dynamically allocated to the
 *        'strings' field of a STRINGS object.
 *
 * SEE ALSO
 *   get_files
 *
 * EXAMPLE
 *   #include <mcce.h>
 *   ...
 *        char    *dir = "funalgo";
 *   STRINGS files;
 *
 *   files = get_files(dir);
 *   ...
 *   free_strings(&files);
 *
 * AUTHOR
 *   Yanjun Wang, 06/09/2003
 */
void free_strings(STRINGS *s)
{
	int i;

	for (i = 0; i < s->n; i++) free(s->strings[i]);
	if (s->n > 0) {
		free(s -> strings);
		s -> n = 0;
	}
	return;
}


int rot_swap(PROT prot) {
	int i_res, i_conf, n_conf, ins, i_atom, j_atom, i_swap, counter;
	SWAP_RULE swap_rule;
	char sbuff[MAXCHAR_LINE];
	VECTOR swap_xyz;

	for (i_res=0; i_res<prot.n_res; i_res++) {
		RES *res_p = &prot.res[i_res];

		counter = 0;
		while (1) {
			/* go over each ROT_SWAP parameter associated with this residue */
			sprintf(sbuff, "%d", counter);
			if (param_get("ROT_SWAP", res_p->resName, sbuff, &swap_rule)) break;
			counter++;

			/* for each conformer, make a new conformer and apply swapping rule */
			n_conf = prot.res[i_res].n_conf;
			for (i_conf=1; i_conf<n_conf; i_conf++) {
				CONF *conf_p = &prot.res[i_res].conf[i_conf];

				/* make new conformer */
				ins = ins_conf(res_p, res_p->n_conf, conf_p->n_atom);
				conf_p = &prot.res[i_res].conf[i_conf];
				if (ins == USERERR) {
					printf("   FATAL: rot_swap(): Can't add conformer. Maybe out of memory!\n");
					return USERERR;
				}
				cpy_conf(&res_p->conf[ins], conf_p);
				//strncpy(res_p->conf[ins].history+2, "SP", 2);

				/* apply swapping rule */
				for (i_swap=0; i_swap<swap_rule.n_swap; i_swap++) {
					if (param_get("IATOM",res_p->conf[ins].confName,swap_rule.swap_atom1[i_swap],&i_atom)) continue;
					if (param_get("IATOM",res_p->conf[ins].confName,swap_rule.swap_atom2[i_swap],&j_atom)) continue;

					swap_xyz = res_p->conf[ins].atom[i_atom].xyz;
					res_p->conf[ins].atom[i_atom].xyz = res_p->conf[ins].atom[j_atom].xyz;
					res_p->conf[ins].atom[j_atom].xyz = swap_xyz;
				}
			}
		}
	}
	return 0;
}
