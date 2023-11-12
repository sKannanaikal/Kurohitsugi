/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//header file to include holding function prototypes
#ifndef LIB_ENCRYPTION_H
#define LIB_ENCRYPTION_H

EVP_CIPHER * generateAESCipher(void);
int encryptAES(EVP_CIPHER * cipher, unsigned char * ciphertext, char *key, char *iv, char *plaintext);
int decryptAES(EVP_CIPHER * cipher, char * key, char *iv, unsigned char * ciphertext, int ciphertext_length, char * plaintext);
void randomGeneration(char buffer[]);
int otherEncryptAES(unsigned char *out, char *key, char *iv, char *msg, size_t msg_len);

#endif //LIB_ENCRYPTION_H