#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "ClienteSocket.h"

using namespace std;

/* Constructor */
ClienteSocket::ClienteSocket(const char* ip, int puerto)
{
    this->ip = ip;
    this->puerto = puerto;
}

/* Conecta al servidor */
void ClienteSocket::conectar()
{
    WSADATA wsa;

    sockaddr_in servidor;

    /* Inicializar WinSock */
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* Crear socket */
    cliente_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* Validar socket */
    if (cliente_fd == INVALID_SOCKET)
    {
        cout << "Error al crear socket cliente" << endl;
        return;
    }

    /* Configurar dirección */
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr(ip);
    servidor.sin_port = htons(puerto);

    /* Intentar conexión */
    if (connect(cliente_fd,
                (struct sockaddr*)&servidor,
                sizeof(servidor)) < 0)
    {
        cout << "Error de conexion" << endl;
        return;
    }

    cout << "Conexion exitosa al servidor" << endl;
}

/* Recibe mensajes */
void ClienteSocket::recibirMensaje()
{
    char buffer[1024];

    /* Recibir mensaje */
int bytesRecibidos = recv(
    cliente_fd,
    buffer,
    sizeof(buffer) - 1,
    0
);

/* Validar conexión */
if (bytesRecibidos <= 0)
{
    cout << "Servidor desconectado" << endl;
    return;
}

/* Finalizar cadena */
buffer[bytesRecibidos] = '\0';

cout << "Mensaje recibido: "
     << buffer << endl;
}