//---------------------------------------------------------------------------

#pragma hdrstop

#include "Rutas.h"

Rutas::Rutas(){
    for (int i = 0; i < RUTAS_CANTIDAD; i++)
    {
        for (int j = 0; j < RUTAS_CANTIDAD; j++)
        {
            if (i == j){
                matrizRutas[i][j] = 0;
            }
            else{
                matrizRutas[i][j] = -1;
            }
        }
    }
}

void Rutas::ActualizarRuta(int origen, int destino, int creada){
    if (origen == destino) {
        return;
    }
    matrizRutas[origen][destino] = creada;
    matrizRutas[destino][origen] = creada;
}

int Rutas::ConsultarRuta(int origen, int destino){
    return matrizRutas[origen][destino];
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
