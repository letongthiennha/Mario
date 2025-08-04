#include "Level.h"
#include "ResourceManager.h"
#include "Map.h"
#include "LevelState.h"
#include "SoundController.h"
#include "Monster.h"
#include "raylib.h"
#include "QuestionBlock.h"
#include "EyesOpenedBlock.h"
#include "CharacterFactory.h"
#include "BanzaiBill.h"
Level::Level(int mapNumber,GameState* gamestate,const PlayerData& playerData,CharacterType selectedCharacterType):map(mapNumber),
gameState(gamestate),
monstersSection(map.getMonstersSection()),
itemsSection(map.getItemsSection()), blocksSection(map.getBlocksSection()),
interactiveTilesSection(map.getInteractiveTilesSection()),
nonInteractiveTilesSection(map.getNonInteractiveTilesSection()), currentPlayerSection(0),
state(LevelState::LEVEL_STATE_PLAYING),
selectedCharacterType(selectedCharacterType),
player(CharacterFactory::createCharacter(selectedCharacterType, map.getStartPositionForPlayer(), playerData))
{

        switch(mapNumber) {
            case 0:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_0");
                backgroundColor = Color{0,96,184,255}; // Default color for level 0
                break;
            case 1:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_LEVEL_1");
                backgroundColor = {0,96,184,255};

                break;
            case 2:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_LEVEL_2");
                backgroundColor = DARKGREEN;
                break;
             case 3:
                 background = ResourceManager::getInstance().getTexture("BACKGROUND_LEVEL_3");
                 backgroundColor = BLUE;
                 break;
            default:
                // background = ResourceManager::getInstance().getTexture("DEFAULT_BACKGROUND");
                backgroundColor = WHITE;
        }
        player->addObserver(&gameState->getHUD());
        player->addCoin(0);
        player->addLives(0);
        player->addScore(0);

        camera.offset = Vector2{(float)GetScreenWidth()/2,(float) GetScreenHeight()/2};
        camera.target = player->getPosition();
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;


}


LevelState Level::getState() const
{
    return state;
}
bool Level::needReset() const
{
    return state == LevelState::LEVEL_STATE_NEED_RESET;
}
Level::~Level()
{

}

std::unique_ptr<PlayerData> Level::getPlayerData()
{
    return player->createMemento();
}

bool Level::IsCompleted()
{
    return this->state==LevelState::LEVEL_STATE_COMPLETED;
}

void Level::UpdateLevel()
{
        //Check collision when it is not in special state
        const float activationWidth=GetScreenWidth()/2.0f+50; // Width within which monsters are activated

   


         currentPlayerSection=(int)(player->getPosition().x / map.getSectionWidth());
        for (int i = -2; i <= 2; ++i) // Check sections around the player
        {
                        int currentSection = currentPlayerSection + i;
                        if(currentSection<0 || currentSection >= map.getMapWidth()/map.getSectionWidth()) continue; // Skip sections out of bounds
                        std::vector<Tile*>& interactiveTiles = interactiveTilesSection[currentSection];
                        std::vector<Block*>& blocks = blocksSection[currentSection];
                        std::vector<Item*>& items = itemsSection[currentSection];
                        std::vector<Monster*>& monsters = monstersSection[currentSection];
                if(i>=-1&&i<=1){
                        for(auto &monster: monsters)
                        {
                                if(monster->getState() == ENTITY_STATE_DYING) continue; // Skip monsters that are dying
                                if(monster->getPosition().x<GetScreenWidth()&&monster->getIsActive()==false){
                                        monster->setIsActive(true); // Activate monster if it is within the screen
                                }
                                if(abs(player->getPosition().x - monster->getPosition().x) <activationWidth&&monster->getIsActive()==false )
                                {
                                        monster->setIsActive(true); // Activate monster if player is close enough
                                }
                        };
                }
                if (player->getState() != ENTITY_STATE_DYING && player->getState() != ENTITY_STATE_TO_BE_REMOVED && player->getState() != ENTITY_STATE_VICTORY_DANCE) // If player falls off the screen, reset the level
                        {
                                if (player->getPosition().y >= GetScreenHeight() - 32) // If player falls below the screen, reset the level
                                {
                                        player->die();
                                        return;
                                }
                                for (auto const &tile : interactiveTiles)
                                {
                                        CollisionInfo playerCollision = player->CheckCollisionType(*tile);
                                        if (playerCollision)
                                                collisionMediator.HandleCollision(player, tile);

                                        for (auto &fireball : *player->getFireballs())
                                        {
                                                CollisionInfo fireballCollision = fireball->CheckCollisionType(*tile);
                                                if (fireballCollision)
                                                {
                                                        collisionMediator.HandleCollision(fireball, tile);
                                                }
                                        }
                                };
                                for (auto const &block : blocks)
                                {
                                    if (std::abs(player->getPosition().x - block->getPosition().x) > activationWidth) continue;
                                        CollisionInfo playerCollision = player->CheckCollisionType(*block);
                                        if (playerCollision)
                                                collisionMediator.HandleCollision(player, block);
                                        for (auto &fireball : *player->getFireballs())
                                        {
                                                CollisionInfo fireballCollision = fireball->CheckCollisionType(*block);
                                                if (fireballCollision)
                                                {
                                                        collisionMediator.HandleCollision(fireball, block);
                                                }
                                        }
                                        for (auto &monster : monsters)
                                        {
                                            if (std::abs(player->getPosition().x - monster->getPosition().x) > activationWidth) continue;
                                            CollisionInfo monsterCollision = monster->CheckCollisionType(*block);
                                                if (monsterCollision)
                                                        collisionMediator.HandleCollision(monster, block);
                                        }
                                        for (auto const &item : items)
                                        {
                                                if (dynamic_cast<Coin *>(item) != nullptr)
                                                {
                                                        continue;
                                                }

                                                CollisionInfo itemCollision = item->CheckCollisionType(*block);
                                                if (itemCollision)
                                                        collisionMediator.HandleCollision(item, block);
                                        }
                                }

                                for (auto const &item : items)
                                {
                                    if (std::abs(player->getPosition().x - item->getPosition().x) > activationWidth) continue;
                                        CollisionInfo playerCollision = player->CheckCollisionType(*item);
                                        if (playerCollision)
                                        {
                                                collisionMediator.HandleCollision(player, item);
                                        }
                                }
                                for (auto &monster : monsters)
                                {

                                        if (player->getPosition().x < 0)
                                        {
                                                player->setPosition({0, player->getPosition().y}); // Prevent player from going off the left side of the screen
                                        }
                                        else if (player->getPosition().x > map.getMapWidth() - player->getSize().x)
                                        {
                                                player->setPosition({map.getMapWidth() - player->getSize().x, player->getPosition().y}); // Prevent player from going off the right side of the screen
                                        }

                                        if (!monster->getIsActive() || monster->getState() == ENTITY_STATE_DYING)
                                                continue;
                                        if (std::abs(player->getPosition().x - monster->getPosition().x) > activationWidth) continue;
                                        CollisionInfo playerCollision = player->CheckCollisionType(*monster);
                                        if (playerCollision)
                                                collisionMediator.HandleCollision(player, monster);
                                }
                                for (auto const &item : items)
                                {
                                    if (std::abs(player->getPosition().x - item->getPosition().x) > activationWidth) continue;
                                        // Check collision with each interactive tile
                                        if (dynamic_cast<Coin *>(item) != nullptr)
                                        {
                                                continue;
                                        }

                                        item->setOnGround(false);

                                        // Skip coins, as they are handled separately
                                        for (auto const &tile : interactiveTiles)
                                        {
                                                CollisionInfo itemCollision = item->CheckCollisionType(*tile);

                                                if (itemCollision)
                                                {
                                                        collisionMediator.HandleCollision(item, tile);
                                                }
                                        }
                                }

                                // Update monsters
                                for (auto &monster : monsters)
                                {
                                        if (monster->getState() == ENTITY_STATE_TO_BE_REMOVED || monster->getIsActive() == false)
                                                continue;
                                        monster->updateStateAndPhysic();
                                        if(dynamic_cast<BanzaiBill*>(monster))
                                        {
                                                continue;;
                                        }
                                        //Border collision handling
                                        if(monster->getPosition().x < 0)
                                        {
                                                monster->setPosition({0, monster->getPosition().y}); // Prevent monster from going off the left side of the screen
                                                monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Stop horizontal movement
                                        }
                                        else if (monster->getPosition().x > map.getMapWidth() - monster->getSize().x)
                                        {
                                                monster->setPosition({map.getMapWidth() - monster->getSize().x, monster->getPosition().y}); // Prevent monster from going off the right side of the screen
                                                monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Stop horizontal movement
                                        }
                                        if(monster->getPosition().y> GetScreenHeight() + monster->getSize().y)
                                        {
                                                monster->die();
                                        }
                                        for (auto const &tile : interactiveTiles)
                                        {
                                                CollisionInfo collision = monster->CheckCollisionType(*tile);
                                                if (collision)
                                                        collisionMediator.HandleCollision(monster, tile);
                                        }
                                        for (auto &fireball : *player->getFireballs())
                                        {
                                                CollisionInfo collision = monster->CheckCollisionType(*fireball);
                                                if (collision)
                                                {
                                                        collisionMediator.HandleCollision(monster, fireball);
                                                }
                                        }
                                }
                                // Update items
                                for (auto const &item : items)
                                {
                                    if (std::abs(player->getPosition().x - item->getPosition().x) > activationWidth) continue;
                                        Coin *coin = dynamic_cast<Coin *>(item);
                                        if (coin != nullptr)
                                        {
                                                if (!coin->isItem)
                                                        continue;
                                        }
                                        if(item->getPosition().x < 0)
                                        {
                                                item->setPosition({0, item->getPosition().y}); // Prevent item from going off the left side of the screen
                                                item->setVelocity({-item->getVelocity().x, item->getVelocity().y}); // Stop horizontal movement
                                        }
                                        else if (item->getPosition().x > map.getMapWidth() - item->getSize().x)
                                        {
                                                item->setPosition({map.getMapWidth() - item->getSize().x, item->getPosition().y}); // Prevent item from going off the right side of the screen
                                                item->setVelocity({-item->getVelocity().x, item->getVelocity().y}); // Stop horizontal movement
                                        }
                                        if(item->getPosition().y> GetScreenHeight() + item->getSize().y)
                                        {
                                                item->setState(ItemState::COLLECTED);
                                        }
                                        if(item->getState()==ItemState::IDLE)
                                        item->updateStateAndPhysic();
                                        if (item->getState() == ItemState::POP_UP)
                                        item->Activate();
                        }
                //Update Blocks
                        for (auto& block : blocks) {
                            if (std::abs(player->getPosition().x - block->getPosition().x) > activationWidth) continue;
                        if (dynamic_cast<QuestionBlock*>(block) || dynamic_cast<EyesOpenedBlock*>(block)) {
                                block->updateStateAndPhysic();
                        }
                        }
                }

                for (int i = 0;i<monsters.size();i++){
                        int belongSection= monsters[i]->getPosition().x / map.getSectionWidth();
                        if (belongSection==currentSection)
                                continue;
                        monstersSection[belongSection].push_back(monsters[i]); // Add monster to the section it belongs to
                        monsters.erase(monsters.begin() + i); // Remove monster from the current section
                        i--; // Adjust index after erasing
                }
                for (int i = 0; i < items.size(); i++) {
                        int belongSection = items[i]->getPosition().x / map.getSectionWidth();
                        if (belongSection == currentSection) 
                                continue;
                        itemsSection[belongSection].push_back(items[i]); // Add item to the section it belongs to
                        items.erase(items.begin() + i); // Remove item from the current section
                        i--; // Adjust index after erasing
                }
        };
        // Update monsters across all sections
        for (auto& monster_section : monstersSection) {
            for (auto& monster : monster_section) {
                if (monster->getState() == ENTITY_STATE_TO_BE_REMOVED || !monster->getIsActive())
                    continue;
                if (std::abs(player->getPosition().x - monster->getPosition().x) >GetScreenWidth()) continue;
                monster->updateStateAndPhysic();

                int monsterSectionIndex = monster->getPosition().x / map.getSectionWidth();
                if (monsterSectionIndex < 0) monsterSectionIndex = 0;
                if (monsterSectionIndex >= interactiveTilesSection.size()) monsterSectionIndex = interactiveTilesSection.size() - 1;
                
                // Check for collisions with tiles in the monster's current section
                for (auto& tile : interactiveTilesSection[monsterSectionIndex]) {
                    CollisionInfo collision = monster->CheckCollisionType(*tile);
                    if (collision)
                        collisionMediator.HandleCollision(monster, tile);
                }

                // Check for collisions with fireballs
                for (auto& fireball : *player->getFireballs()) {
                    CollisionInfo collision = monster->CheckCollisionType(*fireball);
                    if (collision) {
                        collisionMediator.HandleCollision(monster, fireball);
                    }
                }
            }
        }

        // if(player->getPosition().x>3000) // If player is past a certain point, switch to next level
        // {
        //         state= LevelState::LEVEL_STATE_COMPLETED;
        //         player->startVictoryDance();
        //         return;
        // } 

        if (player->getWinState() == true) {
            state = LevelState::LEVEL_STATE_COMPLETED;
            player->startVictoryDance();
            player->changeWinState(false);
            return;
        }
        if (player->getState() == ENTITY_STATE_TO_BE_REMOVED) // If player is dead, reset the level
            {
                    if (player->getLives() > 0) // If player has lives left, reset the level
                    {
                            state = LevelState::LEVEL_STATE_NEED_RESET;
                    }
                    else // If player has no lives left, game over
                    {
                            state = LevelState::LEVEL_STATE_GAME_OVER;
                    }
                    return;
            }

        // Clean up inactive monsters and items
        for (auto &it: monstersSection) {
                        for(int i = 0; i < it.size(); i++) {
                        if (it[i]->getState() == ENTITY_STATE_TO_BE_REMOVED) {
                                delete it[i];
                                it[i] = nullptr; // Set to nullptr to avoid dangling pointer
                                it.erase(it.begin() + i);
                                i--; // Adjust index after erasing
                        }
                }
        };
        for(auto&section: itemsSection) {
                for (int i = 0;i<section.size();i++){
                if(section[i]->getState()==ItemState::COLLECTED) {
                        delete section[i];
                        section[i] = nullptr; // Set to nullptr to avoid dangling pointer
                        section.erase(section.begin() + i);
                        i--; // Adjust index after erasing
                }
            }
        }

        player->updateStateAndPhysic();

}
void Level::DrawLevel()
{
        ClearBackground(backgroundColor);
        camera.target.y = GetScreenHeight()/2;
        if(player->getPosition().x>GetScreenWidth()/2&&player->getPosition().x<map.getMapWidth()-GetScreenWidth()/2)
        {
                camera.target.x = player->getPosition().x ;
        }
        else if(player->getPosition().x<GetScreenWidth()/2)
        {
                camera.target.x = GetScreenWidth()/2;
        }
        else camera.target.x=map.getMapWidth()-GetScreenWidth()/2;

        if(camera.target.x-GetScreenWidth()/2>=currBackgroundStarX)
        {
            currBackgroundStarX = currBackgroundStarX+background.width*1.3f;
        }
        if(camera.target.x+GetScreenWidth()/2<=currBackgroundStarX+background.width*1.3f)
        {
            currBackgroundStarX = currBackgroundStarX-background.width*1.3f;
        }

    

        
        BeginMode2D(camera);
        
        DrawTextureEx(background, Vector2{currBackgroundStarX-background.width*1.3f,-200}, 0.0f, 1.3f, WHITE);
        DrawTextureEx(background,Vector2{currBackgroundStarX,-200},0.0f,1.3f,WHITE);
        DrawTextureEx(background,Vector2{currBackgroundStarX+background.width*1.3f,-200},0.0f,1.3f,WHITE);
        for (int i = -1; i <= 1; ++i) // Check sections around the player
        {
                        int currentSection = currentPlayerSection + i;

                        if(currentPlayerSection==0)
                                currentSection++;
                        if(currentSection==map.getMapWidth()/map.getSectionWidth())
                                currentSection--;
                        std::vector<Tile*>& interactiveTiles = interactiveTilesSection[currentSection];
                        std::vector<Tile*>& nonInteractiveTiles = nonInteractiveTilesSection[currentSection];
                        std::vector<Block*>& blocks = blocksSection[currentSection];
                        std::vector<Item*>& items = itemsSection[currentSection];
                        std::vector<Monster*>& monsters = monstersSection[currentSection];
                        for (auto const &tile : interactiveTiles)
                        {
                                tile->Draw();
                        }
                        for (auto const &tile : nonInteractiveTiles)
                        {
                                tile->Draw();
                        }
                        for (auto const &item : items)
                        {
                                item->Draw();
                        }
                        for (auto const &block : blocks)
                        {
                                block->Draw();
                        }

                        for (auto const &monster : monsters)
                        {
                                monster->Draw();
                        }

        }
        player->Draw();
        EndMode2D();
}

void Level::loadCoins() {
    }
