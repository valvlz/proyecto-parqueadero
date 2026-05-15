#include <iostream>
#include <ctime>
#include <windows.h>

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

    /* Crear servidor */
    ServidorSocket servidor(8080);

    /* Iniciar servidor */
    servidor.iniciarServidor();

    /* Esperar cliente */
    servidor.esperarCliente();

    /* Envío continuo */
    while (true)
    {
        /* Generar mensaje */
        string mensaje = generador.generarMensaje();
        
        /* Validar capacidad */
        if (mensaje == "PARQUEADERO_LLENO")
        {
            cout << mensaje << endl;
            break;
        }

        cout << "Mensaje generado: "
             << mensaje << endl;

        /* Enviar mensaje */
        servidor.enviarMensaje(mensaje.c_str());

        /* Esperar 5 segundos */
        Sleep(5000);
    }

    return 0;
}