#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H

#include "FiguraGeometrica.h"

class PutEllipsoid : public FiguraGeometrica {
private:
    int xcenter, ycenter, zcenter, rx, ry, rz;
    float r, g, b, a;

public:
    PutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz, float _r, float _g, float _b, float _a);
    void draw(Sculptor& sculptor) const override;
};

#endif // PUTELLIPSOID_H
