#include "graphics.h"

void Graphics::InitSDL()
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	SDL_WindowFlags windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	mWindow = SDL_CreateWindow
	(
		"BCI",			        // Title
		SDL_WINDOWPOS_CENTERED, // X
		SDL_WINDOWPOS_CENTERED, // Y
		mWidth,					// Width
		mHeight,				// Height
		windowFlags				// Flags
	);

	mRenderer = SDL_CreateRenderer
	(
		mWindow,  // The window
		-1,	      // Index of rendering driver
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED // Flags
	);

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // all black
}

void Graphics::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io{ ImGui::GetIO() }; (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
	ImGui_ImplSDLRenderer2_Init(mRenderer);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
}

void Graphics::Cleanup()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Graphics::Loop(const std::function<void()>& toRender)
{
	while (mIsRunning)
	{
		#pragma region Window Events

		// Poll and Handle events like inputs, window resize ...
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);

			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				SDL_GetRendererOutputSize(mRenderer, &mWidth, &mHeight);

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				mIsRunning = false;
		}

		#pragma endregion

		SDL_RenderClear(mRenderer);

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();
		toRender();
		ImGui::EndFrame(); 

#ifdef IMGUI_HAS_VIEWPORT
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
#endif 

		ImGui::Render();

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);
		SDL_RenderPresent(mRenderer);
	}

	Cleanup();
}

