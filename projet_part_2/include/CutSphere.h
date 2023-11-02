#ifndef CUTSPHERE_H
#define CUTSPHERE_H

#include "FiguraGeometrica.h"

class CutSphere : public FiguraGeometrica {
private:
    int xcenter, ycenter, zcenter, radius;

public:
    CutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius);
    void draw(Sculptor& sculptor) const override;
};

#endif // CUTSPHERE_H
