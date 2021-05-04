#pragma once

#include "Components/Component.h"
#include <string>

using namespace std;

class MeshComponent : public Component
{
public:
    MeshComponent(string name);
    ~MeshComponent();

    bool GetModel(string name);

    vector<guVector> Vertices;
    vector<guVector> UVs;
    vector<guVector> Normals;
};
