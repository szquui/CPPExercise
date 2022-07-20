#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <winsock.h>
#include <thread>


#define PORT 8081
#define SIZE 1024

int WaitClient(int InSocketID)
{
    struct sockaddr_in CliendAddr;
    int AddrLen = sizeof(CliendAddr);

    std::cout << "Waiting for connection....\n";

    int ClientSocketID = accept(InSocketID, (struct sockaddr*)&CliendAddr, &AddrLen);
    if (ClientSocketID == -1)
    {
        std::cout << "Client connect failed!";
        return -1;
    }

	std::cout << "Client connect success! SocketID:"<< ClientSocketID << "\n";

    return ClientSocketID;
}

void ReceiveAndSendMessages(int InClientSocketID)
{
    char Buffer[SIZE];
    while(true)
    {
        int ReadResult = recv(InClientSocketID, Buffer, sizeof(Buffer), 0);
        if (ReadResult == -1)
		{
			std::cout << "Server recv failed!";
			return;
        }

        std::cout << "Receive msg : " <<  Buffer << "\n";
        send(InClientSocketID, Buffer, sizeof(Buffer), 0);
    }
}


int main()
{
    WORD WVersionRequested = MAKEWORD(1, 1);
    WSADATA WsaDta;
    int ErrorCode = WSAStartup(WVersionRequested, &WsaDta);

    if (ErrorCode != 0)
    {
		std::cout << "Create socket failed!";
		return 0;
    }

    int ServerSocketID = socket(AF_INET, SOCK_STREAM, 0);

    if (ServerSocketID == -1)
    {
        std::cout << "Create socket failed!";
        return 0;
    }

    struct sockaddr_in ServerAddr;
    memset(&ServerAddr, 0, sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddr.sin_port = htons(PORT);

    int BindResult = bind(ServerSocketID, (struct sockaddr*) &ServerAddr, sizeof(ServerAddr));

    if (BindResult == -1)
    {
        std::cout << "Bind failed!";
        return 0;
    }

    int ListenResult = listen(ServerSocketID, 5);
    if (ListenResult == -1)
    {
		std::cout << "Listen failed!";
		return 0;
    }

    int ClientSocketID = WaitClient(ServerSocketID);

    std::thread ReceiveAndSend(ReceiveAndSendMessages, ClientSocketID);
    ReceiveAndSend.join();

}
