// SceneComponent.h
#pragma once
class SceneObject;

#include "Export.h"

class SCENE_API SceneComponent
{
	friend class SceneObject;
public:
	SceneObject& GetOwner();
	bool& IsEnabled();

    virtual void OnUpdate() {};
	virtual void OnFixedUpdate() {};
    virtual void OnRender() {};
    virtual void OnGUI() {};

	void Update();
	void FixedUpdate();
	void Render();
	void GUI();

protected:
	explicit SceneComponent(SceneObject& owner);
	virtual ~SceneComponent() = default;

protected:
    bool isEnabled { true };
	SceneObject& owner;
};
