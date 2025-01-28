#include <iostream>
#include <stdio.h>

#include "menu.h"

#pragma warning(disable: 4996)

void Menu::TrainingActioner(const char* label, bool* b_value)
{
    ImGui::PushID(label);

    ImVec2 actioner_position   = ImGui::GetCursorScreenPos();

    float width = 30, height = 30;

    // To place the actioner at the exact position by taking consideration of its width and height
    ImVec2 actioner_dimension = ImVec2(actioner_position.x + width, actioner_position.y + height);

    // Colors in format RGBA
    ImU32 active_col  = ImGui::GetColorU32(ImVec4(0.0f,  1.0f,  0.0f,  1.0f));
    ImU32 disable_col = ImGui::GetColorU32(ImVec4(0.45f, 0.45f, 0.45f, 1.0f));

    // Act as a button for now
    bool is_pressed = ImGui::InvisibleButton(label, ImVec2(width, height)); // an invisible button is here to make it interactable

    if (is_pressed)
        *b_value = !*b_value;

    
        
    ImGui::GetWindowDrawList()->AddRectFilled(
        actioner_position, 
        actioner_dimension, 
        (*b_value) ? active_col : disable_col
    );

    ImGui::PopID();
}


void Menu::ShowMenu()
{
	ImGui::Begin("Plotting");
        ImGui::Text("Hello");
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