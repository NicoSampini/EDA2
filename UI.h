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
	TButton *CortarRutaBtn;
	TLabel *RioTercero;
	TLabel *BellVille;
	TMemo *MemoDatos;
	void __fastcall BtnSalirClick(TObject *Sender);
	void __fastcall BtnBuscarClick(TObject *Sender);
	void __fastcall CortarRutaBtnClick(TObject *Sender);
	void __fastcall BtnAdministrarNodosClick(TObject *Sender);
	void __fastcall BtnAdministrarConexionesClick(TObject *Sender);
private:	// User declarations
    Grafo g;
    int ObtenerIdSeleccionado(TComboBox *combo);
    void GuardarDatos();
    void CrearBotonesAdministrar();
    void RefrescarDespuesDeAdministrar(const String &mensaje);
public:		// User declarations
	__fastcall TInterfazGrafica(TComponent* Owner);
    void DibujarMapa(char color, int destino1, int destino2);
    void CargarCombo();
    void InicializarMapa();
    void LimpiarMapa();
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfazGrafica *InterfazGrafica;
//---------------------------------------------------------------------------
#endif
