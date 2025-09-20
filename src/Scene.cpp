// Scene.cpp
#include <Scene.h>

#include <random>

Scene::Scene()
{
    // constructor
}

Scene::~Scene()
{
    // destructor
}

void Scene::Update()
{
    // Update logic for the scene
    for (auto& [id, object] : objects)
    {
        object.Update();
	}
}

void Scene::FixedUpdate()
{
    // Fixed update logic for the scene
    for (auto& [id, object] : objects)
    {
        object.FixedUpdate();
	}
}

void Scene::Render()
{
    // Render logic for the scene
    for (auto& [id, object] : objects)
    {
        object.Render();
	}
}

void Scene::GUI()
{
    // GUI logic for the scene
    for (auto& [id, object] : objects)
    {
        object.GUI();
	}
}

SceneObject& Scene::AddObject()
{
	static std::mt19937_64 rng(std::random_device{}());
	size_t id;
    do
    {
        id = rng();
	} while (objects.find(id) != objects.end());

	objects.emplace(id, SceneObject(nullptr));
	return objects.at(id);
}

bool Scene::HasObject(size_t id) const
{
    return objects.find(id) != objects.end();
}

bool Scene::HasObject(SceneObject* object) const
{
    for (const auto& [key, obj] : objects)
    {
        if (&obj == object)
        {
            return true;
        }
    }
    return false;
}

bool Scene::RemoveObject(size_t id)
{
    return objects.erase(id) > 0;
}

bool Scene::RemoveObject(SceneObject* object)
{
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        if (&(it->second) == object)
        {
            objects.erase(it);
            return true;
        }
    }
    return false;
}

SceneObject* Scene::GetObject(size_t id)
{
    auto it = objects.find(id);
    if (it != objects.end())
    {
        return &(it->second);
    }
    return nullptr;
}

size_t Scene::GetObjectID(SceneObject* object) const
{
    for (const auto& [key, obj] : objects)
    {
        if (&obj == object)
        {
            return key;
        }
    }
    return 0; // or some invalid ID
}