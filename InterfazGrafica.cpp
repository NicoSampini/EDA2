//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InterfazGrafica.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfazDeUsuario *InterfazDeUsuario;
//---------------------------------------------------------------------------
__fastcall TInterfazDeUsuario::TInterfazDeUsuario(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInterfazDeUsuario::BtnSalirClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
