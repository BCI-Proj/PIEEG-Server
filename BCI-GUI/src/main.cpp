#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

static void InitImGui(SDL_Window* window, SDL_Renderer* renderer) 
{
	// Setup Imgui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io{ ImGui::GetIO() }; (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

	// Imgui Style
	ImGui::StyleColorsDark();

	// Setup Renderer Backend
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	// Start Imgui Frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
}

int main(int argc, char** argv) 
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	int window_width{ 600 };
	int window_height{ 400 };

	auto window_flags {(SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)};

	SDL_Window* window 
	{ 
		SDL_CreateWindow(
			"BCI",			// Title
			SDL_WINDOWPOS_CENTERED, // Pos x
			SDL_WINDOWPOS_CENTERED, // Pos Y
			window_width,		// Width
			window_height,		// Height
			window_flags			// Flags
		) 
	};

	SDL_Renderer* renderer 
	{ 
		SDL_CreateRenderer(
			window,  // the window
			-1,	     // index of rendering driver
			SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED // Flags
		) 
	};

	// Setup Imgui Context
	InitImGui(window, renderer);

	// Init
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // all black

	bool showDemoWindow{ true };
	bool isRunning{ true };
	while (isRunning) 
	{
		#pragma region Window Events

		// Poll and Handle events like inputs, window resize ...
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) 
				SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
				isRunning = false;
		}

		#pragma endregion

		SDL_RenderClear(renderer);

		#pragma region ImGui Displayed Elements

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();

		if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

		ImGui::Begin("SomeTest");
			ImGui::Text("Hi ImGui");
		ImGui::End();

		if (ImGui::Begin("MainWindow")) 
		{
			ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
		}
		ImGui::End();

		// Fullscreen the frame as window size
#ifdef IMGUI_HAS_VIEWPORT
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
#endif 

		ImGui::Render();

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);

		#pragma endregion
	}

	#pragma region Cleanup

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	#pragma endregion

	return 0;
}