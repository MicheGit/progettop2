//
// Created by chrim on 23/05/2020.
//

#ifndef ZOMBIEDUNGEON_CASELLA_H
#define ZOMBIEDUNGEON_CASELLA_H

#include "linkedlist.h"
#include "gameobject.h"

class Casella : public LinkedList<GameObject*> {
public:
    /**
     * cost_type
     *
     * Tipo dei costi per attraversale una casella. Corrisponde a unsigned short.
     */
    typedef unsigned short cost_type;
    /**
     * Ticket
     *
     * Tipo degli iteratori della casella. Questione di leggibilità del codice.
     */
    typedef LinkedList<GameObject*>::Iterator Ticket;
    /**
     * canEnter
     *
     * @return true sse il costo inserito è sufficiente per entrare nella casella.
     */
    virtual bool canEnter(cost_type) const = 0;
    /**
     * canExit
     *
     * @return true sse il costo inserito è sufficiente per uscire dalla casella.
     */
    virtual bool canExit(cost_type) const = 0;

    /**
     * applyAbilityToAll
     *
     * Scorciatoia per applicare un effetto a tutti i GameObject nella casella.
     *
     * @param ability una funzione o puntatore a funzione che rappresenta l'abilità.
     *
     * Il parametro deve essere un'abilità con valore di ritorno void e prende un parametro di tipo GameObject*.
     */
    virtual void applyAbilityToAll(void (*ability)(GameObject*));
};

/**
 * Le classi figlie di Casella possono avere un costo di entrata e di uscita.
 *
 * Le classi che non hanno questi costi sono classi speciali, come muri sui quali non ci si può arrampicare.
 */

class Pianura : public Casella {
public:
    static const cost_type costoEntrata = 1;
    static const cost_type costoUscita = 0;
    bool canEnter(cost_type) const;
    bool canExit(cost_type) const;
};

class Palude : public Casella {
public:
    static const cost_type costoEntrata = 1;
    static const cost_type costoUscita = 1;
    bool canEnter(cost_type) const;
    bool canExit(cost_type) const;
};

class Muro : public Casella {
public:
    static const cost_type costoUscita = 0;
    bool canEnter(cost_type) const;
    bool canExit(cost_type) const;
};

class Porta : public Pianura {
    bool _isOpen;
public:
    Porta();
    bool canEnter(cost_type) const;
    void open();
    bool isOpen() const;
};



#endif //ZOMBIEDUNGEON_CASELLA_H
