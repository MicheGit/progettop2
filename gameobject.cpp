    #include "gameobject.h"

    bool Character::isDead(){
        return ( HP - currentDmg ) <= 0;
    }

    Character::Character(int maxHP, int dmg, int actions):
        HP(maxHP), atkDmg(dmg), actionPoints(actions),
        currentDmg(0), spentPoints(0) {}

    // Getters.

    short int Character::getCurrentHP() const{
        return HP - currentDmg;
    }

    short int Character::getMaxHP() const{
        return HP;
    }

    short int Character::getFreeActionPoints() const{
        return actionPoints - spentPoints;
    }

    short int Character::getAtkDmg() const{
        return atkDmg;
    }

    // Setters

    /* Un personaggio che riceve danno negativo viene guarito del
        massimo di punti guaribili portando danni a 0.*/
    void Character::getDamaged(const int damage){
        if(currentDmg + damage > HP)
            currentDmg = HP;
        else if(currentDmg + damage < 0)
            currentDmg = 0;
        else
            currentDmg += damage;
    }

    void Character::spendAction(const int spent){
        spentPoints += spent;
    }

    bool canPerform(ActiveAbility * ability){
        return ability->getCostoAzioni() + spentPoints <= actionPoints;
    }


    int PC::getLeveL() const{
        /* Sarò necessaria griglia di conversione per livello?*/
        return experience / 1024;
    }

    int PC::addExperience(int exp){
        experience += exp;
    }



/* A dead player may be revived. */

