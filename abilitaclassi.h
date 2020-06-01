#ifndef ABILITACLASSI_H
#define ABILITACLASSI_H

#ifndef GAMEOBJECT_H
#include "gameobject.h"
#endif

#include <string>

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

        virtual short int useAbility(Character *) = 0;
        virtual ~BaseAbility();
};


/* Abilità di tipo attivo.*/
class ActiveAbility : public virtual BaseAbility {
    private:
        short int cooldown; short int turnoCooldown;
        // static ? si potrebbe
        short int costo; short int gittata;
    public:
        ActiveAbility(short int = 0, short int = 0, short int = 0);

        // Getters.
        short int getCost() const;
        short int getGittata() const;
        // Cooldown. Should not be changeable?
        short int getCooldown() const;
        short int getCurrentCooldownTurn() const;

        virtual void reset();

        virtual short int consumeAbility();
        short int nextTurn();

        virtual short int useAbility(Character *) = 0;
};

// Un'abilità multitarget non si interessa dei target da colpire
// ma va in cooldown nel momento in cui ha consumato tutti i colpi
// o dall'esterno non ha più target da colpire.
class MultiTarget : public ActiveAbility{
    private:
        // Il numero di target se = - 1 significa all targets in cell.
        const short int targets; short int hitCount;

    public:
        // Eccezzione se i target = 1 o 0 ?
        MultiTarget(short int = 2, short int = 0, short int = 0, short int = 0);

        short int getTargets() const;
        short int getCurrentCount() const;

        // Usato su nuovo target, quindi incremento i colpiti.
        void increaseCount();
        // Controlla targets - targetCount
        short int missingTargets();
        virtual void reset();

        // Se non ci sono più target l'abilità deve andare in cooldownm.
        void noTargets();

        virtual short int useAbility(Character *) = 0;

        virtual ~MultiTarget();
};

class SingleTarget : public virtual ActiveAbility{
    public:
        SingleTarget(short int = 0, short int = 0, short int = 0);
        virtual short int useAbility(Character * )= 0;
};

class PassiveAbility : public virtual BaseAbility{
    public:
        virtual short int useAbility(Character *) = 0;
        ~PassiveAbility();
};



/* Srtuttura a diamante. Abilita passive / attive in  multitaregt o
    single target. */


class PassiveActiveS : public SingleTarget, public PassiveAbility {
    public:
        PassiveActiveS(short int = 0, short int = 0, short int =0);
        virtual short int useAbility(Character * ) = 0;

        // Potrebbe non essere una buona idea.
        virtual short int usePassive(Character *) = 0;
        virtual short int useActive(Character *) = 0;
};

class PassiveActiveM : public MultiTarget, public PassiveAbility{
    public:
        PassiveActiveM(short int = 2, short int = 0, short int = 0, short int = 0);
        virtual short int useAbility(Character *) = 0;

        // Potrebbe non essere una buona idea.
        virtual void usePassive(Character *) = 0;
        virtual short int useActive(Character *) = 0;
};




/* Gives you a bonus shield of 5. (5HP for the next turn?) */
class ArmorPlate : public SingleTarget {
    private:
       short int bonusHealth;
    public:
        ArmorPlate(short int = 4);

        static std::string getName();
        virtual short int useAbility(Character * target);
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
class Bow : public PassiveAbility{
    private:
        short int maxRange;
    public:
        Bow(short int = 2, short int = 0, short int = 0, short int = 0);
        short int retRange();

        virtual short int useAbility(Character * target);
};

class Martello : public PassiveActiveM{
    private:
        short int bonusDmg;
    public:
        Martello(short int = 0);
        short int getBonusDmg() const;

        virtual short useAbility(Character *);
};

// Infliggi più danni e una volta per turno puoi sferrare un colpo
//  ad area che infligge tutti i target vicini.
class Axe : public PassiveActiveM{
    private:
        int bonusDamage;
    public:
        virtual short useAbility(Character *);
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
        virtual short int useAbility(Character *);

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
        virtual short int useAbility(Character * target);
};

/* Target is feared and won't perform action the coming turn */
class GhostTouch : public SingleTarget {
    public:
        GhostTouch();
        virtual short int useAbility(Character * target);
};

/* Taunts all targets in a seen cell. */
class Taunt : public MultiTarget {
    public:
        Taunt();
        virtual short int useAbility(Character * target);
};

/* Moves all enemies to a next cell. */
class Push : public MultiTarget {
    public:
        Push();
};

class Heal: public SingleTarget{
    public:
        Heal();
};

class Skillset {
    private:
        class Skill{
            public:
                BaseAbility * ability;
                Skill * next;

                Skill(BaseAbility * one, Skill * next = 0): ability(new BaseAbility(one)), next(next) {}
                ~Skill();
        };

        Skill * first; Skill * last;

    public:
        Skillset(int size = 5, Skillset * copy = 0); // Copia?
        void learnAbility(BaseAbility * abilityType); // DeepCopy?

        Skill operator[](const int &pos) const{
            return *getPosition(first,pos);
        }

        static Skill * getPosition(Skill * pos, const int index){
            if(!index)
                return  pos;
            return getPosition(pos->next, index - 1);
        }

        class iterator{
            friend class Skillset;
            private:
                Skill * ptr;
                bool pasTheEnd;
                iterator(Skill* p, bool pte):
                    ptr(p), pasTheEnd(pte){}
            public:
        };


        ~Skillset();
};


#endif // ABILITACLASSI_H
