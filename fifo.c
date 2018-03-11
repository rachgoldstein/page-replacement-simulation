/* Rachel Goldstein
 * W 2:15
 * FIFO algorithm implementation
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

//function checks if requested page is already stored as a page table entry
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
	int *head = pageTable;
	int i;
	int count=0;
	int index;

	//while page requests being inputted 
	while((bytesRead = getline(&input, &inputAllocated, stdin)) != EOF) {
		pageRequest = atoi(input);
		requests++;
		
		//if the page is not already stored in the page table
		if(!isInMemory(pageRequest, pageTable, tableSize)){
			printf("Page %d caused a page fault\n", pageRequest);
			missRate++;
			//if the page table isn't already full
			if(count < tableSize) {
				pageTable[count++] = pageRequest;
				index = count;
			} 
			//if the page table is full, implmenet FIFO
			else {
				*head = pageRequest;
				pageTableIndex++;
				pageTableIndex=pageTableIndex%tableSize;
				if (pageTableIndex==0)
					head = pageTable;
				else
					head++;
				fprintf(stderr, "Ran out of memory! Implemented fifo!!!\n");
				index = pageTableIndex;
			}
		}		
	}

	printf("Hit rate = %d\n", requests-missRate);

	//TODO free other pointers 
	free(input);
	free(pageTable);
	return 0;
}	
