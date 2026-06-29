# Manual de Usuario - Proyecto Cordoba

## 1. Para que sirve

El programa permite buscar la ruta mas corta entre ciudades de Cordoba. Tambien permite cortar rutas, restaurarlas y administrar ciudades o conexiones.

## 2. Archivos necesarios

Para usarlo, en la carpeta deben estar:

```text
ProyectoCordobaUI.exe
mapaCordoba3.jpg
```

Opcionales:

```text
nodos.dat
matriz.dat
Historial.txt
```

## 3. Como abrirlo

1. Entrar a la carpeta del programa.
2. Hacer doble click en `ProyectoCordobaUI.exe`.
3. Se abre la pantalla principal con el mapa.

## 4. Pantalla principal

| Parte | Uso |
| --- | --- |
| `Origen` | Ciudad desde donde empieza el recorrido. |
| `Destino` | Ciudad a donde se quiere llegar. |
| `Buscar` | Calcula la ruta mas corta. |
| `Cortar/restaurar ruta` | Cambia el estado de una ruta directa. |
| `Administrar ciudades` | Abre el ABM de ciudades. |
| `Administrar conexiones` | Abre el ABM de conexiones. |
| `Salir` | Guarda y cierra. |

## 5. Colores del mapa

| Color | Significado |
| --- | --- |
| Negro | Ruta activa |
| Rojo | Ruta cortada |
| Azul | Ruta calculada |
| Circulo blanco | Ciudad activa |

## 6. Buscar una ruta

1. Elegir una ciudad en `Origen`.
2. Elegir una ciudad en `Destino`.
3. Presionar `Buscar`.

El sistema muestra la distancia total y las ciudades del recorrido.

## 7. Cortar una ruta

1. Elegir origen y destino.
2. Presionar `Cortar/restaurar ruta`.

Si habia una ruta directa, queda cortada y se ve roja. Mientras este cortada, no se usa para calcular recorridos.

## 8. Restaurar una ruta

Para restaurar una ruta roja:

1. Elegir las mismas dos ciudades.
2. Presionar `Cortar/restaurar ruta`.

La ruta vuelve a estar activa.

## 9. Administrar ciudades

Entrar desde `Administrar ciudades`.

Se puede:

- dar de alta una ciudad disponible;
- modificar nombre o coordenadas;
- dar de baja una ciudad.

Para modificar o dar de baja, primero se presiona el boton correspondiente y despues se elige la ciudad.

## 10. Administrar conexiones

Entrar desde `Administrar conexiones`.

Se puede:

- agregar una conexion;
- modificar distancia;
- eliminar una conexion.

La distancia debe ser un numero positivo.

## 11. Guardado

Los cambios se guardan en:

- `nodos.dat`;
- `matriz.dat`;
- `Historial.txt`.

Lo recomendable es cerrar siempre con el boton `Salir`.

## 12. Problemas comunes

| Problema | Posible solucion |
| --- | --- |
| No aparece el mapa | Revisar que este `mapaCordoba3.jpg`. |
| No aparece una ciudad | Puede estar dada de baja. |
| No se encuentra camino | Puede haber rutas cortadas o conexiones eliminadas. |
| No agrega conexion | Revisar que origen y destino sean distintos y distancia positiva. |

## 13. Flujo rapido

```text
Abrir programa
Elegir origen y destino
Buscar ruta
Ver resultado
Modificar rutas si hace falta
Salir
```

