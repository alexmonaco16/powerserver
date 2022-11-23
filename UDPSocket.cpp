#include "UDPSocket.h"

UDPSocket::UDPSocket() {
	slen = sizeof(si_other);

	// Initialise Winsock
	cout << " UDP | Inizializzazione Winsock\n";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	cout << " UDP | Winsock inizializzato.\n";

	// Create a socket
	cout << " UDP | Inizializzazione socket\n";
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	cout << " UDP | Socket inizializzata\n";
}

void UDPSocket::init(int port) {

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	// Bind the socket
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

Pacchetto UDPSocket::receivePacchetto() {

	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);

	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	Pacchetto misurazione = *(Pacchetto*)buf;

	return misurazione;
}

UDPSocket::~UDPSocket() {
	closesocket(s);
	WSACleanup();
}