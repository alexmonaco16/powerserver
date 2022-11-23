#ifndef _UDPSocket_h
#define _UDPSocket_h

#include<windows.h>
#include<stdint.h>
#include<stdio.h>
#include<iostream>

using namespace std;

// required to use Winsock library
#pragma comment(lib,"ws2_32.lib")

// Max length of buffer
#define BUFLEN 512

typedef struct {
	uint16_t id;
	uint16_t power;
} Pacchetto;

class UDPSocket {
private:
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen;
	int recv_len;
	char buf[BUFLEN];
	WSADATA wsa;
public:
	UDPSocket();
	void init(int);
	Pacchetto receivePacchetto();
	~UDPSocket();
};

#endif