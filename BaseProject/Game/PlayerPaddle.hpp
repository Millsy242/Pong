//
//  PlayerPaddle.hpp
//  Pong
//
//  Created by Daniel Harvey on 22/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#ifndef PlayerPaddle_hpp
#define PlayerPaddle_hpp
#include "Paddle.hpp"

class PlayerPaddle : public Paddle
{
public:
    PlayerPaddle();
    ~PlayerPaddle(){};
    
    void Input(std::queue<sf::Event> &events, float dt) override;
};

#endif /* PlayerPaddle_hpp */
