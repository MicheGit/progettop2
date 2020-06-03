//
// Created by chrim on 28/05/2020.
//

#include "gameobject.h"

GameObject::GameObject(Mappa * map, ushort x, ushort y)
: _map(map), _position(map->getCasella(x, y)) {
    if (_position) {
        _ticket = _position->push_back(this);
    } else {
        // TODO error
    }
}

GameObject::GameObject(const GameObject& other)
: _map(other._map), _position(other._position) {
    _ticket = _position->push_back(this);
}

GameObject& GameObject::operator=(const GameObject & other) {
    if (this != &other) {
        _position->erase(_ticket);
        _map = other._map;
        _position = other._position;
        _ticket = _position->push_back(this);
    }
    return *this;
}

GameObject::~GameObject() {
    _position->erase(_ticket);
};

AnimateObject::AnimateObject(Mappa * map, ushort x, ushort y, ushort actions)
: _maxActions(actions), _currentActions(actions), GameObject(map, x, y) {}

Casella::Ticket AnimateObject::move(Casella * target) {
    if (_position->canExit(_currentActions) && target->canEnter(_currentActions - _position->getCostoUscita())) {
        _position->erase(_ticket);
        _currentActions -= _position->getCostoUscita();
        _position = target;
        _currentActions -= _position->getCostoEntrata();
        _ticket = _position->push_back(this);
    } else {
        // TODO recoverable error
    }

    return _ticket;
}

ushort AnimateObject::getMaxActions() const {
    return _maxActions;
}

ushort AnimateObject::getCurrentActions() const {
    return _currentActions;
}

void AnimateObject::resetTurn() {
    _currentActions = _maxActions;
}

tupla<ushort, tupla<ushort, Casella*>*> AnimateObject::getCaselleRaggiungibili() const {
    return _map->dijkstra(_position, _currentActions);
}

Character::Character(Mappa * map, ushort x, ushort y, ushort actions, ushort hp, ushort strength)
: _baseStrength(strength), _maxHp(hp), _currentHp(hp), AnimateObject(map, x, y, actions) {

}

ushort Character::getMaxHp() const {
    return _maxHp;
}

ushort Character::getCurrentHp() const {
    return _currentHp;
}

ushort Character::getStrength() const {
    return _baseStrength;
}

void Character::dealDamageOrHeal(short modifier) {
    if (_currentHp + modifier > _maxHp) {
        _currentHp = _maxHp;
    } else if (_currentHp < - modifier) {
        _currentHp = 0;
    } else {
        _currentHp += modifier;
    }
}

bool Character::isDead() const {
    return _currentHp == 0;
}

void Character::basicAttack(Character * enemy) const {
    enemy->dealDamage(getStrength());
}

void Character::dealDamage(ushort damage) {
    dealDamageOrHeal(-damage);
}

void Character::dealHeal(ushort heal) {
    dealDamageOrHeal(heal);
}

