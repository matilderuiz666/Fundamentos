#ifndef HORARIOS_H
#define HORARIOS_H

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

void Menu();
void registrar(sqlite3* db, const string& contrasenha);
void mostrarHorario(sqlite3* db, const string& contrsenha);
void eliminarActividad(sqlite3* db, const string& contrasenha);

namespace base_datos {
    void horarios(sqlite3* db) {
        int opc;
        string contrasenha;
        
        cout << "\nIngrese su contrasenha de usuario: ";
        cin.ignore();
        getline(cin, contrasenha);

        do {
            Menu();
            cin >> opc;
            cout << "\n-----------------------------------";
            cin.ignore(); //limpiar el buffer de entrada
            switch (opc) {
                case 1:
                    registrar(db, contrasenha);
                    break;
                case 2:
                    mostrarHorario(db, contrasenha);
                    break;
                case 3:
                    eliminarActividad(db, contrasenha);
                    break;
                case 0:
                    cout << "Saliendo...";
                    break;
                default:
                    cout << "Esta opcion no está disponible.";
                    break;
            }
        } while (opc != 0);
        
    }
}

void Menu() {
    cout << "-----------------------------------";
    cout << "\nElija la opcion de su preferencia.";
    cout << "\n-----------------------------------";
    cout << "\n0. Salir";
    cout << "\n1. Registrar nueva consulta/actividad";
    cout << "\n2.Ver horario";
    cout << "\n3.Eliminar consulta/actividad";
    cout << "\nIngrese su opcion: ";
}

void registrar(sqlite3* db, const string& contrasenha) {
    string actividad, hora;
    cout << "\nIngrese el nombre de la actividad: ";
    getline(cin, actividad);
    cout << "Ingrese la hora (formato HH:MM): ";
    getline(cin, hora);

    // Construye la consulta SQL para insertar la actividad
    string sql = "INSERT INTO Horarios (PacienteCodigo, Actividad, Hora) VALUES ('" +
        contrasenha + "', '" + actividad + "', '" + hora + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al registrar la actividad: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Actividad registrada correctamente.\n";
    }
}

void mostrarHorario(sqlite3* db, const string& contrasenha) {
    string sql = "SELECT Actividad, Hora FROM Horarios WHERE PacienteCodigo = '" + contrasenha + "' ORDER BY Hora ASC;";
    sqlite3_stmt* stmt;

    // Prepara la consulta
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "\nHorario de actividades:\n";
    cout << "----------------------------------\n";

    // Ejecuta la consulta y muestra los resultados
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* actividad = sqlite3_column_text(stmt, 0);
        const unsigned char* hora = sqlite3_column_text(stmt, 1);
        cout << "Hora: " << hora << " | Actividad: " << actividad << endl;
    }

    cout << "----------------------------------\n";

    // Finaliza la consulta
    sqlite3_finalize(stmt);
}


void eliminarActividad(sqlite3* db, const string& contrasenha) {
    string actividad;
    cout << "\nIngrese el nombre de la actividad que desea eliminar: ";
    getline(cin, actividad);

    string sql = "DELETE FROM Horarios WHERE PacienteCodigo = '" + contrasenha + "' AND Actividad = '" + actividad + "';";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al eliminar la actividad: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Actividad eliminada correctamente.\n";
    }
}

#endif
