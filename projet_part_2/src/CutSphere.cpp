#include "CutSphere.h"

CutSphere::CutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius)
    : xcenter(_xcenter), ycenter(_ycenter), zcenter(_zcenter), radius(_radius) {}

void CutSphere::draw(Sculptor& sculptor) const {
    sculptor.cutSphere(xcenter, ycenter, zcenter, radius);
}
