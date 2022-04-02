#include "ww.h"
#include "word.h"


/**
* @brief 
* word wraps a given input
* @return
* Error code, if any
*/
int main(int argc, char* argv[]) {
    //read line width
    int width = atoi(argv[1]);
    
    //if only 1 input, read from std input
    if (argc == 2) {
        wrap(STDIN_FILENO, STDOUT_FILENO, width);
    } else if (argc == 3) {
        //determine if path is file or dir
        //provided struct for file path
        struct stat sbuf;
        //test for file found
        int checkFileInDir = stat(argv[2], &sbuf);
        //if not throw error
        if (checkFileInDir){
			perror("File was not found in directory!");
        }

        //if directory
        if (S_ISDIR(sbuf.st_mode)) {

            //open dir and init pointer
            DIR* d = opendir(argv[2]);
            struct dirent* pDirent;

            //read dit
            pDirent = readdir(d);
            //create vars for strcmp
            char* filename;
            char* wraptext = "wrap.";
            char* newline = "\0";
            //iterate over files
            while (pDirent != NULL) {
                //do not wrap hidden or non default filetypes
                if(pDirent->d_type == DT_REG) {
                    //get length
                    int length = strlen(pDirent->d_name);
                    //copy first 5 chars (check for .wrap)
                    filename = (char*)malloc(sizeof(char)*(5 + length));
                    memcpy(filename, pDirent->d_name, 5);
                    memcpy(filename+5, newline, 1);

                    //perform comparision
                    int c = strcmp(wraptext, filename);

                    //if good
                    if((pDirent->d_name[0] != '.') && (c)) {
                        //change dir
                        int d = chdir(argv[2]);

                        //handle errors
                        if(d) perror("Error cding!");
                        int fd = open(pDirent->d_name, O_RDONLY);
						if(fd == -1) perror("Error opening file!");

                        //copy new filename
                        memcpy(filename, wraptext, 5);
                        memcpy(filename+5, pDirent->d_name, length);

                        //open a new file, using hex code 0644 for permissions
                        int dest = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);

                        //handle errrors
                        if(dest == -1) perror("Error creating destination file");
                        wrap(fd, dest, width);
                        c = close(dest);
                        if(c) perror("Error closing file!");

                        //cd out
                        d = chdir("..");
                    }

                    //free filename
                    free(filename);
                    
                }

                //read next file
                pDirent = readdir(d);
            }

            //close dir and handle errors
            int c = closedir(d);
			if(c == -1) perror("Error closing directory!");


        //if file
        } else if(S_ISREG(sbuf.st_mode)) {
            //open file read-only
            int fd = open(argv[2], O_RDONLY);
            //throw error if file couldn't be opened
            if(fd == -1) perror("Error opening file!");
            //call wrap with fd and stdout
            wrap(fd, STDOUT_FILENO, width);
            //close file
		    int c = close(fd);
            //throw error if file could't be closed
            if(c == -1) perror("Error closing file!");

        } else {
            //fallthrough case
            perror("Unexpected input!");
        }

    } else {
        return EXIT_FAILURE;
    }
}

void wrap(int read_fd, int write_fd, int width){
    //buffer to hold read calls
    char buffer[BUFFER_SIZE];
    //basic character definitions
    char newline = '\n';
    char space = ' ';


    //increment consecutive spaces
    int numSpaces = 0;
    //increment continuous newlines
    int numNewlines = 0;
    //track if we hit the end of a line
    int charsOnLine = 0;
    //first space
    int firstSpace = 1;
    //create a dynamically sized word
    Word currentWord;
    createWord(&currentWord, INIT_WORD_SIZE);


    //boolean (truthy) to determine if the file has ended
    int bytesRead = read(read_fd,buffer,BUFFER_SIZE);
    //read first amount of data into buffer

    while (bytesRead > 0) {
        //iterate over characters
        for(int i = 0; i < bytesRead; i++) {
            
            switch(buffer[i]) {
                case ' ':
                    numSpaces++;
                    break;
                case '\n':
                    numNewlines++;
                    break;
                default:

                    //previous methods collect consecutive spaces and newlines to deal with here
                    if(numNewlines >= 2) {
                        //write newline if needed
                        if (charsOnLine + currentWord.used > width) {
                            write(write_fd, &newline, sizeof(char));
                            charsOnLine = 0;
                        }
                        //write word
                        write(write_fd, currentWord.word, currentWord.used);
                        charsOnLine += currentWord.used;
                        freeWord(&currentWord);
                        createWord(&currentWord, INIT_WORD_SIZE);

                        //write newlines
                        write(write_fd, &newline, sizeof(char));
                        write(write_fd, &newline, sizeof(char));
                        //reset char counter
                        charsOnLine = 0;

                    } else if ((numSpaces || numNewlines) && !firstSpace) {
                        //same condition as top branch, just checks for first line space
                        if (charsOnLine + currentWord.used > width) {
                            write(write_fd, &newline, sizeof(char));
                            charsOnLine = 0;
                        }
                        write(write_fd, currentWord.word, currentWord.used);
                        charsOnLine += currentWord.used;
                        freeWord(&currentWord);
                        createWord(&currentWord, INIT_WORD_SIZE);

                        //write a space
                        write(write_fd, &space, sizeof(char));
                        charsOnLine++;
                    }
                    //reset vars
                    numSpaces = 0;
                    numNewlines = 0;
                    firstSpace = 0;

                    //add character to vector
                    push_back(&currentWord, buffer[i]);
                    break;            
            }
        }
        //read into buffer again
        bytesRead = read(read_fd,buffer,BUFFER_SIZE);
    }
    //working?? fix for last word, recheck condition and insert newline if needed
    if (charsOnLine + currentWord.used > width) {
        write(write_fd, &newline, sizeof(char));
    }        
    write(write_fd, currentWord.word, currentWord.used);
    //end file with a newline
    write(write_fd, &newline, sizeof(char));

    //free the last word
    freeWord(&currentWord);
}