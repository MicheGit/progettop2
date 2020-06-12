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

dijkstra_table AnimateObject::getCaselleRaggiungibili() const {
    return _map->dijkstra(_position, _currentActions);
}

bool AnimateObject::spendActions(ushort actions) {
    if (actions <= _currentActions) {
        _currentActions -= actions;
        return true;
    } else {
        return false;
    }
}

Character::Character(Mappa * map, ushort x, ushort y, ushort actions, ushort hp, ushort strength, ushort range)
: _baseStrength(strength), _maxHp(hp), _currentHp(hp), AnimateObject(map, x, y, actions), _bonusRange(0),
_shield(0), _bonusStrength(0), _baseRange(range) {

}

ushort Character::getMaxHp() const {
    return _maxHp;
}

ushort Character::getCurrentHp() const {
    return _currentHp;
}

ushort Character::getShield() const {
    return _shield;
}

ushort Character::getStrength() const {
    return _baseStrength + (_bonusStrength >= 0 ? _bonusStrength : 0);
}

ushort Character::getRange() const {
    return _baseRange + _bonusRange;
}

void Character::takeDamageOrHeal(short modifier) {
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

void Character::basicAttack(Character * enemy) {
    if (spendActions(1)) {
        enemy->takeDamage(getStrength());
    }
}

void Character::takeDamage(ushort damage) {
    if (damage >= _shield) {
        damage -= _shield; // mitigate damage
        _shield = 0;
        takeDamageOrHeal(-damage);
    } else {
        _shield -= damage;
    }

}

void Character::takeHeal(ushort heal) {
    takeDamageOrHeal(heal);
}

void Character::addShield(ushort shield) {
    _shield += shield;
}

void Character::addBonusRange(short range) {
    _bonusRange += range;
}

void Character::addBonusStrength(short strength) {
    _bonusStrength += strength;
}

void Character::resetTurn() {
    AnimateObject::resetTurn();
    _shield = 0;
    _bonusStrength = 0;
    _bonusRange = 0;
}

Player::Player(Mappa * map, ushort x, ushort y)
: Character(map, x, y, _player_base_actions, _player_base_health, _player_base_strength, _player_base_range),
_bonusMagicDamage(0) {

}

void Player::goToTarget(const LinkedList<Casella *>& path) {
    for (auto i = path.begin(); i != path.end(); ++i) {
        move(*i);
    }
}



void Player::resetTurn() {
    Character::resetTurn();
    _bonusMagicDamage = 0;
}

void Player::addBonusMagicDamage(short bonus) {
    if (_bonusMagicDamage > bonus){
        _bonusMagicDamage += bonus;
    } else {
        _bonusMagicDamage = 0;
    }
}

ushort Player::getBonusMagicDamage() const {
    return _bonusMagicDamage;
}

void Player::gainExpPoints(ushort exp) {
    _expPoints += exp;
}

ushort Player::getLevel() const {
    return _expPoints / _player_exp_per_level;
}

void Player::addAbility(BaseAbility* ability) {
    _skillset.push_back(ability);
}


Monster::Monster(Mappa * map, ushort x, ushort y, ushort actions, ushort hp, ushort strength, ushort range)
: Character(map, x, y, actions, hp, strength, range) {

}

dijkstra_table Monster::getCaselleRaggiungibili() const {
    return _map->dijkstra(_position);
}

void Monster::goToTarget(const LinkedList<Casella *>& path) {
    for (auto i = path.begin(); i != path.end(); ++i) {
        move(*i);
    }
}

void Monster::selectCasellaAndMove() {
    auto results = getCaselleRaggiungibili();
    GoodArray<short> indexes = results.indexes;
    GoodArray<dijkstra_node> riga = results.nodes;

    int targetIndex = 0;
    Casella * targetPointer = nullptr;
    int k = 0; // coefficiente di appetibilità

    for (int i = 0; i < riga.size(); ++i) {
        ushort costo = riga[i].costo;
        Casella * target = (*_map)[indexes[i]];

        if (k < target->size() - costo
            || (k == target->size() - costo && riga[targetIndex].costo > costo)
        ) {
            targetIndex = i;
            targetPointer = target;
            k = target->size() -  costo;
        }
    }

    // target index è quello con l'indice di appetibilità maggiore

    LinkedList<Casella *> path;
    path.push_front(targetPointer);
    while (riga[targetIndex].provenienza) {
        path.push_front(riga[targetIndex].provenienza);
        targetIndex = results.index_indexes[_map->getIndexFromCasella(riga[targetIndex].provenienza)];
    }

    if ((*path.begin()) == _position) {
        goToTarget(path);
    } // else la destinazione è irraggiungibile
}



Zombie::Zombie(Mappa * map, ushort x, ushort y)
: Monster(map, x, y, _zombie_base_actions, _zombie_base_hp, _zombie_base_strength, _zombie_base_range) {

}

void Zombie::doActions() {
    LinkedList<Player *> players;
    for (auto i = _position->begin(); i != _position->end(); ++i) {
        Player * cast = dynamic_cast<Player*>(*i);
        if (cast) {
            players.push_front(cast);
        }
    }
    if (players.size() > 0) {
        // TODO dare priorità in base alla difficoltà selezionata?
        while (!(*players.begin())->isDead() && getCurrentActions() > 0) {
            basicAttack(*players.begin());
        }
    } else {
        selectCasellaAndMove();
    }
}

void Zombie::resetTurn() {
    resetTurn();
    takeHeal(_zombie_base_hp);
}

Ghost::Ghost(Mappa * map, ushort x, ushort y)
: Monster(map, x, y, _ghost_base_actions, _ghost_base_hp, _ghost_base_strength, _ghost_base_range) {}

void Ghost::doActions() {
    selectCasellaAndMove();
    if (getCurrentActions() > 0) {
        LinkedList<Player *> players;
        for (auto i = _position->begin(); i != _position->end(); ++i) {
            Player * cast = dynamic_cast<Player*>(*i);
            if (cast) {
                players.push_front(cast);
            }
        }
        if (players.size() > 0) {
            // TODO dare priorità in base alla difficoltà selezionata?
            while (!(*players.begin())->isDead() && getCurrentActions() > 0) {
                basicAttack(*players.begin());
            }
        }
    }
}

void Ghost::takeDamage(ushort) {
    // TODO impedire che subisca danni fisici
}

SpawnPoint::SpawnPoint(Mappa * map, ushort x, ushort y, ushort capacity): GameObject(map, x, y), _capacity(capacity) {}

Monster * SpawnPoint::spawn(Monsters code) const {
    Monster * nuovo = nullptr;
    auto positions = _map->getXandYfromCasella(_position);
    switch(code) {
        case ZOMBIE: {
            nuovo = new Zombie(_map, positions.first, positions.second);
            break;
        }
        case GHOST: {
            nuovo = new Ghost(_map, positions.first, positions.second);
            break;
        }
        default:
            nuovo = new Zombie(_map, positions.first, positions.second);
    }
    return nuovo;
}

Casella::Ticket SpawnPoint::move(Casella * target) {
    _position->erase(_ticket);
    _position = target;
    _ticket = _position->push_front(this);
}

const char* GameObjectError::codeToString(GameObjectError::ErrorCode code) {
    switch (code) {
        case NULL_POSITION:
            return "GameObjectError: tentativo di inserimento in casella nulla.";
        case UNREACHABLE_DESTINATION:
            return "GameObjectError: la destinazione selezionata non è raggiungibile.";
        default:
            return "GameObjectError: Errore non specificato.";
    }
}
