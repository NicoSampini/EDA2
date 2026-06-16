//---------------------------------------------------------------------------

#ifndef UIH
#define UIH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "Grafo.h"
#include <Vcl.Imaging.jpeg.hpp>

class TInterfazGrafica : public TForm
{
__published:	// IDE-managed Components
	TComboBox *OrigenCB;
	TComboBox *DestinoCB;
	TButton *BtnBuscar;
	TButton *BtnSalir;
	TLabel *Titulo;
	TLabel *TituloDatos;
	TImage *ImageMapa;
	void __fastcall BtnSalirClick(TObject *Sender);
	void __fastcall BtnBuscarClick(TObject *Sender);

private:	// User declarations
    Grafo g;
public:		// User declarations
	__fastcall TInterfazGrafica(TComponent* Owner);
    void DibujarMapa();
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfazGrafica *InterfazGrafica;
//---------------------------------------------------------------------------
#endif
