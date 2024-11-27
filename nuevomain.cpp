#include <iostream>
#include <fstream>
#include "Usuario.h"

using namespace std;
// Crear el archivo binario con datos de usuario
void crearArchivo();
// Pedir datos al usuario
void pedirDatos(Usuario& usuario);
// Verificar si el usuario y la contraseña coinciden con los almacenados en el archivo
bool verificarUsuario(const Usuario& usuarioIngresado);

int main() {
    // Paso 1: Crear el archivo binario con datos de usuario (solo se hace una vez)
    crearArchivo();

    // Paso 2: Pedir datos al usuario
    Usuario usuarioIngresado;
    pedirDatos(usuarioIngresado);

    // Paso 3: Verificar si el usuario y la contraseña coinciden
    if (verificarUsuario(usuarioIngresado)) {
        cout << "¡Acceso permitido!" << endl;
    }
    else {
        cout << "Usuario o contraseña incorrectos." << endl;
    }

    return 0;
}

void crearArchivo() {
    ofstream archivo("usuarios.dat", ios::binary);

    if (!archivo) {
        std::cout << "Error al abrir el archivo!" << std::endl;
        return;
    }

    Usuario usuario("matilde", "matilderuiz");
    usuario.escribirEnArchivo(archivo);

    archivo.close();
}

// Pedir datos al usuario
void pedirDatos(Usuario& usuario) {
    cout << "Ingrese su nombre de usuario: ";
    cin >> usuario.nombre;
    cout << "Ingrese su contraseña: ";
    cin >> usuario.contrasena;
}

// Verificar si el usuario y la contraseña coinciden con los almacenados en el archivo
bool verificarUsuario(const Usuario& usuarioIngresado) {
    ifstream archivo("usuarios.dat", std::ios::binary);

    if (!archivo) {
        cout << "Error al abrir el archivo!" << endl;
        return false;
    }

    Usuario usuarioAlmacenado = Usuario::leerDesdeArchivo(archivo);

    archivo.close();

    // Comparar los datos ingresados con los almacenados
    return (usuarioIngresado.nombre == usuarioAlmacenado.nombre &&
        usuarioIngresado.contrasena == usuarioAlmacenado.contrasena);
}
