#include "window/graphics.h"
#include "pieeg/inference.h"

void Graphics::InitSDL()
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	
	m_pWindow = SDL_CreateWindow
	(
		"BCI",			        // Title
		SDL_WINDOWPOS_CENTERED, // X
		SDL_WINDOWPOS_CENTERED, // Y
		m_width,			    // Width
		m_height,				// Height
		windowFlags				// Flags
	);

	m_pRenderer = SDL_CreateRenderer
	(
		m_pWindow,  // The window
		-1,	        // Index of rendering driver
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED // Flags
	);

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255); // all black
}

void Graphics::SetupImGuiStyle() const
{
	// Style mess

	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 5.599999904632568f;
	style.ScrollbarRounding = 18.0f;
	style.GrabMinSize = 10.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.57f, 0.5f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.57f, 0.5f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.57f, 0.5f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f,0.0f,0.0f,0.8f);
}

void Graphics::InitImGui() const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();

	ImGuiIO& io{ ImGui::GetIO() }; (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20);

	ImGui::StyleColorsDark();

	SetupImGuiStyle();

	ImGui_ImplSDL2_InitForSDLRenderer(m_pWindow, m_pRenderer);
	ImGui_ImplSDLRenderer2_Init(m_pRenderer);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
}

void Graphics::Cleanup() const
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Graphics::Loop()
{
	while (IsRunning)
	{
		#pragma region Window Events

		// Poll and Handle events like inputs, window resize ...
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				SDL_GetRendererOutputSize(m_pRenderer, &m_width, &m_height);
			
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				IsRunning = false;

			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
				Menu::isPaused = !Menu::isPaused;
		}

		#pragma endregion

		SDL_RenderClear(m_pRenderer);

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();
			Menu::ShowMenu();
		ImGui::EndFrame(); 

		// for fullscreen
#ifdef IMGUI_HAS_VIEWPORT
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
#endif 

		ImGui::Render();

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_pRenderer);
		SDL_RenderPresent(m_pRenderer);
	}

	Cleanup();
}

