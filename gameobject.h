#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "casella.h"
#include "mappa.h"
#include "array.h"
#include "abilitaclassi.h"
#include "custom_types.h"

class GameObjectError : public Error {
public:
    enum ErrorCode {
        UNDEFINED,
        NULL_POSITION,
        UNREACHABLE_DESTINATION,
    };
private:
    static const char * codeToString(ErrorCode);

public:
    GameObjectError(ErrorCode);
    GameObjectError(const char*);
};

class GameObject {
protected:
    /**
     * TODO studiare protected o private qui
     *  un'alternativa sarebbe mettere come modalità di eredità protected su
     *  AnimatedObject
     */
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
     * @param map: Mappa * , x: ushort, y: ushort, actions: ushort
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
     * spendActions
     *
     * spende un un numero di azioni
     */
    bool spendActions(ushort);

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
    virtual dijkstra_table getCaselleRaggiungibili() const;

    /**
     * Ogni classe figlia di AnimatedObject implementa un modo diverso di muoversi.
     *
     * @param percorso: LinkedList<Casella*>, l'AnimateObject camminerà lungo il percorso
     *
     * @return
     */
    virtual void goToTarget(const LinkedList<Casella*>&) = 0;
};

class Character : public AnimateObject {

    // Si modificano solo a level up  o altre condizioni
    // base
    ushort _maxHp;
    ushort _baseStrength;
    ushort _baseRange;

    // bonus
    ushort _currentHp;
    ushort _shield;

    short _bonusStrength;
    short _bonusRange;

    /**
     * @param modifier: short
     *  se short > 0 -> heal
     *  se short < 0 -> damage
     */
    virtual void takeDamageOrHeal(short);

public:

    Character(Mappa *, ushort, ushort, ushort, ushort, ushort, ushort);
    // totali in lettura, per visualizzazione
    virtual ushort getMaxHp() const;

    virtual ushort getCurrentHp() const;

    virtual ushort getShield() const;

    virtual ushort getStrength() const;

    virtual ushort getRange() const;

    virtual bool isDead() const;

    // bonus in scrittura

    virtual void takeDamage(ushort);

    virtual void takeHeal(ushort);

    virtual void addShield(ushort);

    virtual void addBonusStrength(short);

    virtual void addBonusRange(short);

    // interazione con altri
    virtual void basicAttack(Character*);

    // reset turno
    void resetTurn();

};

class Player : public Character {
    static const ushort _player_base_actions = 3;
    static const ushort _player_base_health = 5;
    static const ushort _player_base_strength = 1;
    static const ushort _player_base_range = 0;
    static const ushort _player_exp_per_level = 10;

    ushort _bonusMagicDamage;
    ushort _expPoints;

    GoodArray<BaseAbility*> _skillset;
public:
    Player(Mappa *, ushort, ushort);

    void addBonusMagicDamage(short);

    ushort getBonusMagicDamage() const;

    void goToTarget(const LinkedList<Casella*>&);

    // time purpose
    // void startTurn(); // TODO

    void resetTurn();

    // exp
    void gainExpPoints(ushort);

    ushort getLevel() const;

    // abilities
    void addAbility(BaseAbility*);

    // TODO get all abilities

};

class Monster : public Character {
public:
    Monster(Mappa *, ushort, ushort, ushort, ushort, ushort, ushort);


    dijkstra_table getCaselleRaggiungibili() const;

    void goToTarget(const LinkedList<Casella *>&);

    virtual void selectCasellaAndMove();

    virtual void doActions() = 0;

};

class Zombie : public Monster {
    static const ushort _zombie_base_hp = 3;
    static const ushort _zombie_base_strength = 1;
    static const ushort _zombie_base_range = 0;
    static const ushort _zombie_base_actions = 2;

public:
    Zombie(Mappa *, ushort, ushort);

    void doActions();

    void resetTurn();
};

class Ghost : public Monster {
    static const ushort _ghost_base_hp = 1;
    static const ushort _ghost_base_strength = 1;
    static const ushort _ghost_base_range = 0;
    static const ushort _ghost_base_actions = 4;

public:
    Ghost(Mappa *, ushort, ushort);

    void doActions();

    void takeDamage(ushort);
};

/**
 * Necromante come figlio di
 *  Player e Zombie?
 */

class SpawnPoint : public GameObject {
    ushort _capacity;
public:
    enum Monsters{
        ZOMBIE,
        GHOST
    };

    SpawnPoint(Mappa *, ushort, ushort, ushort);

    Monster * spawn(Monsters) const;

    Casella::Ticket move(Casella*);
};

#endif // GAMEOBJECT_H
