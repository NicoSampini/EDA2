#include <cstring>
#include <climits>
#include <cstdio>

#include "Grafo.h"

Grafo::Grafo()
{
    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        nodos[i].id = i;
        strcpy(nodos[i].nombre, "");
        nodos[i].x = 0;
        nodos[i].y = 0;
        nodos[i].xPX = 0;
        nodos[i].yPX = 0;
        nodos[i].activo = false;

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
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        return;
    }

    if (a == b || distancia <= 0)
    {
        return;
    }

    if (!nodos[a].activo || !nodos[b].activo)
    {
        return;
    }

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
    nodos[id].activo = true;
}

void Grafo::activarNodo(int id, int xPX, int yPX)
{
    if (id < 0 || id >= NODOS_CANTIDAD)
    {
        return;
    }

    nodos[id].xPX = xPX;
    nodos[id].yPX = yPX;
    nodos[id].activo = true;
}

void Grafo::modificarNodo(int id, const char nombre[], int x, int y, int xPX, int yPX)
{
    if (id < 0 || id >= NODOS_CANTIDAD)
    {
        return;
    }

    if (!nodos[id].activo)
    {
        return;
    }

    strcpy(nodos[id].nombre, nombre);
    nodos[id].x = x;
    nodos[id].y = y;
    nodos[id].xPX = xPX;
    nodos[id].yPX = yPX;
}

void Grafo::bajaNodo(int id)
{
    if (id < 0 || id >= NODOS_CANTIDAD)
    {
        return;
    }

    if (!nodos[id].activo)
    {
        return;
    }

    nodos[id].activo = false;
}

int Grafo::esNodoActivo(int id)
{
    if (id < 0 || id >= NODOS_CANTIDAD)
    {
        return 0;
    }

    if (nodos[id].activo)
    {
        return 1;
    }

    return 0;
}

void Grafo::eliminarConexion(int a, int b)
{
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        return;
    }

    if (a == b)
    {
        return;
    }

    matriz[a][b] = -1;
    matriz[b][a] = -1;
}

int Grafo::obtenerDistanciaConexion(int a, int b)
{
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        return -1;
    }

    if (matriz[a][b] == -1)
    {
        return -1;
    }

    if (matriz[a][b] < -1)
    {
        return matriz[a][b] * -1;
    }

    return matriz[a][b];
}

void Grafo::cortarORestaurarConexion(int a, int b)
{
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        return;
    }

    if (!nodos[a].activo || !nodos[b].activo)
    {
        return;
    }

    if (a == b)
    {
        return;
    }

    if (matriz[a][b] == -1)
    {
        return;
    }

    matriz[a][b] = matriz[a][b] * -1;
    matriz[b][a] = matriz[b][a] * -1;
}

int Grafo::verSiConexionActiva(int a, int b)
{
    if (a < 0 || a >= NODOS_CANTIDAD || b < 0 || b >= NODOS_CANTIDAD)
    {
        return -1;
    }

    if (!nodos[a].activo || !nodos[b].activo)
    {
        return -1;
    }

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

int Grafo::consultarDistancia(int origen, int destino)
{
    if (origen < 0 || origen >= NODOS_CANTIDAD || destino < 0 || destino >= NODOS_CANTIDAD)
    {
        return -3;
    }

    if (!nodos[origen].activo || !nodos[destino].activo)
    {
        return -3;
    }

    if (matriz[origen][destino] == -1)
    {
        return -1;
    }
    else if (matriz[origen][destino] < -1)
    {
        return -1;
    }
    else
    {
        return matriz[origen][destino];
    }
}

int Grafo::dijkstra(int origen, int destino, int arrayNuevo[])
{

    if (origen < 0 || origen >= NODOS_CANTIDAD)
    {
        return 0;
    }

    if (destino < 0 || destino >= NODOS_CANTIDAD)
    {
        return 0;
    }

    if (!nodos[origen].activo || !nodos[destino].activo)
    {
        return 0;
    }

    if (origen == destino)
    {
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
            if (nodos[i].activo &&
                matriz[nodoActual][i] > 0 &&
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
            if (nodos[i].activo && !visitado[i] && distancias[i] < distanciaMinima)
            {
                nodoActual = i;
                distanciaMinima = distancias[i];
                changed = 1;
            }
        }

        if (nodoActual == destino)
        {
            changed = 0;

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
        }
        else if (changed == 0)
        {
            return 0;
        }
    }

    return 0;
}

Nodo Grafo::enviarNodo(int i){
	return nodos[i];
}

void Grafo::guardarMatriz(const char archivo[])
{
    FILE *f = fopen(archivo, "wb");
    if (f == NULL)
    {
        return;
    }

    fwrite(matriz, sizeof(int), NODOS_CANTIDAD * NODOS_CANTIDAD, f);

    fclose(f);
}

void Grafo::cargarMatriz(const char archivo[])
{
    FILE *f = fopen(archivo, "rb");
    if (f == NULL)
    {
        return;
    }

    fseek(f, 0, SEEK_END);
    long tamanio = ftell(f);
    rewind(f);

    if (tamanio != sizeof(int) * NODOS_CANTIDAD * NODOS_CANTIDAD)
    {
        fclose(f);
        return;
    }

    fread(matriz, sizeof(int), NODOS_CANTIDAD * NODOS_CANTIDAD, f);

    fclose(f);
}

void Grafo::guardarNodos(const char archivo[])
{
    FILE *f = fopen(archivo, "wb");
    if (f == NULL)
    {
        return;
    }

    fwrite(nodos, sizeof(Nodo), NODOS_CANTIDAD, f);

    fclose(f);
}

void Grafo::cargarNodos(const char archivo[])
{
    FILE *f = fopen(archivo, "rb");
    if (f == NULL)
    {
        return;
    }

    fseek(f, 0, SEEK_END);
    long tamanio = ftell(f);
    rewind(f);

    if (tamanio != sizeof(Nodo) * NODOS_CANTIDAD)
    {
        fclose(f);
        return;
    }

    fread(nodos, sizeof(Nodo), NODOS_CANTIDAD, f);

    fclose(f);
}
