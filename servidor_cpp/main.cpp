#include <iostream>
#include <ctime>

#include "ServidorSocket.h"
#include "GeneradorPlacas.h"

using namespace std;

/*
    Punto de inicio del servidor
*/
int main()
{
    /* Inicializar números aleatorios */
    srand(time(0));

    /* Crear generador */
    GeneradorPlacas generador;

    /* Generar placa */
    string placa = generador.generarPlaca();

    cout << "Placa generada: "
         << placa << endl;

    /* Crear servidor */
    ServidorSocket servidor(8080);

    /* Iniciar servidor */
    servidor.iniciarServidor();

    /* Esperar cliente */
    servidor.esperarCliente();

    /* Enviar placa */
    servidor.enviarMensaje(placa.c_str());

    return 0;
}