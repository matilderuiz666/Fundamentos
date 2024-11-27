#include "Usuario.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor para inicializar el usuario
Usuario::Usuario(const string& nombre, const string& contrasena)
    : nombre(nombre), contrasena(contrasena) {}

// Mostrar los datos del usuario
void Usuario::mostrarDatos() const {
    cout << "Usuario: " << nombre << endl;
    cout << "Contraseña: " << contrasena << endl;
}

// Escribir los datos del usuario en un archivo binario
void Usuario::escribirEnArchivo(ofstream& archivo) const {
    size_t tamNombre = nombre.size();
    size_t tamContrasena = contrasena.size();

    archivo.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
    archivo.write(nombre.c_str(), tamNombre);

    archivo.write(reinterpret_cast<const char*>(&tamContrasena), sizeof(tamContrasena));
    archivo.write(contrasena.c_str(), tamContrasena);
}

// Leer los datos de un usuario desde un archivo binario
Usuario Usuario::leerDesdeArchivo(ifstream& archivo) {
    size_t tamNombre, tamContrasena;
    string nombre, contrasena;

    archivo.read(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
    nombre.resize(tamNombre);
    archivo.read(&nombre[0], tamNombre);

    archivo.read(reinterpret_cast<char*>(&tamContrasena), sizeof(tamContrasena));
    contrasena.resize(tamContrasena);
    archivo.read(&contrasena[0], tamContrasena);

    return Usuario(nombre, contrasena);
}
