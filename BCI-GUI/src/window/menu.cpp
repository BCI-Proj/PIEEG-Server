#include "menu.h"

float gDeltaTime = 0.0f;
Menu::Graph graph(3000);

void Menu::ChannelGraph(float* buffer)
{
    using namespace PIEEG;

    if (ImPlot::BeginPlot("Channels", ImVec2(-1, -1), ImPlotFlags_NoTitle | ImPlotFlags_NoFrame))
    {
        // To make the graph scrolling for new data
        if (!bPaused)
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, gDeltaTime - 5.0f, gDeltaTime, ImGuiCond_Always);
            gDeltaTime += ImGui::GetIO().DeltaTime;

            // Receive data to a buffer
            // Add received to graph data
            Channels chns(gDeltaTime, buffer);
            graph.Add(chns.vals);
        }

        // Plot all 8 channels
        for (int i = 1; i <= Globals::kNumElectrodes; i++)
        {
            ImPlot::PlotLine(
                std::to_string(i).c_str(),
                &graph.data[0][0], // Delta Time
                &graph.data[0][i], // Value of Channel that is being plotted
                graph.data.size(),
                0, 0,
                9 * sizeof(float)  // Size of the 9 elements in graph ChannelsArray
            );
        }
        ImPlot::EndPlot();
    }
}

void Menu::TrainingActioner(const TrainingDirection direction, bool* pBoolean)
{
    ImGui::PushID(direction);

    ImVec2 actionerPos = ImGui::GetCursorScreenPos();

    float width = 30, height = 30;

    // To place the actioner at the exact position by taking consideration of its width and height
    ImVec2 actionerSize = ImVec2(actionerPos.x + width, actionerPos.y + height);

    // Colors in format RGBA ( From 1.0f to 0.0f | Max is 1.0f so 255 )
    ImU32 activeColor  = ImGui::GetColorU32(ImVec4(0.0f,  1.0f,  0.0f,  1.0f));
    ImU32 disableColor = ImGui::GetColorU32(ImVec4(0.45f, 0.45f, 0.45f, 1.0f));

    // Act as a button for now 
    bool isPressed = ImGui::InvisibleButton("button", ImVec2(width, height)); // an invisible button is here to make it interactable

    if (isPressed)
        *pBoolean = !*pBoolean;
        
    ImGui::GetWindowDrawList()->AddRectFilled(
        actionerPos, 
        actionerSize, 
        (*pBoolean) ? activeColor : disableColor
    );

    ImGui::PopID();
}

void Menu::TrainingView()
{
    ImVec2 wndDimensions = ImGui::GetWindowSize(); // x refer to width, y refer to height

    int margins[2] = { 30, 50 };

    // Top
    PositionActioner(
        wndDimensions,
        margins,
        kTop, &Menu::bActionerT
    );

    // Right
    PositionActioner(
        wndDimensions,
        margins,
        kRight, &Menu::bActionerR
    );  
    // Left
    PositionActioner(
        wndDimensions,
        margins,
        kLeft, &Menu::bActionerL
    );
    // Bottom
    PositionActioner(
        wndDimensions,
        margins,
        kBottom, &Menu::bActionerB
    );

    // Center
    PositionActioner(
        wndDimensions,
        margins,
        kCenter, &Menu::bActionerC
    );
}

void Menu::ShowMenu()
{
    ImGui::Begin("Plotting");
        if (ImGui::Button("Start Training"))
        {
            Info(L"Info", L"la session d'entrainement à commencé", MB_ICONINFORMATION);
        }
        ImGui::Checkbox("Pause",  &bPaused);
        ImGui::SeparatorText("Graph");
        ChannelGraph(PIEEG::receiver.buffer);
    ImGui::End();

	ImGui::Begin("Training", nullptr, ImGuiWindowFlags_NoScrollbar);
        TrainingView();
	ImGui::End();

	ImGui::Begin("Profile Loader");

        static int selected = 0;

        ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
        for (int i = 0; i < 20; i++)
        {
            char label[128];
            std::sprintf(label, "Profile %d", i);
            if (ImGui::Selectable(label, selected == i))
                selected = i;
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginGroup();
            ImGui::SeparatorText("Info");
		    ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
            ImGui::Text("On Profile %d", selected);
            ImGui::SeparatorText("Options");
            ImGui::Button("Load");
        ImGui::EndGroup();

	ImGui::End();
}