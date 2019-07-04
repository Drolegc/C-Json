// IntKey.h

#ifndef INTKEY_H
#define INTKEY_H

#include "interfaces/OrderedKey.h"

struct IntKey : public OrderedKey {
public:
    IntKey(int entero);
    ~IntKey() {}

    ComparisonRes compare(OrderedKey* k) const;

private:
    int num;
};

#endif
