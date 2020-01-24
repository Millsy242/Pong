//
//  ComputerPaddle.cpp
//  Pong
//
//  Created by Daniel Harvey on 22/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#include "ComputerPaddle.hpp"
#include <iostream>
void ComputerPaddle::Input(std::queue<sf::Event> &events, float dt)
{
    //Use this when varying AI difficulty, use paddlespeed_modifier to vary difficult. disable for lower difficulty
    //Also for lower difficulty, lower ball speed and ai reaction time
    if(lastTouched)
    {
        
        if(WindowSize.y/2 > GetPosition().y)
            Move(0, PaddleSpeed/paddlespeed_modifier, dt);
        if(WindowSize.y/2 < GetPosition().y)
            Move(0, -PaddleSpeed/paddlespeed_modifier, dt);
    }
    else
    {
        float tempX{ballpos.x}, tempY{ballpos.y};
        float tempVX{ballVelocity.x}, tempVY{ballVelocity.y};
        int i = 0;
        
        auto predict = [&]()
        {
            tempX += tempVX * dt * predictionAccuracy;
            tempY += tempVY * dt * predictionAccuracy;
            
            if(tempY<=0 || tempY >= WindowSize.y)
                tempVY = -tempVY;
            i++;
        };
        
        
        if(onLeft)
        {
            while (tempX > GetPosition().x)
            {
                predict();
                if(i > 100)
                    break;
            }
        }
        else
        {
            while (tempX < GetPosition().x)
            {
                predict();
                if(i > 100)
                    break;
            }
        }
        
        
        if(tempY + GetSize().y/riskValue > GetPosition().y)
            Move(0, PaddleSpeed, dt);
        if(tempY - GetSize().y/riskValue < GetPosition().y)
            Move(0, -PaddleSpeed, dt);
    }

}
void ComputerPaddle::Giveballdetails(sf::Vector2f bPos, sf::Vector2f bVel)
{
    ballpos = bPos;
    ballVelocity = bVel;
}
