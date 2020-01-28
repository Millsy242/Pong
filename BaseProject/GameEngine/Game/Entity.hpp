//
//  Entity.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 13/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp
#include "Base.hpp"
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "collision.hpp"
#include "SfMath.hpp"
#include "Selbaward.hpp"

class Entity : public Base
{
public:
    Entity(){};
    ~Entity(){};
    
    virtual void Start() override = 0;
    virtual void LoadTexture(std::string filepath);
    void Update() override;
    virtual void EntityUpdate()  = 0 ;
    virtual void FixedUpdate(float dt) override {};
    virtual void Render(std::shared_ptr<Window> window) override;
    virtual void Input(std::queue<sf::Event> &events, float dt) override = 0;
    virtual void Exit() override = 0;
    virtual bool isCollision(sf::Sprite *sprite);
    virtual void FlipTexture(bool Vertical);
     
    
    virtual void SetPosition(sf::Vector2f NewPosition);
    void SetScale(sf::Vector2f scale);
    sf::Sprite GetSprite();
    void SetPosition(float x, float y);
    void ResetPosition();
    sf::Vector2f GetPosition();
    sf::Vector2f GetOldPosition();
    
protected:
    sf::Sprite EntitySprite;
    sf::Texture EntityTexture;
    sf::Vector2f Position, OldPosition;
    bool Active = true;
};

#endif /* Entity_hpp */
