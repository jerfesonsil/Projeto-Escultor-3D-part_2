#include "CutVoxel.h"

CutVoxel::CutVoxel(int _x, int _y, int _z)
    : x(_x), y(_y), z(_z) {}

void CutVoxel::draw(Sculptor& sculptor) const {
    sculptor.cutVoxel(x, y, z);
}
