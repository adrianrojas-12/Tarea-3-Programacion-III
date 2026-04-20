#include "CommandCenter.h"
#include <iostream>

using namespace std;

CommandCenter::CommandCenter(Entity& e) : entidad(e) {}

void CommandCenter::registerCommand(const string& name, Command cmd) {
    comando[name] = cmd;
}

void CommandCenter::execute(const string& name, const list<string>& args) {
    map<string, Command>::iterator iterador = comando.find(name);

    if (iterador == comando.end()) {
        cout << "[ERROR] Comando no encontrado: " << name << endl;
        historial.push_back("ERROR: '" + name + "' no existe");
        return;
    }

    string antes = entidad.getStatus();
    iterador->second(args);
    string despues = entidad.getStatus();

    string registro = "Comando: " + name + " | " + antes + " -> " + despues;
    historial.push_back(registro);
}

void CommandCenter::eliminarComando(const string& name) {
    map<string, Command>::iterator iterador = comando.find(name);

    if (iterador == comando.end()) {
        cout << "[WARN] Comando no existe: " << name << endl;
        return;
    }

    comando.erase(iterador);
    cout << "[INFO] Comando eliminado: " << name << endl;
}

void CommandCenter::registerMacro(const string& name, const list<pair<string, list<string>>>& steps) {
    macros[name] = steps;
}

void CommandCenter::executeMacro(const string& name) {
    map<string, list<pair<string, list<string>>>>::iterator macroIterador = macros.find(name);

    if (macroIterador == macros.end()) {
        cout << "[ERROR] Macro no encontrado: " << name << endl;
        return;
    }

    list<pair<string, list<string>>>::iterator stepIterador = macroIterador->second.begin();
    while (stepIterador != macroIterador->second.end()) {
        map<string, Command>::iterator cmdIt = comando.find(stepIterador->first);

        if (cmdIt == comando.end()) {
            cout << "[ERROR] Macro detenido: '" << stepIterador->first << "' no existe" << endl;
            return;
        }

        execute(stepIterador->first, stepIterador->second);
        ++stepIterador;
    }
}

void CommandCenter::printHistorial() const {
    list<string>::const_iterator iterador = historial.begin();
    while (iterador != historial.end()) {
        cout << " - " << *iterador << endl;
        ++iterador;
    }
}