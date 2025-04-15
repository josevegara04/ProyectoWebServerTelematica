#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <thread>
#include <sstream>
#include <chrono>
#include <iomanip>

#pragma comment(lib, "Ws2_32.lib") // Librería Winsock

using namespace std;

// Funcín para detectar el tipo MIME
string getMimeType(const string& path) {
    auto endsWith = [](const string& value, const string& ending) {
        if (ending.size() > value.size()) return false;
        return equal(ending.rbegin(), ending.rend(), value.rbegin());
    };

    if (endsWith(path, ".html")) return "text/html";
    if (endsWith(path, ".css")) return "text/css";
    if (endsWith(path, ".js")) return "application/javascript";
    if (endsWith(path, ".jpg") || endsWith(path, ".jpeg")) return "image/jpeg";
    if (endsWith(path, ".png")) return "image/png";
    if (endsWith(path, ".gif")) return "image/gif";
    if (endsWith(path, ".mp4")) return "video/mp4";
    return "application/octet-stream";
}

// Logger de peticiones
void logRequest(const string& clientIP, const string& method, const string& path, const string& statusCode) {
    cout << "[LOG] Ejecutando logRequest()...\n";  // Verificación en consola

    ofstream logFile("server.log", ios::app);
    if (!logFile.is_open()) {
        cerr << "Error al abrir server.log para escribir.\n";
        return;
    }

    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm localTime;
    localtime_s(&localTime, &now);

    logFile << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " | "
            << clientIP << " | "
            << method << " | "
            << path << " | "
            << statusCode << "\n";
    
    logFile.close();
}


// Funcíon que maneja las conexiones del cliente
void handleClient(SOCKET clientSocket)
{
    sockaddr_in clientAddr;
    int addrSize = sizeof(clientAddr);
    getpeername(clientSocket, (sockaddr*)&clientAddr, &addrSize);
    string clientIP = inet_ntoa(clientAddr.sin_addr);

    char tempBuffer[4096];
    int bytesReceived = recv(clientSocket, tempBuffer, sizeof(tempBuffer), 0);
    if (bytesReceived <= 0) {
        closesocket(clientSocket);
        return;
    }

    string request(tempBuffer, bytesReceived);
    istringstream requestStream(request);
    string method, path;
    requestStream >> method >> path;

    if (method == "GET" || method == "HEAD") {
        string filePath = "templates" + path;
        if (path == "/") filePath = "templates/index.html";
        else if (path == "/index") filePath = "templates/index.html";

        string mimeType = getMimeType(filePath);
        ifstream file(filePath, ios::in | ios::binary);

        if (file) {
            if (mimeType == "text/html") {
                ostringstream ss;
                ss << file.rdbuf();
                string body = ss.str();

                string response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: text/html\r\n";
                response += "Content-Length: " + to_string(body.size()) + "\r\n";
                response += "Connection: close\r\n\r\n";
                if (method != "HEAD")
                    response += body;

                send(clientSocket, response.c_str(), response.size(), 0);
            } else {
                file.seekg(0, ios::end);
                int contentLength = file.tellg();
                file.seekg(0, ios::beg);

                ostringstream headers;
                headers << "HTTP/1.1 200 OK\r\n";
                headers << "Content-Type: " << mimeType << "\r\n";
                headers << "Content-Length: " << contentLength << "\r\n";
                headers << "Connection: close\r\n\r\n";
                string headerStr = headers.str();
                send(clientSocket, headerStr.c_str(), headerStr.size(), 0);

                if (method != "HEAD") {
                    char buffer[4096];
                    while (!file.eof()) {
                        file.read(buffer, sizeof(buffer));
                        streamsize bytesRead = file.gcount();
                        if (bytesRead > 0) {
                            send(clientSocket, buffer, bytesRead, 0);
                        }
                    }
                }
            }
            logRequest(clientIP, method, path, "200");
        } else {
            string errorResponse = "HTTP/1.1 404 Not Found\r\n"
                                   "Content-Type: text/html\r\n"
                                   "Content-Length: 22\r\n"
                                   "Connection: close\r\n\r\n"
                                   "<h1>404 Not Found</h1>";
            send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
            logRequest(clientIP, method, path, "404");
        }
    } else {
        const char* errorResponse = "HTTP/1.1 400 Bad Request\r\n\r\n";
        send(clientSocket, errorResponse, strlen(errorResponse), 0);
        logRequest(clientIP, method, path, "400");
    }

    closesocket(clientSocket);
    cout << "--------------------------------" << endl;
    cout << "Waiting for a client to connect...\r\n" << endl;
}

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup failed with error: " << result << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed. Error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    cout << "\r\nSocket created successfully!" << endl;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind failed. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen failed. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Server is listening on port 8080...\r\n" << endl;

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Accept failed. Error: " << WSAGetLastError() << endl;
            continue;
        }

        cout << "Client connected!\r\n" << endl;
        thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
