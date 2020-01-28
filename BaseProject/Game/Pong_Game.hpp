//
//  MyGame.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef MyGame_hpp
#define MyGame_hpp
#include <iostream>
#include <stdio.h>
#include "Game.hpp"
#include <array>
#include "Yaml.hpp"
#include "PlayerPaddle.hpp"
#include "ComputerPaddle.hpp"
#include "Ball.hpp"
#include "PongSaveStruct.hpp"
class Pong_Game : public Game
{
public:
    Pong_Game(std::shared_ptr<ige::FileLogger> LOG,std::shared_ptr<SettingsManager> SM) ;
    void Start() override;
    void Input(std::queue<sf::Event> &events, float dt) override;
    void Render(std::shared_ptr<Window> window) override;
    void UI() override;
    void EarlyUpdate() override;
    void LateUpdate() override;
    void FixedUpdate(float dt) override; 
private:
    void Reset(bool scored);
    void AddSave();
    void saveSavestofile();
    void LoadSave(PongSaveStruct PSS);
    void LoadSaveFromFile(std::string filename);
    
    std::vector<PongSaveStruct> PongSaves;
    std::array<std::shared_ptr<Paddle>, 2> paddles;
    Yaml::Node loadROOT; 
    Ball ball;
    sf::Text Player1Scores;
    sf::Text Player2Scores;
    sf::RectangleShape ghostball; 
    sf::Font font;
    int lastTouched = -1;
    int oldlastTouched = -2;
    bool touch = false;
    int frame = 0;
    int SelectedSave = 0; 
};

#endif /* MyGame_hpp */
