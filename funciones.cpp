// funciones.cpp
#include <iostream>
#include "funciones.h"  // Incluir el archivo de cabecera, si no se incluye no va a reconocer a saludar ni a sumar

using namespace std;

// Definición de la función saludar
void saludar() {
    cout << "¡Hola desde el archivo funciones.cpp!" << endl;
}

// Definición de la función sumar
int suma(int a, int b) {
    return a + b;
}
int multiplicar(int a, int b) {
    return a * b;
}
int restar(int a, int b) {
    return a - b;
}
