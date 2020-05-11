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

    /***
     * Classe Node
     *
     * Struttura che rappresenta un elemento nella lista.
     */
    class Node {
    public:
        T info;
        Node *next;

        /***
         * Costruttore
         *
         * Costruisce `info` con costruttore di copia e assegna `next`.
         */
        Node(const T &, Node * = nullptr);

        /***
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

    Node *_first;
    Node *_last; // per push back
    unsigned short _size;

public:
    typedef unsigned short size_type;

    /***
     * Classe ConstIterator
     *
     * Rappresenta un iteratore utilizzabile per scorrere gli elementi della lista. Trattandosi di una lista
     *  unidirezionale, l'iteratore può solo essere incrementato. Gli elementi ai quali viene fatto puntare non sono
     *  modificabili
     */
    class ConstIterator {
        Node *_node;

        /***
         * Costruttore parametrizzato privato.
         *
         * Privato perché non dovrebbe essere consentito di creare iteratori al di fuori dei metodi di LinkedList,
         *  si rischierebbe di creare iteratori non safe.
         *
         */
        ConstIterator(Node *);

    public:

        /***
         * Costruttore di default pubblico.
         *
         * Crea un ConstIterator PastTheEnd.
         */
        ConstIterator();
        /***
         * Costruttore di copia, assegnazione e distruzione sono tutti in forma standard.
         */

        // Operazioni consentite standard

        /***
         * Operatore di uguaglianza
         *
         * @return true sse i due iteratori puntano allo stesso oggetto
         */
        bool operator==(const ConstIterator &) const;

        /***
         * Operatore di diseguaglianza
         *
         * @return true sse l'uguaglianza avesse restituito false
         */
        bool operator!=(const ConstIterator &) const;

        /***
         * Operatore di dereferenziazione
         *
         * Se l'iteratore era PastTheEnd lancia un'eccezione di tipo LinkedList::Error.
         *
         * @return l'elemento puntato per riferimento.
         */
        virtual const T &operator*() const;

        /***
         * Operatore di dereferenziazione e accesso
         *
         * Invoca un metodo o cerca di accedere a un campo dati nell'elemento puntato.
         *
         * Se l'iteratore era PastTheEnd lancia un'eccezione di tipo LinkedList::Error.
         */
        virtual const T *operator->() const;

        /***
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

        /***
         * Operatore di incremento postfisso
         *
         * Modifica l'iteratore puntato, facendolo puntare al prossimo elemento nella lista o facendolo diventare
         *  PastTheEnd.
         *
         * @return un iteratore che punta all'elemento puntato prima dell'incremento.
         */
        ConstIterator operator++(int);
    };

    /***
     * Classe Iterator <: ConstIterator
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
    class Iterator : public ConstIterator {
        Iterator(Node*);
    public:

        T &operator*() const override;

        T *operator->() const override;

        Iterator &operator++() override;

        /**
         * Operatore di incremento
         *
         * Overload dell'operatore di incremento di ConstIterator.
         *
         * @return un Iterator che punta all'elemento precedente.
         */
        Iterator operator++(int);
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
    LinkedList(size_type, const T &);

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

    /**
     * Inserimento
     *
     * Inserisco in tempo costante l'elemento subito prima dell'iteratore dato.
     *
     * @return un iteratore che punta all'elemento appena inserito.
    */
    Iterator insert(const ConstIterator &, const T &);

    /**
     * Inserimento
     *
     * Inserisco in tempo costante `n` elementi prima dell'elemento puntato dall'iteratore.
     *
     * @return un iteratore che punta al primo elemento inserito.
     */
    Iterator insert(const ConstIterator &, size_type, const T &);

    Iterator push_back(const T &);

    Iterator push_front(const T &);

    // metodi di rimozione
    /**
     * Rimozione
     *
     * Rimuovo in tempo costante l'elemento puntato da quell'iteratore.
     *
     * @return un iteratore all'elemento che si trova ora la posto dell'elemento tolto.
     */
    Iterator erase(const Iterator &);

    Iterator erase(const Iterator &, const ConstIterator &);

    T pop_back();

    T pop_front();

    void clear(); // <= erase(begin(), end());

    // metodi di iterazione

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

    // Metodi in tempo O(n)
    // metodi di ricerca

    Iterator search_equal(const T &);

    ConstIterator search_equal(const T &) const;

    Iterator get_by_index(size_type);

    ConstIterator get_by_index(size_type) const;

    // TODO std::function in <functional>
    //  foreach : ([const] T -> void) -> void, find : ([const] T -> bool) -> [Const]Iterator

};


#endif //ZOMBIEDUNGEON_LINKEDLIST_H
