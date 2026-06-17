//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UI.h"
#include "Grafo.h"
#include "Rutas.h"
#include "DatosIniciales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfazGrafica *InterfazGrafica;
int camino[NODOS_CANTIDAD];
//---------------------------------------------------------------------------
__fastcall TInterfazGrafica::TInterfazGrafica(TComponent* Owner)
	: TForm(Owner)
{
    cargarDatosIniciales(g);
    g.cargarMatriz("matriz.dat");
    LimpiarMapa();
    InicializarMapa();


    CargarCombo();
}

//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnSalirClick(TObject *Sender)
{
	g.guardarMatriz("matriz.dat");
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnBuscarClick(TObject *Sender)
{
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;

    MemoDatos->Lines->Clear();

    if (origen == -1 || destino == -1) {
        MemoDatos->Lines->Add("Seleccione origen y destino.");
        return;
    }

    if (origen == destino) {
        MemoDatos->Lines->Add("El origen y destino no pueden ser iguales.");
        return;
    }

    LimpiarMapa();
    InicializarMapa();

    int cant = g.dijkstra(origen, destino, camino);

    if (cant == 0) {
        MemoDatos->Lines->Add("No hay camino posible entre");
        MemoDatos->Lines->Add(g.enviarNodo(origen).nombre);
        MemoDatos->Lines->Add("y");
        MemoDatos->Lines->Add(g.enviarNodo(destino).nombre);
        return;
    }

    int distanciaTotal = 0;
    for (int i = 0; i < cant - 1; i++) {
        distanciaTotal += g.consultarDistancia(camino[i], camino[i+1]);
        DibujarMapa('a', camino[i], camino[i+1]);
    }

    MemoDatos->Lines->Add("Distancia total: " + IntToStr(distanciaTotal) + " km");
    MemoDatos->Lines->Add("Recorrido:");
    for (int i = 0; i < cant; i++) {
        MemoDatos->Lines->Add("  " + String(g.enviarNodo(camino[i]).nombre));
    }
}
//---------------------------------------------------------------------------

void __fastcall TInterfazGrafica::CortarRutaBtnClick(TObject *Sender)
{
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;

    if (origen == -1 || destino == -1) {
        MemoDatos->Lines->Add("Seleccione origen y destino.");
        return;
    }

    int estado = g.verSiConexionActiva(origen, destino);

    if (estado == -1) {
        MemoDatos->Lines->Clear();
        MemoDatos->Lines->Add("No existe conexion directa entre");
        MemoDatos->Lines->Add(g.enviarNodo(origen).nombre);
        MemoDatos->Lines->Add("y");
        MemoDatos->Lines->Add(g.enviarNodo(destino).nombre);
        return;
    }

    g.cortarORestaurarConexion(origen, destino);
    LimpiarMapa();
    InicializarMapa();

    MemoDatos->Lines->Clear();
    if (estado == 1) {
        MemoDatos->Lines->Add("Ruta cortada entre");
    } else {
        MemoDatos->Lines->Add("Ruta restaurada entre");
    }
    MemoDatos->Lines->Add(g.enviarNodo(origen).nombre);
    MemoDatos->Lines->Add("y");
    MemoDatos->Lines->Add(g.enviarNodo(destino).nombre);
}
//---------------------------------------------------------------------------
void TInterfazGrafica::CargarCombo(){
   for(int i = 0; i < NODOS_CANTIDAD; i++)
    {
    	OrigenCB->Items->Add(String(g.enviarNodo(i).nombre));
        DestinoCB->Items->Add(String(g.enviarNodo(i).nombre));
    }
}
//---------------------------------------------------------------------------

void TInterfazGrafica::InicializarMapa(){
    TCanvas *canvas = ImageMapa->Canvas;
    canvas->Pen->Width = 3;

    for (int i = 0; i < NODOS_CANTIDAD; i++) {
        for (int j = i + 1; j < NODOS_CANTIDAD; j++) {

            int conexion = g.verSiConexionActiva(i, j);

            if (conexion == 1) {
                canvas->Pen->Color = clBlack;
            } else if (conexion == 0) {
                canvas->Pen->Color = clRed;
            } else {
                continue;
            }

            Nodo a = g.enviarNodo(i);
            Nodo b = g.enviarNodo(j);
            canvas->MoveTo(a.xPX, a.yPX);
            canvas->LineTo(b.xPX, b.yPX);
        }
    }
}
//---------------------------------------------------------------------------

void TInterfazGrafica::DibujarMapa(char color, int destino1, int destino2){

    TCanvas *canvas = ImageMapa-> Canvas;


     if (color == 'a') {
        canvas->Pen->Color = clBlue;
     }else if(color == 'r'){
        canvas->Pen->Color = clRed;
     }else{
     	canvas->Pen->Color = clBlack;
     }

    canvas->Pen->Width = 3;

    Nodo a = g.enviarNodo(destino1);
    Nodo b = g.enviarNodo(destino2);

    canvas->MoveTo(a.xPX, a.yPX);
	canvas->LineTo(b.xPX, b.yPX);

}
//---------------------------------------------------------------------------
void TInterfazGrafica::LimpiarMapa(){
    ImageMapa->Picture->LoadFromFile("mapaCordoba3.jpg");

    Graphics::TBitmap *bmp = new Graphics::TBitmap();
    bmp->Width  = ImageMapa->Width;
    bmp->Height = ImageMapa->Height;
    bmp->Canvas->Draw(0, 0, ImageMapa->Picture->Graphic);
    ImageMapa->Picture->Assign(bmp);
    delete bmp;
}
//---------------------------------------------------------------------------

