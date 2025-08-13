#include "EngineGUI.h"
#include "Window.h"
#include <imgui.h>

void
EngineGUI::init(const EngineUtilities::TSharedPointer<Window>& window) {
	//initialize imgui resource
	ImGui::SFML::Init(*window->m_windowPtr);
	setupGUIStyle();
}

void
EngineGUI::update(const EngineUtilities::TSharedPointer<Window>& window,
	              sf::Time deltaTime) {
	ImGui::SFML::Update(*window->m_windowPtr, deltaTime);
	barMenu();
}

void
EngineGUI::render(const EngineUtilities::TSharedPointer<Window>& window) {
	ImGui::SFML::Render(*window->m_windowPtr);
}

void
EngineGUI::processEvent(const sf::Window& window, const sf::Event& event) {
	ImGui::SFML::ProcessEvent(window, event);
}

void EngineGUI::setupGUIStyle() {
    ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();

    // ===== Densidad (compacta) =====
    style.WindowPadding = ImVec2(8, 6);
    style.FramePadding = ImVec2(8, 5);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 5);
    style.ScrollbarSize = 13.0f;

    // ===== Bordes medios + esquinas grandes =====
    style.WindowRounding = 16.0f;
    style.FrameRounding = 12.0f;
    style.GrabRounding = 12.0f;
    style.PopupRounding = 12.0f;
    style.ChildRounding = 12.0f;
    style.TabRounding = 2.0f;  // tabs “subrayadas” (más planas)
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.TabBorderSize = 0.0f;

    // ===== Paleta (Light + teal vibrante) =====
    ImVec4 ACCENT = ImVec4(0.10f, 0.70f, 0.65f, 1.00f);
    ImVec4 ACCENT_HOVER = ImVec4(0.10f, 0.80f, 0.75f, 1.00f);
    ImVec4 ACCENT_ACT = ImVec4(0.05f, 0.90f, 0.85f, 1.00f);

    ImVec4 BG = ImVec4(0.97f, 0.98f, 0.99f, 1.00f);
    ImVec4 BG_PANEL = ImVec4(0.94f, 0.96f, 0.98f, 1.00f);
    ImVec4 BG_HI = ImVec4(0.89f, 0.93f, 0.97f, 1.00f);
    ImVec4 TEXT = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
    ImVec4 TEXT_DIS = ImVec4(0.45f, 0.48f, 0.52f, 1.00f);
    ImVec4 BORDER = ImVec4(0.75f, 0.78f, 0.82f, 1.00f);

    ImVec4* c = style.Colors;
    c[ImGuiCol_Text] = TEXT;
    c[ImGuiCol_TextDisabled] = TEXT_DIS;
    c[ImGuiCol_WindowBg] = BG;
    c[ImGuiCol_ChildBg] = BG;
    c[ImGuiCol_PopupBg] = ImVec4(1, 1, 1, 1);
    c[ImGuiCol_Border] = BORDER;
    c[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    c[ImGuiCol_FrameBg] = ImVec4(1, 1, 1, 1);
    c[ImGuiCol_FrameBgHovered] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.25f);
    c[ImGuiCol_FrameBgActive] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.40f);

    c[ImGuiCol_TitleBg] = BG_PANEL;
    c[ImGuiCol_TitleBgActive] = BG_HI;
    c[ImGuiCol_TitleBgCollapsed] = BG_PANEL;

    c[ImGuiCol_MenuBarBg] = BG_PANEL;
    c[ImGuiCol_ScrollbarBg] = BG_PANEL;
    c[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.74f, 0.78f, 1.0f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.62f, 0.66f, 0.70f, 1.0f);
    c[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.54f, 0.58f, 0.62f, 1.0f);

    // === Acento en sliders/checkbox/tabs (sí) ===
    c[ImGuiCol_CheckMark] = ACCENT;
    c[ImGuiCol_SliderGrab] = ACCENT;
    c[ImGuiCol_SliderGrabActive] = ACCENT_ACT;

    // === Botones rellenos + hover/active notorios ===
    c[ImGuiCol_Button] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.85f);
    c[ImGuiCol_ButtonHovered] = ImVec4(ACCENT_HOVER.x, ACCENT_HOVER.y, ACCENT_HOVER.z, 0.95f);
    c[ImGuiCol_ButtonActive] = ACCENT_ACT;

    // === Headers (Selectables/Tree/Collapsing) ===
    c[ImGuiCol_Header] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.25f);
    c[ImGuiCol_HeaderHovered] = ImVec4(ACCENT_HOVER.x, ACCENT_HOVER.y, ACCENT_HOVER.z, 0.35f);
    c[ImGuiCol_HeaderActive] = ImVec4(ACCENT_ACT.x, ACCENT_ACT.y, ACCENT_ACT.z, 0.45f);

    c[ImGuiCol_Separator] = BORDER;
    c[ImGuiCol_SeparatorHovered] = ACCENT_HOVER;
    c[ImGuiCol_SeparatorActive] = ACCENT_ACT;

    c[ImGuiCol_ResizeGrip] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.25f);
    c[ImGuiCol_ResizeGripHovered] = ImVec4(ACCENT_HOVER.x, ACCENT_HOVER.y, ACCENT_HOVER.z, 0.45f);
    c[ImGuiCol_ResizeGripActive] = ImVec4(ACCENT_ACT.x, ACCENT_ACT.y, ACCENT_ACT.z, 0.65f);

    // === Tabs: look “subrayado” minimal ===
    c[ImGuiCol_Tab] = BG;
    c[ImGuiCol_TabHovered] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.20f);
    c[ImGuiCol_TabActive] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.28f);
    c[ImGuiCol_TabUnfocused] = BG_PANEL;
    c[ImGuiCol_TabUnfocusedActive] = BG_PANEL;

    // === Tablas / selección / navegación (notorio) ===
    c[ImGuiCol_TableHeaderBg] = BG_PANEL;
    c[ImGuiCol_TableBorderStrong] = BORDER;
    c[ImGuiCol_TableBorderLight] = ImVec4(BORDER.x, BORDER.y, BORDER.z, 0.60f);
    c[ImGuiCol_TextSelectedBg] = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.35f);
    c[ImGuiCol_DragDropTarget] = ACCENT_ACT;
    c[ImGuiCol_NavHighlight] = ACCENT;
    c[ImGuiCol_NavWindowingHighlight] = ImVec4(0.1f, 0.1f, 0.1f, 0.70f);
    c[ImGuiCol_NavWindowingDimBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.20f);
    c[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.35f);
}

void EngineGUI::barMenu() {
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project", "Ctrl+N")) { /* TODO: new */ }
            if (ImGui::MenuItem("Open...", "Ctrl+O")) { /* TODO: open */ }
            bool canSave = true; // pon tu condición real
            if (ImGui::MenuItem("Save", "Ctrl+S", false, canSave)) { /* TODO: save */ }
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* TODO: save as */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Preferences...", "Ctrl+,")) { /* TODO: prefs */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* TODO: set flag de salir */ }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            bool canUndo = true, canRedo = true, hasClipboard = true; // tus estados
            if (ImGui::MenuItem("Undo", "Ctrl+Z", false, canUndo)) { /* TODO */ }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, canRedo)) { /* TODO */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* TODO */ }
            if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* TODO */ }
            if (ImGui::MenuItem("Paste", "Ctrl+V", false, hasClipboard)) { /* TODO */ }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            static bool show_demo = false;
            static bool show_console = true;
            static bool show_prof = false;

            ImGui::MenuItem("Show Demo Window", nullptr, &show_demo);
            ImGui::MenuItem("Console", nullptr, &show_console);
            ImGui::MenuItem("Profiler", nullptr, &show_prof);

            if (ImGui::BeginMenu("Theme")) {
                // Llama a tu setupGUIStyle() para cambiar
                bool light_sel = true;  // marca el actual
                bool dark_sel = false;
                if (ImGui::MenuItem("Light (Teal Vibrant)", nullptr, light_sel)) { setupGUIStyle(); }
                if (ImGui::MenuItem("Dark", nullptr, dark_sel)) { /* TODO: set dark */ }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::MenuItem("Reload Assets", "F5")) { /* TODO */ }
            if (ImGui::MenuItem("Bake Lighting")) { /* TODO */ }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About Labrid Engine...")) { /* TODO: abrir ventana About */ }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // Ejemplo: mostrar la demo si está activada
    // if (show_demo) ImGui::ShowDemoWindow(&show_demo);
}

void
EngineGUI::destroy() {
	ImGui::SFML::Shutdown();
}