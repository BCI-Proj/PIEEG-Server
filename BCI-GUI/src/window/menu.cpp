#include "menu.h"

void Menu::ShowMenu()
{
	ImGui::Begin("");
		ImGui::Text("Hi ImGui");
	ImGui::End();

	ImGui::Begin("Profile Selector");
		ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
	ImGui::End();
}