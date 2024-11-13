// main.cpp
#include <iostream>
#include "funciones.h"  // Incluir el archivo de cabecera

using  namespace std;

int main() {
    // Llamar a las funciones definidas en funciones.cpp
    saludar();  // Llama a la función saludar

    int resultado = suma(5, 3);  // Llama a la función sumar
    cout << "El resultado de la suma es: " << resultado << endl;
    int result = multiplicar(5, 3);  // Llama a la función sumar
    cout << "El resultado de la multiplicacion es: " << result << endl;
    int resulta = restar(5, 3);  // Llama a la función sumar
    cout << "El resultado de la resta es: " << resulta << endl;

    return 0;
}
