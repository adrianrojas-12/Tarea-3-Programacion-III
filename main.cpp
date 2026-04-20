#include <iostream>
#include <vector>
#include "Entity.h"
#include "CommandCenter.h"
using namespace std;

void moverLibre(Entity& e, const list<string>& args) {
    if (args.size() < 2) {
        cout << "[ERROR] Mover requiere x e y" << endl;
        return;
    }
    try {
        e.move(stoi(args.front()), stoi(*next(args.begin())));
    } catch (...) { cout << "[ERROR] Argumentos invalidos en moverLibre" << endl; }
}

void curarlibre(Entity& e, const list<string>& args) {
    if (args.empty()) {
        cout << "[ERROR] Curar requiere un valor" << endl;
        return;
    }
    try {
        e.curar(stoi(args.front()));
    } catch (...) {
        cout << "[ERROR] Argumentos invalidos en curarlibre" << endl;
    }
}

void subirNivelLibre(Entity& e, const list<string>& args) {
    if (args.empty()) return;
    try {
        e.setLevel(stoi(args.front()));
    } catch (...) {cout << "[ERROR] Nivel invalido" << endl; }
}

class ContadorDanio {
private:
    int totalUsos = 0;
    Entity& ent;
public:
    ContadorDanio(Entity& e) : ent(e) {}
    void operator() (const list<string>& args) {
        if  (args.empty()) return;
        try {
            ent.danio(stoi(args.front()));
            totalUsos++;
            cout << "[Functor] Ataque realizados: " << totalUsos << endl;
        }catch (...) {}
    }
};

class RegistroTeleport {
private:
    int saltos=0;
    Entity& ent;
public:
    RegistroTeleport(Entity& e) : ent(e) {}
    void operator() (const list<string>& args) {
        ent.move(100,100);
        saltos++;
        cout << "[Functor] Teletransportes: " << saltos << endl;
    }
};


class LoggerEntidad {
    public:
        void operator()(const list <string>& args) {
            cout << "Consultando datos de la entidad..." << endl;
        }
};

int main() {
    //1
    Entity heroe("Ticlla", 100);
    CommandCenter cc(heroe);
    //2
    cc.registerCommand("move", bind(moverLibre, ref(heroe), placeholders::_1));
    cc.registerCommand("heal", bind(curarlibre, ref(heroe), placeholders::_1));
    //3
    cc.registerCommand("status", [&](const list<string>& args) {
        cout << "Estado actual: " << heroe.getStatus() << endl;
    });
    cc.registerCommand("reset_hp", [&] (const list<string>& args){
        heroe.curar(100);
        cout << "HP restaurado." << endl;
    });
    cc.registerCommand("quick_move", [&](const list<string>& args) {
        heroe.move(1, 1);
    });
    //4
    cc.registerCommand("damage", ContadorDanio(heroe));
    cc.registerCommand("teleport", RegistroTeleport(heroe));
    cc.registerCommand("log", LoggerEntidad());
    //5
    list<pair<string, list<string>>> pasos1 = {{"heal", {"50"}}, {"status", {}}};
    cc.registerMacro("full_buff", pasos1);

    list<pair<string, list<string>>> pasos2 = {{"move", {"10", "10"}}, {"damage", {"15"}}, {"status", {}}};
    cc.registerMacro("atacar_y_mover", pasos2);

    list<pair<string, list<string>>> pasos3 = {{"teleport", {}}, {"set_lvl", {"5"}}, {"log", {}}};
    cc.registerMacro("evolucionar", pasos3);
    //6
    cout << "--- PRUEBAS DE COMANDOS ---" << endl;
    cc.execute("move", {"20", "30"});
    cc.execute("heal", {"no_numero"}); // Prueba de error de validación
    cc.execute("comando_inexistente", {}); // Prueba de comando no encontrado

    cout << "\n--- PRUEBAS DE MACROS ---" << endl;
    cc.executeMacro("full_buff");
    cc.executeMacro("evolucionar");
    cc.executeMacro("macro_inexistente"); // Prueba de error de macro

    cout << "\n--- ELIMINACION DINAMICA ---" << endl;
    cc.eliminarComando("teleport");
    cc.execute("teleport", {}); // Debe reportar error
    //7
    cout << "\n--- ESTADO FINAL DEL SISTEMA ---" << endl;
    cout << "Nombre: " << heroe.getName() << " | " << heroe.getStatus() << endl;

    cout << "\n--- HISTORIAL COMPLETO ---" << endl;
    cc.printHistorial();
}
