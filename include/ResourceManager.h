#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
Texture2D FlipTextureHorizontal(const Texture2D &texture);
class ResourceManager{
    private:
        ResourceManager() = default;
        ~ResourceManager();
        static ResourceManager* instance;   

        std::unordered_map<std::string, Texture2D> textures;
        std::unordered_map<std::string, Sound> sounds;
        std::unordered_map<std::string, Music> musics;

         void loadTextures();
         void loadSounds();
         void loadMusics();

         void unloadTexture();
         void unloadSounds();
         void unloadMusics();

    public:
        static ResourceManager &getInstance();

        // Load and unload
        void loadResource();
        void unloadResource();
        // Texture
        // Access an element by typing getTexture[nameofanimation+index]
        Texture2D &getTexture(const std::string&) ;
        Sound &getSounds(const std::string& name) ;
        Music &getMusics(const std::string& name) ;
};