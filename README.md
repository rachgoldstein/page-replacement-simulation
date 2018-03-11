# page-replacement-simulation

Description of Implementations:

FIFO: FIFO uses an array and a circular buffer to handle page replacement. If the page table is not full and the page is not already in the page table, pages are added to the page table as they are requested. If the page table is full and the page is not already in the page table, the new page is put at the end of the beginning of the circular buffer, and the head of the buffer moves to the next index of the array so that the position right after where this new page was inserted is the new beginning of the buffer. 

LRU: LRU uses a linked list to replace the least recently used page in a page table. Every time a new page is requested, the node associated with that page becomes the head of the linked list. If the page already exists as a node in the linked list, it is also changed to become the head of the linked list when its page is requested. When the page table is full, since the linked list orders itself with each request, the least recently used page’s node is already at the end of the linked list. So, the tail of the linked list is removed. 

LFU: LFU uses two arrays that are linked by their index as a page table. One array stores the frequency of a page’s requests and the other stores the value of the page. Every time a new page is requested, that page’s frequency increases. When the page table is full, a new page will be inserted where the least frequently used page is indexed. If the page table is not full, the arrays will be filled as the pages are requested. 

RAND: This algorithm uses an array as its page table. When the page table is full, an index of the array is randomly chosen. This is done by assigning a random number, modded to reside within the range of the page table, to an index variable. The page residing at that index is replaced by the new page. 



Analysis of Results:
SCAN reads in #1-500 sequentially. Given that the largest page size is 100, it makes sense that there are always page faults. Since the pages are only requested once, LRU and LFU function exactly the same as FIFO. Since the page table is less than 500 in all cases, of course the page that is requested will not be in memory at the time of its request, which is why there is a 0% hit rate.

10SCAN is the same as SCAN, but 10 times (so 5000 total page requests). Since now there is a frequency in page requests above one, LFU can begin to function as expected and keep “important” pages in memory. However, LRU still functions like FIFO since the pages are always requested in the same order, and so LRU and FIFO will never have the requested page in memory since it was last requested more than n pages ago, where n is the number of pages available to be stored in memory at one time. 

The Random order of requesting pages shows that all four algorithms work roughly equally well when the page size is between 10-100. Here, the hit rate increases linearly with page size increase for each algorithm. 



How I could improve upon the performance of these replacement algorithms:

I will discuss how to improve performance with 10SCAN. 10SCAN is a test file with the numbers 1-500 sequentially, repeated ten times. When the hit rate was tested within a memory size of 10-100 pages, FIFO and LRU had 0 hits. This occurred because the pages are always requested in the same order, and so LRU and FIFO will never have the requested page in memory since it was last requested more than n pages ago, where n is the number of pages available to be stored in memory at one time. Because LFU brakes ties (multiple pages have minimum frequency) by removing the page closest to the front of the array, as 10SCAN runs the first page in the array will be replaced with each occurrence since all pages have a frequency of 1. Because of this, when the second round of 1-500 is requested, some pages will already be stored in memory because they were never replaced, which explains why there is a hit rate roughly linearly related to the page size for LFU. Rand, because it replaced pages randomly, has a higher chance for hits with a bigger table size because there is a higher probability that the desired page will happen to be in memory because it wasn’t randomly replaced. 

To improve the performance of these replacement algorithms, a page table size of 500 should be implemented. This way, there is enough memory to allow every page requested to be stored. This changes the performance of these replacement algorithms significantly. With a table size of 500, FIFO and LRU have a hit rate of 4500 rather than 0. In fact, at a page table size of 500 LRU and Rand also have a hit rate of 4500. This is because all the page table algorithms reach their optimum performance with this page table size. Since there are 500 pages to be requested, there will be a page fault the first time a page is requested, but because there is now enough room to store each page in memory, the next nine times that the page is requested there will not be a page fault. This explains why at a page table size of 500 all the algorithms have a hit rate of 4500. All of the algorithms are now running with optimal performance. Of course, with a page table size of 500 and 500 pages, no actual page replacements must be done. However, the algorithms are still sorting and updating their data as expected. 
