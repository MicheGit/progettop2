#ifndef ARRAY_H
#define ARRAY_H

#endif // ARRAY_H


/*
    Rifare bene: Iteratori e ConstIteratori.
    Libro ranzi.


    Manca:

        erase()
        clear()
        push_front()
        pop_front()
*/


template<typename T = int>
class GoodArray{
    public:
        typedef short size_type;
        typedef T value_type;

    private:
        value_type * item;

        size_type _size;
        size_type _capacity;

    public:

        class ConstIterator{
            private:
                friend class GoodArray<T>;
                // Privato perchè non devi poter creare iteatori al di fuori
                // di goodArray.
                value_type* elem;
                ConstIterator(value_type*);
            public:

                ConstIterator();

                // Operazioni standard ConstOperator:

                bool operator==(const ConstIterator &) const;
                bool operator!=(const ConstIterator &) const;

                // Operatori di dereferenzazione
                const value_type& operator*() const;
                const value_type* operator->() const;


                // Muoversi nel constiterator.
                ConstIterator& operator++();
                ConstIterator& operator++(int);

                ConstIterator& operator--();
                ConstIterator& operator--(int);

                ConstIterator& operator+=(const size_type&);
                ConstIterator& operator-=(const size_type&);

                value_type& operator[](const size_type &);
        };

        // Iteratore utilizzabile
        class Iterator{
            private:
                friend class GoodArray<T>;
                // Costruttore privato.
                value_type* elem;
                Iterator(value_type*);

            public:
                Iterator(); // Costruisce l'iteratore vuoto.

                bool operator==(const Iterator&) const;
                bool operator!=(const Iterator&) const;

                value_type& operator*() const;
                value_type* operator->() const;

                Iterator& operator++();
                Iterator operator++(int);

                Iterator& operator--();
                Iterator operator--(int);

                Iterator& operator+=(const size_type &);
                Iterator& operator-=(const size_type&);

                value_type& operator[](const size_type &);

        };

        GoodArray(size_type = 0);

        // Crea lista con size_type quantità di copie di T.
        GoodArray(size_type, value_type);
        // Duplica un goodArray.
        GoodArray(const GoodArray<value_type> &);
        // Assegnazione profonda di due array.
        GoodArray<value_type>& operator=(const GoodArray<value_type> &);


        ~GoodArray();
    // ---- Metodi in O(1) --- //

    // Operatore di accesso casuale. Restituisce elemento T.
        value_type &operator[](const int&) const;


        void push_back(const T& val);
        void push_back(T&& val);

        void pop_back();

    // -- Size methods -- //
        // inutile : size_type max_size() const;
        size_type size() const;
        // Ritorna la capacità del vector.
        size_type capacity() const;
        bool empty() const;

        // Riadatta la dimensione massima dell'array alla dimensione data.
        void resize(size_type);
        // Permette di salvare dello spazio per il vector.
        void reserve(size_type);


        Iterator begin();
        ConstIterator begin() const;

        Iterator end();
        ConstIterator end() const;

};


// Metodi e funzioni di ConstIterator:

template <typename T>
GoodArray<T>::ConstIterator::ConstIterator(T* element): elem(element){}

template <typename T>
GoodArray<T>::ConstIterator::ConstIterator(): elem(nullptr){}

// Operazioni standard ConstOperator:

template <typename T>
bool GoodArray<T>::ConstIterator::operator ==(const ConstIterator & element) const{
    return element.elem == elem;
}
template <typename T>
bool GoodArray<T>::ConstIterator::operator !=(const ConstIterator & element) const{
    return element.elem != elem;
}

// Operatori di dereferenzazione
template <typename T>
const T& GoodArray<T>::ConstIterator::operator *() const{
    return *elem;
}


template <typename T>
const T* GoodArray<T>::ConstIterator::operator->() const{
    return elem;
}

template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator++(){
    if(elem)  ++ elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator++(int offset){
    if(elem)  ++ elem;
    // Restituisco il constiterator di errore.
    return *this;
}

template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator--(){
    if(elem) -- elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator--(int offset){
    if(elem) -- elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator+=(const size_type& offset){
    elem = elem + offset;
    return *this;
}
template <typename T>
typename GoodArray<T>::ConstIterator& GoodArray<T>::ConstIterator::operator-=(const size_type& offset){
    elem = elem - offset;
    return *this;
}


template <typename T>
T& GoodArray<T>::ConstIterator::operator[](const size_type& offset){
     return elem[offset];
}


// Metodi e funzioni di Iterator.

template <typename T>
GoodArray<T>::Iterator::Iterator(T* element): elem(element){}

template <typename T>
GoodArray<T>::Iterator::Iterator(): elem(nullptr){}

// Operazioni standard ConstOperator:

template <typename T>
bool GoodArray<T>::Iterator::operator ==(const Iterator & element) const{
    return element.elem == elem;
}
template <typename T>
bool GoodArray<T>::Iterator::operator !=(const Iterator & element) const{
    return element.elem != elem;
}

// Operatori di dereferenzazione

template <typename T>
T& GoodArray<T>::Iterator::operator*() const{
    return *elem;
}

template <typename T>
T* GoodArray<T>::Iterator::operator->() const{
    return elem;
}

template <typename T>
typename GoodArray<T>::Iterator& GoodArray<T>::Iterator::operator++(){
    if(elem) ++ elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::Iterator GoodArray<T>::Iterator::operator++(int offset){
    if(elem) ++ elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::Iterator& GoodArray<T>::Iterator::operator--(){
    if(elem) -- elem;
    return *this;
}

template <typename T>
typename GoodArray<T>::Iterator GoodArray<T>::Iterator::operator--(int offset){
     if(elem) -- elem;
     return *this;
}

template <typename T>
typename GoodArray<T>::Iterator& GoodArray<T>::Iterator::operator+=(const size_type& offset){
    elem = elem + offset;
    return *this;
}

template <typename T>
typename GoodArray<T>::Iterator& GoodArray<T>::Iterator::operator-=(const size_type& offset){
    elem = elem - offset;
    return *this;
}



template <typename T>
T& GoodArray<T>::Iterator::operator[](const size_type& offset){
     return elem[offset];
}





template <typename T>
GoodArray<T>::GoodArray(size_type elements){
    item = new T[elements];
    _size = 0; _capacity = elements;
}
template <typename T>
GoodArray<T>::GoodArray(size_type elements, T value){
    item = new T*[elements];
    _size  = elements; _capacity = elements;

    for(size_type a = 0; a <_size; a++)
        item[a] = value;
}

template <typename T>
GoodArray<T>::GoodArray(const GoodArray<T> & other){
    item = new T[other.capacity()];

    _size = other.size(); _capacity = other.capacity();
    // Iterator per copiare tutti gli elemetni di other in item.
    for(size_type a = 0; a < _size; ++ a)
        item[a] = other[a];
}

// Metodo clone? O faccioa  meno?

template <typename T>
GoodArray<T>& GoodArray<T>::operator=(const GoodArray<T>& from){
    if(this != &from){
        delete[] item;

        _size = from.size(); _capacity = from.capacity();

        item = new T[from.capacity()];
        // Iterator per copiare tutt gli elementi di other in item.
        for(size_type i = 0; i < _size; ++ i)
            item[i] = from[i];
     }
    return *this;
}


template <typename T>
T& GoodArray<T>::operator[](const int& pos) const{
    // Se out of bounds errore. Gestione dell'eccezione sarà sopra.
    return *(item + pos);
}

template <typename T>
void GoodArray<T>::push_back(const T& val){
    if(_capacity <= _size )
        resize(_capacity * 2);
    item[_size] = T(val);
    ++_size;
}

template <typename T>
void GoodArray<T>::push_back(T&& val){
    if(_capacity <= _size )
        resize(_capacity * 2);
    item[_size] =  T(val);
    ++_size;
}

template <typename T>
void GoodArray<T>::pop_back(){
    if(_size ==  0)
        return; // Exception? if size = 0  and call of popo_back
    (item + (_size - 1))->~T(); --_size;
}


/* ___________________________________________________________
 *
 *   Size Methods:
 *      metodi per la gestione della dimensione dell'array
 *      dinamico. Size è dimensione in elemtni occupati invece
 *      capacity è lo spazio totale disponibile.
 * ___________________________________________________________
*/

template <typename T>   // Ritorna dimensione attuale.
typename GoodArray<T>::size_type GoodArray<T>::size() const{
    return _size;
}

template <typename T>   // Ritorna dimensione massima attuale.
typename GoodArray<T>::size_type GoodArray<T>::capacity() const{
    return _capacity;
}

template <typename T>
bool GoodArray<T>::empty() const{
    return _size == 0;
}

template <typename T>
void GoodArray<T>::resize(GoodArray<T>::size_type newCapacity){
    if(newCapacity != _size){
        // Array di appoggio da cui poi copio in *this.
        GoodArray<T> * app  = new GoodArray<T>(newCapacity);

        if(newCapacity < _capacity)
            for(size_type i = 0; i < newCapacity; i++)
                app->push_back(item[i]);

         else if( newCapacity > _capacity )
            for(size_type i = 0; i <_size; ++ i)
                app->push_back(item[i]);

        *this =  *app;
    }
}

// Se l'array è più piccolo della quantità da riservare allora
// devo ridimensionare l'array alla dimensione richiesta.
template <typename T>
void GoodArray<T>::reserve(GoodArray<T>::size_type amount){
    if(_size + amount > _capacity)
        resize(_size + amount);
}


// Da iteratori inziali e finali .

// Iniziali
template <typename T>
typename GoodArray<T>::Iterator GoodArray<T>::begin(){
    return item;
}

template <typename T>
typename GoodArray<T>::ConstIterator GoodArray<T>::begin() const{
    return item;
}

// Finali
template <typename T>
typename GoodArray<T>::Iterator GoodArray<T>::end(){
    return item + _size;
}

template <typename T>
typename GoodArray<T>::ConstIterator GoodArray<T>::end() const{
    return item + _size;
}


template <typename T>
GoodArray<T>::~GoodArray(){
    delete[] item;
}



