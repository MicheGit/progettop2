//
// Created by chrim on 12/06/2020.
//

#include "error.h"

Error::Error(const char * message)
: _message(message) {

}

Error::operator const char *() const {
    return _message;
}
