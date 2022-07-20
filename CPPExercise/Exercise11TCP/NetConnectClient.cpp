#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <winsock.h>
#include <thread>

#define PORT 8081
#define SIZE 1024

void SendBuffer(int InSockerID)
{
	char SendBuffer[SIZE] = { 0 };
	while (true)
	{
		std::cout << "[ThreadID: " << std::this_thread::get_id() << "] Enter msg:\n";
		std::cin >> SendBuffer;

		send(InSockerID, SendBuffer, sizeof(SendBuffer), 0);
		memset(SendBuffer, 0, sizeof(SendBuffer));
	}
}

void RecvBuffer(int InSocketID)
{
	char ReceiveBuffer[SIZE] = { 0 };
	while (true)
	{
		int ReadResult = recv(InSocketID, ReceiveBuffer, sizeof(ReceiveBuffer), 0);
		if (ReadResult == -1)
		{
			std::cout << "Receive failed!";
			return;
		}
		std::cout << "[ThreadID: " << std::this_thread::get_id() << "] Receive server msg : " << ReceiveBuffer << "\n";
		memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
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


	int ClientSocketID = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSocketID == -1)
	{
		std::cout << "Create socket failed!";
		return 0;
	}

	struct sockaddr_in ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(PORT);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int AddrLen = sizeof(ServerAddr);
	int ConnectResult = connect(ClientSocketID, (struct sockaddr*)&ServerAddr, AddrLen);

	if (ConnectResult == -1)
	{
		std::cout << "Connect failed!";
		return 0;
	}

	std::cout << "Connect success!\n";

	std::thread SendThread(SendBuffer, ClientSocketID);
	std::thread ReceiveThread(RecvBuffer, ClientSocketID);

	ReceiveThread.join();
	SendThread.join();
}

