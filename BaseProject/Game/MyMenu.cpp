//
//  MyMenu.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "MyMenu.hpp"

MyMenu::MyMenu(std::shared_ptr<ige::FileLogger> LOG,std::shared_ptr<SettingsManager> SM) : Menu(LOG,SM)
{
    
}
void MyMenu::GameSettingsMenu()
{
    ImGui::InputInt("Max Score", &settings->MaxScore);
    ImGui::InputInt("Win Margin", &settings->WinMargin);
    ImGui::Checkbox("Ball Predicition", &settings->showBallPrediction);
    ImGui::SliderFloat("Paddle Speed", &settings->paddleSpeed, 100, 1000);
    ImGui::SliderFloat("Paddle Size", &settings->PaddleSize, 8, settings->GameSize.y/3);
    ImGui::Checkbox("Player 1 is AI", &settings->Player1AI);
    ImGui::Checkbox("Player 2 is AI", &settings->Player2AI);
    
    if(settings->Player1AI)
        ImGui::SliderInt("Player 1 AI Difficulty", &settings->AIDifficultyP1,1,100);
    if(settings->Player2AI)
        ImGui::SliderInt("Player 2 AI Difficulty", &settings->AIDifficultyP2,1,100);
}
void MyMenu::Input(std::queue<sf::Event> &events, float dt)
{
    *log << "Menu Input";
}
void MyMenu::Render(std::shared_ptr<Window> window)
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
