#include "menu.h"
#include "pieeg.h"

#pragma warning(disable: 4996)

float delta_time = 0.0f;

Menu::Graph graph(2000);

void Menu::ChannelGraph()
{
    using namespace PIEEG;

    ImGui::Text("Size : %d", graph.data.size());
    ImGui::Text("Capacity : %d", graph.data.capacity());

    ImGui::Checkbox("pause", &is_paused);

    if (ImPlot::BeginPlot("Channels", ImVec2(-1, -1), ImPlotFlags_NoTitle | ImPlotFlags_NoFrame))
    {
        // To make the graph scrolling for new data
        if (!is_paused)
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, delta_time - 5.0f, delta_time, ImGuiCond_Always);
            delta_time += ImGui::GetIO().DeltaTime;

            graph.Add(RetrieveData(delta_time).vals);
        }

        // Plot all 8 channels
        for (int i = 1; i <= kNumElectrodes; i++)
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

void Menu::TrainingActioner(TrainingDirection direction, bool* b_value)
{
    ImGui::PushID(direction);

    ImVec2 actioner_position   = ImGui::GetCursorScreenPos();

    float width = 30, height = 30;

    // To place the actioner at the exact position by taking consideration of its width and height
    ImVec2 actioner_dimension = ImVec2(actioner_position.x + width, actioner_position.y + height);

    // Colors in format RGBA ( From 1.0f to 0.0f | Max is 1.0f so 255 )
    ImU32 active_col  = ImGui::GetColorU32(ImVec4(0.0f,  1.0f,  0.0f,  1.0f));
    ImU32 disable_col = ImGui::GetColorU32(ImVec4(0.45f, 0.45f, 0.45f, 1.0f));

    // Act as a button for now 
    bool is_pressed = ImGui::InvisibleButton("button", ImVec2(width, height)); // an invisible button is here to make it interactable

    if (is_pressed)
        *b_value = !*b_value;
        
    ImGui::GetWindowDrawList()->AddRectFilled(
        actioner_position, 
        actioner_dimension, 
        (*b_value) ? active_col : disable_col
    );

    ImGui::PopID();
}

void Menu::TrainingView()
{
    int margin_width = 30, margin_height = 50;

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 0.5f);
    TrainingActioner(kTop,    &Menu::is_activet);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 1.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 0.5f);
    TrainingActioner(kRight,  &Menu::is_activer);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 0.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 0.5f);
    TrainingActioner(kLeft,   &Menu::is_activel);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 0.5f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 1.0f);
    TrainingActioner(kBottom, &Menu::is_activeb);
}

void Menu::ShowMenu()
{
    ImGui::Begin("Plotting");
        ChannelGraph();
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