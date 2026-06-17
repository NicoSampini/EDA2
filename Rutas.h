//---------------------------------------------------------------------------

#ifndef RutasH
#define RutasH

#define RUTAS_CANTIDAD 8

class Rutas{
    private:
        int matrizRutas[RUTAS_CANTIDAD][RUTAS_CANTIDAD];
    public:
    	Rutas();
        void ActualizarRuta(int origen, int destino, int creada);
        int ConsultarRuta(int origen, int destino);
};

//---------------------------------------------------------------------------
#endif
