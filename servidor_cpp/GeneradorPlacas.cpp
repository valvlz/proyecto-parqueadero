#include <cstdlib>
#include <ctime>
#include <sstream>

#include "GeneradorPlacas.h"

using namespace std;

/* Genera placa aleatoria */
string GeneradorPlacas::generarPlaca()
{
    string placa = "";

    /* Generar letras */
    for (int i = 0; i < 3; i++)
    {
        placa += 'A' + rand() % 26;
    }

    /* Generar números */
    for (int i = 0; i < 3; i++)
    {
        placa += '0' + rand() % 10;
    }

    return placa;
}

/* Obtiene hora actual */
string GeneradorPlacas::obtenerHora()
{
    time_t ahora = time(0);

    tm* tiempo = localtime(&ahora);

    char hora[9];

    strftime(hora,
             sizeof(hora),
             "%H:%M:%S",
             tiempo);

    return string(hora);
}

/* Genera número de celda */
int GeneradorPlacas::generarCelda()
{
    int celda;

    do
    {
        celda = rand() % 10 + 1;
    }
    while (celdasOcupadas.count(celda));

    /* Marcar celda ocupada */
    celdasOcupadas.insert(celda);

    return celda;
}

/* Genera mensaje completo */
string GeneradorPlacas::generarMensaje()
{
    string placa;

    /* Generar repetición ocasional */
    /* if (!placasActivas.empty() && rand() % 2 == 0) */
    if (!placasActivas.empty() && rand() % 2 == 0)
    {
        auto it = placasActivas.begin();

        advance(it, rand() % placasActivas.size());

        placa = it->first;
    }
    else
    {
        /* Validar capacidad */
        if (celdasOcupadas.size() >= 10)
        {
            return "PARQUEADERO_LLENO";
        }

        placa = generarPlaca();
    }

    string hora = obtenerHora();

    stringstream mensaje;

    /* Validar si la placa ya existe */
    if (placasActivas.count(placa))
    {
        int celda = placasActivas[placa];

        mensaje << placa
                << ",SALIDA,"
                << hora
                << ","
                << celda;

        /* Liberar celda */
        celdasOcupadas.erase(celda);
        
        /* Eliminar placa */
        placasActivas.erase(placa);
    }
    else
    {
        int celda = generarCelda();

        placasActivas[placa] = celda;

        mensaje << placa
                << ",ENTRADA,"
                << hora
                << ","
                << celda;
    }

    return mensaje.str();
}