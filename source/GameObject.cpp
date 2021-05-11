#include "Components/GameObject.h"

GameObject::GameObject(std::string objectName, guVector position, guQuaternion rotation, guVector scale)
    : Name(objectName), Transform(position, rotation, scale)
{
}

GameObject::~GameObject()
{
    for (Component *comp : SubComponents)
    {
        delete comp;
    }
}

void GameObject::AddComponent(Component *inComp)
{
    inComp->Owner = this;
    SubComponents.push_back(inComp);
}

//use template class to allow for any future components
template <class T>
T *GameObject::FindComponent()
{
    //loop through all sub components
    for (u16 i = 0; i < SubComponents.size(); i++)
    {
        //dynamically cast to the template class in the sub components
        T *tempComp = dynamic_cast<T *>(SubComponents[i]);
        //checks to see if its found and returns
        if (tempComp)
            return tempComp;
    }

    return nullptr;
}