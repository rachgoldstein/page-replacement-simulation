/*Rachel Goldstein
 * LRU algorithm implementation
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node * next;
} node_t;

node_t * head;


//function to read in page requests 
int parseArguments(int argc, char *argv[]) {
	int tableSize;
	if(argc == 2 && (tableSize = atoi(argv[1]))) {
		return tableSize;
	}
	fprintf(stderr, "Wrong arguments. Pass tableSize\n");
	exit(-1);
} 


//function to check if the requested page is already stored in the page table 
int isInMemory(int pageRequest, node_t **head) {
	node_t *curr;
	curr = *head;
	node_t *temp;
	while (curr!=NULL)
	{
		if (curr->val == pageRequest)
		{
			if (curr==*head)//if first in list do nothing
			{
				//printList();
				return 1;
			}
			else //(curr->next!=NULL) //in middle
			{	
				temp->next = curr->next;
				curr->next = *head;
				*head=curr;
				//printList();
				return 1;
			}
		}
		else //update curr and temp pointers
		{
			temp = curr;
			curr=curr->next;
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
	node_t *t = malloc(sizeof(node_t));

	while((bytesRead = getline(&input, &inputAllocated, stdin)) != EOF) {
		pageRequest = atoi(input);
		requests++;
		if(!isInMemory(pageRequest, &head)){
			printf("Page %d caused a page fault\n", pageRequest);
			missRate++;
			if(pageTableIndex < tableSize) { //one of first nodes 
				node_t * new_node = malloc(sizeof(node_t));
				new_node->val = pageRequest;

				//if first element
				if (head==NULL)
				{
					head=new_node;
					new_node->next=NULL;
				}

				else
				{	
					new_node->next = head;
					head = new_node;
				}	
				free(new_node);
				pageTableIndex++;

			} else { //page table full, need to delete from end 
				node_t * new_node = malloc(sizeof(node_t));
				new_node->val = pageRequest;
				
				//make new node head
				new_node->next = head;
				head = new_node;
				
				//delete last node of list 
				node_t *curr = malloc(sizeof(node_t));
				curr = head;
				while (curr->next!=NULL)
				{
					t = curr;
					curr=curr->next;
				}
				t->next=NULL;
				free(new_node);
				free(curr);
					
				fprintf(stderr, "Ran out of memory! Implemented LRU!!!\n");
			}
		}			}

	printf("Hit rate = %d\n", requests-missRate);

	free(t);
	free(input);
	free(pageTable);
	return 0;
}	
