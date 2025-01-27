#include "menu.h"
#include <iostream>
#include <stdio.h>

#pragma warning(disable: 4996)

void Menu::ShowMenu()
{
	ImGui::Begin("Test");
		ImGui::Text("Hi ImGui");
	ImGui::End();

	ImGui::Begin("Profile Selector");

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
		    ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
            ImGui::Text("On Profile %d", selected);
        ImGui::EndGroup();

	ImGui::End();
}