//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UI.h"
#include "Grafo.h"
#include "DatosIniciales.h"
#include "FormNodos.h"
#include "FormConexiones.h"
#include <System.SysUtils.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfazGrafica *InterfazGrafica;
//---------------------------------------------------------------------------

namespace
{
    const TColor COLOR_FONDO = TColor(0x00AAB2B8);  // #B8B2AA
    const TColor COLOR_CAMPO = TColor(0x00F4F5F6);  // #F6F5F4
    const TColor COLOR_TEXTO = TColor(0x002C2F31);  // #312F2C
    const TColor COLOR_ACENTO = TColor(0x002C2F31); // #312F2C

    void EstilizarControl(TControl *control)
    {
        if (TButton *boton = dynamic_cast<TButton*>(control))
        {
            boton->Font->Color = COLOR_TEXTO;
            boton->Font->Name = "Segoe UI";
            boton->Font->Size = 9;
            boton->ParentFont = false;
            return;
        }

        if (TComboBox *combo = dynamic_cast<TComboBox*>(control))
        {
            combo->Font->Color = COLOR_TEXTO;
            combo->Font->Name = "Segoe UI";
            combo->Color = COLOR_CAMPO;
            combo->ParentFont = false;
            return;
        }

        if (TMemo *memo = dynamic_cast<TMemo*>(control))
        {
            memo->Font->Color = COLOR_TEXTO;
            memo->Font->Name = "Segoe UI";
            memo->Color = COLOR_CAMPO;
            memo->ParentFont = false;
            return;
        }

        if (TLabel *label = dynamic_cast<TLabel*>(control))
        {
            label->Font->Color = COLOR_TEXTO;
            label->ParentFont = false;
        }
    }

    void EstilizarControles(TWinControl *contenedor)
    {
        for (int i = 0; i < contenedor->ControlCount; i++)
        {
            TControl *control = contenedor->Controls[i];
            EstilizarControl(control);

            if (TWinControl *hijo = dynamic_cast<TWinControl*>(control))
            {
                EstilizarControles(hijo);
            }
        }
    }
}

int TInterfazGrafica::ObtenerIdSeleccionado(TComboBox *combo)
{
    if (combo->ItemIndex == -1)
    {
        return -1;
    }

    String texto = combo->Items->Strings[combo->ItemIndex];
    int posicionSeparador = texto.Pos(" - ");

    if (posicionSeparador == 0)
    {
        return -1;
    }

    return StrToIntDef(texto.SubString(1, posicionSeparador - 1), -1);
}

void TInterfazGrafica::GuardarDatos()
{
    g.guardarMatriz("matriz.dat");
    g.guardarNodos("nodos.dat");
}

void TInterfazGrafica::CrearBotonesAdministrar()
{
    TButton *administrarCiudades = new TButton(this);
    administrarCiudades->Parent = this;
    administrarCiudades->Left = 24;
    administrarCiudades->Top = 230;
    administrarCiudades->Width = 204;
    administrarCiudades->Height = 33;
    administrarCiudades->Caption = "Administrar ciudades";
    administrarCiudades->OnClick = BtnAdministrarNodosClick;

    TButton *administrarConexiones = new TButton(this);
    administrarConexiones->Parent = this;
    administrarConexiones->Left = 24;
    administrarConexiones->Top = 272;
    administrarConexiones->Width = 204;
    administrarConexiones->Height = 33;
    administrarConexiones->Caption = "Administrar conexiones";
    administrarConexiones->OnClick = BtnAdministrarConexionesClick;

    EstilizarControl(administrarCiudades);
    EstilizarControl(administrarConexiones);
}

void TInterfazGrafica::RefrescarDespuesDeAdministrar(const String &mensaje)
{
    CargarCombo();
    LimpiarMapa();
    InicializarMapa();
    GuardarDatos();

    MemoDatos->Lines->Clear();
    MemoDatos->Lines->Add(mensaje);
}

void guardarHistorial(Grafo &g, int origen, int destino, int distanciaTotal, int camino[], int cantidad)
{
    FILE *f = fopen("Historial.txt", "a");
    if (f == NULL)
    {
        return;
    }

    fprintf(f, "Origen: %s\n", g.enviarNodo(origen).nombre);
    fprintf(f, "Destino: %s\n", g.enviarNodo(destino).nombre);
    fprintf(f, "Distancia total: %d km\n", distanciaTotal);
    fprintf(f, "Recorrido: ");

    for (int i = 0; i < cantidad; i++)
    {
        fprintf(f, "%s", g.enviarNodo(camino[i]).nombre);
        if (i < cantidad - 1)
        {
            fprintf(f, " -> ");
        }
    }

    fprintf(f, "\n------------------------------\n");
    fclose(f);
}

__fastcall TInterfazGrafica::TInterfazGrafica(TComponent* Owner)
	: TForm(Owner)
{
    Color = COLOR_FONDO;
    Font->Color = COLOR_TEXTO;
    Titulo->Font->Color = COLOR_ACENTO;
    TituloDatos->Font->Color = COLOR_ACENTO;

    cargarDatosIniciales(g);
    g.cargarNodos("nodos.dat");
    g.cargarMatriz("matriz.dat");
    LimpiarMapa();
    InicializarMapa();

    CrearBotonesAdministrar();
    EstilizarControles(this);
    Titulo->Font->Color = COLOR_ACENTO;
    TituloDatos->Font->Color = COLOR_ACENTO;
    CargarCombo();
}

//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnSalirClick(TObject *Sender)
{
	GuardarDatos();
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TInterfazGrafica::BtnBuscarClick(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    MemoDatos->Lines->Clear();

    if (origen == -1 || destino == -1)
    {
        MemoDatos->Lines->Add("Seleccione origen y destino.");
        return;
    }

    if (origen == destino)
    {
        MemoDatos->Lines->Add("El origen y destino no pueden ser iguales.");
        return;
    }

    LimpiarMapa();
    InicializarMapa();

    int camino[NODOS_CANTIDAD];
    int cant = g.dijkstra(origen, destino, camino);

    if (cant == 0)
    {
        MemoDatos->Lines->Add("No hay camino posible entre");
        MemoDatos->Lines->Add(g.enviarNodo(origen).nombre);
        MemoDatos->Lines->Add("y");
        MemoDatos->Lines->Add(g.enviarNodo(destino).nombre);
        return;
    }

    int distanciaTotal = 0;
    for (int i = 0; i < cant - 1; i++)
    {
        distanciaTotal += g.consultarDistancia(camino[i], camino[i+1]);
        DibujarMapa('a', camino[i], camino[i+1]);
    }

    MemoDatos->Lines->Add("Distancia total: " + IntToStr(distanciaTotal) + " km");
    MemoDatos->Lines->Add("Recorrido:");
    for (int i = 0; i < cant; i++)
    {
        MemoDatos->Lines->Add("  " + String(g.enviarNodo(camino[i]).nombre));
    }

    guardarHistorial(g, origen, destino, distanciaTotal, camino, cant);
}
//---------------------------------------------------------------------------

void __fastcall TInterfazGrafica::CortarRutaBtnClick(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    if (origen == -1 || destino == -1)
    {
        MemoDatos->Lines->Add("Seleccione origen y destino.");
        return;
    }

    int estado = g.verSiConexionActiva(origen, destino);

    if (estado == -1)
    {
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
    if (estado == 1)
    {
        DibujarMapa('r', origen, destino);
    }
    GuardarDatos();

    MemoDatos->Lines->Clear();
    if (estado == 1)
    {
        MemoDatos->Lines->Add("Ruta cortada entre");
    }
    else
    {
        MemoDatos->Lines->Add("Ruta restaurada entre");
    }
    MemoDatos->Lines->Add(g.enviarNodo(origen).nombre);
    MemoDatos->Lines->Add("y");
    MemoDatos->Lines->Add(g.enviarNodo(destino).nombre);
}
//---------------------------------------------------------------------------

void __fastcall TInterfazGrafica::BtnAdministrarNodosClick(TObject *Sender)
{
    TFormNodos *formNodos = new TFormNodos(this, &g);
    formNodos->ShowModal();

    if (formNodos->TieneCambios())
    {
        RefrescarDespuesDeAdministrar("Cambios de ciudades guardados.");
    }

    delete formNodos;
}
//---------------------------------------------------------------------------

void __fastcall TInterfazGrafica::BtnAdministrarConexionesClick(TObject *Sender)
{
    TFormConexiones *formConexiones = new TFormConexiones(this, &g);
    formConexiones->ShowModal();

    if (formConexiones->TieneCambios())
    {
        RefrescarDespuesDeAdministrar("Cambios de conexiones guardados.");
    }

    delete formConexiones;
}
//---------------------------------------------------------------------------

void TInterfazGrafica::CargarCombo(){
    OrigenCB->Items->Clear();
    DestinoCB->Items->Clear();
    OrigenCB->Text = "Origen";
    DestinoCB->Text = "Destino";

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        if (g.esNodoActivo(i))
        {
            String item = IntToStr(i) + " - " + String(g.enviarNodo(i).nombre);
            OrigenCB->Items->Add(item);
            DestinoCB->Items->Add(item);
        }
    }
}
//---------------------------------------------------------------------------

void TInterfazGrafica::InicializarMapa(){
    TCanvas *canvas = ImageMapa->Canvas;
    canvas->Pen->Width = 3;

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        if (!g.esNodoActivo(i))
        {
            continue;
        }

        for (int j = i + 1; j < NODOS_CANTIDAD; j++)
        {
            if (!g.esNodoActivo(j))
            {
                continue;
            }

            int conexion = g.verSiConexionActiva(i, j);

            if (conexion == 1)
            {
                canvas->Pen->Color = clBlack;
                canvas->Pen->Width = 3;
            }
            else if (conexion == 0)
            {
                canvas->Pen->Color = clRed;
                canvas->Pen->Width = 5;
            }
            else
            {
                continue;
            }

            Nodo a = g.enviarNodo(i);
            Nodo b = g.enviarNodo(j);
            canvas->MoveTo(a.xPX, a.yPX);
            canvas->LineTo(b.xPX, b.yPX);
        }
    }

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        if (!g.esNodoActivo(i))
        {
            continue;
        }

        Nodo nodo = g.enviarNodo(i);
        canvas->Pen->Color = clNavy;
        canvas->Brush->Color = clWhite;
        canvas->Ellipse(nodo.xPX - 5, nodo.yPX - 5, nodo.xPX + 5, nodo.yPX + 5);
        canvas->Brush->Style = bsClear;
        canvas->TextOut(nodo.xPX + 8, nodo.yPX - 8, String(nodo.nombre));
        canvas->Brush->Style = bsSolid;
    }
}
//---------------------------------------------------------------------------

void TInterfazGrafica::DibujarMapa(char color, int destino1, int destino2){

    TCanvas *canvas = ImageMapa-> Canvas;


    if (color == 'a')
    {
        canvas->Pen->Color = clBlue;
    }
    else if(color == 'r')
    {
        canvas->Pen->Color = clRed;
        canvas->Pen->Width = 5;
    }
    else
    {
     	canvas->Pen->Color = clBlack;
        canvas->Pen->Width = 3;
    }

    if (color == 'a')
    {
        canvas->Pen->Width = 3;
    }

    Nodo a = g.enviarNodo(destino1);
    Nodo b = g.enviarNodo(destino2);

    canvas->MoveTo(a.xPX, a.yPX);
	canvas->LineTo(b.xPX, b.yPX);

}
//---------------------------------------------------------------------------
void TInterfazGrafica::LimpiarMapa(){
    String rutaMapa = ExtractFilePath(Application->ExeName) + "mapaCordoba3.jpg";

    if (!FileExists(rutaMapa))
    {
        rutaMapa = ExtractFilePath(Application->ExeName) + "..\\mapaCordoba3.jpg";
    }

    if (!FileExists(rutaMapa))
    {
        rutaMapa = ExtractFilePath(Application->ExeName) + "..\\..\\mapaCordoba3.jpg";
    }

    if (FileExists(rutaMapa))
    {
        ImageMapa->Picture->LoadFromFile(rutaMapa);
    }

    Graphics::TBitmap *bmp = new Graphics::TBitmap();
    bmp->Width  = ImageMapa->Width;
    bmp->Height = ImageMapa->Height;
    bmp->Canvas->Draw(0, 0, ImageMapa->Picture->Graphic);
    ImageMapa->Picture->Assign(bmp);
    delete bmp;
}
//---------------------------------------------------------------------------

