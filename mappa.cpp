//
// Created by chrim on 29/05/2020.
//

#include "mappa.h"
#include <math.h>

Mappa::Mappa(Mappa::size_type width, Mappa::size_type height)
: _width(width), _height(height), _map(new Casella*[width * height]) {}

Mappa::~Mappa() {
    for (int i = 0; i < _width * _height; ++i) {
        delete _map[i];
    }
    delete [] _map;
}

Casella *& Mappa::operator[](size_type index) const {
    return _map[index];
}

Casella *& Mappa::getCasella(size_type x, size_type y) const {
    return _map[x + y * _width];
}

dijkstra_table Mappa::dijkstra(ushort start, ushort limit) const {


    // init
    ushort start_x = start % _width;
    ushort start_y = start / _width;

    if (start_y >= _height) {
        // TODO error
    }

    if (limit == -1) {
        limit = _height + _width;
    } // se limit == 1 -> il limite è la mappa (percorso con cammino più lungo)

    // il numero di nodi è 1 + (2 * (ogni nuovo nodo - 1 per ogni nodo non vertice)) * ogni iterazione
    // ovvero: 1 + 4 + (2 * 4 - 0) + (2 * 8 - 4) + (2 * 12 - 8)
    // ovvero: 1 + 4*0 + 4*1 + 4*2 ...


    ushort nodes_number = 1;
    for (int i = 1; i <= limit; ++i) {
        nodes_number += 4 * i;
    }

    GoodArray<short> node_indexes(nodes_number);
    // short node_indexes[nodes_number];
    short max_index = start_x + (start_y + limit) * _width;
    ushort count = 0;
    while (max_index >= _width * _height) {
        max_index = start_x + count + (start_y + limit - count) * _width;
        count++;
    }
    GoodArray<short> node_indexes_indexes(max_index + 1);
    for (int i = 0; i <= max_index; ++i) {
        node_indexes_indexes[i] = -1;
    }

    node_indexes[0] = start;
    node_indexes_indexes[start] = 0;

    ushort previous_ring = 1;
    for (int i = 1; i <= limit; ++i) {
        // per ogni step
        // il sistema di riferimento è come canvas html, le y vanno verso il basso

        // indice dei cicli: i + i * j + k
        // per ogni quadrante
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante dx alto



            short c_x = start_x + i - k; // passi a destra aum x
            short c_y = start_y - k; // passi in alto dim y
            short c_i = c_y * _width + c_x;

            // posso andare a dx e su?

            if (_width - start_x > i - k && start_y >= k
                && c_i >= 0 && c_i < _width * _height) {
                // se posso andare a dx e su con questi valori
                // e c_i è un indice valido
                node_indexes[previous_ring + k] = c_i;
                // if (c_i >= 0 && c_i <= max_index) {
                node_indexes_indexes[c_i] = previous_ring + k;
            } else {
                node_indexes[previous_ring + k] = start;
            }


        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante sx alto
            short c_x = start_x - k; // passi a sinistra dim x
            short c_y = start_y - i + k; // passi in alto dim y
            short c_i = c_y * _width + c_x;

            // posso andare a sx e su?
            if (start_x >= k && start_y >= i - k
                && c_i >= 0 && c_i < _width * _height) {
                node_indexes[previous_ring + i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + i + k;
            } else {
                node_indexes[previous_ring + i + k] = start;
            }

            /*
            node_indexes[previous_ring + i + k] = c_i >= 0 && c_i < _width * _height ? c_i : start;
            if (c_i >= 0 && c_i <= max_index) {
                node_indexes_indexes[c_i] = previous_ring + i + k;
            }
             */
        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante sx basso
            short c_x = start_x - i + k; // dim x
            short c_y = start_y + k; // aum y
            short c_i = c_y * _width + c_x;

            // posso andare a sx e giu?

            if (start_x >= i - k && _height - start_y > k
                && c_i >= 0 && c_i < _width * _height) {
                node_indexes[previous_ring + 2 * i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + 2 * i + k;
            } else {
                node_indexes[previous_ring + 2 * i + k] = start;
            }
        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante dx basso
            short c_x = start_x + k; // aum x
            short c_y = start_y + i - k; // aum y
            short c_i = c_y * _width + c_x;

            // posso andare a dx giu?
            if (_width - start_x > k && _height - start_y > i - k) {
                node_indexes[previous_ring + 3 * i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + 3 * i + k;
            } else {
                node_indexes[previous_ring + 3 * i + k] = start;
            }
        }
        previous_ring += 4 * i;
    }

    // node_indexes contiene in maniera ordinata per l'algoritmo di dijkstra gli indici dei nodi
    // per i nodi out of bound metto indice start: quello non verrà ricontrollato

    dijkstra_node defaultNode(limit + 1, nullptr);
    // tupla<ushort, Casella *> defaultTuple(limit + 1, nullptr);

    GoodArray<dijkstra_node> memory(nodes_number);
    // auto memory = new tupla<ushort, Casella *>[nodes_number];

    for (int i = 0; i < nodes_number; ++i) {
        memory[i] = defaultNode;
    }

    memory[0] = {0, nullptr}; // start

    // end init

    // start algorithm

    for (int i = 0; i < limit; ++i) {
        // ogni livello contiente il percorso possibile per ogni casella con costo i

        for (int j = nodes_number - 1; j > 0; --j) {
            // j = 0, index = start
            // gli altri index == start sono da ignorare
            if (node_indexes[j] == start) {
                continue;
            }

            // arco per arco


            short index_of_left = node_indexes[j] - 1;
            if (index_of_left >= 0
                && index_of_left <= max_index
                && node_indexes_indexes[index_of_left] != -1
                && node_indexes[j] % _width > 0
                && _map[index_of_left]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_left]]->getCostoUscita())) {
                // index of left è un indice valido
                // node_indexes[j] non è sul lato sinistro
                // puoi uscire dalla casella a sinistra e entrare in questa

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_left]].costo // costo per arrivare a sx
                        + _map[index_of_left]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].costo > costo_minimo) {
                    memory[j].costo = costo_minimo;
                    memory[j].provenienza = _map[index_of_left]; // il nodo a sinistra
                }

            }

            short index_of_right = node_indexes[j] + 1;
            if (index_of_right >= 0
                && index_of_right <= max_index
                && node_indexes_indexes[index_of_right] != -1
                && node_indexes[j] % _width < _width - 1
                && _map[index_of_right]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_right]]->getCostoUscita())) {
                // index of right è un indice valido
                // node_indexes[j] non è sul lato destro

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_right]].costo // costo per arrivare a sx
                        + _map[index_of_right]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].costo > costo_minimo) {
                    memory[j].costo = costo_minimo;
                    memory[j].provenienza = _map[index_of_right]; // il nodo a destra
                }

            }

            short index_of_above = node_indexes[j] - _width;
            if (index_of_above >= 0
                && index_of_above <= max_index
                && node_indexes_indexes[index_of_above] != -1
                && node_indexes[j] / _width > 0
                && _map[index_of_above]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_above]]->getCostoUscita())) {
                // index of above è un indice valido
                // node_indexes[j] non è sulla prima riga

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_above]].costo // costo per arrivare a sx
                        + _map[node_indexes[node_indexes_indexes[index_of_above]]]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].costo > costo_minimo) {
                    memory[j].costo = costo_minimo;
                    memory[j].provenienza = _map[index_of_above]; // il nodo sopra
                }

            }
            short index_of_under = node_indexes[j] + _width;
            if (index_of_under >= 0
                && index_of_under <= max_index
                && node_indexes_indexes[index_of_under] != -1
                && node_indexes[j] / _width < _height - 1
                && _map[index_of_under]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_under]]->getCostoUscita())) {
                // index of under è un indice valido
                // node_indexes[j] non è sull'ultima riga

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_under]].costo // costo per arrivare a sx
                        + _map[index_of_under]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].costo > costo_minimo) {
                    memory[j].costo = costo_minimo;
                    memory[j].provenienza = _map[index_of_under]; // il nodo a sinistra
                }

            }
        }
    }

    return {node_indexes, memory, node_indexes_indexes};

}

dijkstra_table Mappa::dijkstra(Casella * start, ushort limit) const {
    return dijkstra(getIndexFromCasella(start), limit);
}

ushort Mappa::getIndexFromCasella(Casella * casella) const {
    ushort i = 0;
    while (_map[i] != casella) {
        ++i;
        if (i >= _width * _height) {
            // TODO error
            break;
        }
    }
    return i;
}


tupla<ushort, Casella *> * Mappa::test_init_dijkstra(std::stringstream & log, ushort start, ushort limit) const {

    // init
    ushort start_x = start % _width;
    ushort start_y = start / _width;

    if (start_y >= _height) {
        // TODO error
    }

    if (limit == -1) {
        limit = _height + _width;
    } // se limit == 1 -> il limite è la mappa (percorso con cammino più lungo)

    // il numero di nodi è 1 + (2 * (ogni nuovo nodo - 1 per ogni nodo non vertice)) * ogni iterazione
    // ovvero: 1 + 4 + (2 * 4 - 0) + (2 * 8 - 4) + (2 * 12 - 8)
    // ovvero: 1 + 4*0 + 4*1 + 4*2 ...


    ushort nodes_number = 1;
    for (int i = 1; i <= limit; ++i) {
        nodes_number += 4 * i;
    }

    short node_indexes[nodes_number];
    short max_index = start_x + (start_y + limit) * _width;
    ushort count = 0;
    while (max_index >= _width * _height) {
        max_index = start_x + count + (start_y + limit - count) * _width;
        count++;
    }
    short node_indexes_indexes[max_index + 1];
    for (int i = 0; i <= max_index; ++i) {
        node_indexes_indexes[i] = -1;
    }

    node_indexes[0] = start;
    node_indexes_indexes[start] = 0;

    ushort previous_ring = 1;
    for (int i = 1; i <= limit; ++i) {
        // per ogni step
        // il sistema di riferimento è come canvas html, le y vanno verso il basso

        // indice dei cicli: i + i * j + k
        // per ogni quadrante
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante dx alto



            short c_x = start_x + i - k; // passi a destra aum x
            short c_y = start_y - k; // passi in alto dim y
            short c_i = c_y * _width + c_x;

            // posso andare a dx e su?

            if (_width - start_x > i - k && start_y >= k
                && c_i >= 0 && c_i < _width * _height) {
                // se posso andare a dx e su con questi valori
                // e c_i è un indice valido
                node_indexes[previous_ring + k] = c_i;
                // if (c_i >= 0 && c_i <= max_index) {
                node_indexes_indexes[c_i] = previous_ring + k;
            } else {
                node_indexes[previous_ring + k] = start;
            }


        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante sx alto
            short c_x = start_x - k; // passi a sinistra dim x
            short c_y = start_y - i + k; // passi in alto dim y
            short c_i = c_y * _width + c_x;

            // posso andare a sx e su?
            if (start_x >= k && start_y >= i - k
                && c_i >= 0 && c_i < _width * _height) {
                node_indexes[previous_ring + i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + i + k;
            } else {
                node_indexes[previous_ring + i + k] = start;
            }

            /*
            node_indexes[previous_ring + i + k] = c_i >= 0 && c_i < _width * _height ? c_i : start;
            if (c_i >= 0 && c_i <= max_index) {
                node_indexes_indexes[c_i] = previous_ring + i + k;
            }
             */
        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante sx basso
            short c_x = start_x - i + k; // dim x
            short c_y = start_y + k; // aum y
            short c_i = c_y * _width + c_x;

            // posso andare a sx e giu?

            if (start_x >= i - k && _height - start_y > k
                && c_i >= 0 && c_i < _width * _height) {
                node_indexes[previous_ring + 2 * i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + 2 * i + k;
            } else {
                node_indexes[previous_ring + 2 * i + k] = start;
            }
        }
        for (int k = 0; k < i; ++k) {
            // aggiungo i indici
            // quadrante dx basso
            short c_x = start_x + k; // aum x
            short c_y = start_y + i - k; // aum y
            short c_i = c_y * _width + c_x;

            // posso andare a dx giu?
            if (_width - start_x > k && _height - start_y > i - k) {
                node_indexes[previous_ring + 3 * i + k] = c_i;
                node_indexes_indexes[c_i] = previous_ring + 3 * i + k;
            } else {
                node_indexes[previous_ring + 3 * i + k] = start;
            }
        }
        previous_ring += 4 * i;
    }

    log << "Indici:\n";
    for (int i = 0; i < nodes_number; ++i) {
        log << "\tIn posizione " << i << " nodo di indice " << node_indexes[i] << "\n";
    }
    log << std::endl << "Indici degli indici\n";
    for (int i = 0; i <= max_index; ++i) {
        log << "\tIn posizione " << i << "indice di indice " << node_indexes_indexes[i] << "\n";
    }

    // node_indexes contiene in maniera ordinata per l'algoritmo di dijkstra gli indici dei nodi
    // per i nodi out of bound metto indice start: quello non verrà ricontrollato

    tupla<ushort, Casella *> defaultTuple(limit + 1, nullptr);

    auto memory = new tupla<ushort, Casella *>[nodes_number];

    for (int i = 0; i < nodes_number; ++i) {
        memory[i] = defaultTuple;
    }

    memory[0] = tupla<ushort, Casella *>(0, nullptr); // start

    // end init

    // start algorithm

    for (int i = 0; i < limit; ++i) {
        log << "Inizio iterazione " << i << std::endl;
        // ogni livello contiente il percorso possibile per ogni casella con costo i

        for (int j = nodes_number - 1; j > 0; --j) {
            // j = 0, index = start
            // gli altri index == start sono da ignorare
            if (node_indexes[j] == start) {
                log << "\tIndice " << j << " == start, che è " << start << ". continue;\n";
                continue;
            }

            // arco per arco
            // sóta la sènder brasca l'è la rassa bèrgamàsca


            short index_of_left = node_indexes[j] - 1;
            if (index_of_left >= 0
                && index_of_left <= max_index
                && node_indexes_indexes[index_of_left] != -1
                && node_indexes[j] % _width > 0
                && _map[index_of_left]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_left]]->getCostoUscita())) {
                // index of left è un indice valido
                // node_indexes[j] non è sul lato sinistro
                // puoi uscire dalla casella a sinistra e entrare in questa

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_left]].first // costo per arrivare a sx
                        + _map[index_of_left]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].first > costo_minimo) {
                    memory[j].first = costo_minimo;
                    memory[j].second = _map[node_indexes[j]]; // il nodo a sinistra
                }

            }

            short index_of_right = node_indexes[j] + 1;
            if (index_of_right >= 0
                && index_of_right <= max_index
                && node_indexes_indexes[index_of_right] != -1
                && node_indexes[j] % _width < _width - 1
                && _map[index_of_right]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_right]]->getCostoUscita())) {
                // index of right è un indice valido
                // node_indexes[j] non è sul lato destro

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_right]].first // costo per arrivare a sx
                        + _map[index_of_right]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].first > costo_minimo) {
                    memory[j].first = costo_minimo;
                    memory[j].second = _map[node_indexes[j]]; // il nodo a sinistra
                }

            }

            short index_of_above = node_indexes[j] - _width;
            if (index_of_above >= 0
                && index_of_above <= max_index
                && node_indexes_indexes[index_of_above] != -1
                && node_indexes[j] / _width > 0
                && _map[index_of_above]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_above]]->getCostoUscita())) {
                // index of above è un indice valido
                // node_indexes[j] non è sulla prima riga

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_above]].first // costo per arrivare a sx
                        + _map[node_indexes[node_indexes_indexes[index_of_above]]]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].first > costo_minimo) {
                    memory[j].first = costo_minimo;
                    memory[j].second = _map[node_indexes[j]]; // il nodo a sinistra
                }

            }
            short index_of_under = node_indexes[j] + _width;
            if (index_of_under >= 0
                && index_of_under <= max_index
                && node_indexes_indexes[index_of_under] != -1
                && node_indexes[j] / _width < _height - 1
                && _map[index_of_under]->canExit(limit - i)
                && _map[node_indexes[j]]->canEnter(limit - i - _map[node_indexes_indexes[index_of_under]]->getCostoUscita())) {
                // index of under è un indice valido
                // node_indexes[j] non è sull'ultima riga

                if (node_indexes[j] == 4) {
                    int breakpoint = 9;
                }

                ushort costo_minimo =
                        memory[node_indexes_indexes[index_of_under]].first // costo per arrivare a sx
                        + _map[index_of_under]->getCostoUscita() // costo per entrare qui
                        + _map[node_indexes[j]]->getCostoEntrata(); // costo per uscire da sx

                if (memory[j].first > costo_minimo) {
                    memory[j].first = costo_minimo;
                    memory[j].second = _map[node_indexes[j]]; // il nodo a sinistra
                }

            }
            log << "\tNodo " << j << " di indice " << node_indexes[j] << " costo " << memory[j].first << "\n";
        }
        log << "Fine iterazione " << i << std::endl;
    }

    return memory;
}

tupla<ushort, ushort> Mappa::getXandYfromCasella(Casella* casella) const {
    ushort index = getIndexFromCasella(casella);
    ushort x = index % _width;
    ushort y = index / _width;
    return {x, y};
}
