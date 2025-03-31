#ifndef SERPIENTE_H
#define SERPIENTE_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

// Clase que representa la serpiente
class Serpiente {
public:
    int x, y;                     // Posición de la cabeza
    int longitud;                  // Tamaño de la serpiente
    int colaX[100], colaY[100];    // Coordenadas de la cola

    Serpiente(int startX, int startY);
    void mover(int dirX, int dirY);
    void crecer();
};

// Clase del juego
class Juego {
private:
    int ancho, alto;               // Dimensiones del tablero
    int frutaX, frutaY;            // Posición de la fruta
    int puntaje;                    // Puntuación actual
    bool juegoTerminado;            // Estado del juego
    Serpiente* serpiente;           // Puntero a la serpiente
    int dirX, dirY;                 // Dirección actual de la serpiente

public:
    Juego(int w, int h);
    ~Juego();

    void generarFruta();
    void dibujar();
    void capturarTecla();
    void moverSerpiente();          // Nueva función para movimiento continuo
    void logica();
    bool estaTerminado();
    int obtenerPuntaje();
};

// Clase para manejar los archivos
class Archivo {
public:
    static void guardarPuntaje(const string& jugador, int puntaje);
    static void mostrarPuntajes();
};

#endif
