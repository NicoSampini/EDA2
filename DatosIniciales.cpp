#include "DatosIniciales.h"

void cargarDatosIniciales(Grafo &g)
{
    g.setearNodo(0, "Cordoba", 350, 120, 205, 178);
    g.setearNodo(1, "Villa Maria", 500, 280, 292, 286);
    g.setearNodo(2, "Rio Cuarto", 420, 500, 170, 410);
    g.setearNodo(3, "Carlos Paz", 250, 140, 145, 185);
    g.setearNodo(4, "San Francisco", 700, 80, 333, 188);
    g.setearNodo(5, "Bell Ville", 620, 260, 295, 355);
    g.setearNodo(6, "Alta Gracia", 300, 220, 160, 255);
    g.setearNodo(7, "Rio Tercero", 420, 320, 230, 315);

    g.conectar(0, 1, 140); // Cordoba - Villa Maria
    g.conectar(0, 3, 35);  // Cordoba - Carlos Paz
    g.conectar(0, 4, 210); // Cordoba - San Francisco
    g.conectar(0, 6, 40);  // Cordoba - Alta Gracia
    g.conectar(0, 7, 110); // Cordoba - Rio Tercero

    g.conectar(1, 2, 220); // Villa Maria - Rio Cuarto
    g.conectar(1, 4, 150); // Villa Maria - San Francisco
    g.conectar(1, 5, 65);  // Villa Maria - Bell Ville
    g.conectar(1, 7, 100); // Villa Maria - Rio Tercero

    g.conectar(2, 3, 190); // Rio Cuarto - Carlos Paz
    g.conectar(2, 5, 180); // Rio Cuarto - Bell Ville
    g.conectar(2, 7, 140); // Rio Cuarto - Rio Tercero

    g.conectar(3, 6, 40);  // Carlos Paz - Alta Gracia
    g.conectar(4, 5, 170); // San Francisco - Bell Ville
    g.conectar(5, 7, 120); // Bell Ville - Rio Tercero
    g.conectar(6, 7, 90);  // Alta Gracia - Rio Tercero

    g.bajaNodo(2); // Rio Cuarto queda disponible para alta controlada
    g.bajaNodo(4); // San Francisco queda disponible para alta controlada
}
