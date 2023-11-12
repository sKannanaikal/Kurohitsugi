/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//header file to include holding function prototypes
#ifndef LIB_FILE_SYSTEM_H
#define LIB_FILE_SYSTEM_H

DIR* walkFileSystem(char * dirName);
void walkDirectory(DIR * directory, char * filePath, EVP_CIPHER * cipher, char *key, char *iv);
void walkInnerDirectory(char * oldFilePath, char * filename, EVP_CIPHER * cipher, char *key, char *iv);
void encryptFile(char * filePath, char * fileName, EVP_CIPHER * cipher, char *key, char *iv);

#endif // LIB_FILE_SYSTEM_H
