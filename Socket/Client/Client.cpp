#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA WSAData{};
    //  初始化 WinSock 库
    WSAStartup(MAKEWORD(2, 2), &WSAData);

    int iResult{};

    //  创建连接 Socket
    const SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in ServerAddress{};
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(8888);
    ServerAddress.sin_addr.S_un.S_addr = inet_addr("192.168.2.173");

    iResult = connect(ClientSocket, reinterpret_cast<SOCKADDR*>(&ServerAddress), sizeof(ServerAddress));
    if(iResult == SOCKET_ERROR)
    {
        cerr << "Connect failed : " << WSAGetLastError() << endl;
        system("pause");
        return -1;
    }

    cout << "Connected to server." << endl;

    closesocket(ClientSocket);
    cout << "Client disconnected." << endl;
    WSACleanup();
    cout << "Clean WinSock." << endl;

    system("pause");
    return 0;
}