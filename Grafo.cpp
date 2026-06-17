#include <iostream>
#include <cstring>
#include <climits>
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
        //cout << "Uno de los IDs ingresados no es valido." << endl;
        return;
    }

    if (a == b)
    {
        //cout << "No se puede cortar una conexion de un nodo hacia si mismo." << endl;
        return;
    }

    if (matriz[a][b] == -1)
    {
        //cout << "No existe una conexion directa entre ";
        //cout << nodos[a].nombre << " y " << nodos[b].nombre << "." << endl;
        return;
    }

    matriz[a][b] = matriz[a][b] * -1;
    matriz[b][a] = matriz[b][a] * -1;

    //if (matriz[a][b] < -1)
    //{
        //cout << "La conexion fue cortada temporalmente." << endl;
    //}
    //else
    //{
        //cout << "La conexion fue restaurada." << endl;
    //}
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
        return -3;
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
        //ShowMessage("La ruta entre " + String(nodos[origen].nombre) + " y " + String(nodos[destino].nombre) + " esta cortada temporalmente.");
        return -1;
    }
    else
    {
        //cout << "Distancia entre ";
        //cout << nodos[origen].nombre << " y " << nodos[destino].nombre;
        //cout << ": " << matriz[origen][destino] << " km" << endl;
        //ShowMessage("Distancia entre " + String(nodos[origen].nombre) + " y " + String(nodos[destino].nombre) + ": "+ matriz[origen][destino] + " km");
        return matriz[origen][destino];
    }
}

int Grafo::dijkstra(int origen, int destino, int arrayNuevo[])
{

    if (origen < 0 || origen >= NODOS_CANTIDAD)
    {
        //cout << "ID de origen invalida" << endl;
        return 0;
    }

    if (destino < 0 || destino >= NODOS_CANTIDAD)
    {
        //cout << "ID de destino invalida" << endl;
        return 0;
    }

    if (origen == destino)
    {
        //cout << "El origen y destino no pueden ser iguales" << endl;
        return 0;
    }

    int distancias[NODOS_CANTIDAD];
    bool visitado[NODOS_CANTIDAD];
    int anterior[NODOS_CANTIDAD];
    int nodoActual = origen;

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        distancias[i] = INT_MAX;
        visitado[i] = false;
        anterior[i] = -1;
    }

    distancias[nodoActual] = 0;

    int changed = 1;

    while (changed == 1)
    {
        changed = 0;
        visitado[nodoActual] = true;
        for (int i = 0; i < NODOS_CANTIDAD; i++)
        {
            if (matriz[nodoActual][i] > 0 &&
                distancias[nodoActual] + matriz[nodoActual][i] < distancias[i])
            {
                distancias[i] =
                    distancias[nodoActual] + matriz[nodoActual][i];

                anterior[i] = nodoActual;
            }
        }

        int distanciaMinima = INT_MAX;

        for (int i = 0; i < NODOS_CANTIDAD; i++)
        {
            if (!visitado[i] && distancias[i] < distanciaMinima)
            {
                nodoActual = i;
                distanciaMinima = distancias[i];
                changed = 1;
            }
        }

        if (nodoActual == destino)
        {
            changed = 0;

            //cout << endl;
            //cout << "======================================" << endl;
            //cout << "MEJOR RUTA DESDE "
                 //<< nodos[origen].nombre
                 //<< " HASTA "
                 //<< nodos[destino].nombre
                 //<< endl;

            //cout << "DISTANCIA TOTAL: "
                 //<< distancias[destino]
                 //<< " km"
                 //<< endl;

            //cout << "======================================" << endl;

            int camino[NODOS_CANTIDAD];
            int cantidad = 0;

            int actual = destino;

            while (actual != -1)
            {
                arrayNuevo[cantidad] = actual;
                cantidad++;

                actual = anterior[actual];

            }
            for (int i = 0; i < cantidad / 2; i++)
			{
            	int temp = arrayNuevo[i];
            	arrayNuevo[i] = arrayNuevo[cantidad - 1 - i];
    			arrayNuevo[cantidad - 1 - i] = temp;
			}
            return cantidad;
            //cout << endl;
            //cout << "RECORRIDO:" << endl;
            //cout << endl;
        }
        else if (changed == 0)
        {
            return 0;
        }
    }
}

Nodo Grafo::enviarNodo(int i){
	return nodos[i];
}

void Grafo::guardarMatriz(const char archivo[])
{
    FILE *f = fopen("GrafoBinario.bin", "wb");
    if (f == NULL) return;

    fwrite(matriz, sizeof(int), NODOS_CANTIDAD * NODOS_CANTIDAD, f);

    fclose(f);
}

void Grafo::cargarMatriz(const char archivo[])
{
    FILE *f = fopen("GrafoBinario.bin", "rb");
    if (f == NULL) return;

    fread(matriz, sizeof(int), NODOS_CANTIDAD * NODOS_CANTIDAD, f);

    fclose(f);
}
