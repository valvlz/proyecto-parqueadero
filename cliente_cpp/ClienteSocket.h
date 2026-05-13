#ifndef CLIENTE_SOCKET_H
#define CLIENTE_SOCKET_H

#include <winsock2.h>

/*
    Clase encargada de conectar
    el cliente al servidor.
*/
class ClienteSocket
{
    private:

        /* Socket del cliente */
        SOCKET cliente_fd;

        /* Dirección IP */
        const char* ip;

        /* Puerto del servidor */
        int puerto;

    public:

        /* Constructor */
        ClienteSocket(const char* ip, int puerto);

        /* Conecta al servidor */
        void conectar();
};

#endif