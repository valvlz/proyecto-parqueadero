#include "ClienteSocket.h"

/*
    Punto de inicio del cliente
*/
int main()
{
    /* Crear cliente */
    ClienteSocket cliente("127.0.0.1", 8080);

    /* Conectar al servidor */
    cliente.conectar();

    /* Recibir mensaje */
    while (true)
    {
        cliente.recibirMensaje();
    }

    return 0;
}