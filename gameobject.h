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
        int HP; int atkDmg;
        int actionPoints; bool isAlive;
    public:
        Character();

        bool isDead();


        ~Character = 0;
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
