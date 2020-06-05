//
// Created by chrim on 29/05/2020.
//

#ifndef ZOMBIEDUNGEON_MAPPA_H
#define ZOMBIEDUNGEON_MAPPA_H

#include "casella.h"
#include "custom_types.h"
#include "array.h"

#include <sstream>
// TODO togliere sstream per log

struct dijkstra_node {
    ushort costo;
    Casella * provenienza;
    dijkstra_node(ushort c, Casella* p): costo(c), provenienza(p) {}
    dijkstra_node() = default;
};

struct dijkstra_table {
    GoodArray<short> indexes;
    GoodArray<dijkstra_node> nodes;
    GoodArray<short> index_indexes;
    dijkstra_table(const GoodArray<short>& i, const GoodArray<dijkstra_node> n, const GoodArray<short>& ii): indexes(i), nodes(n), index_indexes(ii) {}
    dijkstra_table() = default;
};

class Mappa {

    const ushort _width; // column number x-axis
    const ushort _height; // row number y-axis
    Casella * * const _map; // devono essere per forza puntatori altrimenti ciao ciao polimorfismo

public:
    typedef ushort size_type;

    Mappa(size_type, size_type);
    ~Mappa();

    Mappa(const Mappa&) = delete;
    Mappa& operator=(const Mappa&) = delete;

    Casella*& operator[](size_type) const;

    Casella*& getCasella(size_type, size_type) const;

    ushort getIndexFromCasella(Casella*) const;

    tupla<ushort, ushort> getXandYfromCasella(Casella*) const;

    /**
     * Implementazione ottimizzata dell'algoritmo di Dijkstra
     *  per il cammino minimo
     *
     * @param start: ushort, indice di casella dove partire
     * @param limit: ushort default = -1, punti movimento disponibii
     * @return
     */
    dijkstra_table dijkstra(ushort, ushort = -1) const;

    dijkstra_table dijkstra(Casella *, ushort = -1) const;

    tupla<ushort, Casella *> * test_init_dijkstra(std::stringstream&, ushort, ushort = -1) const;
};


#endif //ZOMBIEDUNGEON_MAPPA_H
