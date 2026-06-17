#ifndef GRAFO_H
#define GRAFO_H


#include <string>

#include "Nodo.h"

#define NODOS_CANTIDAD 8

class Grafo
{
private:
    int matriz[NODOS_CANTIDAD][NODOS_CANTIDAD];
    Nodo nodos[NODOS_CANTIDAD];

public:
    Grafo();

    void conectar(int a, int b, int distancia);
    void setearNodo(int id, const char nombre[], int x, int y, int xPX, int yPX);
    void cortarORestaurarConexion(int a, int b);
    int verSiConexionActiva(int a, int b);

    void mostrarNodos();
    void mostrarMatriz();
    void mostrarConexionesDeNodo(int id);
    int consultarDistancia(int origen, int destino);
    int dijkstra(int origen, int destino, int arrayNuevo[]);

    void guardarMatriz(const char archivo[]);
	void cargarMatriz(const char archivo[]);

    Nodo enviarNodo(int i);
};

#endif
