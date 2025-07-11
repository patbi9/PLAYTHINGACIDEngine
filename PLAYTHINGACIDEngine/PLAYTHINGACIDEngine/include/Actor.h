#pragma once
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "CShape.h"

class
	Actor : Entity {

public:
	Actor() = default;
	Actor(const std::string & actorName);

	virtual
	~Actor() = default;

	void
		start() override;

	void
		update(float deltaTime) override;

	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	void
		destroy() override;

	template<typename T>
	EngineUtilities::TSharedPointer<T>
		getComponent();


private:
	std::string m_name = "Actor";
};

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
	for (auto& component : components) {
		EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T> ();
		if (specificComponent) {
			return specificComponent;
		}
	}
	//devuelve t shared pointer vacio si no se encuentra
	return EngineUtilities::TSharedPointer<T>();
}