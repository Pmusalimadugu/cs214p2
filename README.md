# cs214p2 Word Wrap
# Pranay Musalimadugu 
## netid: pm778
## Usage
To build and run ww:
```bash
make all
./ww.out 30 test1.txt
```
Clean all:
```bash
make clean
```
## Test Plan
Here are the following properties needed to determine the program as fully working:
1. Program can
2. No memory is leaked and all invalid sys calls are handled
3. All outputs from text-identical files are identical
4. Leading spaces are rejected


Here is a description of the tests that demonstrate these design goals. Each test is numbered with the test plan name in the tests.c file.
1. Allocate a block with zero size, reports an InvalidSize Error
2. All test schenarios are thoroughly validated with valgrind
3. Free a null pointer, reports a NullPointer Error
4. Free a pointer not provided by mymalloc(), reports a InvalidPointer Error
5. Free an already free pointer, reports a FreedPointer Error

