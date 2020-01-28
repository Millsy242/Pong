//
//  Ball.hpp
//  Pong
//
//  Created by Daniel Harvey on 12/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp
#include "Base.hpp"
#include "grand.hpp"
class Ball : public Base
{
public:
    Ball();
    ~Ball();
    void Start() override;
    void Update() override;
    void Exit() override;
    void Render(std::shared_ptr<Window> window) override;
    void Input(std::queue<sf::Event> &events, float dt) override;
    //Used to collide with paddle
    void Collide(sf::Vector2f col_pos,float paddleHeight, float intersectY);
    //used to collide with wall
    void Collide();
    void SetPosition(sf::Vector2f pos, bool SetStart=false);
    void Move(float dt);
    void SetVelocity(sf::Vector2f v);
    
    void SetSize(sf::Vector2f size);
    
    sf::Vector2f GetSize();
    sf::Vector2f GetVelocity();
    sf::Vector2f GetPosition();
    sf::FloatRect GetRect();
    void Reset(bool fireright);
private:
    sf::RectangleShape ball_shape;
    sf::Vector2f Position;
    sf::Vector2f Velocity;
    sf::Vector2f StartPosition; 
    float MaxSpeed = 600;
    GRand random; 
    int bounces = 0; 
};

#endif /* Ball_hpp */

