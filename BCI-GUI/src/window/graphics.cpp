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
	// Windark style by DestroyerDarkNess from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 8.399999618530273f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildRounding = 3.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 3.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 5.599999904632568f;
	style.ScrollbarRounding = 18.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 3.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.125490203499794f, 0.125490203499794f, 0.125490203499794f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.125490203499794f, 0.125490203499794f, 0.125490203499794f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.125490203499794f, 0.125490203499794f, 0.125490203499794f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.125490203499794f, 0.125490203499794f, 0.125490203499794f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.125490203499794f, 0.125490203499794f, 0.125490203499794f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3490196168422699f, 0.3490196168422699f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.4705882370471954f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 0.4705882370471954f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.3294117748737335f, 0.6000000238418579f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.250980406999588f, 0.250980406999588f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.168627455830574f, 0.168627455830574f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.4705882370471954f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.3294117748737335f, 0.6000000238418579f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.4705882370471954f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.3294117748737335f, 0.6000000238418579f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.4705882370471954f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
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

