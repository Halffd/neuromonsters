// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "GameObject.h"
#include "asset/TilemapManager.h"

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public GameObject {
public:
    // Constructors
    Player();
    Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, unsigned int tileWidth, unsigned int tileHeight);

    // Movement and update functions
    void Move(Direction dir);
    void Stop();
    void Update(float dt);
    void Draw(SpriteRenderer& renderer) override;

    // Animation
    void UpdateAnimation(float dt);
    void UpdateSpriteFrame();

    // Game properties
    bool isMoving;
    Direction facing;
    
    // Movement properties
    float movementSpeed;
    
    // Animation properties
    static constexpr float FRAME_DURATION = 0.1f;
    float animationTimer;
    int currentFrame;
    float frameTime;
    unsigned int anim = 0;
    unsigned int frame = 0;
    unsigned int animDir = 0;
    unsigned int animTime = 30;
    Direction prevDir = Direction::UP;
    std::vector<std::vector<unsigned int>> anims = {
        { 13, 14, 15 }, //up
        { 1, 2, 3 }, //down
        { 7, 8, 9 }, //left
        { 19, 20, 21 } //right
    };

    // Tilemap
    std::shared_ptr<TilemapManager> sheet;
    int tile = 0;

private:
    // Add any private members here
};

#endif // PLAYER_H