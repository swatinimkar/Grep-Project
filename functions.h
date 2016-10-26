#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <regex.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>


#define MAX_MATCHES 1


char* fStrJoin(char **str, const char *delimiters);
int findHyphenInStr(char *str);
int get_string_len(char *str);
int isdelimiter(char ch);
int matchWholeWord(const char *haystack, const char *needle);
char *extractPattern(char *str);
int match(regex_t *pexp, char *sz);
const char *get_filename_ext(const char *filename);
int checkFile(char *str);
#endif
