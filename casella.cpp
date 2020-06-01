//
// Created by chrim on 23/05/2020.
//

#include "casella.h"

void Casella::applyEffectToAll(void (*ability)(GameObject *)) {
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

Pianura * Pianura::copy() const {
    return new Pianura(*this);
}

Casella::cost_type Pianura::getCostoEntrata() const {
    return costoEntrata;
}

Casella::cost_type Pianura::getCostoUscita() const {
    return costoUscita;
}

bool Palude::canEnter(cost_type residuo) const {
    return residuo >= costoEntrata;
}

bool Palude::canExit(cost_type residuo) const {
    return residuo >= costoUscita;
}

Casella::cost_type Palude::getCostoEntrata() const {
    return costoEntrata;
}

Casella::cost_type Palude::getCostoUscita() const {
    return costoUscita;
}

Palude * Palude::copy() const {
    return new Palude(*this);
}

bool Muro::canEnter(cost_type) const {
    return false;
}

bool Muro::canExit(cost_type residuo) const {
    return residuo >= costoUscita;
}

Casella::cost_type Muro::getCostoEntrata() const {
    return 0;
}

Casella::cost_type Muro::getCostoUscita() const {
    return costoUscita;
}

Muro* Muro::copy() const {
    return new Muro(*this);
}

bool Porta::canEnter(cost_type residuo) const {
    return _isOpen && residuo >= costoEntrata;
}

void Porta::open() {
    _isOpen = true;
}

bool Porta::isOpen() const {
    return _isOpen;
}

Casella::cost_type Porta::getCostoEntrata() const {
    return costoEntrata;
}

Casella::cost_type Porta::getCostoUscita() const {
    return costoUscita;
}

Porta* Porta::copy() const {
    return new Porta(*this);
}