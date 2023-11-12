/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//necessary library includes
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include "encryption.h"
#include <string.h>
#include <time.h>


/*
@param buffer
This function will generate a 16 character random string when called.  This
is used to randomlly generate the AES key as well as the corresponding ciphers
initialization vector. This will write it to the buffer that is passed in
*/
void randomGeneration(char buffer[]){
    char source[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //characters to pull from for key
    for(int i = 0; i < 16; i++){
        buffer[i] = source[rand() % strlen(source)];
    }
    //buffer[15] = '\0';
}

/*
@return THis function will return a pointer to the EVP_CIPHER object created
This function will create an AES cipher object which will be used to conduct encryption.
The specific encryption model chosen was aes 128 bit in cipher block chaining mode.
*/
EVP_CIPHER * generateAESCipher(void){
    EVP_CIPHER *cipher = NULL;
    
    cipher = EVP_aes_128_cbc();
    
    return cipher;
}

/*
@param the cipher, a pointer to store the ciphertext, the key, iv, and the plaintext to encrypt.
@return int succes(0)
This function will go ahead and encrypt using AES and the randomly generated key and iv the plaintext
and store it in the ciphertext
*/
int encryptAES(EVP_CIPHER * cipher, unsigned char * ciphertext, char *key, char *iv, char *plaintext){
    EVP_CIPHER_CTX *ctx;
    int result;
    int ciphertext_length;
    int length;
    int plaintext_length;

    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    ctx = EVP_CIPHER_CTX_new();
    
    result = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);
    if(result != 1){
        exit(1);
    }
   
    result = EVP_EncryptUpdate(ctx, ciphertext, &length, plaintext, plaintext_length);
    if(result == 1){
        printf("Error occurred!\n");
        exit(1);
    }

    ciphertext_length = length;
    
    result = EVP_EncryptFinal_ex(ctx, ciphertext + length, &length);
    ciphertext_length += length;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_length;

}
/*
@param the cipher, ciphertext to decrpyt, the key, iv, and the plaintext buffer.
@return int succes(0)
This function will go ahead and encrypt using AES and the randomly generated key and iv the plaintext
and store it in the ciphertext
*/
int decryptAES(EVP_CIPHER * cipher, char * key, char *iv, unsigned char * ciphertext, int ciphertext_length, char * plaintext){
    EVP_CIPHER_CTX *ctx;
    int result;
    int length;
    int plaintext_length;

    ctx = EVP_CIPHER_CTX_new();

    result = EVP_DecryptInit(ctx, cipher, key, iv);
    if(result != 1){
        exit(1);
    }

    result = EVP_DecryptUpdate(ctx, plaintext, &length, ciphertext, ciphertext_length);
    if(result != 1){
        exit(1);
    }
    plaintext_length = length;

    result = EVP_DecryptFinal(ctx, plaintext + length, &length);
    plaintext_length += length;

    return plaintext_length;
}