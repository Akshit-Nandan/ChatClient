#include<iostream>
#include<WinSock2.h>
#include <WS2tcpip.h>
#include<tchar.h>

#pragma	comment(lib, "ws2_32.lib")

using namespace std;

bool Initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main()
{
	if (!Initialize()) {
		cout << "Initialize winsock failed " << endl;
		return 1;
	}
	cout << "Client Program started " << endl;

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	if (s == INVALID_SOCKET) {
		cout << "Invalid Socket " << endl;
		WSACleanup();
		return 1;
	}

	string serveraddress = "127.0.0.1";
	int port = 12345;

	sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

	if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "There is some error in connecting to server." << endl;
		closesocket(s);
		WSACleanup();
		return 1;
	}

	cout << "Successfully connected to server." << endl;

	// send / recv
	string message = "ab!";

	int bytesent;
	bytesent = send(s,message.c_str(), message.length(), 0);

	if (bytesent == SOCKET_ERROR) {
		cout << "There was some issue in sending message." << endl;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}