#include "Utility/Maff.h"

namespace Maff
{
    float LengthSq(guVector v)
    {
        return (v.x * v.x + v.y * v.y + v.z * v.z);
    }
    float Length(guVector v)
    {
        return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    }
    guQuaternion QuatFromAxisAngle(guVector axis, float angle)
    {
        guQuaternion quat;
        float halfAngle = angle / 2;
        quat.w = cos(halfAngle);
        quat.x = axis.x * sin(halfAngle);
        quat.y = axis.y * sin(halfAngle);
        quat.z = axis.z * sin(halfAngle);
        return quat;
    }

    //Inverse unit quaternion
    guQuaternion QuatInverse(guQuaternion q)
    {
        return guQuaternion{-q.x, -q.y, -q.z, q.w};
    }

    guVector EulerToDirection(guVector eulerAngle)
    {

        float z = cos(eulerAngle.y) * cos(eulerAngle.x);
        float y = sin(eulerAngle.x);
        float x = cos(eulerAngle.x) * sin(eulerAngle.y);
        guVector rv = guVector{x, y, z};

        return rv;
    }
}