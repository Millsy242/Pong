//
//  SettingsManager.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 27/10/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "SettingsManager.hpp"
#include <iostream>

SettingsManager::SettingsManager()
{
    
}
SettingsManager::~SettingsManager()
{
    UpdateFile();
}
void SettingsManager::Setup()
{
    int ver = -1;
    if(parse.loadFromFile(FileName))
    {
        parse.get("Version",ver);

        unsigned int Mx{MenuSize.x},Gx{GameSize.x}, MARY{MenuApsectRatio.y},MARX{MenuApsectRatio.x},GARY{GameApsectRatio.y},GARX{GameApsectRatio.x};
        //load from file to data
        parse.get("MenuScreenWidth", Mx);
        parse.get("GameScreenWidth", Gx);
        parse.get("MenuAspectRatioX",MARX);
        parse.get("MenuAspectRatioY",MARY);
        parse.get("GameAspectRatioX",GARX);
        parse.get("GameAspectRatioY",GARY);
        parse.get("Vsync", Vsync);
        parse.get("FullScreen",Fullscreen);
        parse.get("MaxScore",MaxScore);
        parse.get("WinMargin",WinMargin);
        parse.get("AIDifficulty_Player_1",AIDifficultyP1);
        parse.get("AIDifficulty_Player_2",AIDifficultyP2);
        parse.get("Player1_AI",Player1AI);
        parse.get("Player2_AI",Player2AI);
        parse.get("PaddleSize",PaddleSize);
        parse.get("ShowBallPredict",showBallPrediction);
        parse.get("PaddleSpeed",paddleSpeed);
        
        GameApsectRatio = sf::Vector2u(GARX,GARY);
        MenuApsectRatio = sf::Vector2u(MARX,MARY);
        
        MenuSize = sf::Vector2u(Mx,(Mx/MARX)*MARY);
        GameSize = sf::Vector2u(Gx,(Gx/GARX)*GARY);
        if(ver != SettingsVersion)
        {
            std::cout<<"settings version doesnt match, correcting" << std::endl;
            UpdateFile();
        }
    }
    else
    {
        UpdateFile();
    }
}
void SettingsManager::UpdateFile()
{
    parse.set("Version",SettingsVersion);
    parse.set("MenuAspectRatioX",MenuApsectRatio.x);
    parse.set("MenuAspectRatioY",MenuApsectRatio.y);
    parse.set("GameAspectRatioX",GameApsectRatio.x);
    parse.set("GameAspectRatioY",GameApsectRatio.y);
    parse.set("MenuScreenWidth", MenuSize.x);
    parse.set("GameScreenWidth", GameSize.x);
    parse.set("Vsync", Vsync);
    parse.set("FullScreen",Fullscreen);
    parse.set("MaxScore",MaxScore);
    parse.set("WinMargin",WinMargin);
    parse.set("AIDifficulty_Player_1",AIDifficultyP1);
    parse.set("AIDifficulty_Player_2",AIDifficultyP2);
    parse.set("Player1_AI",Player1AI);
    parse.set("Player2_AI",Player2AI);
    parse.set("PaddleSize",PaddleSize);
    parse.set("ShowBallPredict",showBallPrediction);
    parse.set("PaddleSpeed",paddleSpeed);
    parse.saveToFile(FileName);
}

