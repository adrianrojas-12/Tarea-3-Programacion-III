#ifndef TAREA3_COMMANDCENTER_H
#define TAREA3_COMMANDCENTER_H

#include <string>
#include <map>
#include <list>
#include <functional>
#include "Entity.h"
using namespace std;

using Command = std::function<void(const std::list<std::string>&)>;

class CommandCenter {
private:
    Entity& entidad;
    map<string, Command> comando;
    list<string> historial;
    map<string, list<pair<string, list<string>>>> macros;

public:
    CommandCenter(Entity& e);
    void registerCommand(const string& name, Command cmd);
    void execute(const string& name, const list<string>& args);
    void eliminarComando(const string& name);
    void registerMacro(const string& name,
                       const list<pair<string, list<string>>>& steps);
    void executeMacro(const string& name);
    void printHistorial() const;
};

#endif //TAREA3_COMMANDCENTER_H