#include "functions.h"

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


int get_string_len(char *str) {
	int i;
	for(i=0;str[i]!='\0';i++);
	return i;
}

int isdelimiter(char ch) {
  return (ch == ' ') || (ch == '\0');
}

int checkFile(char *str) {

	FILE *file = fopen(str, "r");
	int c,flag=0;
	while ((c = fgetc(file)) != EOF && c <= 127) {}
	if(c == EOF) {
		flag=1;
	} else {
		flag=0;
	}

	return flag;
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}


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


int match(regex_t *pexp, char *sz) {
	regmatch_t matches[MAX_MATCHES];
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		return 1;
	} else {
		return 0;
	}
}

