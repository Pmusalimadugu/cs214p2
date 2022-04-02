#include "ww.h"
#include "word.h"

int main(int argc, char* argv[]) {
    //read line width
    int width = atoi(argv[1]);
    
    //if only 1 input, read from std input
    if (argc == 2) {
        wrap(STDIN_FILENO, STDOUT_FILENO, width);
    } else if (argc == 3) {
        int file = open(argv[2], O_RDONLY);
        wrap(file, STDOUT_FILENO, width);
		close(file);
    } else {
        return EXIT_FAILURE;
        perror("test");
        
    }
}

int wrap(int read_fd, int write_fd, int width){
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
                    if(numNewlines >= 2) {
                        if (charsOnLine + currentWord.used > width) {
                            write(write_fd, &newline, sizeof(char));
                            charsOnLine = 0;
                        }
                        write(write_fd, currentWord.word, currentWord.used);
                        charsOnLine += currentWord.used;
                        createWord(&currentWord, INIT_WORD_SIZE);

                        write(write_fd, &newline, sizeof(char));
                        write(write_fd, &newline, sizeof(char));

                        charsOnLine = 0;

                    } else if ((numSpaces || numNewlines)) {
                        if (charsOnLine + currentWord.used > width) {
                            write(write_fd, &newline, sizeof(char));
                            charsOnLine = 0;
                        }
                        write(write_fd, currentWord.word, currentWord.used);
                        charsOnLine += currentWord.used;
                        createWord(&currentWord, INIT_WORD_SIZE);

                        write(write_fd, &space, sizeof(char));
                        charsOnLine++;
                    }

                    numSpaces = 0;
                    numNewlines = 0;

                    push_back(&currentWord, buffer[i]);
                    break;            
            }
        }

        bytesRead = read(read_fd,buffer,BUFFER_SIZE);
    }

    write(write_fd, currentWord.word, currentWord.used);
    write(write_fd, &newline, sizeof(char));


    freeWord(&currentWord);

    return 10;
}