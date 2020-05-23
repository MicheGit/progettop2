//
// Created by chrim on 23/05/2020.
//

#include "casella.h"

void Casella::applyAbilityToAll(void (*ability)(GameObject *)) {
    for (Ticket i = begin(); i != end(); ++i) {
        ability(*i);
    }
}

bool Pianura::canEnter(cost_type residuo) const {
    return residuo >= costoEntrata;
}

bool Pianura::canExit(cost_type residuo) const {
    return residuo >= costoUscita;
}

bool Palude::canEnter(cost_type residuo) const {
    return residuo >= costoEntrata;
}

bool Palude::canExit(cost_type residuo) const {
    return residuo >= costoUscita;
}

bool Muro::canEnter(cost_type) const {
    return false;
}

bool Muro::canExit(cost_type residuo) const {
    return residuo >= costoUscita;
}

Porta::Porta(): Pianura(), _isOpen(false) {}

bool Porta::canEnter(cost_type residuo) const {
    return _isOpen && residuo >= costoEntrata;
}

void Porta::open() {
    _isOpen = true;
}

bool Porta::isOpen() const {
    return _isOpen;
}