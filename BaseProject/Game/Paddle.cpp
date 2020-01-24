//
//  Paddle.cpp
//  Pong
//
//  Created by Daniel Harvey on 12/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#include "Paddle.hpp"
#include "Ball.hpp"
#include <iostream>
Paddle::Paddle()
{
    
}
Paddle::~Paddle()
{
    
}
void Paddle::Start()
{
    paddle_shape.setSize({16,128});
    paddle_shape.setOrigin(paddle_shape.getSize().x/2, paddle_shape.getSize().y/2);
    paddle_shape.setFillColor(sf::Color::White);
    paddle_shape.setOutlineColor(sf::Color::Red);
    paddle_shape.setOutlineThickness(2);
}
void Paddle::Update()
{
    if(GetPosition().y - GetSize().y/2 < 0)
        SetPosition({GetPosition().x,GetSize().y/2});
    if(GetPosition().y + GetSize().y/2 > WindowSize.y)
        SetPosition({GetPosition().x,WindowSize.y - GetSize().y/2});
}
bool Paddle::CollwithBall(Ball *b)
{
    sf::FloatRect intersection;
    if(paddle_shape.getGlobalBounds().intersects(b->GetRect(), intersection))
    {
        if(intersection.width > 3.5 && intersection.width < 8)
        {
            b->Collide(paddle_shape.getPosition(), paddle_shape.getSize().y, intersection.top+(intersection.height/2));
            return true;
        }
    }
    return false;
}
sf::Vector2f Paddle::GetPosition()
{
    return paddle_shape.getPosition();
}
sf::Vector2f Paddle::GetSize()
{
    return paddle_shape.getSize();
}
void Paddle::ResetPosition()
{
    paddle_shape.setPosition(StartPosition); 
}
void Paddle::SetPosition(sf::Vector2f Pos, bool SetStart)
{
    paddle_shape.setPosition(Pos);
    if(SetStart)
        StartPosition = Pos;
}
void Paddle::Move(float moveX, float moveY, float dt)
{
    Velocity = {moveX*dt,moveY*dt};
    paddle_shape.move(Velocity);
}
void Paddle::Exit()
{
    
}
void Paddle::Render(Window *window)
{
    window->draw(paddle_shape);
}

void Paddle::GiveWindowSize(sf::Vector2f winsize)
{
    WindowSize = winsize;
}
void Paddle::setlastTouched(bool lt)
{
    lastTouched = lt;
}
void Paddle::SetSide(bool isleft)
{
    onLeft = isleft; 
}
