#include "window.h"

Window::Window(int width, int height, const std::string& title) {
 //Inicializar ventana
    m_windowPtr = EngineUtilities::MakeUnique <sf::RenderWindow>(
        sf::VideoMode({ static_cast<unsigned int>(width), 
                        static_cast<unsigned int>(height) }), 
                        title, 
                        sf::Style::Default
    );

 if (!m_windowPtr.isNull()) {
  m_windowPtr->setFramerateLimit(60); //limitar 60 fps
  MESSAGE("Window", "Window", "Window created successfully");
 }
 else {
  ERROR("Window", "Window", "Failed to create window");
 }

 //initialize imgui resource
 ImGui::SFML::Init(*m_windowPtr);
}

Window::~Window(){
	ImGui::SFML::Shutdown();
 m_windowPtr.release();
 //SAFE_PTR_RELEASE(m_window);
}

void 
Window::handleEvents()
{
    //while (m_windowPtr->isOpen())
    //{
    //}
        //process events
        while (const std::optional event = m_windowPtr->pollEvent())
        {
            ImGui::SFML::ProcessEvent(*m_windowPtr, *event);
            //close window: exit
            if (event->is<sf::Event::Closed>())
                m_windowPtr->close();
        }
}

bool
 Window::isOpen() const {
 // Check that window is not null

 if (!m_windowPtr.isNull()) {
  return m_windowPtr->isOpen();
 }
 else {
  ERROR("Window", "isOpen", "Window is null");
  return false;
 }
}

void
 Window::clear(const sf::Color& color) {
 if (!m_windowPtr.isNull()) {
  m_windowPtr->clear(color);
 }
 else {
  ERROR("Window", "isOpen", "Window is null");
        
 }
}

void
 Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
 if (!m_windowPtr.isNull()) {
  m_windowPtr->draw(drawable, states);
 }
 else {
  ERROR("Window", "draw", "Window is null");
 }
}

void
 Window::display() {
 if (!m_windowPtr.isNull()) {
  m_windowPtr->display();
 }
 else {
  ERROR("Window", "display", "Window is null");
 }
}

void 
 Window::update() {
   //almacena el deltatime una sola vez
    deltaTime = clock.restart();
	ImGui::SFML::Update(*m_windowPtr, deltaTime); // Actualizar ImGui con el deltaTime
}

void
Window::render() {
    ImGui::SFML::Render(*m_windowPtr); // Actualizar ImGui con el deltaTime
}

void
Window::destroy() {
    ImGui::SFML::Shutdown();
    m_windowPtr.release();
    //SAFE_PTR_RELEASE(m_window);
}