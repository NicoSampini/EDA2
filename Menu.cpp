#include <iostream>

#include "Menu.h"

using namespace std;

void mostrarMenu()
{
    cout << endl;
    cout << "MENU PRINCIPAL" << endl;
    cout << "--------------" << endl;
    cout << "1. Ver nodos cargados" << endl;
    cout << "2. Ver matriz de adyacencia" << endl;
    cout << "3. Ver conexiones de un nodo" << endl;
    cout << "4. Consultar distancia entre dos nodos" << endl;
    cout << "5. Cortar o restaurar una conexion" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

void ejecutarOpcion(Grafo &g, int opcion)
{
    switch (opcion)
    {
    case 1:
        g.mostrarNodos();
        break;

    case 2:
        g.mostrarMatriz();
        break;

    case 3:
    {
        int id;
        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese el ID del nodo: ";
        cin >> id;
        g.mostrarConexionesDeNodo(id);
        break;
    }

    case 4:
    {
        int origen, destino;
        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese ID de origen: ";
        cin >> origen;
        cout << "Ingrese ID de destino: ";
        cin >> destino;
        g.consultarDistancia(origen, destino);
        break;
    }

    case 5:
    {
        int origen, destino;
        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese ID de origen: ";
        cin >> origen;
        cout << "Ingrese ID de destino: ";
        cin >> destino;
        g.cortarORestaurarConexion(origen, destino);
        break;
    }

    case 0:
        cout << "Saliendo del sistema..." << endl;
        break;

    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
