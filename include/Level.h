#pragma once
#include "raylib.h"
#include "GameClock.h"
#include "Tile.h"
#include <vector>
#include "PlayableCharacter.h"
#include"Map.h"     
#include "CollisionMediator.h"
#include "GameState.h"
#include "LevelState.h"
#include "CharacterType.h"
#include "Luigi.h"
class GameState;
//Physical level of the game, contains the gameplay
class Level
{   
private:
    float currBackgroundStarX=0.0f;
    Texture2D background;
    Color backgroundColor;
    Map map;

    PlayableCharacter* player;
    CharacterType selectedCharacterType;

    int currentPlayerSection;
    std::vector<std::vector<Tile*>>& interactiveTilesSection;
    std::vector<std::vector<Tile*>>& nonInteractiveTilesSection;
    std::vector<std::vector<Block*>>& blocksSection;
    std::vector<std::vector<Item*>>& itemsSection;
    std::vector<std::vector<Monster*>>& monstersSection;
    
    CollisionMediator collisionMediator;

    Camera2D camera;    
    GameState *gameState;
    LevelState state;

public:
    Level(int mapNumber,GameState* gameState,const PlayerData& PlayerData, CharacterType selectedCharacterType);
    LevelState getState() const;
    bool needReset() const;
    ~Level();
    std::unique_ptr<PlayerData> getPlayerData();
    bool IsCompleted() ;
    void UpdateLevel();
    void DrawLevel();
    static  constexpr float GRAVITY=1800;

    void loadCoins();

};
