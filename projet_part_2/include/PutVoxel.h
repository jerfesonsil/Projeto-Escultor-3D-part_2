#ifndef PUTVOXEL_H
#define PUTVOXEL_H

#include "FiguraGeometrica.h"

class PutVoxel : public FiguraGeometrica {
private:
    int x, y, z;
    float r, g, b, a;

public:
    PutVoxel(int _x, int _y, int _z, float _r, float _g, float _b, float _a);
    void draw(Sculptor& sculptor) const override;
};

#endif // PUTVOXEL_H
