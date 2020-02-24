/*
 * dt.c
 *
 *  Created on: Sep 7, 2019
 *      Author: afrah
 */


/*
 * Filessource.c
 *
 *  Created on: Sep 5, 2019
 *      Author: afrah
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include<stdbool.h>
#include <ctype.h>
int max=0;
int counter=0;
int isdirectory(char *path)
{
	struct stat statbuf;
	if(stat(path,&statbuf)==-1)
	{
		perror("dt: failed to get information about the file:");

		return 0;
	}
	else
		return S_ISDIR(statbuf.st_mode);
}
int isfile(char *path)
{
	struct stat statbuf;
		if(stat(path,&statbuf)==-1)
			return 0;
		else
			return S_ISREG(statbuf.st_mode);
}
void printing(char *path,bool t, bool p, bool i, bool u, bool g, bool s, bool d, bool l, bool L)
{
	struct stat fileStat1;


	    if(stat(path,&fileStat1) < 0)// returns negative value is failed to get information on the file
	    {
	    	perror("dt: failed to get information about the file:");
	    }
	  //  printf("The file %s a symbolic link\n", (S_ISDIR(fileStat1.st_mode)) ? "is" : "is not");


	    					if(t)
	    			    	printf( (S_ISDIR(fileStat1.st_mode)) ? "\t\tdirectory" : "\t\tfile");
	    			    			if(s)
	    			    			{
	    			                //printf("\t\t %ld",fileStat1.st_size);
	    			                float size=fileStat1.st_size;

	    			                if(size>1000.0)
	    			                {
	    			                	size=size/1000;
	    			                	printf("\t\t%.2fK",size);
	    			                }
	    			                else if (size>1000000.0)
	    			                {
	    			                	size=size/1000000;
	    			                	printf("\t\t%.2fM",size);
	    			                }
	    			                else if (size>1073741824.0)
	    			                {
	    			                	printf("\t\t%.2fG",size);
	    			                }
	    			                else if(size<1000)
	    			                	{printf("\t\t%.2f",size);}
	    			    			}
	    			                if(i)
	    			                    printf("\t\t%d",fileStat1.st_nlink);
	    			                if(u)
	    			                    printf("\t\t%d", fileStat1.st_uid);
	    			                if(g)
	    			                    printf("\t\t%d", fileStat1.st_gid);
	    			                if(d)
	    			                    printf(" \t\t%s",ctime(&fileStat1.st_mtime));
	    			                if(p)
	    			                {
	    			                    printf("\t\t");

	    			                    printf( (fileStat1.st_mode & S_IRUSR) ? "r" : "-");
	    			                    printf( (fileStat1.st_mode & S_IWUSR) ? "w" : "-");
	    			                    printf( (fileStat1.st_mode & S_IXUSR) ? "x" : "-");
	    			                    printf( (fileStat1.st_mode & S_IRGRP) ? "r" : "-");
	    			                    printf( (fileStat1.st_mode & S_IWGRP) ? "w" : "-");
	    			                    printf( (fileStat1.st_mode & S_IXGRP) ? "x" : "-");
	    			                    printf( (fileStat1.st_mode & S_IROTH) ? "r" : "-");
	    			                    printf( (fileStat1.st_mode & S_IWOTH) ? "w" : "-");
	    			                    printf( (fileStat1.st_mode & S_IXOTH) ? "x" : "-");

	    			                }
	    			                if(l)//making an if separately instead of setting flags so it can print in tpiugs order
	    			                {
	    			                	printf( (S_ISDIR(fileStat1.st_mode)) ? "\t\tdirectory" : "\t\tFile");
	    			                	 printf("\t\t");

	    				                    printf( (fileStat1.st_mode & S_IRUSR) ? "r" : "-");
	    				                    printf( (fileStat1.st_mode & S_IWUSR) ? "w" : "-");
	    				                    printf( (fileStat1.st_mode & S_IXUSR) ? "x" : "-");
	    				                    printf( (fileStat1.st_mode & S_IRGRP) ? "r" : "-");
	    				                    printf( (fileStat1.st_mode & S_IWGRP) ? "w" : "-");
	    				                    printf( (fileStat1.st_mode & S_IXGRP) ? "x" : "-");
	    				                    printf( (fileStat1.st_mode & S_IROTH) ? "r" : "-");
	    				                    printf( (fileStat1.st_mode & S_IWOTH) ? "w" : "-");
	    				                    printf( (fileStat1.st_mode & S_IXOTH) ? "x" : "-");


	    			                    printf("\t\t%d",fileStat1.st_nlink);
	    			                    printf("\t\t%d", fileStat1.st_uid);
	    			                    printf("\t\t%d", fileStat1.st_gid);
	    			                    float size=fileStat1.st_size;
	    			                    	                if(size>1000)
	    			                    	                {
	    			                    	                	size=size/1000;
	    			                    	                	printf("\t\t%.2fK",size);
	    			                    	                }
	    			                    	                else if (size>1000000)
	    			                    	                {
	    			                    	                	size=size/1000000;
	    			                    	                	printf("\t\t%.2fM",size);
	    			                    	                }
	    			                    	                else if (size>1073741824)
	    			                    	                {
	    			                    	                	printf("\t\t%.2fG",size);
	    			                    	                }
	    			                    	                else if(size<1000)
	    			                    	                	{printf("\t\t%.2f",size);}

	    			                }//endif(l)

	    printf("\n");
}
//this function only prints out the names for the directory
void printingname(char *names,int root, int indent)
	{
		int z;
		for (z=0; z<root; z++)
		{
			if (z%2 == 0 || z == 0)
			      printf("%*s",indent,"");
			                    //printf("%c", 179);
			 else
			      printf(" ");

         }
      // printf("%c%c%s\n", 195, 196, dp->d_name);
	  printf("%*s%*s%s",indent,"",indent,"", names);


	}
//this function checks for symbollic links
int checklink(char *path)
{
	struct stat fileStat1;

		    if(stat(path,&fileStat1) < 0)// returns negative value is failed to get information on the file
		    {
		    	perror("dt: failed to get information about the file:");
		    }
		    //printf("The file %s a symbolic link\n", (S_ISDIR(fileStat1.st_mode)) ? "is" : "is not");
		    return(S_ISDIR(fileStat1.st_mode));

}

//Part of code taken from https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html
//contains dfs algorithm
	void dfs(char *basePath, const int root,int indent,bool t,bool p,bool i,bool u,bool g,bool s,bool d,bool l, bool L)
	{

	    char path[1000];
	    struct dirent *dp;

	    DIR *dir= opendir(basePath);

	    if (!dir)
	        return;


	    while ((dp = readdir(dir)) != NULL)
	    {
	        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
	        {

	        	//printingname(dp->d_name,root,indent);


	            strcpy(path, basePath);
	            strcat(path, "/");
	            strcat(path, dp->d_name);
	            if(L==false)//if L is not mentioned in the command it won't print symbollic links
	            {	if(checklink(path))
	            	{dfs(path, root + 2,indent,t,p,i,u,g,s,d,l,L);}//if it is a symbollic link we skip the printing and continue traversing
	            	else
	            	{
	            		printingname(dp->d_name,root,indent);
	            		printing(path,t,p,i,u,g,s,d,l,L);
	            		dfs(path, root + 2,indent,t,p,i,u,g,s,d,l,L);
	            	}
	            }
	            else if(L)
	            {
	            	printingname(dp->d_name,root,indent);
	            	printing(path,t,p,i,u,g,s,d,l,L);
	            	dfs(path, root + 2,indent,t,p,i,u,g,s,d,l,L);
	            }

	        }
	    }

	    closedir(dir);
	}


	int main(int argc, char **argv)
	{
		char mycwd[255];//="..";//mycwd has the pathname of the current directory

		int options;
        int w=4;
		//char tempI='I';
        if (getcwd(mycwd, 255) == NULL)
        		{
        			perror("Failed to get current working directory");
        			return 1;
        		}

	bool flagt=false,flagp=false,flagi=false,flagu=false,flagg=false,flags=false,flagd=false,flagh=false,flagI=false,flagl=false,flagL=false;;
	 char *tempargv=argv[argc-1];

	    	//all the options that require an argument are preceeded by :
	 	 	 //:: means optional argument, command must look like -I2 i.e no space between -I and indentation number
	    	while((options=getopt(argc,argv,"-:hI::Ltpiugsdl"))!=-1)
	    	{
	    		switch(options)
	    		{
	    		case 'h':
	    			printf("Please read readMe.txt to understand how to run the project\n");
	    			flagh=true;
	    			break;
	    		case 'I':
	    			flagI=true;
	    			printf("Indentation value: %s\n", optarg ? optarg : "(none)");

	    			if(optarg)//command: -I 5 ,if a number was mentioned with -I
	    			{
	    				w=atoi(optarg);
	    			}

	    			break;
	    	case't':
	    		flagt=true;
	    		break;
	    	case'p':
	    		flagp=true;

	    		break;
	    	case'i':
	    		flagi=true;
	    		break;
	    	case'u':
	    		flagu=true;
	    		break;
	    	case'g':
	    		flagg=true;
	    		break;
	    	case's':
	    		flags=true;
	    		break;
	    	case'd':
	    		flagd=true;
	    		break;
	    	case 'l':
	    		flagl=true;
	    		break;
	    	case 'L':
	    		flagL=true;
	    		break;

			case 1:
				if(!(flagh||flagI||flagt||flagp||flagi||flagu||flagg||flags||flagd||flagl||flagL))
	        		printf("Non-option arg: %s\n", optarg);
	        		break;
			}
	    	}
	    	//checking if any of the flags were turned on except -h
	    	if(flagt||flagp||flagi||flagu||flagg||flags||flagd||flagl||flagL||flagI)
	    	{


	    		if(isdirectory(tempargv))//checking if a directory was mentioned
	    		{printingname(tempargv,0,w);

				printing(tempargv,flagt,flagp,flagi,flagu,flagg,flags,flagd,flagl,flagL);

	    		dfs(tempargv,0,w,flagt,flagp,flagi,flagu,flagg,flags,flagd,flagl,flagL);
	    		}
	    		else if(isfile(tempargv))//checking if file was mentioned
	    		{
	    			printingname(tempargv,0,w);

	    			printing(tempargv,flagt,flagp,flagi,flagu,flagg,flags,flagd,flagl,flagL);
	    			printf("\n");
	    		}
	    		else//takes current directory as star point for dfs
	    		{
	    			//printingname(mycwd,0,w);

	    		//printing(mycwd,flagt,flagp,flagi,flagu,flagg,flags,flagd,flagl,flagL);

	    		dfs(mycwd,0,w,flagt,flagp,flagi,flagu,flagg,flags,flagd,flagl,flagL);

	    		}

	    	}

		    	 return 0;
	}

