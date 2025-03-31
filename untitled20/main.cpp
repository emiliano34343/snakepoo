#include "Serpiente.h"

int main() {
    srand(time(0));

    string nombreJugador;
    cout << "Ingrese su nombre: ";
    cin >> nombreJugador;

    Juego juego(20, 15);

    while (!juego.estaTerminado()) {
        juego.dibujar();
        juego.capturarTecla();
        juego.moverSerpiente();  // Movimiento automático
        juego.logica();
        Sleep(150);  // Ajusta la velocidad
    }

    cout << "Juego terminado! Puntaje final: " << juego.obtenerPuntaje() << endl;

    Archivo::guardarPuntaje(nombreJugador, juego.obtenerPuntaje());
    Archivo::mostrarPuntajes();

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.