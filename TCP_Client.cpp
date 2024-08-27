#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
using namespace std;


int main()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		cout << "Winsock clientSocket Failed!" << endl;
		WSACleanup();
		return -1;
	}

	const int port = 6969;
	string getInput = "Get rekt";
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	if (connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr)) == 0) 
	{
		cout << "Connected!" << endl;
		sendto(clientSocket, getInput.c_str(), getInput.size() + 1, 0, NULL, 0);
	}
	else 
	{
		cout << "Error Connecting to Host" << endl;
	}

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}