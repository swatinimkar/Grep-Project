/*****************************************************************************
 * Copyright (C) Swati Nimbolkar swatinimbolkar32@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#include "functions.h"

// This function will join strings with delimeter

char* fStrJoin(char **str, const char *delimiters)
{
    char *joinedStr;
    int i = 1;
    joinedStr = realloc(NULL, strlen(str[0])+1);
    strcpy(joinedStr, str[0]);
    if (str[0] == NULL){
        return joinedStr;
    }
    while (str[i] !=NULL){
        joinedStr = (char*)realloc(joinedStr, strlen(joinedStr) + strlen(str[i]) + strlen(delimiters) + 1);
        strcat(joinedStr, delimiters);
        strcat(joinedStr, str[i]);
        i++;
    }
    return joinedStr;
}


// This function will find the if pattern is argument or not

int findHyphenInStr(char *str) {

	int i=0;

	for(i=0;str[i]!='\0';i++) {
		if(str[0] == '-') {
			break;
		} else {
			return 1;
		}
	}
	return i;
}


// This function will find the length of string

int get_string_len(char *str) {
	int i;
	for(i=0;str[i]!='\0';i++);
	return i;
}


// This function will check for space of NULL terminating character

int isdelimiter(char ch) {
  return (ch == ' ') || (ch == '\0');
}


// This function will check if file is textfile or binary 

int checkFile(char *str) {

	FILE *file = fopen(str, "r");
	int c,flag=0;
	if(file== NULL){
		flag=0;
	} else {
		while ((c = fgetc(file)) != EOF && c <= 127) {}
		if(c == EOF) {
			flag=1;
		} else {
			flag=0;
		}
	}

	return flag;
}


// This function will return the extension of file name

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}


// This function will match the whole word in given string

int matchWholeWord(const char *haystack, const char *needle) {
  int match = 0;
  const char *h = haystack;
  const char *m;
  size_t len = strlen(needle);
  while ((m = strstr(h, needle)) != NULL) {
    if ((m == haystack || isdelimiter(m[-1])) && isdelimiter(m[len])) {
      // printf("'%s'",m);
      match=1;
      h += len;
      break;
    } else {
      h++;
    }
  }
  return match;
}


// This function will remove double quotes from string

char *extractPattern(char *str) {	
	int i,k=0;
	char *result;

	result = (char *)malloc(sizeof(char));
	
	for(i=0;str[i]!='\0';i++) {
		if(str[i] != '"') {
			result[k++] = str[i];
		}	
	}
	result[k] = '\0';

	return result;
}

// This function will perform regular expression match in entered string
int match(regex_t *pexp, char *sz) {
	regmatch_t matches[MAX_MATCHES];
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		return 1;
	} else {
		return 0;
	}
}

