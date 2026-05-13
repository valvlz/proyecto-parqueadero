#include <iostream>

/* Librerías para sockets en Windows */
#include <winsock2.h>

#include "ServidorSocket.h"

using namespace std;

/* Constructor */
ServidorSocket::ServidorSocket(int puerto)
{
    this->puerto = puerto;
}

/* Inicia el servidor */
void ServidorSocket::iniciarServidor()
{
    WSADATA wsa;

    /* Inicializar WinSock */
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* Crear socket */
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* Validar socket */
    if (servidor_fd == INVALID_SOCKET)
    {
        cout << "Error al crear socket" << endl;
        return;
    }

    cout << "Socket creado correctamente" << endl;
}