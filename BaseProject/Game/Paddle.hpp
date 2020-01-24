//
//  Paddle.hpp
//  Pong
//
//  Created by Daniel Harvey on 12/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp
#include "Base.hpp"
class Ball;
class Paddle : public Base
{
public:
    Paddle();
    ~Paddle();
    
    void Start() override;
    void Update() override;
    void Exit() override;
    void Render(Window *window) override;
    virtual void Input(std::queue<sf::Event> &events, float dt) override = 0;

    void SetPosition(sf::Vector2f Pos, bool SetStart = false); 
    void Move(float moveX, float moveY, float dt);
    void ResetPosition();
    void SetSide(bool isleft);
    bool CollwithBall(Ball *b);
    virtual void Giveballdetails(sf::Vector2f bPos, sf::Vector2f bVel){};
    virtual void GiveWindowSize(sf::Vector2f winsize);
    void setlastTouched(bool lt);
    
    sf::Vector2f GetPosition();
    sf::Vector2f GetSize();
    
    int score = 0;
    bool isAI = false;
    
protected:
    float PaddleSpeed = 400.f;
    sf::Vector2f WindowSize;
    bool lastTouched = false;
    bool onLeft = false;
private:
    sf::Vector2f Velocity; //speed X and speed Y
    sf::RectangleShape paddle_shape;
    sf::Vector2f StartPosition ={0,0};
    float maxVelocity = 2.f;
    float friction = 0.01;
    
};
#endif /* Paddle_hpp */
