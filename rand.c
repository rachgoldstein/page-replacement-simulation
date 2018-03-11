/* Rachel Goldstein
 * RAND page replacement algorithm implementation
 */

#include <stdio.h>
#include <stdlib.h>

//function to read in page requests 
int parseArguments(int argc, char *argv[]) {
	int tableSize;
	if(argc == 2 && (tableSize = atoi(argv[1]))) {
		return tableSize;
	}
	fprintf(stderr, "Wrong arguments. Pass tableSize\n");
	exit(-1);
} 

//function to check if page already exists in the page table 
int isInMemory(int pageRequest, int *pageTable, int tableSize) {
	int i;
	for(i=0; i<tableSize; i++) {
		if(pageRequest == pageTable[i]) {
			return 1;
		}
	}
	return 0;
}	



int main(int argc, char *argv[]){
	int tableSize = parseArguments(argc, argv);
	int pageRequest, pageTableIndex = 0, requests = 0, missRate = 0;
	int *pageTable = (int *) malloc(sizeof(int)*tableSize);
	char *input = NULL; 
	ssize_t bytesRead;
	size_t inputAllocated = 0;
	int deleted;

	//while pages are being requested 
	while((bytesRead = getline(&input, &inputAllocated, stdin)) != EOF) {
		pageRequest = atoi(input);
		requests++;
		//if the page does not exist in the page table 
		if(!isInMemory(pageRequest, pageTable, tableSize)){
			printf("Page %d caused a page fault\n", pageRequest);
			missRate++;
			if(pageTableIndex < tableSize) {
				pageTable[pageTableIndex++] = pageRequest;

			} else { 
				//if the page table is full
				deleted = rand()%tableSize;
				pageTable[deleted] = pageRequest;
				fprintf(stderr, "Ran out of memory! Implement a random algorithm!!!\n");
			}
		}	
	}

	printf("Hit rate = %d\n", requests-missRate);

	free(input);
	free(pageTable);
	return 0;
}	
