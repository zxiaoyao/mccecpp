#include <stdio.h>
#include <string.h>
#include "mcce.h"


/**
 * Get the string without the leading and ending spaces
 * @param target new string without space or '\t'.
 * @param str orignal string.
 * @return number of spaces stripped.
 */
int strip(char *target, const char *str)
/* get the string without the leading and ending spaces, return spaces stripped */
{  int len = strlen(str);
   int i, j;
   char spc[] = " \t";
   char tmp[MAXCHAR_LINE];

   for (i = 0; i < len; i++) if (!strchr(spc,str[i])) break;
   for (j = strlen(str) - 1; j>=i; j--) if (!strchr(spc,str[j])) break;

   /* use tmp so that str and target can be the same string */
   strncpy(tmp, str+i, (j-i)+1);
   strncpy(target, tmp, (j-i)+1);
   target[j-i+1] = '\0';

   return len - (j-i) - 1;
}


/**
 * Remove comments in a string.
 * Get rid of the characters after "REMARK" or '#' comment sign (including itself).
 * @param target a copy of the orignal string without the comment.
 * @param str original string.
 * @return exit status.
 */
int rm_comment(char *target, char *str)
{
	char *pt;

	strcpy(target, str);
	if ((pt=strstr(target, "REMARK")) ||
			(pt=strchr(target, '#'))      ||
			(pt=strchr(target, '\n'))       )  *pt = '\0';

	return 0;
}
