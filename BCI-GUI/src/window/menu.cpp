#include "menu.h"

void Menu::ShowMenu()
{
	ImGui::Begin("SomeTest");
		ImGui::Text("Hi ImGui");
	ImGui::End();

	ImGui::Begin("MainWindow");
		ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
	ImGui::End();
}