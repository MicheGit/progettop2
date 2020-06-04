#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "casella.h"
#include "mappa.h"

class Skill;

typedef unsigned short ushort;

class GameObject {
protected:
    Mappa * _map;
    Casella * _position;
    Casella::Ticket _ticket;
public:
    /**
     * GameObject non è una classe istanziabile, ma pongo lo stesso un costruttore di default che inserisce
     * l'object in una casella
     *
     * @param map: Mappa, mappa di appartenenza
     * @param x: ushort, posizione x
     * @param y: ushort, posizione y
     * */
    GameObject(Mappa *, ushort, ushort);

    /**
     * In caso di clonazione, si crea un oggetto uguale nella stessa casella
     */
    GameObject(const GameObject&);

    /**
     * Come nel caso della clonazione, solo che si rimuove l'oggetto dalla casella corrente
     */
    GameObject& operator=(const GameObject&);

    /**
     * Il distruttore rimuove l'oggetto dalla mappa
     */
    virtual ~GameObject();

    /**
     * un oggetto può essere spostato da una casella all'altra,
     * ma le regole per farlo devono essere definite più in giù
     *
     * @param target: Casella *, casella bersaglio
     *
     * @return il ticket di posizione nella nuova casella
     */
    virtual Casella::Ticket move(Casella *) = 0;


};

class AnimateObject : public GameObject {
protected:
    /**
     * Massimo numero di azioni per turno
     */
    ushort _maxActions;
    /**
     * Numero di azioni residue per questo turno
     */
    ushort _currentActions;
public:
    /**
     * costruttore di base
     *
     * @param map: Mappa * ,
     * @
     * @param actions: unsigned short numero di azioni
     */
    AnimateObject(Mappa *, ushort, ushort, ushort);

    /**
     * costruttori e distruttori e assegnazioni standard vanno bene
     *
     */

    /**
     * move
     *
     *  elimina l'oggetto dalla sua casella corrente e lo inserisce in target, aggiornando il ticket
     *   e le azioni correnti
     *
     * @param target
     * @return il nuovo ticket
     */
    Casella::Ticket move(Casella* target);

    /**
     * getMaxActions
     *
     * @return il numero di azioni che l'animateObject può fare al massimo in un turno
     */
    ushort getMaxActions() const;

    /**
     * getCurrent actions
     *
     * @return il numero di azioni in questo turno
     */

    ushort getCurrentActions() const;

    /**
     * resetTurn
     *
     * resetta le statistiche correnti al valore che devono avere dopo ogni turno
     */
    virtual void resetTurn();

    /**
     * getCaselleRaggiungibili
     *
     * Usa l'algoritmo di Dijkstra per trovare i cammini minimi
     *  verso le caselle raggiungibili.
     *
     * È marcato virtuale perché alcuni AnimateObject hanno bisogno
     *  di un algoritmo inizializzato differentemente, per comportarsi
     *  in maniera differente.
     *
     * @return l'ultima riga dell'algoritmo di Dijkstra, con le caselle e i cammini minimi correlati.
     */
    virtual tupla<ushort, tupla<ushort, Casella *>*> getCaselleRaggiungibili() const;

    /**
     * Ogni classe figlia di AnimatedObject implementa un modo diverso di muoversi.
     *
     * @param percorso: LinkedList<Casella*>, l'AnimateObject camminerà lungo il percorso
     *
     * @return
     */
    virtual void goToTarget(LinkedList<Casella*>&) const = 0;
};

class Character : public AnimateObject {

    friend class Effect;
    /**
     * TODO
     * A scopo di modificare e applicare effetti che influenzano
     * le statistiche di base dei personaggi ci sono due vie:
     *
     *  - i campi dati sono pubblici (super bad practice)
     *  - la classe Effect è friend di questa classe (bad practice)
     *
     * Un altro aspetto da considerare è rendere disponibile un
     *  lifetime: "quanti turni sono passati da..."
     */

    /**
     * @param modifier: short
     *  se short > 0 -> heal
     *  se short < 0 -> damage
     */
    virtual void dealDamageOrHeal(short);
protected:
    ushort _maxHp;
    ushort _currentHp;

    ushort _baseStrength;


public:

    Character(Mappa *, ushort, ushort, ushort, ushort, ushort);

    // in sola lettura
    virtual ushort getMaxHp() const;

    virtual ushort getCurrentHp() const;

    virtual ushort getStrength() const;

    virtual bool isDead() const;

    // interazione con altri
    virtual void dealDamage(ushort);

    virtual void dealHeal(ushort);

    virtual void basicAttack(Character*) const;

};

#endif // GAMEOBJECT_H
