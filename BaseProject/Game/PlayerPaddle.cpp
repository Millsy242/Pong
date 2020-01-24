//
//  PlayerPaddle.cpp
//  Pong
//
//  Created by Daniel Harvey on 22/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#include "PlayerPaddle.hpp"

PlayerPaddle::PlayerPaddle()
{
    isAI = false;
    
}

void PlayerPaddle::Input(std::queue<sf::Event> &events, float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
       Move(0, -PaddleSpeed, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
       Move(0, PaddleSpeed, dt);
}
