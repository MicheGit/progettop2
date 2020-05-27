#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#ifndef ABILITACLASSI_H
#include<abilitaclassi.h>
#endif


class GameObject {
    public:
        GameObject();
};

class StaticObject : public GameObject{
    public:
        StaticObject();
};

class Spawn : public GameObject {
    public:
        Spawn();
};



class DynamicObject : public GameObject{
    public:
        DynamicObject();
};

/* Character, da essa virtuale derivano i NPC (non giocatori) e i PC( palying character) */

/* Un personaggio è definito dai suoi punti ferita, dal suo danno e dalla sua gittata di attacco
tuttavia gittata di attacco e danno sono relativi a Forza + Arma ? . Dalla quantitò di azioni che può svolgere.*/
class Character : public DynamicObject {
    private:
        short int HP; short int currentDmg;

        short int atkDmg;

        short int actionPoints; short int spentPoints;

    public:

        Character(int maxHP = 3, int dmg = 1, int actions = 3);
        bool isDead();

        virtual void getDamaged(const int damage);
        virtual void spendAction(const int);

        virtual short int getCurrentHP() const;
        virtual short int getMaxHP() const;

        virtual short int getFreeActionPoints() const;
        virtual short int getAtkDmg() const;

        bool canPerform(ActiveAbility *);


        virtual ~Character() = 0;
};

class NPC : public Character{
    public:
        NPC();
        ~NPC();

};

class Zombie : public NPC {
    private:

    public:
        void moveTowardsNoise() const;
        ~Zombie();

};

class PC : public Character{
    private:
        Skillset skills;
        int experience;

    public:
        PC();

        int getLeveL() const;
        void addExperience(int exp);

        ~PC();

};


#endif // GAMEOBJECT_H
