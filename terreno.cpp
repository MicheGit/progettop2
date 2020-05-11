//
// Created by chrim on 14/04/2020.
//

#include "terreno.h"

short Terreno::costoAttraversamento() const {
    return costoEntrata() + costoUscita();
}

bool Terreno::addCreatura(Creatura * creatura) {
    if (creatura) {
        return _creature.insert(creatura);
    } else {
        return false;
    }
}

Creatura* Terreno::removeCreatura(Creatura * creatura) {
    if (creatura) {
        return _creature.remove(creatura);
    } else {
        return nullptr;
    }
}

Creatura** Terreno::getAllCreatures() const {
    Creatura** ritorno = new Creatura*[_creature.length()]();
    for (int i = 0; i < _creature.length(); i++) {
        ritorno[i] = _creature[i];
    }
    return ritorno;
}

bool Terreno::canPass(int points) const {
    return points >= costoAttraversamento();
}

bool Terreno::canEnter(int points) const {
    return points >= costoEntrata();
}

short Piana::costoEntrata() const {
    return 0;
}

short Piana::costoUscita() const {
    return 1;
}

short Fango::costoUscita() const {
    return 2;
}

short Fango::costoEntrata() const {
    return 0;
}

short Muro::costoUscita() const {
    return 0;
}

short Muro::costoEntrata() const {
    return 0;
}

bool Muro::canPass(int) const {
    return false;
}

bool Muro::canEnter(int) const {
    return false;
}

Porta::Porta() {
    open = false;
}

short Porta::costoUscita() const {
    return 1;
}

short Porta::costoEntrata() const {
    return 0;
}

bool Porta::canEnter(int points) const {
    return open && points >= costoEntrata();
}

bool Porta::canPass(int points) const {
    return open && points >= costoAttraversamento();
}

short Montagna::costoEntrata() const {
    return 2;
}

short Montagna::costoUscita() const {
    return 2;
}