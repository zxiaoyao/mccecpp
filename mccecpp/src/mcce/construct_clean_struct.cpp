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
