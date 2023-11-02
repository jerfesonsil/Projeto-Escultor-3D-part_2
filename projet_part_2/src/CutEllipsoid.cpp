#include "CutEllipsoid.h"

CutEllipsoid::CutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz)
    : xcenter(_xcenter), ycenter(_ycenter), zcenter(_zcenter), rx(_rx), ry(_ry), rz(_rz) {}

void CutEllipsoid::draw(Sculptor& sculptor) const {
    sculptor.cutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}
