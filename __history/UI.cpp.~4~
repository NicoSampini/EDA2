//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UI.h"
#include "Grafo.h"
#include "DatosIniciales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfazGrafica *InterfazGrafica;

//---------------------------------------------------------------------------
__fastcall TInterfazGrafica::TInterfazGrafica(TComponent* Owner)
	: TForm(Owner)
{
	ImageMapa->Picture->LoadFromFile("mapaCordoba3.jpg");

    Graphics::TBitmap *bmp = new Graphics::TBitmap();
    bmp->Width  = ImageMapa->Width;
    bmp->Height = ImageMapa->Height;
    bmp->Canvas->Draw(0, 0, ImageMapa->Picture->Graphic);
    ImageMapa->Picture->Assign(bmp);
    delete bmp;


    cargarDatosIniciales(g);

    for(int i = 0; i < NODOS_CANTIDAD; i++)
    {
    	OrigenCB->Items->Add(String(g.enviarNodo(i).nombre));
        DestinoCB->Items->Add(String(g.enviarNodo(i).nombre));
    }


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

    if (origen == -1 || origen == -1) {
       return;
    }
    if(g.consultarDistancia(origen, destino) == -1){
          ShowMessage("No existe conexion directa");
    }
    else{
    	DibujarMapa();
    	g.consultarDistancia(origen, destino);
    }

}
//---------------------------------------------------------------------------
void TInterfazGrafica::DibujarMapa(){

    TCanvas *canvas = ImageMapa-> Canvas;
    int origen = OrigenCB->ItemIndex;
    int destino = DestinoCB->ItemIndex;

    canvas->Pen->Color = clBlue;
    canvas->Pen->Width = 3;

    Nodo a = g.enviarNodo(origen);
    Nodo b = g.enviarNodo(destino);

    canvas->MoveTo(a.xPX, a.yPX);
	canvas->LineTo(b.xPX, b.yPX);

}



