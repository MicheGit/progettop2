//
// Created by chrim on 29/05/2020.
//

#ifndef ZOMBIEDUNGEON_MAPPA_H
#define ZOMBIEDUNGEON_MAPPA_H

#include "casella.h"
#include "custom_types.h"

#include <sstream>

class Mappa {

    const ushort _width; // column number x-axis
    const ushort _height; // row number y-axis
    Casella * * const _map;

public:
    typedef ushort size_type;

    Mappa(size_type, size_type);
    ~Mappa();

    Mappa(const Mappa&) = delete;
    Mappa& operator=(const Mappa&) = delete;

    Casella*& operator[](size_type) const;

    Casella*& getCasella(size_type, size_type) const;

    /**
     * Implementazione ottimizzata dell'algoritmo di Dijkstra
     *  per il cammino minimo
     *
     * @param start: ushort, indice di casella dove partire
     * @param limit: ushort default = -1, punti movimento disponibii
     * @return
     */
    tupla<ushort, Casella *> * dijkstra(ushort, ushort = -1) const;

    tupla<ushort, Casella *> * test_init_dijkstra(std::stringstream&, ushort, ushort = -1) const;
};


#endif //ZOMBIEDUNGEON_MAPPA_H
