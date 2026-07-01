#include <vcl.h>
#pragma hdrstop

#include "FormConexiones.h"
#include <System.SysUtils.hpp>

#pragma package(smart_init)

__fastcall TFormConexiones::TFormConexiones(TComponent* Owner, Grafo *grafo)
    : TForm(Owner, 0)
{
    g = grafo;
    huboCambios = false;

    Caption = "Administrar conexiones";
    Width = 370;
    Height = 380;
    Position = poOwnerFormCenter;
    BorderStyle = bsDialog;

    TLabel *origenLabel = new TLabel(this);
    origenLabel->Parent = this;
    origenLabel->Left = 24;
    origenLabel->Top = 24;
    origenLabel->Caption = "Origen";

    OrigenCB = new TComboBox(this);
    OrigenCB->Parent = this;
    OrigenCB->Left = 24;
    OrigenCB->Top = 46;
    OrigenCB->Width = 296;
    OrigenCB->Style = csDropDownList;
    OrigenCB->OnChange = ConexionCBChange;

    TLabel *destinoLabel = new TLabel(this);
    destinoLabel->Parent = this;
    destinoLabel->Left = 24;
    destinoLabel->Top = 82;
    destinoLabel->Caption = "Destino";

    DestinoCB = new TComboBox(this);
    DestinoCB->Parent = this;
    DestinoCB->Left = 24;
    DestinoCB->Top = 104;
    DestinoCB->Width = 296;
    DestinoCB->Style = csDropDownList;
    DestinoCB->OnChange = ConexionCBChange;

    TLabel *distanciaLabel = new TLabel(this);
    distanciaLabel->Parent = this;
    distanciaLabel->Left = 24;
    distanciaLabel->Top = 140;
    distanciaLabel->Caption = "Distancia en km";

    DistanciaEdit = new TEdit(this);
    DistanciaEdit->Parent = this;
    DistanciaEdit->Left = 24;
    DistanciaEdit->Top = 162;
    DistanciaEdit->Width = 296;
    DistanciaEdit->Text = "100";

    TButton *altaConexion = new TButton(this);
    altaConexion->Parent = this;
    altaConexion->Left = 24;
    altaConexion->Top = 200;
    altaConexion->Width = 96;
    altaConexion->Height = 27;
    altaConexion->Caption = "Agregar";
    altaConexion->OnClick = AltaConexionClick;

    TButton *modificarConexion = new TButton(this);
    modificarConexion->Parent = this;
    modificarConexion->Left = 124;
    modificarConexion->Top = 200;
    modificarConexion->Width = 96;
    modificarConexion->Height = 27;
    modificarConexion->Caption = "Modificar";
    modificarConexion->OnClick = ModificarConexionClick;

    TButton *bajaConexion = new TButton(this);
    bajaConexion->Parent = this;
    bajaConexion->Left = 224;
    bajaConexion->Top = 200;
    bajaConexion->Width = 96;
    bajaConexion->Height = 27;
    bajaConexion->Caption = "Eliminar";
    bajaConexion->OnClick = BajaConexionClick;

    MemoConexiones = new TMemo(this);
    MemoConexiones->Parent = this;
    MemoConexiones->Left = 24;
    MemoConexiones->Top = 238;
    MemoConexiones->Width = 296;
    MemoConexiones->Height = 44;
    MemoConexiones->ReadOnly = true;

    TButton *cerrar = new TButton(this);
    cerrar->Parent = this;
    cerrar->Left = 224;
    cerrar->Top = 292;
    cerrar->Width = 96;
    cerrar->Height = 27;
    cerrar->Caption = "Cerrar";
    cerrar->OnClick = CerrarClick;

    CargarCombos();
}

bool TFormConexiones::TieneCambios()
{
    return huboCambios;
}

int TFormConexiones::ObtenerIdSeleccionado(TComboBox *combo)
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

void TFormConexiones::CargarCombos()
{
    OrigenCB->Items->Clear();
    DestinoCB->Items->Clear();

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        if (g->esNodoActivo(i))
        {
            String item = IntToStr(i) + " - " + String(g->enviarNodo(i).nombre);
            OrigenCB->Items->Add(item);
            DestinoCB->Items->Add(item);
        }
    }

    OrigenCB->ItemIndex = -1;
    DestinoCB->ItemIndex = -1;
    DistanciaEdit->Text = "100";
}

void TFormConexiones::MostrarMensaje(const String &mensaje)
{
    MemoConexiones->Lines->Clear();
    MemoConexiones->Lines->Add(mensaje);
}

void TFormConexiones::MarcarCambio()
{
    huboCambios = true;
}

void __fastcall TFormConexiones::ConexionCBChange(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    if (origen == -1 || destino == -1 || origen == destino)
    {
        return;
    }

    int distancia = g->obtenerDistanciaConexion(origen, destino);
    if (distancia != -1)
    {
        DistanciaEdit->Text = IntToStr(distancia);
    }
}

void __fastcall TFormConexiones::AltaConexionClick(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    if (origen == -1 || destino == -1)
    {
        MostrarMensaje("Seleccione origen y destino.");
        return;
    }

    if (origen == destino)
    {
        MostrarMensaje("Origen y destino deben ser distintos.");
        return;
    }

    if (g->verSiConexionActiva(origen, destino) != -1)
    {
        MostrarMensaje("Ya existe una conexion directa.");
        return;
    }

    int distancia = StrToIntDef(DistanciaEdit->Text, -1);
    if (distancia <= 0)
    {
        MostrarMensaje("La distancia debe ser positiva.");
        return;
    }

    g->conectar(origen, destino, distancia);
    MarcarCambio();
    MostrarMensaje("Conexion agregada.");
}

void __fastcall TFormConexiones::ModificarConexionClick(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    if (origen == -1 || destino == -1)
    {
        MostrarMensaje("Seleccione origen y destino.");
        return;
    }

    if (origen == destino)
    {
        MostrarMensaje("Origen y destino deben ser distintos.");
        return;
    }

    if (g->obtenerDistanciaConexion(origen, destino) == -1)
    {
        MostrarMensaje("No existe una conexion directa.");
        return;
    }

    int distancia = StrToIntDef(DistanciaEdit->Text, -1);
    if (distancia <= 0)
    {
        MostrarMensaje("La distancia debe ser positiva.");
        return;
    }

    g->conectar(origen, destino, distancia);
    MarcarCambio();
    MostrarMensaje("Conexion modificada.");
}

void __fastcall TFormConexiones::BajaConexionClick(TObject *Sender)
{
    int origen = ObtenerIdSeleccionado(OrigenCB);
    int destino = ObtenerIdSeleccionado(DestinoCB);

    if (origen == -1 || destino == -1)
    {
        MostrarMensaje("Seleccione origen y destino.");
        return;
    }

    if (origen == destino)
    {
        MostrarMensaje("Origen y destino deben ser distintos.");
        return;
    }

    if (g->obtenerDistanciaConexion(origen, destino) == -1)
    {
        MostrarMensaje("No existe una conexion directa para eliminar.");
        return;
    }

    g->eliminarConexion(origen, destino);
    MarcarCambio();
    MostrarMensaje("Conexion eliminada.");
}

void __fastcall TFormConexiones::CerrarClick(TObject *Sender)
{
    Close();
}
