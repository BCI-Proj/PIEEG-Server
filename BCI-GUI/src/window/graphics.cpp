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

void Graphics::SetupImGuiStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha						= 1.0f;
	style.WindowPadding			    = ImVec2(8.0f, 8.0f);
	style.WindowBorderSize		    = 1.0f;
	style.WindowMinSize			    = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign		    = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition  = ImGuiDir_Right;
	style.ChildBorderSize		    = 1.0f;
	style.FrameBorderSize		    = 1.0f;
	style.ItemSpacing			    = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing		    = ImVec2(4.0f, 4.0f);
	style.CellPadding			    = ImVec2(4.0f, 2.0f);
	style.IndentSpacing			    = 21.0f;
	style.ColumnsMinSpacing		    = 6.0f;
	style.ScrollbarSize			    = 5.59f;
	style.ScrollbarRounding		    = 18.0f;
	style.GrabMinSize			    = 10.0f;
	style.TabBorderSize			    = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition		= ImGuiDir_Right;
	style.ButtonTextAlign			= ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign		= ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text]					= ImVec4(1.0f,  1.0f,  1.0f,  1.0f);
	style.Colors[ImGuiCol_TextDisabled]			= ImVec4(0.60f, 0.60f, 0.60f, 1.0f);
	style.Colors[ImGuiCol_Border]				= ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow]			= ImVec4(0.0f,  0.0f,  0.0f,  0.0f);
	style.Colors[ImGuiCol_FrameBg]				= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered]		= ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive]		= ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TitleBg]				= ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive]		= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed]		= ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg]			= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_Button]				= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive]			= ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_Header]				= ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered]		= ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive]			= ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Separator]			= ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_Tab]					= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabHovered]			= ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
	style.Colors[ImGuiCol_TabActive]			= ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused]			= ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive]	= ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
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

	SetupImGuiStyle();

	ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
	ImGui_ImplSDLRenderer2_Init(mRenderer);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
}

void Graphics::Cleanup()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	ImPlot::DestroyContext();
	ImGui::DestroyContext();

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

