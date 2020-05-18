#ifndef ABILITACLASSI_H
#define ABILITACLASSI_H
/*
    NOTE :

        - Da fare iteratore e container. Skillset come container di skills.

        - Se nomi delle abilità fossero char * statiche per ogni sottoclasse in fondo?
            Potremmo mettere un nome standard in caso non definito da uno in futuro. Sembra idea buona per risparmiare
            spazio ma sbagliata concettualmente.



*/
#ifndef GAMEOBJECT_H
#include "gameobject.h"
#endif

#include<string.h>

/* Abilità di base. Classe astratta. */

 class BaseAbility {
    private:
        bool hasBeenUsed; // We use an ability max once per turn expect special ones.
    public:
        BaseAbility(bool used = false) :
            hasBeenUsed(used){}

        virtual void useAbility(GameObject * target) = 0;

        virtual static std::string getName(){
            return "BaseAbilityName";
        }

        bool getHasBeenUsed() const;
        void setHasBeenUsed(const bool &has = true);

        ~BaseAbility();
};

/* Abilità di tipo attivo. Classe */

class ActiveAbility : public virtual BaseAbility {
    private:
        int turniRicarica;
        int costoAzioni; int gittata;
    public:
        ActiveAbility(int cooldown = 0, int cost = 0, int range = 0) :
            turniRicarica(cooldown) , costoAzioni(cost), gittata(range){}
        virtual void useAbility(GameObject * target);
};

class PassiveAbility : public virtual BaseAbility{

    public:
        virtual void useAbility(GameObject * target = 0);
        ~PassiveAbility();
};


class APAbility : public ActiveAbility, public PassiveAbility {
    public:
        APAbility();
        virtual void useAbility(GameObject * target = 0);
};

/* Gives you a bonus shield of 5. */
class ArmorPlate : public PassiveAbility {
    private:
        int bonusArmor;
    public:
        ArmorPlate();
        virtual static string getName(){
            return "Armor Plate";
        }
        virtual void useAbility(GameObject * target = 0);
};

/* Restores 1 hp for each enemy killed. */
class LifeSteal : public PassiveAbility {
    private:
        int killedThisTurn;
    public:
        LifeSteal();
        virtual void useAbility(GameObject * target);
};

/* Target is feared and won't perform action the coming turn */
class GhostTouch : public ActiveAbility {
    public:
        GhostTouch();
};

/* Taunts all targets in a seen cell. */
class Taunt : public ActiveAbility {
    public:
        Taunt();
        virtual void useAbility(GameObject * target);
};

/* Moves all enemies to a next cell. */
class Push : public ActiveAbility {
    public:
        Push();
};

/*
    SKILLS IDEAS:

        -   Doppio incantamento (una abilità può essere lanciata due volte)
        -   Cometa Arcana
        -   Scan (vedi la vita dei nemici)
        -   Raid ( lancia arma in riga )
        -   Cura
        -   Scudo magioc
        -   Berserk
        -   Stormo di corvi ( rallenta tutti i nemici in una casella e fa danno

*/


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
