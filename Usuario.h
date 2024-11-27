#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
public:
    string nombre;       // Nombre de usuario
    string contrasena;   // Contraseña del usuario


    // Constructor para inicializar el usuario
    Usuario(const string& nombre = "", const string& contrasena = "");

    // Métodos para mostrar los datos (usados solo para depuración)
    void mostrarDatos() const;

    // Métodos para leer y escribir en un archivo binario
    void escribirEnArchivo(ofstream& archivo) const;
    static Usuario leerDesdeArchivo(ifstream& archivo);
};

#endif
