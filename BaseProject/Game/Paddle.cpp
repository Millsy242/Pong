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
    paddle_shape.setSize({32,128});
    paddle_shape.setOrigin(paddle_shape.getSize().x/2, paddle_shape.getSize().y/2);
    paddle_shape.setFillColor(sf::Color::White);
    paddle_shape.setOutlineColor(sf::Color::Red);
    paddle_shape.setOutlineThickness(2);
}
bool Paddle::getOnLeft()
{
    return onLeft;
}
void Paddle::Update()
{
    if(GetPosition().y - GetSize().y/2 < WindowSize.top)
        SetPosition({GetPosition().x,WindowSize.top + GetSize().y/2});
    if(GetPosition().y + GetSize().y/2 > WindowSize.height)
        SetPosition({GetPosition().x,WindowSize.height - GetSize().y/2});
}
void Paddle::SetSize(sf::Vector2f size)
{
    paddle_shape.setSize(size);
     paddle_shape.setOrigin(paddle_shape.getSize().x/2, paddle_shape.getSize().y/2);
}
bool Paddle::CollwithBall(Ball *b)
{
    //Need to create paddleEdge, as if the paddles globalbounds are used for the collision,
    //the ball gets stuck inside the paddle - if it hits on the top/bottom edges
    sf::FloatRect intersection,paddleEdge;
    paddleEdge = paddle_shape.getGlobalBounds();
    //paddleEdge.left = paddle_shape.getPosition().x;
    //Set the paddleEdge width to the width of the ball to help avoid trapping
    
    if(paddleEdge.intersects(b->GetRect(), intersection))
    {
        b->Collide(paddle_shape.getPosition(), paddle_shape.getSize().y, intersection.top+(intersection.height/2.1f));
        return true;
    }
    return false;
}
sf::Vector2f Paddle::GetVelocity()
{
    return Velocity;
}
void Paddle::SetPaddleSpeed(float speed)
{
    PaddleSpeed = speed;
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
void Paddle::Move(float dt)
{
    paddle_shape.move({Velocity.x * dt,Velocity.y * dt});
}
void Paddle::Move(float moveX, float moveY, float dt)
{
    Velocity = {moveX*dt,moveY*dt};
    paddle_shape.move(Velocity);
}
void Paddle::SetVelocity(sf::Vector2f vel)
{
    Velocity = vel;
}
void Paddle::Exit()
{
    
}
void Paddle::Render(std::shared_ptr<Window> window)
{
    window->draw(paddle_shape);
}
void Paddle::GiveGameArea(sf::IntRect GameArea)
{
    WindowSize = GameArea;
}
void Paddle::setlastTouched(bool lt)
{
    lastTouched = lt;
}
void Paddle::SetSide(bool isleft)
{
    onLeft = isleft; 
}
