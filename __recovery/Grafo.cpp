#include <iostream>
#include <cstring>
#include <string>

#include "Grafo.h"

using namespace std;

Grafo::Grafo()
{
    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        nodos[i].id = i;
        strcpy(nodos[i].nombre, "");
        nodos[i].x = 0;
        nodos[i].y = 0;

        for (int j = 0; j < NODOS_CANTIDAD; j++)
        {
            if (i == j)
            {
                matriz[i][j] = 0;
            }
            else
            {
                matriz[i][j] = -1;
            }
        }
    }
}

void Grafo::conectar(int a, int b, int distancia)
{
    matriz[a][b] = distancia;
    matriz[b][a] = distancia;
}

void Grafo::setearNodo(int id, const char nombre[], int x, int y, int xPX, int yPX)
{
    nodos[id].id = id;
    strcpy(nodos[id].nombre, nombre);
    nodos[id].x = x;
    nodos[id].y = y;
    nodos[id].xPX = xPX;
    nodos[id].yPX = yPX;
}

void Grafo::cortarORestaurarConexion(int a, int b)
{
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        cout << "Uno de los IDs ingresados no es valido." << endl;
        return;
    }

    if (a == b)
    {
        cout << "No se puede cortar una conexion de un nodo hacia si mismo." << endl;
        return;
    }

    if (matriz[a][b] == -1)
    {
        cout << "No existe una conexion directa entre ";
        cout << nodos[a].nombre << " y " << nodos[b].nombre << "." << endl;
        return;
    }

    matriz[a][b] = matriz[a][b] * -1;
    matriz[b][a] = matriz[b][a] * -1;

    if (matriz[a][b] < -1)
    {
        cout << "La conexion fue cortada temporalmente." << endl;
    }
    else
    {
        cout << "La conexion fue restaurada." << endl;
    }
}

int Grafo::verSiConexionActiva(int a, int b)
{
    if (matriz[a][b] == -1)
    {
        // No existe la conexion.
        return -1;
    }
    else if (matriz[a][b] < -1)
    {
        // Conexion cortada temporalmente.
        return 0;
    }
    else
    {
        // Conexion activa.
        return 1;
    }
}

void Grafo::mostrarNodos()
{
    cout << endl;
    cout << "NODOS CARGADOS" << endl;
    cout << "--------------" << endl;

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        cout << "ID: " << nodos[i].id;
        cout << " | Ciudad: " << nodos[i].nombre;
        cout << " | X: " << nodos[i].x;
        cout << " | Y: " << nodos[i].y << endl;
    }
}

void Grafo::mostrarMatriz()
{
    cout << endl;
    cout << "MATRIZ DE ADYACENCIA" << endl;
    cout << "--------------------" << endl;
    cout << "Referencias: -1 = no existe conexion, numero positivo = distancia en km" << endl;
    cout << endl;

    cout << "\t";
    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        cout << i << "\t";
    }
    cout << endl;

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        cout << i << "\t";

        for (int j = 0; j < NODOS_CANTIDAD; j++)
        {
            cout << matriz[i][j] << "\t";
        }

        cout << endl;
    }
}

void Grafo::mostrarConexionesDeNodo(int id)
{
    if (id < 0 || id >= NODOS_CANTIDAD)
    {
        cout << "El ID ingresado no es valido." << endl;
        return;
    }

    cout << endl;
    cout << "CONEXIONES DE " << nodos[id].nombre << endl;
    cout << "--------------------" << endl;

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        if (matriz[id][i] > 0)
        {
            cout << nodos[id].nombre << " -> " << nodos[i].nombre;
            cout << " = " << matriz[id][i] << " km" << endl;
        }
        else if (matriz[id][i] < -1)
        {
            cout << nodos[id].nombre << " -> " << nodos[i].nombre;
            cout << " = ruta cortada temporalmente" << endl;
        }
    }
}

int Grafo::consultarDistancia(int origen, int destino)
{
    if (origen < 0 || origen >= NODOS_CANTIDAD || destino < 0 || destino >= NODOS_CANTIDAD)
    {
        //cout << "Uno de los IDs ingresados no es valido." << endl;
        return;
    }

    //cout << endl;
    //cout << "Consulta de distancia" << endl;
    //cout << "---------------------" << endl;


    if (matriz[origen][destino] == -1)
    {
        //cout << "No existe conexion directa entre ";
        //cout << nodos[origen].nombre << " y " << nodos[destino].nombre << "." << endl;
        //ShowMessage("No existe conexion directa entre" + String(nodos[origen].nombre) + " y " + String(nodos[destino].nombre));
        return -1;
    }
    else if (matriz[origen][destino] < -1)
    {
        //cout << "La ruta entre ";
        //cout << nodos[origen].nombre << " y " << nodos[destino].nombre;
        //cout << " esta cortada temporalmente." << endl;
        ShowMessage("La ruta entre " + String(nodos[origen].nombre) + " y " + String(nodos[destino].nombre) + " esta cortada temporalmente.");
    }
    else
    {
        //cout << "Distancia entre ";
        //cout << nodos[origen].nombre << " y " << nodos[destino].nombre;
        //cout << ": " << matriz[origen][destino] << " km" << endl;
        ShowMessage("Distancia entre " + String(nodos[origen].nombre) + " y " + String(nodos[destino].nombre) + ": "+ matriz[origen][destino] + " km");
        return matriz[origen][destino];
    }
}

Nodo Grafo::enviarNodo(int i){
	return nodos[i];
}
