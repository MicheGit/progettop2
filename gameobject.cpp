#include "gameobject.h"

gameObject::gameObject()
{

}


bool Character::isDead(){
    return HP == 0;
}

int PC::getLeveL() const{
    /* Sarò necessaria griglia di conversione per livello?*/
    return experience / 1024;
}

int PC::addExperience(int exp){
    experience += exp;
}


/* A dead player may be revived. */

