#include "Actor.h"

Actor::Actor(const std::string& actorName) {
 //setup actorname
 m_name = actorName;
 //setup shape
 EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
 addComponent(shape);
 //setup transform
 EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
 addComponent(transform);
}

void
Actor::update(float deltaTime) {
 auto transform = getComponent <Transform>();
 auto shape = getComponent <CShape>();

 if (transform && shape) {
  shape->setPosition(transform->getPosition());
  shape->setRotation(transform->getRotation().x);
  shape->setScale(transform->getScale());
 }
}

void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
 for (unsigned int i = 0; i < components.size(); i++) {
  if (components[i].dynamic_pointer_cast<CShape>()) {
   components[i].dynamic_pointer_cast<CShape>()->render(window);
  }
 }
}

void
Actor::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
 auto shape = getComponent<CShape>();
 if (shape) {
  if (!texture.isNull()) {
   shape->setTexture(texture);
   addComponent(texture);
  }
 }
}