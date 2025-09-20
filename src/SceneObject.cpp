// SceneObject.cpp
#include <SceneObject.h>

SceneObject::SceneObject(SceneObject* parent)
{
    this->parent = parent;
}

SceneObject::~SceneObject()
{
}

SceneObject* SceneObject::GetParent()
{
    return parent;
}

bool& SceneObject::IsActive()
{
    return isActive;
}

bool SceneObject::HasParent() const
{
    return parent != nullptr;
}

void SceneObject::Update()
{
    if (isActive)
    {
        for (auto& [typeId, component] : components)
        {
            component->Update();
        }
    }
}

void SceneObject::FixedUpdate()
{
    if (isActive)
    {
        for (auto& [typeId, component] : components)
        {
            component->FixedUpdate();
        }
    }
}

void SceneObject::Render()
{
    if (isActive)
    {
        for (auto& [typeId, component] : components)
        {
            component->Render();
        }
    }
}

void SceneObject::GUI()
{
    if (isActive)
    {
        for (auto& [typeId, component] : components)
        {
            component->GUI();
        }
    }
}