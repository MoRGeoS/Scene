// SceneComponent.h
#pragma once
class SceneObject;

#if defined(Scene_EXPORTS)
#	define SCENE_API __declspec(dllexport)
#else
#	define SCENE_API __declspec(dllimport)
#endif

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
