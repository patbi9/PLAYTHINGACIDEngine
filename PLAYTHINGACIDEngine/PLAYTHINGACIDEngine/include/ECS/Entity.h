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
		start(float deltaTime) = 0;
	//actualizar
	virtual void
		update(float deltaTime) = 0;
	//renderiza
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;
	//limpiar
	virtual void
		destroy() = 0;

protected:

	bool isActive;
	//id de la entidad
	uint32_t id;
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};