#include <iostream>
#include <stdio.h>

#include "menu.h"

#pragma warning(disable: 4996)

void Menu::ShowMenu()
{
	ImGui::Begin("Plotting");
		ImGui::Text("Hi ImGui");
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