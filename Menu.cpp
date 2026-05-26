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
    if (opcion == 1)
    {
        g.mostrarNodos();
    }
    else if (opcion == 2)
    {
        g.mostrarMatriz();
    }
    else if (opcion == 3)
    {
        int id;

        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese el ID del nodo: ";
        cin >> id;

        g.mostrarConexionesDeNodo(id);
    }
    else if (opcion == 4)
    {
        int origen;
        int destino;

        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese ID de origen: ";
        cin >> origen;
        cout << "Ingrese ID de destino: ";
        cin >> destino;

        g.consultarDistancia(origen, destino);
    }
    else if (opcion == 5)
    {
        int origen;
        int destino;

        g.mostrarNodos();
        cout << endl;
        cout << "Ingrese ID de origen: ";
        cin >> origen;
        cout << "Ingrese ID de destino: ";
        cin >> destino;

        g.cortarORestaurarConexion(origen, destino);
    }
    else if (opcion == 0)
    {
        cout << "Saliendo del sistema..." << endl;
    }
    else
    {
        cout << "Opcion invalida." << endl;
    }
}
