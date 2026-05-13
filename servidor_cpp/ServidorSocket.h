#ifndef SERVIDOR_SOCKET_H
#define SERVIDOR_SOCKET_H

#include <winsock2.h>

/*
    Clase encargada de administrar
    el servidor socket.
*/
class ServidorSocket
{
    private:

        /* Puerto del servidor */
        int puerto;

        /* Socket principal */
        SOCKET servidor_fd;

    public:

        /* Constructor */
        ServidorSocket(int puerto);

        /* Inicia el servidor */
        void iniciarServidor();
};

#endif