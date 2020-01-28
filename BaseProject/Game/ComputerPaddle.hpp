//
//  ComputerPaddle.hpp
//  Pong
//
//  Created by Daniel Harvey on 22/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#ifndef ComputerPaddle_hpp
#define ComputerPaddle_hpp

#include "Paddle.hpp"

class ComputerPaddle : public Paddle
{
public:
    ComputerPaddle(){isAI = true;};
    ~ComputerPaddle(){};
    
    void Input(std::queue<sf::Event> &events, float dt) override;
    void Giveballdetails(sf::Vector2f bPos, sf::Vector2f bVel) override;
    void SetAIDifficulty(int difficulty) override;
    
private:
    sf::Vector2f ballpos;
    sf::Vector2f ballVelocity;

    double paddlespeed_modifier = 4;
    double riskValue = 8;
    double predictionAccuracy = 1.0;
    int difficulty_ = 0; 
};

#endif /* ComputerPaddle_hpp */
