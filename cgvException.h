#ifndef CGV_EXCEPTION_H
#define CGV_EXCEPTION_H

#include <stdexcept>
class cgvException : public exception {
private:
    char* what_happened;
public:
    cgvException(char* _what): what_happened(_what) {};

    virtual const char* what() const throw(){
        return what_happened;
    }
};
#endif
