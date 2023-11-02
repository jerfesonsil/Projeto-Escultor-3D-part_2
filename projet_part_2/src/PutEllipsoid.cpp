#include "PutEllipsoid.h"

PutEllipsoid::PutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz, float _r, float _g, float _b, float _a)
    : xcenter(_xcenter), ycenter(_ycenter), zcenter(_zcenter), rx(_rx), ry(_ry), rz(_rz), r(_r), g(_g), b(_b), a(_a) {}

void PutEllipsoid::draw(Sculptor& sculptor) const {
    sculptor.setColor(r, g, b, a);
    sculptor.putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}
