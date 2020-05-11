#include "abilitaclassi.h"


Skillset::Skill::~Skill(){
    delete next; delete ability;
}

Skillset::Skillset(int size, Skillset * copy){

}


/* Construcotr. */
BaseAbility::BaseAbility(): hasBeenUsed(false){}



BaseAbility::getHasBeenUsed() const{ return hasBeenUsed; }

BaseAbility::setHasBeenUsed(bool &has = true){
    hasBeenUsed = has;
}


PassiveAbility::~PassiveAbility(){

}
