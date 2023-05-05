#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA WSAData{};
	//	初始化 WinSock 库
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	int iResult{};

	//	创建监听 Socket
	const SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in ServerAddress{};
	ServerAddress.sin_family = AF_INET;	//	绑定协议
	ServerAddress.sin_port = htons(8888);	//	监听端口
	ServerAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//	监听网卡地址

	//	绑定监听
	iResult = bind(ServerSocket, reinterpret_cast<SOCKADDR*>(&ServerAddress), sizeof(ServerAddress));
	if(iResult != 0)
	{
		cerr << "Bind failed : " << WSAGetLastError() << endl;
		system("pause");
		return -1;
	}

	iResult = listen(ServerSocket, 5);
	if(iResult == SOCKET_ERROR)
	{
		cerr << "Listen failed : " << WSAGetLastError() << endl;
		system("pause");
		return -1;
	}

	cout << "Server started, waiting for client..." << endl;

	const SOCKET ClientSocket = accept(ServerSocket, nullptr, nullptr);

	cout << "Client connected." << endl;

	closesocket(ClientSocket);

	cout << "Client disconnected." << endl;
	closesocket(ServerSocket);
	cout << "Server closed." << endl;
	WSACleanup();
	cout << "Clean WinSock." << endl;

	system("pause");
	return 0;
}