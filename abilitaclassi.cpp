
    #include "abilitaclassi.h"


    Skillset::Skill::~Skill(){
        delete next; delete ability;
    }

    Skillset::Skillset(int size, Skillset * copy){}

    bool BaseAbility::getHasBeenUsed() const{
        return hasBeenUsed;
    }

    static std::string BaseAbility::getName(){
        return "BaseAbilityName";
    }

    void BaseAbility::setHasBeenUsed(const bool &has){
        hasBeenUsed = has;
    }

    ActiveAbility::ActiveAbility(int cooldown, int cost, int range):
    turniRicarica(cooldown) , costoAzioni(cost), gittata(range){}

    int ActiveAbility::getCostoAzioni() const{
        return costoAzioni;
    }

    void ActiveAbility::consumeAbility() const{
        ricarica = true; turnoAttuale = 0;
    }

    bool ActiveAbility::abilityUp(){
        return turnoAttuale == turniRicarica || !ricarica;
    }
    /* Potrebbe non essere un metodo della struttura ma del controller.*/
    short int ActiveAbility::nextTurn(){
        if(!abilityUp())
            turnoAttuale++;
        else {
            turnoAttuale = 0;
            ricarica = false;
        }
        // Torna i turni restanti.
        return turniRicarica - turnoAttuale;
    }

    PassiveAbility::~PassiveAbility(){

    }


    ArmorPlate::ArmorPlate(){

    }

    int ArmorPlate::useAbility(Character * target){

    }


    static string ArmorPlate::getName(){
        return "Armor plate";
    }

    int ArmorPlate::useAbility(Character * target){

    }

    /* 1 Hp point for each killed enemy.  (every 2 should be better) */
    int LifeSteal::useAbility(Character * target){

        int maxHp = target ->getMaxHp();

        if(killedThisTurn + target -> currentHp < maxHP)
            target -> setHp(killedThisTurn + target->currentHp);
        else
            target -> setHp(maxHP);

        return 0;
    }

    static string LifeSteal::getName(){
        return "Life Steal";
    }

    int GhostTouch::useAbility(Character * target){
        target->spendAction(target->getFreeActionPoints());

        setHasBeenUsed(true);

        return getCostoAzioni();
    }


