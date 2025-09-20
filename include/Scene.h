// Scene.h
#pragma once
#include "SceneObject.h"

class SCENE_API Scene
{
public:
    Scene();
    ~Scene();

	void Update();
	void FixedUpdate();
	void Render();
	void GUI();

	SceneObject& AddObject();

	bool HasObject(size_t id) const;
	bool HasObject(SceneObject* object) const;

	bool RemoveObject(size_t id);
	bool RemoveObject(SceneObject* object);

	SceneObject* GetObject(size_t id);
	size_t GetObjectID(SceneObject* object) const;

private:
	std::unordered_map<size_t, SceneObject> objects;
};
