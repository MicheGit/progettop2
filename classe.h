#ifndef CLASSE_H
#define CLASSE_H


class ClasseAstratta{
    private:

    public:
        ClasseAstratta();

        virtual void classAction() = 0;


        virtual void passive() = 0;

        virtual void abilityQ();
        virtual void abilityW();
        virtual void abilityE();
        virtual void abilityR();


        virtual int meeleAction();
        virtual int rangedAction();


        virtual ~ClasseAstratta() = 0;

};

/*
 * Mago guerriero e Rogue sono le 3 classi base, da quelle ci si può poi
 * specializzare in base a cosa però? livello minimo e condizioni?
 * Solo livello e a scelta? -> PIU FACILE
 *
 *  Classe base.
 *      Maghi ( classi maghi)
 *          Warlock (mago mago)
 *          Evocatore
 *          Shamano
 *
 *      Guerrieri ( classi tank/fighter)
 *          Cavaliere
 *          Paladino
 *          Templare
 *
 *      Rogue (classi dps non magiche)
 *          Ranger
 *          Ladro
 *          Assassino
 *
 *      Classi ibride :
 *
 *          Bardo (rogue e mago)
 *          Illusionista (rogue e mago)
 *          Necromante (guerriero mago)
 *          Martial Artist (Guerreiro rogue)
*/


//------------------------------------------------------------------------------------

    /* Le tre classi base. Mago combatte a distanza con magia
    il guerriero è un tank. Rogue sono DPS distanza/ravvicinato*/

    class Mago : virtual public ClasseAstratta{
        public:
            ~Mago();

    };

    class Guerriero : virtual public ClasseAstratta{
        public:
            ~Guerriero();
    };

    class Rogue : virtual public ClasseAstratta{
        public:
            ~Rogue();
    };

//------------------------------------------------------------------------------------

    /*  Classi avanzate.
        Classi dei maghi: */

    class Warlock: public Mago{
        public:
            ~Warlock();
    };

    class Evocatore : public Mago{
         public:
            ~Evocatore();
    };

//------------------------------------------------------------------------------------

    /* Classi dei Guerrieri*/

    class Cavaliere : public Guerriero{
        public:
            ~Cavaliere();
    };

    class Paladino : public Guerriero{
        public:
            ~Paladino();
    };

//------------------------------------------------------------------------------------

    /* Classi dei Rogue */

    class Ranger : public Rogue{
        public:
            ~Ranger();
    };

    class Ladro : public Rogue{
        public:
            ~Ladro();
    };

//------------------------------------------------------------------------------------



    /* Classi ibride avanzate. */



    class Necromante : public Mago, public Guerriero{
        public:
            ~Necromante();
    };

    class Bardo : public Mago, public Rogue{
        public:
            ~Bardo();
    };

    class MartialArtist : public Guerriero, public Rogue{
        public:
            ~MartialArtist();
    }


//------------------------------------------------------------------------------------

#endif // CLASSE_H
