#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <TTree.h>
//#include <root/TCanvas.h>
//#include <root/TGraph.h>
#include <typeinfo>
//#include <root/TMultiGrapth.h>


struct testStruct
{
	int x;
} somevar;

int main(){
	short BLOCK_SIZE = 255;
	char* readBuffer;
	FILE* myFilePtr;
	readBuffer = (char*) malloc(BLOCK_SIZE);

	clock_t startTime = clock();
	printf("hello world, we are starting at %f\n", (float) startTime);
	struct testStruct something;
	something.x = 10;
	printf("x = %i\n\n", something.x);
	sleep(1);
	clock_t endTime = clock();
	printf("And now we end at %f The run time was %.20f \n", \
		(float) endTime, ((endTime - startTime)/((float)CLOCKS_PER_SEC)));
	printf("clocks per second? %f\n", (float) CLOCKS_PER_SEC);


	if((myFilePtr = fopen("FileReader.c", "r")) == NULL)
	{
		printf("File Not Found\n");
		return -1;
	}
	int i = 1;

	while(fgets(readBuffer, BLOCK_SIZE, myFilePtr) != NULL)
	{
		printf("Line %4d: %s", i, readBuffer);
		i++;
	}
	return 1;
}
