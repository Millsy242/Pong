//
//  Menu.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 13/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Menu.hpp"
#include <iostream>
 Menu::Menu(ige::FileLogger *LOG,SettingsManager *SM)
{
    log = LOG;
    settings = SM;
}

void Menu::Start()
{
    *log << "Starting Menu";
        Active = true;
    
    StartTexture.loadFromFile("Menu Icons/Start.png");
    SettingsTexture.loadFromFile("Menu Icons/Settings.png");
    ExitTexture.loadFromFile("Menu Icons/Exit.png");
}
void Menu::Input(std::queue<sf::Event> &events, float dt)
{
    *log << "Menu Input";
}
void Menu::Render(Window *window)
{
    *log << "Menu Render";
    window->BeginDraw(sf::Color(40,45,55));
    
    window->EndDraw();
}
void Menu::UI()
{
    *log << "Menu UI";
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    ImGui::Begin("Menu",NULL,window_flags);
    ImGui::SetWindowSize(ImVec2(window->GetSize()));
    ImGui::SetWindowPos(ImVec2(0,25));
    
    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Main"))
        {
            StartScreen();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Program Settings"))
        {
            ProgramSettingsMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game Settings"))
        {
            GameSettingsMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game Settings 2"))
        {
            GameSettingsMenuTWO();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
 ImGui::End();
}
void Menu::EarlyUpdate()
{
    *log << "Menu Early Update";
}
void Menu::LateUpdate()
{
    *log << "Menu Late Update";
}
void Menu::FixedUpdate(float dt)
{
    *log << "Menu Fixed Update";
}
void Menu::StartScreen()
{
    ImGui::SetCursorPos(ImVec2(5,40));
       //Look up how to move buttons into centre
       //possibly just specify size of buttons using button images
       
       if(ImGui::ImageButton((StartTexture)))//,sf::Vector2f(window->GetSize().x-10,window->GetSize().y/4)))
       {
            Active = false;
       }

       if(ImGui::ImageButton(ExitTexture))//,sf::Vector2f(window->GetSize().x-10,window->GetSize().x/4)))
       {
           Continue = false;
           Active = false;
       }
}
void Menu::ProgramSettingsMenu()
{
    static int GameX{(int)settings->GameSize.x},GARX{(int)settings->GameApsectRatio.x},GARY{(int)settings->GameApsectRatio.y},MARX{(int)settings->MenuApsectRatio.x},MARY{(int)settings->MenuApsectRatio.y},MenuX{(int)settings->MenuSize.x};
    
    ImGui::Text("Menu Aspect Ratio: %i x %i",settings->MenuApsectRatio.x, settings->MenuApsectRatio.y);
    ImGui::Text("Game Aspect Ratio: %i x %i",settings->GameApsectRatio.x, settings->GameApsectRatio.y);
    ImGui::Text("Menu Resolution: %i x %i",settings->MenuSize.x, settings->MenuSize.y);
    ImGui::Text("Game Resolution: %i x %i",settings->GameSize.x, settings->GameSize.y);
    
    if(ImGui::SliderInt("Game Resolution",&GameX, 1, 8000))
    {
        settings->GameSize.x = GameX;
        settings->GameSize.y = (GameX/GARX)*GARY;
    }
    if(ImGui::SliderInt("Menu Resolution",&MenuX, 1, 8000))
    {
        settings->MenuSize.x = MenuX;
        settings->MenuSize.y = (MenuX/MARX)*MARY;
    }
    if(ImGui::SliderInt("Game Aspect Ratio X",&GARX, 1, 32))
    {
        settings->GameApsectRatio.x = GARX;
        settings->GameSize.y = (GameX/GARX)*GARY;
    }
    if(ImGui::SliderInt("Game Aspect Ratio Y",&GARY, 1, 32))
    {
        settings->GameApsectRatio.y = GARY;
        settings->GameSize.y = (GameX/GARX)*GARY;
    }
    if(ImGui::SliderInt("Menu Aspect Ratio X",&MARX, 1, 32))
    {
        settings->MenuApsectRatio.x = MARX;
        settings->MenuSize.y = (MenuX/MARX)*MARY;
    }
    if(ImGui::SliderInt("Menu Aspect Ratio Y",&MARY, 1, 32))
    {
        settings->MenuApsectRatio.y = MARY;
        settings->MenuSize.y = (MenuX/MARX)*MARY;
    }
    ImGui::Checkbox("Vsync", &settings->Vsync);
    ImGui::Checkbox("Fullscreen", &settings->Fullscreen);
    settings->UpdateFile();
}
void Menu::GameSettingsMenu()
{
    ImGui::Text("this is the Game Settings Menu!\nIt should be used for settings related to ingame variables. Such as car details, tracks etc");
}
void Menu::GameSettingsMenuTWO()
{
    ImGui::Text("this is the Game Settings 2 Menu!\nIt should be used for settings related to ingame variables. Such as car details, tracks etc");
}
