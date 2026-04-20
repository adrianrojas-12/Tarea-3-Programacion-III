

#ifndef TAREA3_ENTITY_H
#define TAREA3_ENTITY_H
#include <iostream>
#include <string>
using namespace std;


class Entity {
private:
    string name;
    int vida;
    int x,y;
    int nivel;
public:
    Entity(string n, int v);

    void move(int dx, int dy);
    void curar(int cantidad);
    void danio(int cantidad);
    void setLevel(int lvl);

    string getName() const;
    int getVida() const;
    string getStatus() const;

};


#endif //TAREA3_ENTITY_H