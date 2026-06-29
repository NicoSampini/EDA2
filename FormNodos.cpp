#include <vcl.h>
#pragma hdrstop

#include "FormNodos.h"
#include <System.SysUtils.hpp>

#pragma package(smart_init)

namespace
{
    const TColor COLOR_FONDO = TColor(0x00AAB2B8); // #B8B2AA
    const TColor COLOR_CAMPO = TColor(0x00F4F5F6); // #F6F5F4
    const TColor COLOR_TEXTO = TColor(0x002C2F31); // #312F2C

    void EstilizarControl(TControl *control)
    {
        if (TButton *boton = dynamic_cast<TButton*>(control))
        {
            boton->Font->Color = COLOR_TEXTO;
            boton->Font->Name = "Segoe UI";
            boton->ParentFont = false;
            return;
        }

        if (TComboBox *combo = dynamic_cast<TComboBox*>(control))
        {
            combo->Color = COLOR_CAMPO;
            combo->Font->Color = COLOR_TEXTO;
            combo->Font->Name = "Segoe UI";
            combo->ParentFont = false;
            return;
        }

        if (TEdit *edit = dynamic_cast<TEdit*>(control))
        {
            edit->Color = COLOR_CAMPO;
            edit->Font->Color = COLOR_TEXTO;
            edit->Font->Name = "Segoe UI";
            edit->ParentFont = false;
            return;
        }

        if (TMemo *memo = dynamic_cast<TMemo*>(control))
        {
            memo->Color = COLOR_CAMPO;
            memo->Font->Color = COLOR_TEXTO;
            memo->Font->Name = "Segoe UI";
            memo->ParentFont = false;
            return;
        }

        if (TGroupBox *grupo = dynamic_cast<TGroupBox*>(control))
        {
            grupo->Color = COLOR_FONDO;
            grupo->Font->Color = COLOR_TEXTO;
            grupo->Font->Name = "Segoe UI";
            grupo->ParentFont = false;
            return;
        }

        if (TLabel *label = dynamic_cast<TLabel*>(control))
        {
            label->Font->Color = COLOR_TEXTO;
            label->Font->Name = "Segoe UI";
            label->ParentFont = false;
        }
    }

    void EstilizarFormulario(TWinControl *contenedor)
    {
        for (int i = 0; i < contenedor->ControlCount; i++)
        {
            TControl *control = contenedor->Controls[i];
            EstilizarControl(control);

            if (TWinControl *hijo = dynamic_cast<TWinControl*>(control))
            {
                EstilizarFormulario(hijo);
            }
        }
    }
}

__fastcall TFormNodos::TFormNodos(TComponent* Owner, Grafo *grafo)
    : TForm(Owner, 0)
{
    g = grafo;
    huboCambios = false;

    Caption = "Administrar ciudades";
    Width = 430;
    Height = 470;
    Position = poOwnerFormCenter;
    BorderStyle = bsDialog;
    Color = COLOR_FONDO;
    Font->Color = COLOR_TEXTO;
    Font->Name = "Segoe UI";

    TGroupBox *grupoAlta = new TGroupBox(this);
    grupoAlta->Parent = this;
    grupoAlta->Left = 16;
    grupoAlta->Top = 16;
    grupoAlta->Width = 392;
    grupoAlta->Height = 128;
    grupoAlta->Caption = "Alta de ciudad";

    TLabel *altaLabel = new TLabel(this);
    altaLabel->Parent = grupoAlta;
    altaLabel->Left = 16;
    altaLabel->Top = 28;
    altaLabel->Caption = "Ciudad disponible";

    AltaCiudadCB = new TComboBox(this);
    AltaCiudadCB->Parent = grupoAlta;
    AltaCiudadCB->Left = 16;
    AltaCiudadCB->Top = 50;
    AltaCiudadCB->Width = 232;
    AltaCiudadCB->Style = csDropDownList;

    TLabel *altaXLabel = new TLabel(this);
    altaXLabel->Parent = grupoAlta;
    altaXLabel->Left = 16;
    altaXLabel->Top = 82;
    altaXLabel->Caption = "X";

    AltaXEdit = new TEdit(this);
    AltaXEdit->Parent = grupoAlta;
    AltaXEdit->Left = 36;
    AltaXEdit->Top = 78;
    AltaXEdit->Width = 64;
    AltaXEdit->Text = "200";

    TLabel *altaYLabel = new TLabel(this);
    altaYLabel->Parent = grupoAlta;
    altaYLabel->Left = 116;
    altaYLabel->Top = 82;
    altaYLabel->Caption = "Y";

    AltaYEdit = new TEdit(this);
    AltaYEdit->Parent = grupoAlta;
    AltaYEdit->Left = 136;
    AltaYEdit->Top = 78;
    AltaYEdit->Width = 64;
    AltaYEdit->Text = "200";

    TButton *altaCiudad = new TButton(this);
    altaCiudad->Parent = grupoAlta;
    altaCiudad->Left = 264;
    altaCiudad->Top = 66;
    altaCiudad->Width = 104;
    altaCiudad->Height = 27;
    altaCiudad->Caption = "Dar de alta";
    altaCiudad->OnClick = AltaCiudadClick;

    TGroupBox *grupoGestion = new TGroupBox(this);
    grupoGestion->Parent = this;
    grupoGestion->Left = 16;
    grupoGestion->Top = 156;
    grupoGestion->Width = 392;
    grupoGestion->Height = 164;
    grupoGestion->Caption = "Modificar o dar de baja";

    TButton *activarModificar = new TButton(this);
    activarModificar->Parent = grupoGestion;
    activarModificar->Left = 16;
    activarModificar->Top = 28;
    activarModificar->Width = 112;
    activarModificar->Height = 27;
    activarModificar->Caption = "Modificar";
    activarModificar->OnClick = ActivarModificarClick;

    TButton *activarBaja = new TButton(this);
    activarBaja->Parent = grupoGestion;
    activarBaja->Left = 136;
    activarBaja->Top = 28;
    activarBaja->Width = 112;
    activarBaja->Height = 27;
    activarBaja->Caption = "Baja";
    activarBaja->OnClick = ActivarBajaClick;

    CiudadCB = new TComboBox(this);
    CiudadCB->Parent = grupoGestion;
    CiudadCB->Left = 16;
    CiudadCB->Top = 68;
    CiudadCB->Width = 232;
    CiudadCB->Style = csDropDownList;
    CiudadCB->Enabled = false;
    CiudadCB->OnChange = CiudadCBChange;

    BtnConfirmarModificar = new TButton(this);
    BtnConfirmarModificar->Parent = grupoGestion;
    BtnConfirmarModificar->Left = 264;
    BtnConfirmarModificar->Top = 66;
    BtnConfirmarModificar->Width = 104;
    BtnConfirmarModificar->Height = 27;
    BtnConfirmarModificar->Caption = "Guardar";
    BtnConfirmarModificar->Enabled = false;
    BtnConfirmarModificar->OnClick = ConfirmarModificarClick;

    BtnConfirmarBaja = new TButton(this);
    BtnConfirmarBaja->Parent = grupoGestion;
    BtnConfirmarBaja->Left = 264;
    BtnConfirmarBaja->Top = 66;
    BtnConfirmarBaja->Width = 104;
    BtnConfirmarBaja->Height = 27;
    BtnConfirmarBaja->Caption = "Confirmar";
    BtnConfirmarBaja->Enabled = false;
    BtnConfirmarBaja->Visible = false;
    BtnConfirmarBaja->OnClick = ConfirmarBajaClick;

    TLabel *nombreLabel = new TLabel(this);
    nombreLabel->Parent = grupoGestion;
    nombreLabel->Left = 16;
    nombreLabel->Top = 104;
    nombreLabel->Caption = "Nombre";

    NombreEdit = new TEdit(this);
    NombreEdit->Parent = grupoGestion;
    NombreEdit->Left = 16;
    NombreEdit->Top = 124;
    NombreEdit->Width = 152;
    NombreEdit->Enabled = false;

    TLabel *xLabel = new TLabel(this);
    xLabel->Parent = grupoGestion;
    xLabel->Left = 184;
    xLabel->Top = 104;
    xLabel->Caption = "X";

    XEdit = new TEdit(this);
    XEdit->Parent = grupoGestion;
    XEdit->Left = 184;
    XEdit->Top = 124;
    XEdit->Width = 72;
    XEdit->Enabled = false;

    TLabel *yLabel = new TLabel(this);
    yLabel->Parent = grupoGestion;
    yLabel->Left = 272;
    yLabel->Top = 104;
    yLabel->Caption = "Y";

    YEdit = new TEdit(this);
    YEdit->Parent = grupoGestion;
    YEdit->Left = 272;
    YEdit->Top = 124;
    YEdit->Width = 72;
    YEdit->Enabled = false;

    MemoNodos = new TMemo(this);
    MemoNodos->Parent = this;
    MemoNodos->Left = 16;
    MemoNodos->Top = 332;
    MemoNodos->Width = 392;
    MemoNodos->Height = 48;
    MemoNodos->ReadOnly = true;

    TButton *cerrar = new TButton(this);
    cerrar->Parent = this;
    cerrar->Left = 288;
    cerrar->Top = 388;
    cerrar->Width = 120;
    cerrar->Height = 27;
    cerrar->Caption = "Cerrar";
    cerrar->OnClick = CerrarClick;

    EstilizarFormulario(this);
    CargarCombos();
}

bool TFormNodos::TieneCambios()
{
    return huboCambios;
}

int TFormNodos::ObtenerIdSeleccionado(TComboBox *combo)
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

void TFormNodos::CargarCombos()
{
    AltaCiudadCB->Items->Clear();
    CiudadCB->Items->Clear();

    for (int i = 0; i < NODOS_CANTIDAD; i++)
    {
        Nodo nodo = g->enviarNodo(i);
        String item = IntToStr(i) + " - " + String(nodo.nombre);

        if (g->esNodoActivo(i))
        {
            CiudadCB->Items->Add(item);
        }
        else if (String(nodo.nombre) != "")
        {
            AltaCiudadCB->Items->Add(item);
        }
    }

    AltaCiudadCB->ItemIndex = -1;
    CiudadCB->ItemIndex = -1;
    AltaXEdit->Text = "200";
    AltaYEdit->Text = "200";
    LimpiarEdicion();
}

void TFormNodos::MostrarMensaje(const String &mensaje)
{
    MemoNodos->Lines->Clear();
    MemoNodos->Lines->Add(mensaje);
}

void TFormNodos::LimpiarEdicion()
{
    NombreEdit->Text = "";
    XEdit->Text = "";
    YEdit->Text = "";
}

void TFormNodos::SetModoModificar(bool activo)
{
    CiudadCB->Enabled = activo;
    NombreEdit->Enabled = activo;
    XEdit->Enabled = activo;
    YEdit->Enabled = activo;
    BtnConfirmarModificar->Visible = true;
    BtnConfirmarModificar->Enabled = activo;
    BtnConfirmarBaja->Visible = false;
    BtnConfirmarBaja->Enabled = false;
    CiudadCB->ItemIndex = -1;
    LimpiarEdicion();
}

void TFormNodos::SetModoBaja(bool activo)
{
    CiudadCB->Enabled = activo;
    NombreEdit->Enabled = false;
    XEdit->Enabled = false;
    YEdit->Enabled = false;
    BtnConfirmarModificar->Visible = false;
    BtnConfirmarModificar->Enabled = false;
    BtnConfirmarBaja->Visible = true;
    BtnConfirmarBaja->Enabled = activo;
    CiudadCB->ItemIndex = -1;
    LimpiarEdicion();
}

void TFormNodos::MarcarCambio()
{
    huboCambios = true;
}

void __fastcall TFormNodos::CiudadCBChange(TObject *Sender)
{
    int id = ObtenerIdSeleccionado(CiudadCB);
    if (id == -1)
    {
        return;
    }

    Nodo nodo = g->enviarNodo(id);
    NombreEdit->Text = String(nodo.nombre);
    XEdit->Text = IntToStr(nodo.xPX);
    YEdit->Text = IntToStr(nodo.yPX);
}

void __fastcall TFormNodos::AltaCiudadClick(TObject *Sender)
{
    int id = ObtenerIdSeleccionado(AltaCiudadCB);
    if (id == -1)
    {
        MostrarMensaje("Seleccione una ciudad disponible para dar de alta.");
        return;
    }

    g->activarNodo(id, StrToIntDef(AltaXEdit->Text, 200), StrToIntDef(AltaYEdit->Text, 200));
    MarcarCambio();

    String nombre = String(g->enviarNodo(id).nombre);
    CargarCombos();
    MostrarMensaje("Ciudad dada de alta: " + IntToStr(id) + " - " + nombre);
}

void __fastcall TFormNodos::ActivarModificarClick(TObject *Sender)
{
    SetModoModificar(true);
    MostrarMensaje("Seleccione una ciudad activa para modificar.");
}

void __fastcall TFormNodos::ConfirmarModificarClick(TObject *Sender)
{
    int id = ObtenerIdSeleccionado(CiudadCB);
    if (id == -1)
    {
        MostrarMensaje("Seleccione una ciudad activa.");
        return;
    }

    if (NombreEdit->Text.Trim() == "")
    {
        MostrarMensaje("El nombre de la ciudad no puede estar vacio.");
        return;
    }

    Nodo nodoActual = g->enviarNodo(id);
    g->modificarNodo(id,
                     AnsiString(NombreEdit->Text).c_str(),
                     nodoActual.x,
                     nodoActual.y,
                     StrToIntDef(XEdit->Text, nodoActual.xPX),
                     StrToIntDef(YEdit->Text, nodoActual.yPX));
    MarcarCambio();

    String nombre = NombreEdit->Text;
    CargarCombos();
    SetModoModificar(false);
    MostrarMensaje("Ciudad modificada: " + IntToStr(id) + " - " + nombre);
}

void __fastcall TFormNodos::ActivarBajaClick(TObject *Sender)
{
    SetModoBaja(true);
    MostrarMensaje("Seleccione una ciudad activa para dar de baja.");
}

void __fastcall TFormNodos::ConfirmarBajaClick(TObject *Sender)
{
    int id = ObtenerIdSeleccionado(CiudadCB);
    if (id == -1)
    {
        MostrarMensaje("Seleccione una ciudad activa.");
        return;
    }

    String nombre = String(g->enviarNodo(id).nombre);
    g->bajaNodo(id);
    MarcarCambio();

    CargarCombos();
    SetModoBaja(false);
    MostrarMensaje("Ciudad dada de baja: " + IntToStr(id) + " - " + nombre);
}

void __fastcall TFormNodos::CerrarClick(TObject *Sender)
{
    Close();
}
