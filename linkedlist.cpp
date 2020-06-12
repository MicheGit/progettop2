//
// Created by chrim on 12/06/2020.
//

#include "linkedlist.h"

const char *LinkedListError::codeToString(ErrorCode code) {
    switch (code) {
        case ErrorCode::INVALID_ITERATOR_USAGE:
            return "LinkedListError: Iteratore non valido in uso.";
        case ErrorCode::PAST_THE_END_ERASE:
            return "LinkedListError: Tentata cancellazione iteratore PastTheEnd.";
        case ErrorCode::PAST_THE_END_REFERENCE:
            return "LinkedListError: Tentato dereferenziamento dell'iteratore PastTheEnd.";
        default:
            return "LinkedListError: Errore non definito.";
    }
}

LinkedListError::LinkedListError(LinkedListError::ErrorCode code)
: Error(codeToString(code)) {

}

LinkedListError::LinkedListError(const char * message): Error(message) {}

