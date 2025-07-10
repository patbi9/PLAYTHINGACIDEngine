#pragma once
#include "Prerequisites.h"

class Window;

enum
	ComponentType {
	NONE = 0,
	TRANSFORM = 1,
	SPRITE = 2,
	RENDERER = 3,
	PHYSICS = 4,
	AUDIOSOURCE = 5,
	SHAPE = 6,
	TEXTURE = 7
};

class 
Component {
public:

	Component() =  default;

	Component(const ComponentType type) : m_type(type) {}
	//destructor
	virtual
	~Component() = default;
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
	//obtener el tipo de componente
	ComponentType
		getType() const { return m_type; }

protected:
	ComponentType m_type; //tipo de componente

};