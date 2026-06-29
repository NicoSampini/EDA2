#ifndef FORM_NODOS_H
#define FORM_NODOS_H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Grafo.h"

class TFormNodos : public TForm
{
private:
    Grafo *g;
    bool huboCambios;

    TComboBox *AltaCiudadCB;
    TComboBox *CiudadCB;
    TEdit *AltaXEdit;
    TEdit *AltaYEdit;
    TEdit *NombreEdit;
    TEdit *XEdit;
    TEdit *YEdit;
    TButton *BtnConfirmarModificar;
    TButton *BtnConfirmarBaja;
    TMemo *MemoNodos;

    int ObtenerIdSeleccionado(TComboBox *combo);
    void CargarCombos();
    void MostrarMensaje(const String &mensaje);
    void LimpiarEdicion();
    void SetModoModificar(bool activo);
    void SetModoBaja(bool activo);
    void MarcarCambio();

    void __fastcall CiudadCBChange(TObject *Sender);
    void __fastcall AltaCiudadClick(TObject *Sender);
    void __fastcall ActivarModificarClick(TObject *Sender);
    void __fastcall ConfirmarModificarClick(TObject *Sender);
    void __fastcall ActivarBajaClick(TObject *Sender);
    void __fastcall ConfirmarBajaClick(TObject *Sender);
    void __fastcall CerrarClick(TObject *Sender);

public:
    __fastcall TFormNodos(TComponent* Owner, Grafo *grafo);
    bool TieneCambios();
};

#endif
