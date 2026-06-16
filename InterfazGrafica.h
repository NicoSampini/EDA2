//---------------------------------------------------------------------------

#ifndef InterfazGraficaH
#define InterfazGraficaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TInterfazDeUsuario : public TForm
{
__published:	// IDE-managed Components
	TComboBox *Destino1;
	TComboBox *Destino2;
	TButton *BtnBuscar;
	TButton *BtnSalir;
	TImage *Image1;
	TLabel *Titulo;
	TLabel *datos;
	void __fastcall BtnSalirClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TInterfazDeUsuario(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfazDeUsuario *InterfazDeUsuario;
//---------------------------------------------------------------------------
#endif
