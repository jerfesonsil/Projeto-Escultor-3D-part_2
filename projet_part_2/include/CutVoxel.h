#ifndef CUTVOXEL_H
#define CUTVOXEL_H

#include "FiguraGeometrica.h"

class CutVoxel : public FiguraGeometrica {
private:
    int x, y, z;

public:
    CutVoxel(int _x, int _y, int _z);
    void draw(Sculptor& sculptor) const override;
};

#endif // CUTVOXEL_H
