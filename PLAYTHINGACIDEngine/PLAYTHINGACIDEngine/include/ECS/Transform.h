#pragma once
#include "Prerequisites.h"
#include "Component.h"
using sf::Vector2f;

class Transform : public Component
{
public:
	Transform() : Component(ComponentType::TRANSFORM),
				  position(0.0f, 0.0f),
				  rotation(0.0f, 0.0f),
				  scale(1.0f, 1.0f)
	{
	}

	void 
		start() override {}

	void 
		update(float deltaTime) override {}

	void 
		render(const EngineUtilities::TSharedPointer<Window>& window) override {}

	void 
		destroy() override {}


	void 
		setPosition(const Vector2f& pos) {
		position = pos;
	}

	void 
		setRotation(const Vector2f& rot) {
		rotation = rot;
	}

	void 
		setScale(const Vector2f& scl) {
		scale = scl;
	}

	Vector2f 
		getPosition() const { 
		return position;
	
	}

	Vector2f
		getRotation() const { 
		return rotation; 
	}

	Vector2f 
		getScale() const { 
		return scale; 
	}

	virtual
	~Transform() = default;

private:
	sf::Vector2f position;
	sf::Vector2f rotation;
	sf::Vector2f scale;
};