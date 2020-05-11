//
// Created by chrim on 22/04/2020.
//

#include "linkedlist.h"

template <typename T>
LinkedList<T>::Node::Node(const T & i, LinkedList<T>::Node * n): info(i), next(n) {}

template <typename T>
LinkedList<T>::Node::Node(const LinkedList<T>::Node & source): info(source.info), next(source.next ? new Node(*source.next) : source.next) {}

template <typename T>
typename LinkedList<T>::Node& LinkedList<T>::Node::operator=(const LinkedList<T>::Node & source) {
    if (this != &source) {
        info = source.info;
        delete next;
        next = source.next ? new Node(*source.next) : source.next;
    }
    return *this;
}

template <typename T>
LinkedList<T>::Node::~Node() {
    delete next;
}

template <typename T>
LinkedList<T>::ConstIterator::ConstIterator(): _node(nullptr) {}

template <typename T>
LinkedList<T>::ConstIterator::ConstIterator(LinkedList<T>::Node * el): _node(el) {}

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
    return *_node;
}

template <typename T>
const T * LinkedList<T>::ConstIterator::operator->() const {
    // TODO error
    return _node;
}

template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++() {
    if (_node) {
        _node = _node->next;
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int) {
    Node* prev = _node;
    if (_node) {
        _node = _node->next;
    }
    return ConstIterator(prev);
}

template <typename T>
LinkedList<T>::Iterator::Iterator(LinkedList<T>::Node* node): ConstIterator(node) {}

template <typename T>
T& LinkedList<T>::Iterator::operator*() const {
    return ConstIterator::operator*();
}

template <typename T>
T * LinkedList<T>::Iterator::operator->() const {
    return ConstIterator::operator->();
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    ConstIterator::operator++();
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    Iterator prev(*this);
    ConstIterator::operator++();
    return prev;
}