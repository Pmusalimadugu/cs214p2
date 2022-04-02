# cs214p2 Word Wrap
# Pranay Musalimadugu 
## netid: pm778
## Usage
To build and run memgrind:
```bash
make all
./ww.out 30 test1.txt
```
Clean all:
```bash
make clean
```
## Test Plan
Here are the following properties needed to determine the library as fully working:
1. Invalid block sizes are detected
2. Dynamic memory allocation issues are detected
3. Null pointer input is detected
4. Invalid pointer input is detected
5. Freeing an already freed pointer is detected
6. Memory safety is achieved (does not exceed allocated memory bounds)
7. No memory leaks, the allocated array does not have any values left if they are freed
8. Implementation of these features should not excessively slow down the implementation

Here is a description of the tests that demonstrate these design goals. Each test is numbered with the test plan name in the tests.c file.
1. Allocate a block with zero size, reports an InvalidSize Error
2. Allocate blocks that are too large or one block that is too large, reports a OutOfMemory Error
3. Free a null pointer, reports a NullPointer Error
4. Free a pointer not provided by mymalloc(), reports a InvalidPointer Error
5. Free an already free pointer, reports a FreedPointer Error

Points six through eight are tested through the three required stress tests, as well as the two tests that are created and documented below:
### Test 4
test4() is intended to mimic test1(), as they both allocate and deallocate 120 characters. Test 4, however, deallocates them from the center instead of from the beginning, testing the difference between the coalescing algorithm. This is expected to have a minimal impact on the execution time, as the coalescing is O(1) time.
### Test 5
test5() is intended to mimic test2(), as they both allocate and store in an array before deallocating characters. This is expected to have a large impact on the time, as the time complexity of myfree() depends heavily on the order in which the block is located. THis could have been improved by trading space for size, using a hashmap or other data structure, but size complexity is very important for memory allocation.
## Pseudocode implementation
This pseudocode is collected here for easy reference of the thought process and design. 
The comments accompanying the code describe the process in more detail.
For interface and library documentation, reference mymalloc.h
### mymalloc()
Time complexity: O(n), where n is the number of allocated blocks, traverse needed to find free block
Space complexity: O(m + sizeof(unsigned short)) where m is the size of the data allocation
1. init pointer to memory
2. if unallocated create new block
3. traverse the blocks until one is free and has space
4. if cant find one, return NULL else:
5. store the size of the block
6. if the size of the block doesnt have space to reallocate
7. set the block as allocated
8. return address
9. else
10. resize the block
11. set as allocated
12. store the return address
13. move to the end of the resized block
14. create a new block with new size
15. return the address

## myfree()
Time complexity: O(n), where n is the number of allocated blocks, traverse needed to verify block is in the heap. 
Space complexity: 0
1. check for null pointers
2. convert the pointer from data to metadata pointer
3. traverse the selection of block addresses
4. if != any of the blocks, throw error that its not the right address
5. else
6. check the block
7. if not alloc, throw error free called on free block
8. else
9. free the block
10. coalescing
11. check next block for free status
12. check previous block for free status
13. coalesce based on info