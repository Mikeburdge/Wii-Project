#pragma once

#include "Components/Component.h"
#include <string>
#include <vector>
#include "ogc/gu.h"

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
