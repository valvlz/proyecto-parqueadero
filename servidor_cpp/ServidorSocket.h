#ifndef SERVIDOR_SOCKET_H
#define SERVIDOR_SOCKET_H

/*
    Clase encargada de iniciar
    el servidor del socket.
*/
class ServidorSocket
{
    private:

        /* Puerto del servidor */
        int puerto;

    public:

        /* Constructor */
        ServidorSocket(int puerto);

        /* Inicia el servidor */
        void iniciarServidor();
};

#endif