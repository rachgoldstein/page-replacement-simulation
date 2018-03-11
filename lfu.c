/* Rachel Goldstein
 * LFU algorithm implementation
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

//function to check if requested page is already stored in the page table
int isInMemory(int pageRequest, int *pageTable, int tableSize, int **frequency) {
	int i;
	for(i=0; i<tableSize; i++) {
		if(pageRequest == pageTable[i]) { //(*frequency)[i]
			(*frequency)[i]+=1;
			//printTable(pageTable, *frequency, tableSize);
			return 1;
		}
	}
	return 0;
}	



int main(int argc, char *argv[]){
	int tableSize = parseArguments(argc, argv);
	int pageRequest, pageTableIndex = 0, requests = 0, missRate = 0;
	char *input = NULL;
	ssize_t bytesRead;
	ssize_t inputAllocated = 0;
	
	//two arrays. one for frequency, one for value. Linked by index.
	int *pageTable = (int *) malloc(sizeof(int)*tableSize);
	int *frequency = (int *) malloc(sizeof(int)*tableSize);

	//while pages are being requested 
	while((bytesRead = getline(&input, &inputAllocated, stdin)) != EOF) {
		pageRequest = atoi(input);
		requests++;

		//if the page is not already stored in the page table 
		if(!isInMemory(pageRequest, pageTable, tableSize, &frequency)){
			printf("Page %d caused a page fault\n", pageRequest);
			missRate++;

			//if the page table is not full 
			if(pageTableIndex < tableSize) {
				pageTable[pageTableIndex] = pageRequest;
				frequency[pageTableIndex] = 1;
				pageTableIndex++;
			} else {
				int i;
				int leastFrequent = frequency[0];
				int leastFrequentIndex = 0;
				for (i=1; i<tableSize; i++)
				{
					if (frequency[i] < leastFrequent)
						leastFrequentIndex = i; //find where the least frequently used page is located in the arrays 
				}
				pageTable[leastFrequentIndex] = pageRequest;
				frequency[leastFrequentIndex] = 1;



				fprintf(stderr, "Ran out of memory! Implemented LFU\n");
			}
		}	
	}

	printf("Hit rate = %d\n", requests-missRate);

	free(frequency);
	free(input);
	free(pageTable);
	return 0;
}	
