# page-replacement-simulation

Description of Implementations:

FIFO: FIFO uses an array and a circular buffer to handle page replacement. If the page table is not full and the page is not already in the page table, pages are added to the page table as they are requested. If the page table is full and the page is not already in the page table, the new page is put at the end of the beginning of the circular buffer, and the head of the buffer moves to the next index of the array so that the position right after where this new page was inserted is the new beginning of the buffer. 

LRU: LRU uses a linked list to replace the least recently used page in a page table. Every time a new page is requested, the node associated with that page becomes the head of the linked list. If the page already exists as a node in the linked list, it is also changed to become the head of the linked list when its page is requested. When the page table is full, since the linked list orders itself with each request, the least recently used page’s node is already at the end of the linked list. So, the tail of the linked list is removed. 

LFU: LFU uses two arrays that are linked by their index as a page table. One array stores the frequency of a page’s requests and the other stores the value of the page. Every time a new page is requested, that page’s frequency increases. When the page table is full, a new page will be inserted where the least frequently used page is indexed. If the page table is not full, the arrays will be filled as the pages are requested. 

RAND: This algorithm uses an array as its page table. When the page table is full, an index of the array is randomly chosen. This is done by assigning a random number, modded to reside within the range of the page table, to an index variable. The page residing at that index is replaced by the new page. 
