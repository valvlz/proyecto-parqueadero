#include "ServidorSocket.h"

/*
    Punto de inicio del servidor
*/
int main()
{
    /* Crea servidor en puerto 8080 */
    ServidorSocket servidor(8080);

    /* Inicia el servidor */
    servidor.iniciarServidor();

    return 0;
}