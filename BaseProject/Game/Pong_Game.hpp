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
#include "PlayerPaddle.hpp"
#include "ComputerPaddle.hpp"
#include "Ball.hpp"
class Pong_Game : public Game
{
public:
    Pong_Game(ige::FileLogger *LOG,SettingsManager *SM) ;
    void Start() override;
    void Input(std::queue<sf::Event> &events, float dt) override;
    void Render(Window *window) override;
    void UI() override;
    void EarlyUpdate() override;
    void LateUpdate() override;
    void FixedUpdate(float dt) override; 
private:
    void Reset(bool scored); 
    
    std::array<std::shared_ptr<Paddle>, 2> paddles;
    Ball ball;
    sf::Text Player1Scores;
    sf::Text Player2Scores;
    sf::RectangleShape ghostball; 
    sf::Font font;
    int lastTouched = -1;
    int oldlastTouched = -2;
    bool touch = false;
    
};

#endif /* MyGame_hpp */
