#ifndef CGV_EXCEPTION_H
#define CGV_EXCEPTION_H

#include <stdexcept>
class cgvException : public exception {
private:
    const char* what_happened;
public:
    cgvException(const char* _what): what_happened(_what) {};

    virtual const char* what() const throw(){
        return what_happened;
    }
};
#endif
