// This program times the reading of files
// Bobak Hashemi
// UCSD -- June 18 2015
//
// 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h> 
#include <fcntl.h>

int main(int argc, char** argv){
	short BLOCK_SIZE = 1024;
	char *buf, *fileName, *vbuf;
	FILE* fp;
	short PRINT_CONTENTS = 0;
	char c;
	short type = 0;
	/*
	This program impliments three types of reads. They are, as follows:
		Type 0) Unbuffered OS reads. i.e. we use read and write calls to do I/O.
		Type 1) Buffered C standard library input. i.e. we use fgets, but don't call setbuf.
		Type 2) Unbuffered C standard library input. i.e. we use a fgets call along with setting no buffering on the file.
	*/

		
	//Set args from command line
	
	
	/*
	We have five command line options: 
		1) -h displays the help menu
		2) -p prints the contents of the file to screen
		3) -f [filename] is used to specify the file to read, this is a required argument
		4) -b [buffer size] Sets the size of the memory set aside to read from the file, this has a default value of 255
		5) -r [u/b] allows the user the specify whether they want to use standard C reads instead of read/write OS calls. 
				'u' will set the buffering for the read to null, that is, the underlying buffering done by fgets will be 
				terminated. 'b' still uses fgets, but we set fully buffered behavior.  
		
	*/
	while ((c = getopt (argc, argv, "f:hb:pr:")) != -1)
	{
	    switch (c)
	      {
	      case 'h':
	        printf("Usage: -f [filename]<choose file to read>, -h <display this dialog>, -b [block size] <choose read buffer size>, -p <print content of file>, -r [1/2] 1 gives a fgets read with a 1024 byte buffer, 2 has no buffer.\n");
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
		  case 'r':
		  	if(atoi(optarg) == 1)
			{
			  //printf("Using buffered C standard library I/O.\n");
			  type = 1;
		  	}
			else if(atoi(optarg) == 2)
			{
			  //printf("Using unbuffered C standard library input.\n");
			  type = 2;
			}
			else
			{
			  //printf("Using *nix OS reads.\n");
			  type = 0;
			}
			break;  
		  case 'p':
	        printf("File contents will be printed\n");
			PRINT_CONTENTS = 1;
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
	vbuf = malloc (1024);
	clock_t runTime = clock(); //Get initial time
	//Open File:
	if((fp = fopen(fileName, "r")) == NULL)
	{
		printf("File Not Found\n");
		return -1; 
	}
	
	//Set buffering:
	if(type == 2)
	{
		setvbuf(fp, NULL, _IONBF, 1024); //input is not buffered. NULL and 1024 are ignored arguments.
	}
	else if(type == 1)
	{
		setvbuf(fp, vbuf, _IOFBF, 1024); //input is fully buffered by 1024 bytes, NULL lets system choose memory to make the buffer. 
	}
	
	
	if(PRINT_CONTENTS)
	{
		int i = 0; 
		while(fgets(buf, BLOCK_SIZE, fp) != NULL)
		{
			printf("Line %2d: %s", i, buf);
			i++;
			//printf("vbuf: %s\n", vbuf);
		}
	}
	else
	{
		if(type = 0) //OS read
		{
			while(read(fileno(fp), buf, BLOCK_SIZE) > 0) //fileno returns the file descriptor from the File struct. 
			{
				printf("OS Read");
				//do nothing, just read file into memory.
			}
		}
		
		else //Standard C read
		{
			while(fgets(buf, BLOCK_SIZE, fp) != NULL)
			{
				//do nothing, just read file into memory.
				//printf("vbuf: %s\n", vbuf);
			}
		}
		
	}
	runTime = (clock() - runTime); // calculate runtime 
	
	printf("Run time: %.3e seconds.\n", runTime/((float)CLOCKS_PER_SEC));
	
	return 1;
}
