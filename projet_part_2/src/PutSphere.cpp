#include "PutSphere.h"

PutSphere::PutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius, float _r, float _g, float _b, float _a)
    : xcenter(_xcenter), ycenter(_ycenter), zcenter(_zcenter), radius(_radius), r(_r), g(_g), b(_b), a(_a) {}

void PutSphere::draw(Sculptor& sculptor) const {
    sculptor.setColor(r, g, b, a);
    sculptor.putSphere(xcenter, ycenter, zcenter, radius);
}
