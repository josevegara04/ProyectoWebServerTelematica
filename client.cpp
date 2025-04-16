#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsaData;

    // Start Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        cout << "WSAStartup failed. Error: " << result << endl;
        return 1;
    }

    // Create socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed. Error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // Server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // Connect to the server
    if (connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Connection to server failed. Error: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server!" << endl;

    const char *httpRequest =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: close\r\n"
        "\r\n";

    send(clientSocket, httpRequest, strlen(httpRequest), 0);

    char buffer[4096];
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[bytesReceived] = '\0';
        cout << buffer;
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
