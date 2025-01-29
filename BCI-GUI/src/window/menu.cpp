#include <iostream>
#include <stdio.h>
#include <string>
#include "menu.h"

#pragma warning(disable: 4996)

float delta_time = 0.0f;
std::vector<ImVec2> data = {};
bool is_graph_moving = false;

void Menu::ChannelGraph(int numChannel)
{
    delta_time += ImGui::GetIO().DeltaTime;
    data.push_back(ImVec2(delta_time, ImGui::GetIO().MousePos.y)); // for testing | Should be replaced by received data from channels
    
    ImGui::Checkbox("pause", &is_graph_moving);

    if (ImPlot::BeginPlot(std::to_string(numChannel).c_str(), ImVec2(-1, 250), ImPlotFlags_NoTitle | ImPlotFlags_NoFrame))
    {
        // To make the graph scrolling for new data
        if (!is_graph_moving)
            ImPlot::SetupAxisLimits(ImAxis_X1, delta_time - 10.0f, delta_time, ImGuiCond_Always); 

        // Plot for all channels
        ImPlot::PlotLine("ch1", &data[0].x, &data[0].y, data.size(), 0, 0, 2 * sizeof(float));
        //ImPlot::PlotLine("ch2", &data[0].x, &data[0].y, data.size(), 0, 0, 2 * sizeof(float));
        //ImPlot::PlotLine("ch3", &data[0].x, &data[0].y, data.size(), 0, 0, 2 * sizeof(float));
        //ImPlot::PlotLine("ch4", &data[0].x, &data[0].y, data.size(), 0, 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }
}

void Menu::TrainingActioner(Direction direction, bool* b_value)
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
    TrainingActioner(TOP,    &Menu::is_activet);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 1.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 0.5f);
    TrainingActioner(RIGHT,  &Menu::is_activer);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 0.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 0.5f);
    TrainingActioner(LEFT,   &Menu::is_activel);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth()  - margin_width )  * 0.5f);
    ImGui::SetCursorPosY((ImGui::GetWindowHeight() - margin_height)  * 1.0f);
    TrainingActioner(BOTTOM, &Menu::is_activeb);
}

void Menu::ShowMenu()
{
    ImGui::Begin("Plotting");
    ChannelGraph(1);
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