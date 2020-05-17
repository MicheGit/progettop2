//
// Created by chrim on 14/04/2020.
//

#ifndef ZOMBIEDUNGEON_LINKEDLIST_H
#define ZOMBIEDUNGEON_LINKEDLIST_H

/*
 * The return type of an overriding function shall be either identical to the return type of the overridden function or
 * covariant with the classes of the functions. If a function D::f overrides a function B::f, the return types of the
 * functions are covariant if they satisfy the following criteria:
 *  (7.1) — both are pointers to classes, both are lvalue references to classes, or both are rvalue references to
 * classes
 *  (7.2) — the class in the return type of B::f is the same class as the class in the return type of D::f, or is an
 * unambiguous and accessible direct or indirect base class of the class in the return type of D::f
 *  (7.3) — both pointers or references have the same cv-qualification and the class type in the return type of D::f
 * has the same cv-qualification as or less cv-qualification than the class type in the return type of B::f.
 *
 */


/***
 * @tparam T
 *
 * Lista singolarmente linkata
 *
 * Contiene elementi di tipo T.
 *
 * Rispetta alcune peculiarità standard delle liste linkate:
 *  Inserimento in tempo O(1);
 *  Rimozione in tempo O(1);
 *  Accesso casuale in tempo O(n).
 *
 *
 */
template<typename T>
class LinkedList {
public:
    typedef unsigned short size_type;
    typedef T value_type;
private:

    /***
     * Classe Node
     *
     * Struttura che rappresenta un elemento nella lista.
     */
    class Node {
    public:
        T * info;
        Node * next;
        Node * prev;

        /**
         * Costruisce un nodo past the end
         *
         */
        Node();

        /**
         * Costruttore
         *
         * Costruisce `info` con costruttore di copia e assegna `next`.
         */
        Node(const T &, Node * = nullptr, Node* = nullptr);

        /**
         * Costruttore
         *
         * Esegue una copia profonda, duplicando l'eventuale lista next.
         */
        Node(const Node &);

        /***
         * Assegnazione
         *
         * Esegue una copia profonda del nodo parametro e l'assegna al nodo origine.
         * Ritorna il nodo origine per riferimento
         */
        LinkedList<T>::Node &operator=(const Node &);

        /***
         * Distruttore profondo
         *
         * Elimina il nodo corrente e distrugge la lista `next`.
         */
        ~Node();
    };

    Node * _first;
    Node * const _pastTheEnd;
    size_type _size;

public:

    /***
     * Classe ConstIterator
     *
     * Rappresenta un iteratore utilizzabile per scorrere gli elementi della lista. Trattandosi di una lista
     *  unidirezionale, l'iteratore può solo essere incrementato. Gli elementi ai quali viene fatto puntare non sono
     *  modificabili
     */
    class ConstIterator {
        friend class LinkedList<T>;

        Node * _node;


        /**
         * Costruttore parametrizzato privato.
         *
         * Privato perché non dovrebbe essere consentito di creare iteratori al di fuori dei metodi di LinkedList,
         *  si rischierebbe di creare iteratori non safe.
         *
         */
        ConstIterator(Node *);

    public:

        /**
         * Costruttore di default pubblico.
         *
         * Crea un ConstIterator non valido.
         */
        ConstIterator();


        /**
         * Costruttore di copia, assegnazione e distruzione sono tutti in forma standard.
         */

        // Operazioni consentite standard

        /**
         * Operatore di uguaglianza
         *
         * @return true sse i due iteratori puntano allo stesso oggetto
         */
        bool operator==(const ConstIterator &) const;

        /**
         * Operatore di diseguaglianza
         *
         * @return true sse l'uguaglianza avesse restituito false
         */
        bool operator!=(const ConstIterator &) const;

        /**
         * Operatore di dereferenziazione
         *
         * Se l'iteratore era PastTheEnd lancia un'eccezione di tipo LinkedList::Error.
         *
         * @return l'elemento puntato per riferimento.
         */
        virtual const T &operator*() const;

        /**
         * Operatore di dereferenziazione e accesso
         *
         * Invoca un metodo o cerca di accedere a un campo dati nell'elemento puntato.
         *
         * Se l'iteratore era PastTheEnd lancia un'eccezione di tipo LinkedList::Error.
         */
        virtual const T *operator->() const;

        /**
         * Operatore di incremento prefisso
         *
         * Modifica l'iteratore puntato, facendolo puntare al prossimo elemento nella lista o facendolo diventare
         *  PastTheEnd.
         *
         * Se viene chiamato su un iteratore PastTheEnd non succede nulla.
         *
         * @return l'iteratore stesso dopo l'incremento.
         */
        virtual ConstIterator &operator++();

        /**
         * Operatore di incremento postfisso
         *
         * Modifica l'iteratore puntato, facendolo puntare al prossimo elemento nella lista o facendolo diventare
         *  PastTheEnd.
         *
         * @return un iteratore che punta all'elemento puntato prima dell'incremento.
         */
        ConstIterator operator++(int);

        /**
         * Operatore -- prefisso
         *
         * Modifica l'iteratore puntato, facendolo puntare al precedente elemento nella lista o facendolo diventare
         *  l'ultimo se era past the end.
         *
         * @return l'iteratore stesso
         */
        virtual ConstIterator &operator--();

        /**
         * Operatore di incremento postfisso
         *
         * Modifica l'iteratore puntato, facendolo puntare al precedente elemento nella lista o facendolo diventare
         *  l'ultimo se era past the end.
         *
         * @return un iteratore che punta all'elemento puntato prima dell'operazione.
         */
        ConstIterator operator--(int);
    };

    /***
     * Classe Iterator
     *
     * Rappresenta un iteratore utilizzabile per scorrere gli elementi della lista. Trattandosi di una lista
     *  unidirezionale, l'iteratore può solo essere incrementato.
     *
     * Il funzionamento è lo stesso di un ConstIterator, l'unica differenza starà nel tipo di ritorno dei metodi di
     *  dereferenziazione.
     *
     * È, inoltre, convertibile automaticamente in un ConstIterator.
     *
     */
    class Iterator {
        friend class LinkedList<T>;

        Node * _node;

        Iterator(Node*);
    public:
        Iterator();

        bool operator==(const Iterator&) const;

        bool operator!=(const Iterator&) const;

        T &operator*() const;

        T *operator->() const;

        Iterator &operator++();

        /**
         * Operatore di incremento
         *
         * Overload dell'operatore di incremento di ConstIterator.
         *
         * @return un Iterator che punta all'elemento precedente.
         */
        Iterator operator++(int);

        Iterator &operator--();

        /**
         * Operatore di incremento
         *
         * Overload dell'operatore di incremento di ConstIterator.
         *
         * @return un Iterator che punta all'elemento precedente.
         */
        Iterator operator--(int);
    };

    /**
     * Costruttore
     *
     * Crea una lista con `n` elementi inizializzati al valore di default di T.
     *
     */
    LinkedList(size_type = 0);

    /***
     * Costruttore
     *
     * Crea una lista con `n` elementi copie dell'elemento `t`.
     *
     */
    LinkedList(size_type, T);

    /***
     * Costruttore di copia profonda
     *
     * Costruisce una lista duplicando gli elementi della sorgente.
     */
    LinkedList(const LinkedList<T> &);

    /***
     * Assegnazione profonda
     *
     * Elimina gli elementi della lista e la riempie con copie della lista sorgente.
     */
    LinkedList<T> &operator=(const LinkedList<T> &);

    /***
     * Distruzione profonda
     *
     * Elimina gli elementi della lista.
     */
    ~LinkedList();


    // Metodi in tempo costante
    // Metodi di inserimento

    size_type size() const;

    /**
     * Inserimento
     *
     * Inserisco in tempo costante l'elemento subito prima dell'iteratore dato.
     *
     * @return un iteratore che punta all'elemento appena inserito.
    */
    Iterator insert(Iterator, T);

    /**
     * Inserimento
     *
     * Inserisco in tempo costante `n` elementi prima dell'elemento puntato dall'iteratore.
     *
     * @return void
     */
    void insert(Iterator, size_type, T); // costruisce di copia

    Iterator push_back(T);

    Iterator push_front(T);

    // metodi di rimozione
    /**
     * Rimozione
     *
     * Rimuovo in tempo costante l'elemento puntato da quell'iteratore.
     *
     * @return un iteratore all'elemento che si trova ora al posto dell'elemento tolto.
     */
    Iterator erase(Iterator);

    Iterator erase(Iterator, Iterator);

    T pop_back();

    T pop_front();

    void clear(); // <= erase(begin(), end());

    // metodi di iterazione

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

    // TODO std::function in <functional>
    //  foreach : ([const] T -> void) -> void, find : ([const] T -> bool) -> [Const]Iterator



};

template <typename T>
LinkedList<T>::Node::Node()
        : info(nullptr), next(this), prev(nullptr) {}

template <typename T>
LinkedList<T>::Node::Node(const T & i, LinkedList<T>::Node * n, LinkedList<T>::Node * p)
        : info(new T(i)), next(n), prev(p) {}

template <typename T>
LinkedList<T>::Node::Node(const LinkedList<T>::Node & source)
        : info(source.info ? new T(*source.info) : nullptr), next(source.next || source.next != &source ? new Node(*source.next) : nullptr), prev(nullptr) {
    if (next) {
        next->prev = this;
    } else {
        next = this;
    }
}

template <typename T>
typename LinkedList<T>::Node& LinkedList<T>::Node::operator=(const LinkedList<T>::Node & source) {
    if (this != &source) {
        info = source.info;
        delete next;

        next = source.next || source.next != &source ? new Node(*source.next) : nullptr;

        if (next) {
            next->prev = this;
        } else {
            next = this;
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>::Node::~Node() {
    if (next != this) {
        delete next;
    }
    delete info;
}

template <typename T>
LinkedList<T>::ConstIterator::ConstIterator()
        : _node(nullptr) {}

template <typename T>
LinkedList<T>::ConstIterator::ConstIterator(LinkedList<T>::Node * el)
        : _node(el) {}

template <typename T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator & other) const {
    return _node == other._node;
}

template <typename T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator & other) const {
    return _node != other._node;
}

template <typename T>
const T & LinkedList<T>::ConstIterator::operator*() const {
    // TODO error

    /* TODO
    if (_node->next == _node) {
        throw new Error();
    }
    */
    return *_node->info;
}

template <typename T>
const T * LinkedList<T>::ConstIterator::operator->() const {
    // TODO error

    /* TODO
    if (_node->next == _node) {
        throw new Error();
    }
    */
    return _node->info;
}

template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++() {
    // TODO error se invalid
    if (_node) {
        _node = _node->next;
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int) {
    // TODO error se invalid
    Node* aux = _node;
    if (_node) {
        _node = _node->next;
    }
    return ConstIterator(aux);
}

template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator--() {
    // TODO error se invalid
    if (_node) {
        _node = _node->prev;
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator--(int) {
    // TODO error se invalid
    Node* aux = _node;
    if (_node) {
        _node = _node->prev;
    }
    return ConstIterator(aux);
}

template <typename T>
LinkedList<T>::Iterator::Iterator(LinkedList<T>::Node* node)
    : _node(node) {}

template <typename T>
LinkedList<T>::Iterator::Iterator()
    : _node(nullptr) {}

template <typename T>
T& LinkedList<T>::Iterator::operator*() const {
    // TODO error
    return *_node->info;
}

template <typename T>
T * LinkedList<T>::Iterator::operator->() const {
    // TODO error
    return _node->info;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    if (_node) {
        _node = _node->next;
    } // TODO error
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    Iterator prev(*this);
    if (_node) {
        _node = _node->next;
    } // TODO error
    return prev;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--() {
    if (_node) {
        _node = _node->prev;
    } // TODO error
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
    Iterator aux(*this);
    if (_node) {
        _node = _node->prev;
    } // TODO error
    return aux;
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const LinkedList::Iterator & other) const {
    return _node == other._node;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const LinkedList::Iterator & other) const {
    return _node != other._node;
}

template <typename T>
LinkedList<T>::LinkedList(size_type dim)
    : _pastTheEnd(new Node()), _size(0) {
        _first = _pastTheEnd;
    for (int i = 0; i < dim; i++) {
        insert(_pastTheEnd, T());
    }
}

template <typename T>
LinkedList<T>::LinkedList(size_type dim, T sample)
    : _pastTheEnd(new Node()), _size(0) {
    _first = _pastTheEnd;
    for (int i = 0; i < dim; i++) {
        insert(_pastTheEnd, sample);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & other)
    : _first(new Node(*other._first)), _size(other._size) {
        _pastTheEnd = _first;
    while (_pastTheEnd->next != _pastTheEnd) {
        _pastTheEnd = _pastTheEnd->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & other) {
    if (_first != other._first) {
        delete _first;

        _first = new Node(*other._first);
        _pastTheEnd = _first;

        while (_pastTheEnd->next != _pastTheEnd) {
            _pastTheEnd = _pastTheEnd->next;
        }

        _size = other._size;
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    delete _first;
    // avendo distrutto _first, si distruggeranno in automatico tutti i nodi, compreso last
}

template <typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const {
    return _size;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::insert(Iterator it, T element) {
    if (it._node) {
        // iteratore valido, eseguo
        Node * nodo = new Node(element, it._node, it._node->prev);
        nodo->next->prev = nodo;
        if (nodo->prev) {
            nodo->prev->next = nodo;
        } else {
            _first = nodo;
        }
        _size++;
        return Iterator(nodo);
    } else {
        // TODO error
        return Iterator();
    }
}

template <typename T>
void LinkedList<T>::insert(Iterator it, size_type s, T element) {
    for (int i = 0; i < s; i++) {
        insert(it, element);
    }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::push_back(T element) {
    return insert(end(), element);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::push_front(T element) {
    return insert(begin(), element);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(Iterator it) {
    if (it._node == _pastTheEnd) {
        // TODO error
        return Iterator();
    }
    if (it._node) {
        it._node->next->prev = it._node->prev;

        if (it._node->prev) {
            it._node->prev->next = it._node->next;
        } else {
            _first = it._node->next;
        }
        Node* aux = it._node->next;
        it._node->next = nullptr;
        it._node->prev = nullptr;
        delete it._node;
        _size--;
        return Iterator(aux);
    } else {
        // TODO error
        return Iterator();
    }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(LinkedList<T>::Iterator it1, LinkedList<T>::Iterator it2) {
    int count = 0;
    Iterator aux = it1;
    while (aux != end() && aux != it2) {
        count++;
        ++aux;
    }
    if (aux == end()) {
        // TODO error
        return Iterator();
    }
    for (int i = 0; i < count; i++) {
        it1 = erase(it1);
    }
    return it2;
}

template <typename T>
T LinkedList<T>::pop_back() {
    Iterator last = end()--;
    T aux = *last;
    erase(last);
    return aux;
}

template <typename T>
T LinkedList<T>::pop_front() {
    Iterator first = begin();
    T aux = *first;
    erase(first);
    return aux;
}

template <typename T>
void LinkedList<T>::clear() {
    erase(begin(), end());
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return _first;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const {
    return _first;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return _pastTheEnd;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end() const {
    return _pastTheEnd;
}


#endif //ZOMBIEDUNGEON_LINKEDLIST_H
