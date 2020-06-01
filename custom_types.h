//
// Created by chrim on 29/05/2020.
//

#ifndef ZOMBIEDUNGEON_CUSTOM_TYPES_H
#define ZOMBIEDUNGEON_CUSTOM_TYPES_H

typedef unsigned short ushort;

template <typename P, typename S>
struct tupla {
    P first;
    S second;
    tupla(P f, S s): first(f), second(s) {}
    tupla() = default;
};

#endif //ZOMBIEDUNGEON_CUSTOM_TYPES_H
