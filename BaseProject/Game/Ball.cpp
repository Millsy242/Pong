//
//  Ball.cpp
//  Pong
//
//  Created by Daniel Harvey on 12/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#include "Ball.hpp"
#include <math.h>
#include <iostream>

Ball::Ball()
{
    
}
Ball::~Ball()
{
    
}
void Ball::Start()
{
    ball_shape.setSize({2,2});
    ball_shape.setOrigin({ball_shape.getSize().x/2,ball_shape.getSize().y/2});
    ball_shape.setOutlineThickness(2);
    ball_shape.setOutlineColor(sf::Color::Blue);
    ball_shape.setFillColor(sf::Color::White);
}
void Ball::Update()
{

}
sf::Vector2f Ball::GetVelocity()
{
    return Velocity; 
}
void Ball::Reset(bool fireright)
{
    if(fireright)
        SetVelocity({-MaxSpeed,(float)random.d(50) - 25.f });
    else
        SetVelocity({MaxSpeed,(float)random.d(50) - 25.f });
    SetPosition(StartPosition);
}
sf::Vector2f Ball::GetPosition()
{
    return ball_shape.getPosition();
}
sf::FloatRect Ball::GetRect()
{
    return ball_shape.getGlobalBounds();
}
void Ball::Collide()
{
    SetVelocity({Velocity.x,-Velocity.y});
}
void Ball::Collide(sf::Vector2f col_pos,float paddleHeight, float intersectY)
{
    auto relativeIntersectY = (col_pos.y+(paddleHeight/2)) - intersectY;
    auto normalisedrelativeIntersectY = relativeIntersectY/(paddleHeight/2) -1;
    
    SetVelocity({-Velocity.x,MaxSpeed * normalisedrelativeIntersectY});
}
void Ball::SetPosition(sf::Vector2f pos, bool SetStart)
{
    ball_shape.setPosition(pos);
    if(SetStart)
        StartPosition = pos; 
}
sf::Vector2f Ball::GetSize()
{
    return ball_shape.getSize();
}
void Ball::Exit()
{
    return;
}
void Ball::Render(std::shared_ptr<Window> window)
{
    window->draw(ball_shape);
}
void Ball::Input(std::queue<sf::Event> &events, float dt)
{
    return;
}
void Ball::Move(float dt)
{
    ball_shape.move({Velocity.x*dt,Velocity.y*dt});
}
void Ball::SetVelocity(sf::Vector2f v)
{
    Velocity = v;
}
void Ball::SetSize(sf::Vector2f size)
{
    ball_shape.setSize(size);
}
