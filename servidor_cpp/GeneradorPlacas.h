#ifndef GENERADOR_PLACAS_H
#define GENERADOR_PLACAS_H

#include <string>
#include <map>

using namespace std;

/*
    Clase encargada de generar
    información del parqueadero.
*/
class GeneradorPlacas
{
    private:

        /* Placas dentro del parqueadero */
        map<string, int> placasActivas;

    public:

        /* Genera una placa */
        string generarPlaca();

        /* Obtiene hora actual */
        string obtenerHora();

        /* Genera celda */
        int generarCelda();

        /* Genera mensaje */
        string generarMensaje();
};

#endif