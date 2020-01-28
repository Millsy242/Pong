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
    SetVelocity({0, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        SetVelocity({0, -PaddleSpeed});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        SetVelocity({0, PaddleSpeed});
}
