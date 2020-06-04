
/*
    Al posto di Character * userò una
    const GoodArray<Character*>& così da
    risolvere single-target multi-target.
*/


#ifndef ABILITACLASSI_H
#define ABILITACLASSI_H

#ifndef GAMEOBJECT_H
#include "gameobject.h"
#endif

#include <string>

#ifndef ARRAY_H
#include "array.h"
#endif

/* Abilità di base. Classe astratta. */
class BaseAbility {
    private:
        bool used;
    public:
        BaseAbility(bool = false);
        // Restituisce il nome della abilità.
        static std::string getName();

        // Uso l'abilità e quindi used = true. O triggero per reset
        // e l'abilità non è più stata usata.
        virtual void set();
        virtual void reset();

        bool getUsed() const;

        virtual short int useAbility(const GoodArray<Character*>&) = 0;
        virtual ~BaseAbility();
};


/* Abilità di tipo attivo.*/
class ActiveAbility : public virtual BaseAbility {
    private:
        short int cooldown; short int turnoCooldown;
        // static ? si potrebbe
        short int costo; short int gittata;

        // Multitarget properties
        const short int targets; short int hitCount;

    public:
        ActiveAbility(short int = 1, short int = 0, short int = 0, short int = 0);

        // Getters.
        short int getCost() const;
        short int getGittata() const;
        // Cooldown. Should not be changeable?
        short int getCooldown() const;
        short int getCurrentCooldownTurn() const;

        virtual void reset();

        virtual short int consumeAbility();
        short int nextTurn();


        /* Multitarget properties */
        short int getTargets() const;
        short int getCurrentCount() const;

        // Usato su nuovo target, quindi incremento i colpiti.
        void increaseCount();
        short int missingTargets();
        // Se non ci sono più target l'abilità deve andare in cooldownm.
        void noTargets();


        virtual short int useAbility(const GoodArray<Character*>&) = 0;
};

// Un'abilità multitarget non si interessa dei target da colpire
// ma va in cooldown nel momento in cui ha consumato tutti i colpi
// o dall'esterno non ha più target da colpire.

class PassiveAbility : public virtual BaseAbility{
    public:
        virtual short int useAbility(const GoodArray<Character*>&) = 0;
        ~PassiveAbility();
};



/* Srtuttura a diamante. Abilita passive / attive in  multitaregt o
    single target. */


class PassiveActive : public ActiveAbility, public PassiveAbility {
    public:
        PassiveActive(short int = 1,short int = 0, short int = 0, short int =0);
        virtual short int useAbility(const GoodArray<Character*>&) = 0;

        // Potrebbe non essere una buona idea.
        virtual short int applyPassive(Character *) = 0;
        virtual short int useActive(Character *) = 0;
};



/* Gives you a bonus shield of 5. (5HP for the next turn?)
    target -> SELF .*/
class ArmorPlate : public ActiveAbility {
    private:
       short int bonusHealth;
    public:
        ArmorPlate(short int = 4);

        static std::string getName();
        virtual short int useAbility(const GoodArray<Character*>&);
};



/*
 *      Questione Armi:
 *
 *
 *
 *  Gestiamo la questione delle armi qui nelle abilità. Un giocatore
    può avere come abilità un'arma che passivamente gli da qualche
    caratteristica su colpo.

    Lista atttuale:
        - arco  : bonus range base atk : 2
        - balestra : bonus range base atk : 2, danno : 1
        - ascia     : bonus colpo
        - martello : colpi atk bonus, attiva: danno ad area in casella.
        - bastone magico : bonus lancio incantesimi sui danni + speel bonus?
        - canna da pesca    : range 2, sposta il nemico in casella corrente.

*/

// Arco, permette di attaccare a distanza.
class Arco : public PassiveAbility{
    private:
        const short int maxRange;
    public:
        Arco(short int = 2, short int = 0, short int = 0, short int = 0);
        short int getRange() const;

        static std::string getName() const;

        virtual short int useAbility(const GoodArray<Character*>&);

};

class Balestra: public PassiveAbility{
    private:
        const short int maxRange; const short int bonusDmg;
    public:
        Balestra(short int = 1, short int = 1, short int = 0, short int = 0, short int = 0);
        short int getMaxRange() const;

        static std::string getName() const;

        virtual short int useAbility(const GoodArray<Character*>&);

};

class Martello : public PassiveActive{
    private:
        short int bonusDmg;
    public:
        Martello(short int = 0);
        short int getBonusDmg() const;

        virtual short int useAbility(const GoodArray<Character*>&);
};

// Infliggi più danni e una volta per turno puoi sferrare un colpo
//  ad area che infligge tutti i target vicini.
class Axe : public PassiveActive{
    private:
        int bonusDamage;
    public:
        virtual short int useAbility(const GoodArray<Character*>&);
};


/* Abilità che infliggono danni danno un bonus di danno.(parametro nel
    character) e in più è possibile infliggere danni a distanza.*/
class Bastone : public PassiveAbility{
    private:
        short int bonusDamage; // Su spell.
        short int bonusRange; // attacco a distanza.
    public:

        Bastone(short int = 0, short int = 1);

        // Incanta le proprie abilità dando un modificatore bonus
        // di danni sulle spell che infiglggonod danni. Target è self.
        // Avremo campo "danniBonusLancio".
        virtual short int useAbility(const GoodArray<Character*>&);

};


    /*Inzio abilità. Lista:
     *
     *
     *

        */

/* Restores 1 hp for each enemy killed. */
class LifeSteal : public PassiveAbility {
    private:
        short int killedThisTurn;
    public:
        LifeSteal();
        static std::string getName();
        virtual short int useAbility(const GoodArray<Character*>&);
};

/* Target is feared and won't perform action the coming turn */
class GhostTouch : public ActiveAbility {
    public:
        GhostTouch();
        virtual short int useAbility(const GoodArray<Character*>&);
};

/* Taunts all targets in a seen cell. */
class Taunt : public ActiveAbility {
    public:
        Taunt();
        virtual short int useAbility(const GoodArray<Character*>&);
};

/* Moves all enemies to a next cell. */
class Push : public ActiveAbility {
    public:
        Push(short int = -1, short int = 0, short int = 0, short int = 0);
        virtual short int useAbility(const GoodArray<Character*>&);
};


/* Heals ally target. (potremmo fare che puo curare chiunque) */
class Heal: public ActiveAbility{
    private:
        short int heal;
    public:
        Heal(const short int = 0, const short int = 2, const short int = 2, const short int =1);

        // virtual bool canThrow();

        virtual short int useAbility(const GoodArray<Character*>&);
        static bool checkAlly(Character * target);
};


#endif // ABILITACLASSI_H
