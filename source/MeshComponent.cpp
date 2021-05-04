#include "Components/MeshComponent.h"

#include "Systems/GraphicsSystem.h"

MeshComponent::MeshComponent(std::string name)
{
    GetModel(name);
}

MeshComponent::~MeshComponent() {}

bool MeshComponent::GetModel(string name)
{
    GraphicsSystem *sysGraphics = GraphicsSystem::GetInstance();

    vector<Mesh> tempMeshVector = sysGraphics->meshCollection;

    for (u16 i = 0; i < tempMeshVector.size(); i++)
    {
        if (tempMeshVector[i].name.compare(name))
        {
            Vertices = tempMeshVector[i].vertices;
            UVs = tempMeshVector[i].uvs;
            Normals = tempMeshVector[i].normals;
            return true;
        }
    }
    return false;
}