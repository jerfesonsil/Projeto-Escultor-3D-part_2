#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H

#include "FiguraGeometrica.h"

class CutEllipsoid : public FiguraGeometrica {
private:
    int xcenter, ycenter, zcenter, rx, ry, rz;

public:
    CutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz);
    void draw(Sculptor& sculptor) const override;
};

#endif // CUTELLIPSOID_H
