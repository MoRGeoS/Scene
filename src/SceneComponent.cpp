// SceneComponent.cpp
#include <SceneComponent.h>

SceneComponent::SceneComponent(SceneObject& owner) : owner(owner)
{
}

SceneObject& SceneComponent::GetOwner()
{
	return owner;
}

bool& SceneComponent::IsEnabled()
{
	return isEnabled;
}

void SceneComponent::Update()
{
	if (isEnabled)
		OnUpdate();
}

void SceneComponent::FixedUpdate()
{
	if (isEnabled)
		OnFixedUpdate();
}

void SceneComponent::Render()
{
	if (isEnabled)
		OnRender();
}

void SceneComponent::GUI()
{
	if (isEnabled)
		OnGUI();
}
