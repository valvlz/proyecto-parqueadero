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
    return rand() % 10 + 1;
}

/* Genera mensaje completo */
string GeneradorPlacas::generarMensaje()
{
    string placa = generarPlaca();

    string hora = obtenerHora();

    int celda = generarCelda();

    stringstream mensaje;

    mensaje << placa
             << " | "
             << hora
             << " | Celda "
             << celda;

    return mensaje.str();
}