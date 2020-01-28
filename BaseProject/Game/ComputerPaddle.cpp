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
    SetVelocity({0, 0});
    //Use this when varying AI difficulty, use paddlespeed_modifier to vary difficult. disable for lower difficulty
    //Also for lower difficulty, lower ball speed and ai reaction time
    if(lastTouched)
    {
        if(difficulty_ > 50)
        {
            if(WindowSize.y/2 > GetPosition().y)
                SetVelocity({0, (float)paddlespeed_modifier});
            if(WindowSize.y/2 < GetPosition().y)
                 SetVelocity({0, -(float)paddlespeed_modifier});
        }
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
                if(i > difficulty_)
                    break;
            }
        }
        else
        {
            while (tempX < GetPosition().x)
            {
                predict();
                if(i > difficulty_)
                    break;
            }
        }
        
        if(tempY  > GetPosition().y - GetSize().y/riskValue)
            SetVelocity({0, PaddleSpeed});
            
        if(tempY  < GetPosition().y + GetSize().y/riskValue)
            SetVelocity({0, -PaddleSpeed});
    }
    
}
void ComputerPaddle::Giveballdetails(sf::Vector2f bPos, sf::Vector2f bVel)
{
    ballpos = bPos;
    ballVelocity = bVel;
}
void ComputerPaddle::SetAIDifficulty(int difficulty)
{
 //   double paddlespeed_modifier = 4;     //bigger == paddle takes longer to return to center
 //   double riskValue = 8;       //bigger == paddle tries to get ball to hit closer to the edge for more extreme hit
 //   double predictionAccuracy = 1.0;  //smaller == paddle can predict more accurately
    
    auto minmaxrange = [](float input, float input_high, float input_low, float output_high, float output_low)
    {
        return ((input - input_low) / (input_high-input_low)) * (output_high - output_low) + output_low;
    };
    
    paddlespeed_modifier = ((double)difficulty/100.0) * PaddleSpeed;
    riskValue =   minmaxrange((float)difficulty,100,1,2.1,10);
    difficulty_ = difficulty;
    predictionAccuracy = 100.0/(double)difficulty;
}
