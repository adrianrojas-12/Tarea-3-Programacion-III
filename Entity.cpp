//
// Created by PC on 19/04/2026.
//

#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity(string n, int h) : name(n), vida(h), x(0), y(0), nivel(1) {}

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::curar(int cantidad) {
    vida += cantidad;
}

void Entity::danio(int cantidad) {
    vida -= cantidad;
}

string Entity::getName() const {
    return name;
}

int Entity::getVida() const {
    return vida;
}

void Entity::setLevel(int lvl) {
    this -> nivel = lvl;
}

string Entity::getStatus() const {
    return "HP: " + to_string(vida) + "| Pos: (" + to_string(x) + "," + to_string(y) + ")";
}