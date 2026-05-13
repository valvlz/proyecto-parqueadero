#include <iostream>

/* Librerías para sockets en Windows */
#include <winsock2.h>

#include "ServidorSocket.h"

#include <cstring>

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

    /* Información de dirección */
    sockaddr_in servidor;

    /* Inicializar WinSock */
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* Crear socket TCP */
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* Validar socket */
    if (servidor_fd == INVALID_SOCKET)
    {
        cout << "Error al crear socket" << endl;
        return;
    }

    cout << "Socket creado correctamente" << endl;

    /* Configurar dirección */
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(puerto);

    /* Asociar socket al puerto */
    if (bind(servidor_fd,
             (struct sockaddr*)&servidor,
             sizeof(servidor)) < 0)
    {
        cout << "Error en bind" << endl;
        return;
    }

    cout << "Puerto asociado correctamente" << endl;

    /* Escuchar conexiones */
    listen(servidor_fd, 3);

    cout << "Servidor escuchando conexiones..." << endl;    

}

/* Espera conexiones de clientes */
void ServidorSocket::esperarCliente()
{
    sockaddr_in cliente;
    int tamCliente = sizeof(cliente);

    /* Esperar cliente */
    cliente_fd = accept(
        servidor_fd,
        (struct sockaddr*)&cliente,
        &tamCliente
    );

    /* Validar conexión */
    if (cliente_fd == INVALID_SOCKET)
    {
        cout << "Error al aceptar cliente" << endl;
        return;
    }

    cout << "Cliente conectado correctamente" << endl;
}

/* Envía mensaje al cliente */
void ServidorSocket::enviarMensaje(const char* mensaje)
{
    send(cliente_fd,
         mensaje,
         strlen(mensaje),
         0);

    cout << "Mensaje enviado" << endl;
}