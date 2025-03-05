#include "window/menu.h"

float gDeltaTime = 0.0f;
float deadline   = 0.0f;

Menu::Graph graph(Menu::maxGraphCount);

void Menu::ChannelGraph()
{
    if (ImPlot::BeginPlot("Channels", ImVec2(-1, -1), ImPlotFlags_NoTitle | ImPlotFlags_NoFrame))
    {
        // To make the graph scrolling for new data
        if (!isPaused)
        {
            ImPlot::SetupAxis(
                ImAxis_X1, 
                nullptr, 
                ImPlotAxisFlags_NoLabel | ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks
            );

            ImPlot::SetupAxisLimits(ImAxis_X1, gDeltaTime - 5.0f, gDeltaTime, ImGuiCond_Always);
            gDeltaTime += ImGui::GetIO().DeltaTime;

            // Receive data to a buffer
            // Add received to graph data
            PIEEG::Channels chns(&gDeltaTime, PIEEG::receiver.buffer);
            graph.Add(chns.vals);
        }

        // Plot all 8 channels
        for (int i = 1; i <= Globals::kNumElectrodes; i++)
        {
            ImPlot::PushColormap(ImPlotColormap_Cool);
            ImPlot::PlotLine(
                std::to_string(i).c_str(),
                &graph.data[0][0], // Delta Time
                &graph.data[0][i], // Value of Channel that is being plotted
                graph.data.size(),
                0, 0,
                (Globals::kNumElectrodes + 1) * sizeof(float)  // Size of the n (correspond to num of channels) elements in graph ChannelsArray
            );
            ImPlot::PopColormap();
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
    ImU32 activeColor  = Globals::kAccentColor;
    ImU32 disableColor = IM_COL32(115, 115, 115, 255);

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
    ImGui::Begin("Training", nullptr, ImGuiWindowFlags_NoScrollbar);
    {
        if (actionerHidden)
        { 
            PositionActioner(kTop,    &Menu::actionerT);   // Top
            PositionActioner(kRight,  &Menu::actionerR);   // Right
            PositionActioner(kLeft,   &Menu::actionerL);   // Left
            PositionActioner(kBottom, &Menu::actionerB);   // Bottom
        }
        PositionActioner(kCenter, &Menu::actionerC);       // Center
        
    }
    ImGui::End();
}

void Menu::LoggingView()
{
    // Picking last n data from the graph to store them in this vector
    std::vector<ChannelsArray> lastData(graph.data.end() - maxLoggingCount, graph.data.end());

    ImGui::Begin("Logging");
    {
        ImGui::SliderInt("Max displayed", &maxLoggingCount, 100, 2000);
        for (const auto &element : lastData)
        {
            ImGui::Separator();

            ImGui::PushStyleColor(ImGuiCol_Text, Globals::kAccentColor);
            ImGui::Text(" %f ", element[0]);
            ImGui::PopStyleColor();
            for (int i = 1; i < Globals::kNumElectrodes + 1; i++)
            {      
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 255, 255, 255));
                ImGui::Text("%d. ", i);
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::Text("%f", element[i]);
            }
            ImGui::Separator();
        }
    }
    ImGui::End();
}

void Menu::ProfileView()
{
    ImGui::Begin("Profile Loader");
    {
        static int selected = 0;

        ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
        {
            for (int i = 0; i < 20; i++)
            {
                char label[128];
                std::sprintf(label, "Profile %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginGroup();
            ImGui::SeparatorText("Info");
            ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
            ImGui::Text("On Profile %d", selected);
            ImGui::SeparatorText("Options");
            ImGui::Button("Load");

            ImGui::SameLine();

#pragma region Training Popup
            ImGui::PushStyleColor(ImGuiCol_Button, (!isTrainingStarted) ? ImVec4(0, 1, 0, 0.5) : ImVec4(1, 0, 0, 0.5));
            if (ImGui::Button((isTrainingStarted) ? "Stop" : "Start"))
            {
                ImGui::OpenPopup("TrainingPopup");
            }
            ImGui::PopStyleColor();

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("TrainingPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text((!isTrainingStarted) ? "The training session is going to start. Do you want to continue ?" : "The training session in in progress. Do you want to stop ?"); ImGui::Separator();

                if (ImGui::Button("YES"))
                {
                    if (!isTrainingStarted)
                    {
                        isTrainingStarted = true;
                        deadline = gDeltaTime + 5;
                    }
                    else
                        isTrainingStarted = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("NO")) { ImGui::CloseCurrentPopup(); }

                ImGui::EndPopup();
            }
#pragma endregion
            
        ImGui::EndGroup();
    }
    ImGui::End();
}

void Menu::ShowMenu()
{
    ImGui::Begin("Plotting");

        // this is a timing test ( testing how we can use deltatime to make timing events ) 
        if (gDeltaTime >= deadline && deadline != 0.0f) {
            deadline = 0.0f;
            actionerHidden = true;
            Info(L"TIMEOUT", L"PATRON DU PARC #BENSON", MB_ICONEXCLAMATION);
        }
        ImGui::Checkbox("Pause",  &isPaused);
        ImGui::SeparatorText("Graph");

        ChannelGraph();

    ImGui::End();

    TrainingView();
    LoggingView();
    ProfileView();
}