//
//  WindowManager.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 17/10/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "WindowManager.hpp"
#include <iostream>

void WindowManager::Start()
{
    log = std::shared_ptr<ige::FileLogger>(new ige::FileLogger("0.5","GameLog.txt"));
    settings = std::shared_ptr<SettingsManager>(new SettingsManager());
    settings->Setup();
    
    window = std::shared_ptr<Window>(new Window(log));
    window->Start(" ",settings->MenuSize);
    ChangeWindow(windowType::eMenu);
}
void WindowManager::Update()
{
    while(currentWindow->Continue)
    {
        settings->Setup();
        currentWindow->Update();
        if(currentWindow->Continue)
        {
            if(CurrentWindowType == windowType::eMenu)
                ChangeWindow(windowType::eGame);
            else if(CurrentWindowType == windowType::eGame)
                ChangeWindow(windowType::eMenu);
        }
    }
    *log << "Exiting";
}
void WindowManager::Exit()
{
    currentWindow->Exit();
}
void WindowManager::FixedUpdate(float dt)
{
    
}
void WindowManager::Render(std::shared_ptr<Window> window)
{

}
void WindowManager::Input(std::queue<sf::Event> &events, float dt)
{

}
void WindowManager::ChangeWindow(windowType wt)
{
    if(CurrentWindowType != wt)
    {
        CurrentWindowType = wt;
        UpdateFromSettings();
        switch (wt)
        {
            case windowType::eGame:
                currentWindow = std::make_shared<Pong_Game>(log,settings);
                *log << "Changing to Game";
                break;
            case windowType::eMenu:
                currentWindow = std::make_shared<MyMenu>(log,settings);
                *log << "Changing to Menu";
                break;
            default:
                break;
        }
        currentWindow->GiveWindow(window);
        currentWindow->Start();
    }
}
void WindowManager::UpdateFromSettings()
{
    if(CurrentWindowType == windowType::eGame)
    {
        window->Start("Game", settings->GameSize, settings->Fullscreen);
    }
    else if(CurrentWindowType == windowType::eMenu)
    {
        window->Start("Menu", settings->MenuSize);
    }
    window->SetVsync(settings->Vsync);
}
