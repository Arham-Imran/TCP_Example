#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>

int main()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		std::cout << "Winsock serverSocket Failed!" << std::endl;
		return -1;
	}

    const int port = 6969;
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serverAddr;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_family = AF_INET;
    int serverAddrLen = sizeof(serverAddr);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) 
    {
        std::cerr << "Bind failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    
    if (listen(serverSocket, 3) == SOCKET_ERROR) 
    {
        std::cerr << "Listen failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // printf("Server is listening on port %d...\n", port);
    std::cout << "Server is listening on port " << port << "..." << std::endl;

    SOCKADDR_IN clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) 
    {
        std::cerr << "Accept failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Connection accepted." << std::endl;

	char buffer[1024];
    int recvSize;
    if ((recvSize = recv(clientSocket, buffer, sizeof(buffer), 0)) == SOCKET_ERROR) 
    {
        std::cerr << "Receive failed. Error Code: " << WSAGetLastError() << std::endl;
    } 
    else 
    {
        buffer[recvSize] = '\0';
        std::cout << "Received message from client: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

	return 0;
}