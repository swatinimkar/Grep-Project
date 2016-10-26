#ifndef commands_h
#define commands_h


void match_pattern(char *argv[]);
void match_pattern_case_sensitive(char *argv[]);
void match_pattern_whole_word_cs(char *argv[]);
void match_pattern_whole_word_cs_files(char *argv[],int filecount);
void match_pattern_whole_word(char *argv[]);
void match_pattern_files(char *argv[],int filecount);
void match_pattern_files_cs(char *argv[],int filecount);
void match_pattern_file_names(char *argv[],int filecount);
void get_content_excluding_pattern(char *argv[]);
void get_content_excluding_pattern_multi(char *argv[],int filescount);
void count_matching_pattern(char *argv[]);
void show_matched_line_number(char *argv[]);
void count_matching_pattern_invert(char *argv[]);
void get_content_excluding_patterns(char *file,char *pattern);
void show_position_match_pattern(char *argv[]);
void displayHelp();
void usage();
void list_dir(char *dir_name,char *pattern);
void match_pattern_recursive(char *filepath,char *filename, char *pat);
#endif
