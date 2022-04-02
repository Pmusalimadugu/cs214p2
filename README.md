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
1. Program can read from cmd, file, and directory
2. No memory is leaked and all invalid sys calls are handled
3. All outputs from text-identical files are identical
5. Leading spaces are rejected
6. Multiple spaces and chained newlines are rejected
7. Any buffer size can be used (word size also)



Here is a description of the test files that demonstrate these design goals.
1. One test file for each
2. All test schenarios are thoroughly validated with valgrind
3. Several combinations of the provided test file with differently placed spaces
4. Tests with theses cases
5. Tests files with these cases
6. Buffer macros provided that can be modified to use any buffer size

