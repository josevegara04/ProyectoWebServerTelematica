#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <thread>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib") // API Windows Sockets

using namespace std;

// función para manejar cada petición de manera independiente
void handleClient(SOCKET clientSocket)
{
    // se lee directamente desdel el socket
    char tempBuffer[4096];
    int bytesReceived = recv(clientSocket, tempBuffer, sizeof(tempBuffer), 0);
    if (bytesReceived <= 0)
    {
        closesocket(clientSocket);
        return;
    }

    string request(tempBuffer, bytesReceived); 

    // aquí se obtine el metodo y el endpoint
    istringstream requestStream(request);
    string method, path;
    requestStream >> method >> path;

    // Si el método es GET o HEAD
    if (method == "GET" || method == "HEAD")
    {
        string body = "";
        string statusLine;
        int contentLength;
        string response;

        if (path == "/")
        {
            cout << "Resource selected: /\r\n"
                      << endl;
            statusLine = "HTTP/1.1 200 OK";
            body = "<h1>Welcome to the server!</h1>";
        }
        else if (path == "/index")
        {
            cout << "Resource selected: /index" << endl;
            ifstream file("templates/index.html", ios::in | ios::binary);
            if (file)
            {
                ostringstream ss;
                ss << file.rdbuf();
                body = ss.str();
                statusLine = "HTTP/1.1 200 OK";
            }
            else
            {
                statusLine = "HTTP/1.1 404 Not Found";
                body = "<h1>Unable to load the file index.html</h1>";
            }
        }
        else
        {
            cout << "Resource not found: " << path << endl;
            statusLine = "HTTP/1.1 404 Not Found";
            body = "<h1>404 Not Found</h1>";
        }

        if (method == "HEAD")
        {
            body = "";
        }

        contentLength = body.size();

        // se construye la respuesta que se va a enviar al cliente
        response += statusLine;
        response += "\r\nContent-Type: text/html";
        response += "\r\nContent-Length: " + to_string(contentLength);
        response += "\r\nConnection: close\r\n\r\n";
        response += body;

        send(clientSocket, response.c_str(), response.size(), 0);
    }
    // si el método es POST
    else if (method == "POST")
    {
        cout << "POST request received" << endl;

        string::size_type contentLengthPos = request.find("Content-Length:");
        int contentLength = 0;
        if (contentLengthPos != string::npos)
        {
            string::size_type endOfLine = request.find("\r\n", contentLengthPos);
            string contentLengthLine = request.substr(contentLengthPos, endOfLine - contentLengthPos);
            contentLength = stoi(contentLengthLine.substr(15));
            cout << "Content-Length: " << contentLength << endl;
        }
        else
        {
            cout << "Missing Content-Length header" << endl;
            const char *errorResponse = "HTTP/1.1 411 Length Required\r\n\r\n";
            send(clientSocket, errorResponse, strlen(errorResponse), 0);
            closesocket(clientSocket);
            return;
        }

        string::size_type bodyStartPos = request.find("\r\n\r\n");
        if (bodyStartPos == string::npos)
        {
            cout << "Malformed request: no header-body separator found" << std::endl;
            const char *errorResponse = "HTTP/1.1 400 Bad Request\r\n\r\n";
            send(clientSocket, errorResponse, strlen(errorResponse), 0);
            closesocket(clientSocket);
            return;
        }

        bodyStartPos += 4;
        string body = request.substr(bodyStartPos);

        // Receive more if needed
        while ((int)body.length() < contentLength)
        {
            int extraBytes = recv(clientSocket, tempBuffer, sizeof(tempBuffer), 0);
            if (extraBytes <= 0)
                break;
            body.append(tempBuffer, extraBytes);
        }

        string statusLine;
        string bodyResponse;

        if (path == "/submit")
        {
            cout << "Resource selected: /submit" << endl;
            statusLine = "HTTP/1.1 200 OK";

            cout << "Body content: " << body << endl;
            bodyResponse = "<h1>Data Received</h1>";
        }
        else
        {
            cout << "Resource not found: " << path << endl;
            statusLine = "HTTP/1.1 404 Not Found";
            bodyResponse = "<h1>404 Not Found</h1>";
        }

        // se construye la respuesta para el cliente
        ostringstream response;
        response << statusLine << "\r\n"
                 << "Content-Type: text/html\r\n"
                 << "Content-Length: " << bodyResponse.size() << "\r\n"
                 << "Connection: close\r\n\r\n"
                 << bodyResponse;

        string finalResponse = response.str();
        send(clientSocket, finalResponse.c_str(), finalResponse.size(), 0);
    }
    else
    {
        cout << "Unsupported method: " << method << endl;
        const char *errorResponse = "HTTP/1.1 400 Method Not Allowed\r\n\r\n";
        send(clientSocket, errorResponse, strlen(errorResponse), 0);
    }

    // se cierra el socket del cliente
    closesocket(clientSocket);
    cout << "--------------------------------" << endl;
    cout << "Waiting for a client to connect...\r\n"
              << endl;
}

// función main
int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        cout << "WSAStartup failed with error: " << result << endl;
        return 1;
    }

    // se crea el socket del servidor
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed. Error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    cout << "\r\nSocket created successfully!" << endl;

    // se crea la estructura del socket
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;         // se define que trabaja con IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY; // permite que se utilice cualquier IP desde donde se esté ejecutando el servidor
    serverAddr.sin_port = htons(8080);       // define que se va a escuchar en el puerto 8080

    // se construye el socket con la estructura anterior
    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Bind failed. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // el servidor empieza a escuchar 
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen failed. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Server is listening on port 8080...\r\n"
         << endl;

    // loop para mantener el servidor en escucha a peticiones del clientes
    while (true)
    {
        // se obtiene el socket del cliente 
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET)
        {
            cout << "Accept failed. Error: " << WSAGetLastError() << endl;
            continue;
        }
        cout << "Client connected!\r\n"
             << endl;

        thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }


    closesocket(serverSocket); // cerrar el socket del servidor
    WSACleanup();
    return 0;
}