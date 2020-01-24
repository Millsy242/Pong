//
//  MyMenu.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "MyMenu.hpp"

MyMenu::MyMenu(ige::FileLogger *LOG,SettingsManager *SM) : Menu(LOG,SM)
{
    
}
void MyMenu::GameSettingsMenu()
{
    ImGui::InputInt("Max Score", &settings->MaxScore);
    ImGui::InputInt("Win Margin", &settings->WinMargin);
}
void MyMenu::Input(std::queue<sf::Event> &events, float dt)
{
    *log << "Menu Input";
}
void MyMenu::Render(Window *window)
{
    *log << "Menu Render";
    window->BeginDraw(sf::Color(40,45,55));
    
    window->EndDraw();
}
void MyMenu::EarlyUpdate()
{
    *log << "Menu Early Update";
}
void MyMenu::LateUpdate()
{
    *log << "Menu Late Update";
}
void MyMenu::GameSettingsMenuTWO()
{
    
}
