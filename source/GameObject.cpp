#include "Components/GameObject.h"

GameObject::GameObject(std::string objectName, guVector position, guQuaternion rotation, guVector scale)
{
}

GameObject::~GameObject()
{
    for (Component *comp : subComponents)
    {
        delete comp;
    }
}

void GameObject::AddComponent(Component *inComp)
{
    inComp->owner = this;
    subComponents.push_back(inComp);
}

//use template class to allow for any future components
template <class T>
T GameObject::FindComponent(T compToFind)
{
    //loop through all sub components
    for (u16 i = 0; i < subComponents.size(); i++)
    {
        //dynamically cast to the template class in the sub components
        T *tempComp = dynamic_cast<T *>(subComponents[i]);
        //checks to see if its found and returns
        if (tempComp)
            return tempComp;
    }

    return nullptr;
}