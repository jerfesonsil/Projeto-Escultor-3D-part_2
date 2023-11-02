#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H

#include "Sculptor.h"

class FiguraGeometrica {
public:
    virtual ~FiguraGeometrica() {}
    virtual void draw(Sculptor& sculptor) const = 0;
};

#endif // FIGURAGEOMETRICA_H
