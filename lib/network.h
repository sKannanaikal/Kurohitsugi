/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//header file to include holding function prototypes
#ifndef LIB_NETWORK_H
#define LIB_NETWORK_H

int createSocket(void);
int connectToServer(char * ip_addr, int socket_connection, int port);
int sendData(char * key, int socket_connection);
void recvData(int socket_connection, char buffer[]);
void sendAES(char *key, char *iv);
#endif