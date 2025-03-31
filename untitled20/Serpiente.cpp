#include "Serpiente.h"

// Constructor de la serpiente
Serpiente::Serpiente(int startX, int startY) {
    x = startX;
    y = startY;
    longitud = 1;
}

// Movimiento de la serpiente
void Serpiente::mover(int dirX, int dirY) {
    for (int i = longitud - 1; i > 0; --i) {
        colaX[i] = colaX[i - 1];
        colaY[i] = colaY[i - 1];
    }

    if (longitud > 0) {
        colaX[0] = x;
        colaY[0] = y;
    }

    x += dirX;
    y += dirY;
}

// Aumentar la longitud
void Serpiente::crecer() {
    longitud++;
}

// Constructor del juego
Juego::Juego(int w, int h) {
    ancho = w;
    alto = h;
    puntaje = 0;
    juegoTerminado = false;
    serpiente = new Serpiente(w / 2, h / 2);

    // Inicia moviéndose hacia la derecha
    dirX = 1;
    dirY = 0;

    generarFruta();
}

// Destructor
Juego::~Juego() {
    delete serpiente;
}

// Generar fruta en posición aleatoria
void Juego::generarFruta() {
    frutaX = rand() % (ancho - 2) + 1;
    frutaY = rand() % (alto - 2) + 1;
}

// Dibujar el juego
void Juego::dibujar() {
    system("cls");

    for (int i = 0; i < ancho + 2; ++i) cout << "#";
    cout << endl;

    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            if (j == 0) cout << "#";

            if (i == serpiente->y && j == serpiente->x) {
                cout << "O";  // Cabeza
            } else if (i == frutaY && j == frutaX) {
                cout << "@";  // Fruta
            } else {
                bool imprimirCola = false;
                for (int k = 0; k < serpiente->longitud; ++k) {
                    if (serpiente->colaX[k] == j && serpiente->colaY[k] == i) {
                        cout << "o";  // Cola
                        imprimirCola = true;
                    }
                }
                if (!imprimirCola) cout << " ";
            }

            if (j == ancho - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < ancho + 2; ++i) cout << "#";
    cout << endl;

    cout << "Puntaje: " << puntaje << endl;
}

// Captura las teclas para cambiar la dirección
void Juego::capturarTecla() {
    if (_kbhit()) {
        switch (_getch()) {
            case 72: dirX = 0; dirY = -1; break;  // Flecha arriba
            case 80: dirX = 0; dirY = 1; break;   // Flecha abajo
            case 75: dirX = -1; dirY = 0; break;  // Flecha izquierda
            case 77: dirX = 1; dirY = 0; break;   // Flecha derecha
            case 'x': juegoTerminado = true; break;  // Salir
        }
    }
}

// Movimiento automático de la serpiente
void Juego::moverSerpiente() {
    serpiente->mover(dirX, dirY);
}

// Lógica del juego
void Juego::logica() {
    if (serpiente->x == frutaX && serpiente->y == frutaY) {
        puntaje += 10;
        serpiente->crecer();
        generarFruta();
    }

    if (serpiente->x < 0 || serpiente->x >= ancho || serpiente->y < 0 || serpiente->y >= alto) {
        juegoTerminado = true;
    }

    for (int i = 0; i < serpiente->longitud; ++i) {
        if (serpiente->x == serpiente->colaX[i] && serpiente->y == serpiente->colaY[i]) {
            juegoTerminado = true;
        }
    }
}

// Verificar si el juego ha terminado
bool Juego::estaTerminado() {
    return juegoTerminado;
}

// Obtener puntaje
int Juego::obtenerPuntaje() {
    return puntaje;
}

// Guardar puntajes en archivo
void Archivo::guardarPuntaje(const string& jugador, int puntaje) {
    ofstream archivo("puntajes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << jugador << " " << puntaje << endl;
        archivo.close();
    }
}

// Mostrar puntajes guardados
void Archivo::mostrarPuntajes() {
    ifstream archivo("puntajes.txt");
    string linea;
    if (archivo.is_open()) {
        cout << "--- Puntajes ---" << endl;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    }
}
