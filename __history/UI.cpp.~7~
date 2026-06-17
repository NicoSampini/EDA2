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
    LimpiarMapa();
    CargarRutas();


    cargarDatosIniciales(g);
    CargarCombo();
}

//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnSalirClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnBuscarClick(TObject *Sender)
{
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;
    int estadoConexion = g.verSiConexionActiva(origen, destino);

    MemoDatos->Lines->Clear();

    if (origen == -1 || destino == -1) {
       return;
    }

    int cant = g.dijkstra(origen, destino, camino);


     if(estadoConexion == 0){
        DibujarMapa('r', origen, destino);
        g.consultarDistancia(origen, destino);
    }
    else{
       for(int i = 0 ; i < cant - 1; i++)
        {
            DibujarMapa('b', camino[i], camino[i + 1]);
        }
        MemoDatos->Lines->Add("Distancia: " +  IntToStr(g.consultarDistancia(origen, destino)) + "km");
    }

    g.consultarDistancia(origen, destino);
    r.ActualizarRuta(origen, destino, 1);


}
//---------------------------------------------------------------------------

void __fastcall TInterfazGrafica::CortarRutaBtnClick(TObject *Sender)
{
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;
  	g.cortarORestaurarConexion(origen, destino);
    CargarRutas();
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

void TInterfazGrafica::CargarRutas(){
   for (int i = 0; i < RUTAS_CANTIDAD; i++) {
       for (int j = 0; j < RUTAS_CANTIDAD; j++) {
            if(r.ConsultarRuta(i, j) == 1 && g.verSiConexionActiva(i, j) == 1){
               DibujarMapa('b', i, j);
            }
            else if(r.ConsultarRuta(i, j) == 1 && g.verSiConexionActiva(i, j) == 0) {
               DibujarMapa('r', i, j);
            }
       }
   }
}
//---------------------------------------------------------------------------

void TInterfazGrafica::DibujarMapa(char color, int destino1, int destino2){

    TCanvas *canvas = ImageMapa-> Canvas;


    if(color == 'b'){
    	canvas->Pen->Color = clBlue;
    }
    else if(color == 'r') {
      canvas->Pen->Color = clRed;
    }
    else{
        return;
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
void __fastcall TInterfazGrafica::BtnBorrarClick(TObject *Sender)
{
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;
    r.ActualizarRuta(origen, destino, -1);
    LimpiarMapa();
    CargarRutas();
}
//---------------------------------------------------------------------------

