#include "Actor.h"

Actor::Actor(const std::string& actorName) {
	//setup actorname
	m_name = actorName;
	//setup shape
	EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
	addComponent(shape);

	//setup transform
	//EngineUtilities::TSharedPointer<Transform> shape = EngineUtilities::MakeShared<Transform>();
	//addComponent(transform);
}

void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {

}