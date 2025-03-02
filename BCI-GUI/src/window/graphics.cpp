#include "graphics.h"

void Graphics::InitSDL()
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	SDL_WindowFlags windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

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

void Graphics::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();

	ImGuiIO& io{ ImGui::GetIO() }; (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20);

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(m_pWindow, m_pRenderer);
	ImGui_ImplSDLRenderer2_Init(m_pRenderer);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
}

void Graphics::Cleanup()
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

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				IsRunning = false;

			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
				Menu::bPaused = !Menu::bPaused;
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
		ImGuiViewport* viewport = ImGui::GetMainViewport();
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

