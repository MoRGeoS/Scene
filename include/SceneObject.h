// SceneObject.h
#pragma once
class Scene;

#include "SceneComponent.h"
#include <unordered_map>

class SCENE_API SceneObject
{
	friend class Scene;
	friend class SceneComponent;
public:
	SceneObject(SceneObject* parent);
	~SceneObject();

	SceneObject* GetParent();
	bool& IsActive();
	bool HasParent() const;

	void Update();
	void FixedUpdate();
	void Render();
	void GUI();

	template<typename T>
	T* GetComponent();

	template<typename T, typename... Args>
	SceneObject& AddComponent(Args&&... args);

	template<typename T>
	bool RemoveComponent();

private:
	SceneObject* parent{ nullptr };
	std::unordered_map<size_t, SceneComponent*> components;
	bool isActive{ true };
};

// ----------------------------------
// | Templated Function Definitions |
// ----------------------------------

template<typename T>
T* SceneObject::GetComponent()
{
	static_assert(std::is_base_of<SceneComponent, T>::value, "T must be derived from SceneComponent");
	size_t typeId = typeid(T).hash_code();
	auto it = components.find(typeId);
	if (it != components.end())
	{
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

template<typename T, typename... Args>
SceneObject& SceneObject::AddComponent(Args&&... args)
{
	static_assert(std::is_base_of<SceneComponent, T>::value, "T must be derived from SceneComponent");
	size_t typeId = typeid(T).hash_code();
	if (components.find(typeId) != components.end())
	{
		return *this; // Component of this type already exists
	}
	T* component = new T(*this, std::forward<Args>(args)...);
	components[typeId] = component;
	return *this;
}

template<typename T>
bool SceneObject::RemoveComponent()
{
	static_assert(std::is_base_of<SceneComponent, T>::value, "T must be derived from SceneComponent");
	size_t typeId = typeid(T).hash_code();
	auto it = components.find(typeId);
	if (it != components.end())
	{
		delete it->second;
		components.erase(it);
		return true;
	}
	return false;
}