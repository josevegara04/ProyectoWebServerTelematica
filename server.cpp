#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <thread>
#include <sstream>
#include <chrono>
#include <iomanip>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

string logFilePath;
string rootDirectory;

string getMimeType(const string &path) {
    auto endsWith = [](const string &value, const string &ending) {
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

void logRequest(const string &clientIP, const string &method, const string &path, const string &statusCode) {
    ofstream logFile(logFilePath, ios::app);
    if (!logFile.is_open()) {
        cerr << "Error al abrir el archivo de log.\n";
        return;
    }

    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm localTime;
    localtime_s(&localTime, &now);

    logFile << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " | "
            << clientIP << " | " << method << " | " << path << " | "
            << statusCode << "\n";
    logFile.close();
}

void handleClient(SOCKET clientSocket) {
    sockaddr_in clientAddr;
    int addrSize = sizeof(clientAddr);
    getpeername(clientSocket, (sockaddr *)&clientAddr, &addrSize);
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
        string filePath = rootDirectory + path;
        if (path == "/") filePath = rootDirectory + "/index.html";
        else if (path == "/case1") filePath = rootDirectory + "/case1.html";
        else if (path == "/case2") filePath = rootDirectory + "/case2.html";
        else if (path == "/case3") filePath = rootDirectory + "/case3.html";
        else if (path == "/case4") filePath = rootDirectory + "/case4.html";

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
                if (method != "HEAD") response += body;

                send(clientSocket, response.c_str(), response.size(), 0);
            } else {
                file.seekg(0, ios::end);
                int contentLength = file.tellg();
                file.seekg(0, ios::beg);

                ostringstream headers;
                headers << "HTTP/1.1 200 OK\r\n"
                        << "Content-Type: " << mimeType << "\r\n"
                        << "Content-Length: " << contentLength << "\r\n"
                        << "Connection: close\r\n\r\n";
                string headerStr = headers.str();
                send(clientSocket, headerStr.c_str(), headerStr.size(), 0);

                if (method != "HEAD") {
                    char buffer[4096];
                    while (!file.eof()) {
                        file.read(buffer, sizeof(buffer));
                        streamsize bytesRead = file.gcount();
                        if (bytesRead > 0)
                            send(clientSocket, buffer, bytesRead, 0);
                    }
                }
            }
            logRequest(clientIP, method, path, "200");
        } else {
            string errorResponse = "HTTP/1.1 404 Page Not Found\r\n"
                                   "Content-Type: text/html\r\n"
                                   "Content-Length: 27\r\n"
                                   "Connection: close\r\n\r\n"
                                   "<h1>404 Page Not Found</h1>";
            send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
            logRequest(clientIP, method, path, "404");
        }
    } else {
        const char *errorResponse = "HTTP/1.1 400 Method Not Allowed\r\n\r\n";
        send(clientSocket, errorResponse, strlen(errorResponse), 0);
    }

    closesocket(clientSocket);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Uso: ./server <PUERTO> <ARCHIVO_LOG> <CARPETA_RAIZ>\n";
        return 1;
    }

    int port = stoi(argv[1]);
    logFilePath = argv[2];
    rootDirectory = argv[3];

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup falló con error: " << result << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error al crear socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind falló. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen falló. Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Servidor escuchando en el puerto " << port << "...\n";

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Falló al aceptar conexión. Error: " << WSAGetLastError() << endl;
            continue;
        }
        thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
