#include <cstdlib>
#include <ctime>

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