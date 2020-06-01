
    #include "abilitaclassi.h"

    BaseAbility::BaseAbility(bool has) : used(has){}

    std::string BaseAbility::getName(){
        return "baseabilityname";
    }

    void BaseAbility::set(){
        used = true;
    }

    void BaseAbility::reset(){
        used = false;
    }

    bool BaseAbility::getUsed() const{
        return used;
    }

    // Costruisce l'oggetto BaseAbility da cui deriva e assegna coolwon costo e range.
    ActiveAbility::ActiveAbility(
        short int setCooldown, short int cost, short int range):
        cooldown(setCooldown), costo(cost), gittata(range){
            turnoCooldown = 0;
    }

    short int ActiveAbility::getCost() const{
        return costo;
    }

    short int ActiveAbility::getGittata() const{
        return gittata;
    }

    short int ActiveAbility::getCooldown() const{
        return cooldown;
    }

    short int ActiveAbility::getCurrentCooldownTurn() const{
        return turnoCooldown;
    }

    void ActiveAbility::reset(){
        BaseAbility::reset();
        turnoCooldown = 0;
    }

    short int ActiveAbility::consumeAbility(){
    /* Non posso consumare un'abilità già stata consumata.*/
        if(getUsed())
            return -1;

        set();

        return costo;
    }
    /* Passa al turno dopo. Ritorna quanti turni di cooldown siamo.
     * Se 0 allora ha finito il cooldown.*/
    short int ActiveAbility::nextTurn(){
        if(cooldown == turnoCooldown)
            reset();
        else
            turnoCooldown ++;
        return turnoCooldown;
    }



    /* Multitarget . */

    MultiTarget::MultiTarget(short int noTargets, short int setCooldown, short int cost, short int range)
    :ActiveAbility(setCooldown, cost, range),targets(noTargets){
        hitCount = 0;
    }

    short int MultiTarget::getTargets() const{
        return targets;
    }

    short int MultiTarget::getCurrentCount() const{
        return hitCount;
    }

    // Incremento il conteggio dei target colpiti. Dovessero essere
    // il numero di target totali colpibili metto l'abilità in cooldown.
    void MultiTarget::increaseCount(){
        if(hitCount != targets)
            hitCount++;
        else
            set();
    }

    short int MultiTarget::missingTargets(){
        return targets - hitCount;
    }

    void MultiTarget::reset(){
        ActiveAbility::reset();
        hitCount = 0;
    }

    void MultiTarget::noTargets(){
        set();
    }

    SingleTarget::SingleTarget(short int setCooldown, short int cost , short int range)
        :ActiveAbility(setCooldown, cost, range){}


    PassiveAbility::~PassiveAbility(){

    }

    /* Armor Plate è una abilità attiva che per il prossimo turno
        aumenta la vita bonus di 4 + %mod% (armatura).*/
    ArmorPlate::ArmorPlate(short int bonus):
        SingleTarget(3,2,0), bonusHealth(bonus){

    }

    std::string ArmorPlate::getName(){
        return "Armor Plate";
    }


    short int ArmorPlate::useAbility(Character * target){
        return getCost();
    }

    std::string ArmorPlate::getName(){
        return "Armor plate";
    }

    /* 1 Hp point for each killed enemy.  (every 2 should be better) */
    short int LifeSteal::useAbility(Character * target){

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

    short int GhostTouch::useAbility(Character * target){
        target->spendAction(target->getFreeActionPoints());

        setHasBeenUsed(true);

        return getCostoAzioni();
    }


