//
// Created by chrim on 14/04/2020.
//

#ifndef ZOMBIEDUNGEON_TERRENO_H
#define ZOMBIEDUNGEON_TERRENO_H

#import "linkedlist.h"
#import "creatura.h"

class Terreno {
protected:

    LinkedList<Creatura*> _creature;

    virtual short costoEntrata() const = 0;
    virtual short costoUscita() const = 0;
    virtual short costoAttraversamento() const;
public:
    virtual bool canEnter(int) const;
    virtual bool canPass(int) const;

    virtual bool addCreatura(Creatura*);
    virtual Creatura* removeCreatura(Creatura*);
    virtual Creatura** getAllCreatures() const;
};

class Piana : public Terreno {
public:

    short costoUscita() const override;
    short costoEntrata() const override;
};


class Fango : public Terreno {
public:
    short costoEntrata() const override;
    short costoUscita() const override;
};

class Muro : public Terreno {
protected:
    short costoEntrata() const override;
    short costoUscita() const override;

public:
    bool canPass(int) const override;
    bool canEnter(int) const override;
};

class Porta : public Terreno {
protected:
    short costoEntrata() const override;
    short costoUscita() const override;
public:
    bool open;

    Porta();

    bool canPass(int) const override;
    bool canEnter(int) const override;
};

class Montagna : public Terreno {
public:
    short costoEntrata() const override;
    short costoUscita() const override;
};

#endif //ZOMBIEDUNGEON_TERRENO_H
