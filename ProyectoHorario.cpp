#include <iostream>
#include "sqlite3.h"
#include <string>
#include "DatabaseHorario.h" // Archivo que contiene la lógica de base de datos

using namespace std;

void mostrarMenu();
void registrarActividad(sqlite3* db, const string& contrasenha);
void mostrarHorario(sqlite3* db, const string& contrasenha);
void eliminarActividad(sqlite3* db, const string& contrasenha);

int main() {
    sqlite3* db;
    string dbName = "mi_base_de_datos.db";

    // Abrir la base de datos
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Crear la tabla de horarios si no existe
    crearTablaHorarios(db);

    string contrasenha;
    cout << "Ingrese su contrasenha de usuario: ";
    cin.ignore();
    getline(cin, contrasenha);
    system("cls");

    int opc;
    do {
        mostrarMenu();
        cin >> opc;
        system("cls");
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opc) {
        case 1:
            registrarActividad(db, contrasenha);
            break;
        case 2:
            mostrarHorario(db, contrasenha);
            break;
        case 3:
            eliminarActividad(db, contrasenha);
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción no valida. Por favor, intente nuevamente.\n";
            break;
        }
    } while (opc != 0);

    // Cerrar la base de datos
    sqlite3_close(db);
    return 0;
}

void mostrarMenu() {
    cout << "\t-----------------------------------\n";
    cout << "\tElija la opcion de su preferencia:\n";
    cout << "\t-----------------------------------\n";
    cout << "\t0. Salir\n";
    cout << "\t1. Registrar nueva consulta/actividad\n";
    cout << "\t2. Ver horario\n";
    cout << "\t3. Eliminar consulta/actividad\n";
    cout << "\nIngrese su opcion: ";
}

void registrarActividad(sqlite3* db, const string& contrasenha) {
    string actividad, hora;

    // Solicitar los datos de la actividad al usuario
    cout << "\nIngrese el nombre de la actividad: ";
    getline(cin, actividad);
    cout << "Ingrese la hora (formato HH:MM): ";
    getline(cin, hora);

    // Pasar los datos a la función de la base de datos
    bdRegistrar(db, contrasenha, actividad, hora);
}

void mostrarHorario(sqlite3* db, const string& contrasenha) {
    cout << "\nHorario de actividades \n";
    bdMostrar(db, contrasenha); // Llama a la función de la base de datos
}

// Función para eliminar una actividad
void eliminarActividad(sqlite3* db, const string& contrasenha) {
    string actividad;

    cout << "\n\nIngrese el nombre de la actividad que desea eliminar: ";
    getline(cin, actividad);

    bdEliminar(db, contrasenha, actividad);
}
