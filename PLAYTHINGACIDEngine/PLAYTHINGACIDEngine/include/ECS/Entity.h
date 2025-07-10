#pragma once

#include "Prerequisites.h"
#include "Component.h"

class Window;

class Entity
{
public:
	//destructor virtual
	virtual
	~Entity() = default;

	//inicializar
	virtual void
		start() = 0;
	//actualizar
	virtual void
		update(float deltaTime) = 0;
	//renderiza
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;
	//limpiar
	virtual void
		destroy() = 0;

	//agregar un componente a la entidad
	template<typename T> void
	addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	//obtener el componente de la entidad
	template<typename T>
	EngineUtilities::TSharedPointer<T>
		getComponent() {
		for (auto& component : components) {
			EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T> ();
			if (specificComponent) {
				return specificComponent;
			}
		}
		return EngineUtilities::TSharedPointer<T>();
	}

protected:

	bool isActive;
	//id de la entidad
	uint32_t id;
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};