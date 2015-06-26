// This program times the average read speed of files
// Bobak Hashemi
// UCSD -- June 26 2015
//
// 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h> 
#include <sys/stat.h>

int main(int argc, char** argv){
	int BLOCK_SIZE = 1024;
	char *buf, *fileName, *appendString;
	struct stat *fileStats;
	fileStats = (struct stat *) malloc(sizeof(struct stat));
	appendString = (char*) malloc(1024);
	appendString = "";
	FILE* fp;
	char c;
		
	//Set args from command line	
	
	/*
	We have three command line options: 
		1) -h displays the help menu
		2) -f [filename] is used to specify the file to read, this is a required argument
		3) -b [buffer size] Sets the size of the memory set aside to read from the file, this has a default value of 255
		4) -a [string append] Allows a string to be appended to the output of the file. 		
	*/
	while ((c = getopt (argc, argv, "f:hb:a:")) != -1)
	{
	    switch (c)
	      {
	      case 'h':
	        printf("Usage: -f [filename]<choose file to read>, -h <display this dialog>, -b [block size] <choose read buffer size>\n, -a <String> String is appended to the output");
	        return 1;
			break;
	      case 'b':
	        //printf("setting buffer size to %s\n", optarg);
	        BLOCK_SIZE = atoi(optarg);
			break;
	      case 'f':
	        //printf("Infile set to %s\n", optarg);
			//fileName = malloc(FILENAME_MAX); //max size of filename, defined in stdio.h
			fileName = optarg;
	        break;
		  case 'a':
	        //printf("Infile set to %s\n", optarg);
			//fileName = malloc(FILENAME_MAX); //max size of filename, defined in stdio.h
			appendString = optarg;
	        break;  
	      case '?':
	        if (optopt == 'f' || optopt == 'b')
	          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
	        else if (isprint (optopt))
	          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	        else
	          fprintf (stderr,
	                   "Unknown option character `\\x%x'.\n",
	                   optopt);
	        return 1;
	      default:
	        abort ();
     	 }
	}
	
	
	if(fileName == NULL)
	{
		printf("You must specify a file with the -f flag.\n");
		return 1;
	}
	
	buf = malloc(BLOCK_SIZE);
	clock_t runTime = clock(); //Get initial time
	
	//Open File:
	if((fp = fopen(fileName, "r")) == NULL)
	{
		printf("File Not Found\n");
		return -1; 
	}

	while(read(fileno(fp), buf, BLOCK_SIZE) > 0) //fileno returns the file descriptor from the File struct. 
	{
		//do nothing, just read file into memory.
	}
	runTime = (clock() - runTime); // calculate runtime
	
	//calculate average velocity of read
	fstat(fileno(fp), fileStats);
	float delta_time = runTime/((float)CLOCKS_PER_SEC);
	
	printf("%s    %.3e    %i\n", appendString, ((float) fileStats->st_size)/delta_time, BLOCK_SIZE);
	
	return 1;
}
