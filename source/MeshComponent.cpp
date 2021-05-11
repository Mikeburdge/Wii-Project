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
	for (u16 i = 0; i < sysGraphics->meshCollection.size(); i++)
	{
		if (sysGraphics->meshCollection[i].name.compare(name) == 0)
		{
			Vertices = sysGraphics->meshCollection[i].vertices;
			UVs = sysGraphics->meshCollection[i].uvs;
			Normals = sysGraphics->meshCollection[i].normals;
			return true;
		}
	}
	return false;
}