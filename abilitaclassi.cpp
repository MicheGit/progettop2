#include "abilitaclassi.h"


Skillset::Skill::~Skill(){
    delete next; delete ability;
}

Skillset::Skillset(int size, Skillset * copy){

}


/* Construcotr. */

bool BaseAbility::getHasBeenUsed() const{ return hasBeenUsed; }

void BaseAbility::setHasBeenUsed(const bool &has){
    hasBeenUsed = has;
}


PassiveAbility::~PassiveAbility(){

}
