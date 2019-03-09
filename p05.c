/*
 *Assignment 1, the flag read one-by-one is -F, must be at the end of command line arguments
 *Jeffrey Lu
 *174003251
 *JL2088
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main (int argc, char *argv[]){
    //check minium argument:
    if (argc < 2){
        printf("This script needs a file to read and at least one string to compare with...\n");
        return 0;
    }
    if (argc == 2){
        printf("This script needs at least one string to compare with...\n");
        return 0;
    }
    
    int k = sizeof(char);
    int upto = argc;
    int size;
    char* buffer;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Open file error, no such file in this directory\n");
        return 0;
    }
    
    //check for flag: -R
    if(0==strcmp(argv[argc-1],"-F")){
        //if flag is on, use the inefficent way to read file to bufer...
        upto = upto - 1;
        
        //find out the size of my buffer
        fseek(fp, 0, SEEK_END);
        size =ftell(fp)/k;
        rewind(fp);

        buffer = malloc(size*k);

        for(int i = 0; i < size; i++){
            buffer[i]= fgetc(fp);
        }
    }else{
        //else read entire file to buffer...
        
        //find out the size of my buffer
        fseek(fp, 0, SEEK_END);
        size =ftell(fp)/k;
        rewind(fp);
        
        buffer = malloc(size*k);
        
        int check = fread (buffer,1,size,fp);
        if (check != size){
            printf("Read file error\n");
            return 0;
        }
    }
    
    //from element 2 -> last, we compare strings
    for (int i =2; i < upto; i++){
        //str2 is the string to compare with argv[i]
        int length = k*strlen(argv[i]);
        char * str2;
        str2 = (char*) malloc(length);
        int count = 0;
        
        //I should have used strstr here, but two for loops are easier to fix...
        for (int j = 0; j < size -length; j++){
            for(int c = 0; c < length; c++){
                str2 [c] = buffer[j+c];
            }
            int rc = 1;
            //case-insensitive string compare
            rc = strcasecmp(str2,argv[i]);
            if (rc == 0){
                count++;
            }
        }
        
        printf("%d\n",count);
    }
    return 0;
}
