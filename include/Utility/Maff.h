#pragma once

#include <math.h>
#include "ogc/gu.h"

//Useful math things
namespace Maff
{

    const guQuaternion QuaternionIdentity{0, 0, 0, 1};

    const guVector VectorOne{1, 1, 1};

    const guVector VectorZero{0, 0, 0};

    // guVector vecRight{1, 0, 0};
    // guVector vecLeft{-1, 0, 0};

    // guVector vecForward{0, 0, 1};
    // guVector vecBackward{0, 0, -1};

    // guVector vecUp{0, 1, 0};
    // guVector vecDown{0, -1, 0};

    float LengthSq(guVector v);

    float Length(guVector v);

    guQuaternion QuatFromAxisAngle(guVector axis, float angle);

    //Inverse unit quaternion
    guQuaternion QuatInverse(guQuaternion q);

    guVector EulerToDirection(guVector eulerAngle);

}