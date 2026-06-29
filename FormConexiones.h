#ifndef FORM_CONEXIONES_H
#define FORM_CONEXIONES_H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Grafo.h"

class TFormConexiones : public TForm
{
private:
    Grafo *g;
    bool huboCambios;

    TComboBox *OrigenCB;
    TComboBox *DestinoCB;
    TEdit *DistanciaEdit;
    TMemo *MemoConexiones;

    int ObtenerIdSeleccionado(TComboBox *combo);
    void CargarCombos();
    void MostrarMensaje(const String &mensaje);
    void MarcarCambio();

    void __fastcall ConexionCBChange(TObject *Sender);
    void __fastcall AltaConexionClick(TObject *Sender);
    void __fastcall ModificarConexionClick(TObject *Sender);
    void __fastcall BajaConexionClick(TObject *Sender);
    void __fastcall CerrarClick(TObject *Sender);

public:
    __fastcall TFormConexiones(TComponent* Owner, Grafo *grafo);
    bool TieneCambios();
};

#endif
