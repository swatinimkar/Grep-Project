#include "functions.h"
#include "commands.h"


void list_dir(char *dir_name, char *pattern) {
	DIR *d;
	int length = 0;
	char *filepath;

	d = opendir(dir_name);

	if(!d) {
		fprintf(stderr,"Cannot open directory '%s': %s\n",dir_name,strerror(errno));
		exit(1);
	}

	while(1) {



		struct dirent *entry;
		char *d_name;
		
		entry = readdir(d);
		if(!entry) {
			break;
		}

		d_name = entry->d_name;

		if(!(entry->d_type & DT_DIR) && strstr(dir_name,".git")==NULL && strstr(dir_name,"npm")==NULL) {

			length = get_string_len(dir_name) + get_string_len("/") + get_string_len(d_name);
		
			filepath = (char *)malloc(sizeof(char)*PATH_MAX);		

			strcat(filepath,dir_name);
			strcat(filepath,"/");
			strcat(filepath,d_name);
			
			filepath[length] = '\0';

			if(checkFile(filepath) == 1 && strcmp(get_filename_ext(d_name),"o") != 0) {
				match_pattern_recursive(filepath,d_name,pattern);
			}
			
		}

		if(entry->d_type & DT_DIR) {

			if(strcmp(d_name,"..") != 0 && strcmp(d_name,".") != 0) {
				
				int path_length=0;
				char path[PATH_MAX];

				snprintf(path,PATH_MAX,"%s/%s",dir_name,d_name);
				
				if(path_length >= PATH_MAX) {
					fprintf(stderr,"Path length has got too long.\n");
					exit(1);
				}

				list_dir(path,pattern);

			}			
		}
	}
}

void match_pattern(char *argv[])
{
    int fd,r,j=0;
    char temp,line[100];
    int rv;
    regex_t exp;
    char *pattern;

    pattern = extractPattern(argv[1]);
    rv = regcomp(&exp, pattern, REG_EXTENDED);

    if (rv != 0) {
		printf("Please enter correct search pattern");
    } else {

	    if((fd=open(argv[2],O_RDONLY)) != -1)
	    {
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
		        line[j]=temp;
		        j++;
		    }
		    else
		    {

		        line[j]='\0';

		        if(match(&exp, line)==1)
		            printf("%s\n",line);
		        memset(line,0,sizeof(line));
		        j=0;
		    }

		}
	    }   

    }

}

void match_pattern_recursive(char *filepath,char *filename, char *pat)
{
    int fd,r,j=0;
    char temp,line[1000];
    int k=0;
    char *pattern;
    int i;
    char *result[1000];
    char fpath[1000];

    for(i=0;filepath[i]!='\0';i++)
	fpath[i] = filepath[i];
	
    fpath[i] = '\0';
    pattern = extractPattern(pat);

    if((fd=open(fpath,O_RDONLY)) != -1)
    {
	while((r=read(fd,&temp,sizeof(char)))!= 0)
	{
	    if(temp!='\n')
	    {
	        line[j]=temp;
	        j++;
	    }
	    else
	    {
	        line[j]='\0';

	        if(strstr(line,pattern)!=NULL) {
		    result[k] = fpath; 
		    k++;
		}
	        j=0;
	    }

	}
    }

    result[k] = '\0';

    for(i=0;result[i]!='\0';i++) {
	for(j=i+1;result[j]!='\0';j++) {
		if(strncmp(result[i],result[j],get_string_len(result[i]))==0) {
			result[j] = "0";
		} 
	}
    }

    for(i=0;result[i]!='\0';i++) {
	if(strncmp(result[i],"0",get_string_len(result[i]))!=0)
	printf("%s\n",result[i]);
    }

}


void show_position_match_pattern(char *argv[])
{
    int fd,r,j=0;
    char temp,line[100];
    int rv;
    regex_t exp;
    char *pattern;
    regmatch_t matches[MAX_MATCHES];
    regex_t *pexp;

    pattern = extractPattern(argv[3]);
    rv = regcomp(&exp, pattern, REG_EXTENDED);

    pexp = &exp;

    if (rv != 0) {
		printf("Please enter correct search pattern");
    } else {

	    if((fd=open(argv[4],O_RDONLY)) != -1)
	    {
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
		        line[j]=temp;
		        j++;
		    }
		    else
		    {
			
			line[j]='\0';

		        if(regexec(pexp, line, MAX_MATCHES, matches, 0) == 0)
		            printf("%d:%d\n",matches[0].rm_so, matches[0].rm_eo);
		        j=0;
		    }

		}
	    }   

    }

}

void match_pattern_case_sensitive(char *argv[]) {

    int fd,r,j=0,p;
    char temp,line[100],lower_char[100],lower_pattern[100];
    char *pattern;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
		lower_char[j] = tolower(line[j]);
                j++;
            }
            else
            {
		for(p=0;pattern[p]!='\0';p++) {
			lower_pattern[p] = tolower(pattern[p]);
		}

		lower_pattern[p] = '\0';
		lower_char[j] = '\0';
		line[j]='\0';		

                if(strstr(lower_char,lower_pattern)!=NULL)
                    printf("%s\n",line);
                j=0;
            }

        }
    }   
}


void match_pattern_whole_word_cs(char *argv[]) {

    int fd,r,j=0,p;
    char temp,line[100],lower_char[100],lower_pattern[100];
    char *pattern;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
		lower_char[j] = tolower(line[j]);
                j++;
            }
            else
            {
		for(p=0;pattern[p]!='\0';p++) {
			lower_pattern[p] = tolower(pattern[p]);
		}

		lower_pattern[p] = '\0';
		lower_char[j] = '\0';
		line[j]='\0';		

                if(matchWholeWord(lower_char,lower_pattern) == 1)
                    printf("%s\n",line);
                j=0;
            }

        }
    }   
}

void match_pattern_whole_word_cs_files(char *argv[],int filecount) {

    int fd,r,j=0,p;
    char temp,line[100],lower_char[100],lower_pattern[100];
    char *pattern;
    int i;

    pattern = extractPattern(argv[2]);

	
    for(i=3;i<filecount;i++) {

	    if((fd=open(argv[i],O_RDONLY)) != -1)
	    {
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
		        line[j]=temp;
			lower_char[j] = tolower(line[j]);
		        j++;
		    }
		    else
		    {
			for(p=0;pattern[p]!='\0';p++) {
				lower_pattern[p] = tolower(pattern[p]);
			}

			lower_pattern[p] = '\0';
			lower_char[j] = '\0';
			line[j]='\0';		

		        if(matchWholeWord(lower_char,lower_pattern) == 1)
		            printf("%s:%s\n",argv[i],line);
		        j=0;
		    }

		}
	    }   
    }
}



void match_pattern_whole_word(char *argv[]) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
                j++;
            }
            else
            {

		line[j] = '\0';
		

                if(matchWholeWord(line,pattern) == 1)
                    printf("%s\n",line);
                j=0;
            }

        }
    }   
}



void match_pattern_files(char *argv[],int filecount)
{
    int fd,r,j=0;
    char temp,line[100];
    int i;
	
    for(i=2;i<filecount;i++) {
	j=0;
	if((fd=open(argv[i],O_RDONLY)) != -1)
	{
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
			line[j]=temp;
			j++;
		    }
		    else
		    {
			line[j]='\0';

			if(strstr(line,argv[1])!=NULL)
			    printf("%s:%s\n",argv[i],line);
			j=0;
		    }

		}
	}   
    }
}


void match_pattern_files_cs(char *argv[],int filecount)
{
    int fd,r,j=0,p;
    char temp,line[100],lower_char[100],lower_pattern[100];
    int i;
	
    for(i=3;i<filecount;i++) {
	j=0;
	if((fd=open(argv[i],O_RDONLY)) != -1)
	{
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
			line[j]=temp;
			lower_char[j] = tolower(line[j]);
			j++;
		    }
		    else
		    {
			
			for(p=0;argv[2][p]!='\0';p++) {
				lower_pattern[p] = tolower(argv[2][p]);
			}

			lower_pattern[p] = '\0';
			lower_char[j] = '\0';
			line[j]='\0';

			if(strstr(lower_char,lower_pattern)!=NULL)
			    printf("%s:%s\n",argv[i],line);
			j=0;
		    }

		}
	}   
    }
}


void match_pattern_file_names(char *argv[],int filecount)
{
    int fd,r,j=0,k=0;
    char temp,line[100];
    int i;
    char *result[100];
    char file_name_len;
	
    for(i=3;i<filecount;i++) {
	j=0;
	if((fd=open(argv[i],O_RDONLY)) != -1)
	{
		file_name_len = get_string_len(argv[i]);
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
			line[j]=temp;
			j++;
		    }
		    else
		    {
			
			line[j] = '\0';

			if(strstr(line,argv[2])!=NULL) {
			    result[k] = (char *)malloc(sizeof(char)*file_name_len); 
			    memcpy(result[k],argv[i],file_name_len); 
			    //result[k][file_name_len] = '\0';
			    k++;
			}
			j=0;
		    }

		}
	}   
    }

    result[k] = '\0';
	
    for(i=0;result[i]!='\0';i++) {
	for(j=i+1;result[j]!='\0';j++) {
		if(strncmp(result[i],result[j],get_string_len(result[i]))==0) {
			result[j] = "0";
		} 
	}
    }

    for(i=0;result[i]!='\0';i++) {
	if(strncmp(result[i],"0",get_string_len(result[i]))!=0)
	printf("%s\n",result[i]);
    }


}

void get_content_excluding_pattern(char *argv[]) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
                j++;
            }
            else
            {		
		line[j]='\0';

                if(strstr(line,pattern)==NULL)
                    printf("%s\n",line);
                j=0;
            }

        }
    }

}


void get_content_excluding_pattern_multi(char *argv[],int filescount) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;
    int i;

    pattern = extractPattern(argv[2]);

    for(i=3;i<filescount;i++) {

	    if((fd=open(argv[i],O_RDONLY)) != -1)
	    {
		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
		        line[j]=temp;
		        j++;
		    }
		    else
		    {
			line[j] = '\0';
		
		        if(strstr(line,pattern)==NULL)
		            printf("%s:%s\n",argv[i],line);
		        j=0;
		    }

		}
	    }
    }
}



void count_matching_pattern(char *argv[]) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;
    int count_matched = 0;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
	            j++;
            }
            else
            {
		line[j]='\0';

                if(strstr(line,pattern)!=NULL)
                    count_matched++;
                j=0;
            }

        }

	printf("Count Matched: %d",count_matched);	

    }

}

void show_matched_line_number(char *argv[]) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;
    int lines_count = 1;	

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
	            j++;
            }
            else
            {
		line[j]='\0';

                if(strstr(line,pattern)!=NULL)
                    printf("%d:%s\n",lines_count,line);
		lines_count++;
                j=0;
            }

        }

    }

}



void count_matching_pattern_invert(char *argv[]) {

    int fd,r,j=0;
    char temp,line[100];
    char *pattern;
    int count_matched = 0;

    pattern = extractPattern(argv[2]);

    if((fd=open(argv[3],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
	            j++;
            }
            else
            {
		line[j]='\0';

                if(strstr(line,pattern)==NULL)
                    count_matched++;
                j=0;
            }

        }

	printf("Count Not Matched: %d",count_matched);	

    }

}


void get_content_excluding_patterns(char *file,char *pattern) {

    int fd,r,j=0;
    char temp,line[100];
    int rv;
    regex_t exp;

    rv = regcomp(&exp, pattern, REG_EXTENDED);

    if (rv != 0) {
		printf("Please enter correct search pattern");
    } else {

	    if((fd=open(file,O_RDONLY)) != -1)
	    {

		while((r=read(fd,&temp,sizeof(char)))!= 0)
		{
		    if(temp!='\n')
		    {
			line[j]=temp;
			j++;
		    }
		    else
		    {
			line[j] = '\0';
		
			if(match(&exp, line)!=1)
			    printf("%s\n",line);							
			j=0;
		    }

		}
	    }
    }
}


void displayHelp()
{
  printf("SNGREP, written by Swati Nimbolkar\n");
  printf("Usage: sngrep [[arguments] pattern | FILE ] [FILES] ...\n");
  printf("  where FILENAME, if specified, is the name of the file in which you wish to search for pattern.\n");
  printf("  where pattern, is the string to be searched in the file.\n");
  printf("Arguments list:\n");
  printf("  -h : Display this help screen\n");
  printf("  -i : Case insensitive search\n");
  printf("  -w : Complete word search\n");
  printf("  -v : Invert match, display line which dosent contain specified pattern\n");
  printf("  -e : Invert match with more than one pattern specified using this switch\n");
  printf("  -c : Count number of matches\n");
  printf("  -l : Display only the file names which matches the given pattern\n");
  printf("  -n : Show line number while displaying the output\n");
  printf("  -o : If used with -b show position of every matched line\n");
  printf("  -r : Search pattern recursively into directories and sub directories.\n");
}

void usage() {
	  printf("Usage: sngrep [[arguments] pattern | FILE ] [FILES] ...\n");
}


