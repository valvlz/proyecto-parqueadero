#include <iostream>
#include "ServidorSocket.h"

using namespace std;

/* Constructor de la clase */
ServidorSocket::ServidorSocket(int puerto)
{
    this->puerto = puerto;
}

/* Inicia el servidor */
void ServidorSocket::iniciarServidor()
{
    cout << "Servidor iniciado en el puerto: "
         << puerto << endl;
}