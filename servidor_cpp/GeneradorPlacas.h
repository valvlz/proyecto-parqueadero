#ifndef GENERADOR_PLACAS_H
#define GENERADOR_PLACAS_H

#include <string>

using namespace std;

/*
    Clase encargada de generar
    información del parqueadero.
*/
class GeneradorPlacas
{
    public:

        /* Genera una placa */
        string generarPlaca();

        /* Obtiene hora actual */
        string obtenerHora();

        /* Genera celda */
        int generarCelda();

        /* Genera mensaje completo */
        string generarMensaje();
};

#endif