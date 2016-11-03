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
#include "commands.h"

int main(int argc,char *argv[]) {

	struct stat stt;
	int i=0;
	int error=0;
	int hyphenExist;
	char *switch_pattern;
	char switch_char,switch_char1;
	char *patterns[100];
	int patternFlag=0;
	int count1=2,count2=3;
	char *joinedMultiPatterns;


	if(argc == 1) {

	    usage();

	} else {
		switch_pattern = extractPattern(argv[1]);
		hyphenExist = findHyphenInStr(switch_pattern);

		if(hyphenExist == 0) {

			switch_char = switch_pattern[hyphenExist+1];
	
			if(switch_char == 'i') {

				switch_char1 = switch_pattern[hyphenExist+2];

				if(switch_char1 == 'w') {
				
					if(argc==4)
					{				
						if(stat(argv[3],&stt)==0)
						    match_pattern_whole_word_cs(argv);
						else 
						{
						    usage();
						}
					}

					if(argc > 4) {

						for(i=3;i<argc;i++) {
							if(stat(argv[i],&stt)==0) {}	    
							else 
							{
							    error = 1;
							    break;
							}
						}
		
						if(error == 1) {
							usage();
						} else {
							match_pattern_whole_word_cs_files(argv,argc);	
						}
					}



				} else {
		
					if(argc==4)
					{
						if(stat(argv[3],&stt)==0)
						    match_pattern_case_sensitive(argv);
						else 
						{
						    usage();
						}
					}
		
					if(argc > 4) {

						for(i=3;i<argc;i++) {
							if(stat(argv[i],&stt)==0) {}	    
							else 
							{
							    error = 1;
							    break;
							}
						}
		
						if(error == 1) {
							usage();
						} else {
							match_pattern_files_cs(argv,argc);	
						}
					}

				}
	
			} else if(switch_char == 'v') {

				if(argc > 4) {

					switch_pattern = extractPattern(argv[count1]); // -e
					hyphenExist = findHyphenInStr(switch_pattern); //0
				
					if(hyphenExist == 1) {
					
						for(i=3;i<argc;i++) {
							if(stat(argv[i],&stt)==0) {}	    
							else 
							{
							    error = 1;
							    break;
							}
						}
		
						if(error == 1) {
							usage();
						} else {
							get_content_excluding_pattern_multi(argv,argc);
						}
					

					} else {								

						while(hyphenExist == 0 && switch_pattern[1] == 'e'){

							//switches = (char *)malloc(sizeof(char));
							//patterns = (char **)malloc(sizeof(char))

							patterns[patternFlag++] = extractPattern(argv[count2]);				

							count1 = count1 + 2;
							count2 = count2 + 2;

							switch_pattern = extractPattern(argv[count1]); // -e
							hyphenExist = findHyphenInStr(switch_pattern); //0
						}	
			
						patterns[patternFlag] = '\0';

				
						joinedMultiPatterns = fStrJoin(patterns,"|");

						if(stat(argv[argc-1],&stt)==0) {
							get_content_excluding_patterns(argv[argc-1],joinedMultiPatterns);
						} else 
						{
						    usage();
						}	

					}	



				} else {

					switch_char1 = switch_pattern[hyphenExist+2];
				
					if(switch_char1 == 'c') {

						if(stat(argv[3],&stt)==0)
						    count_matching_pattern_invert(argv);
						else 
						{
						    usage();
						}

					} else {

						if(stat(argv[3],&stt)==0) {
							get_content_excluding_pattern(argv);
						} else 
						{
						    usage();
						}

					}

				}		
			
		
				/*if(hypenExist == 0) {

					switch_char = switch_pattern[hyphenexist+1];
				}*/			

			} else if(switch_char == 'c') {
			
				if(stat(argv[3],&stt)==0) {
					count_matching_pattern(argv);
				} else 
				{
				    usage();
				}
			} else if(switch_char == 'n') {

				//show_matched_line_number
				if(stat(argv[3],&stt)==0) {
					show_matched_line_number(argv);
				} else 
				{
				    usage();
				}
			} else if(switch_char == 'l') {
			
		
				for(i=3;i<argc;i++) {
					if(stat(argv[i],&stt)==0) {}	    
					else 
					{
					    error = 1;
					    break;
					}
				}

				if(error == 1) {
					usage();
				} else {
					match_pattern_file_names(argv,argc);	
				}
			

			} else if(switch_char == 'w') {
			
				if(stat(argv[3],&stt)==0)
				    match_pattern_whole_word(argv);
				else 
				{
				    usage();
				}
			

			} else if(switch_char == 'o') {

				switch_pattern = extractPattern(argv[2]); // -e
				hyphenExist = findHyphenInStr(switch_pattern); //0
			
				if(hyphenExist == 0 && switch_pattern[1] == 'b') {
					if(stat(argv[4],&stt)==0)
					    show_position_match_pattern(argv);
					else 
					{
					    usage();
					}
				}			


			

			} else if(switch_char == 'r' || switch_char == 'R') {
			
				if(stat(argv[3],&stt)==0)
				    list_dir(argv[3],argv[2]);
				else 
				{
				    usage();
				}
			

			} else if(switch_char == 'h') {
				displayHelp();
			}

		} else {

			if(argc==3)
			{
				if(stat(argv[2],&stt)==0)
				    match_pattern(argv);
				else 
				{
				    usage();
				}
			}

			if(argc > 3) {
				for(i=2;i<argc;i++) {
					if(stat(argv[i],&stt)==0) {}	    
					else 
					{
					    error = 1;
					    break;
					}
				}
		
				if(error == 1) {
					usage();
				} else {
					match_pattern_files(argv,argc);	
				}

			}

		}
	}
	printf("\n");

	return 0;
}

