#include <iostream>
#pragma hdrstop
#include <tchar.h>

#include "DatosIniciales.h"
#include "Grafo.h"
#include "Menu.h"

 using namespace std;

int _tmain(int argc, _TCHAR* argv[])
 {
    Grafo g;
    int opcion;

    cargarDatosIniciales(g);

    do
    {
        mostrarMenu();
        cin >> opcion;

        ejecutarOpcion(g, opcion);

    } while (opcion != 0);

    system("pause");

    return 0;
}


