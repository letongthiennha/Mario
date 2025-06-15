#pragma once
#include <string>
#include "raylib.h"
#include "UIObject.h"
class Button : public UIObject {
    private:
        const Rectangle originalHitBox;
        Rectangle hitBox;
        Vector2 pos;
        Vector2 size;

        float scale;
        int text_size = 20;
        std::string text;
        Vector2 text_pos;
        const Color* text_color;

        Texture2D *texture = nullptr;
        Rectangle textureRect; 

        const Color* buttonColor;
        const Color idle_color,idle_text_color;
        const Color hover_color, hover_text_color;
        const Color active_color, active_text_color;

        bool haveBackground = true;
        float clickAcum;
        bool recivedClick;
        void handleClick();
        bool doneClick;
        const static float CLICK_TIME; // Time to consider a click valid
    public:
        Button(Vector2 position, Vector2 size, std::string text = "", Texture2D *const &texture = nullptr, 
            Color idleColor = WHITE, Color hoverColor = LIGHTGRAY, Color activeColor = GRAY,
            Color idleTextColor = BLACK, Color hoverTextColor = WHITE, Color activeTextColor = WHITE);
        ~Button() override;
        bool isHover() const;
        bool isClicked() ;

        void setTextPosition(Vector2 pos);
        void setTextSize(int size);



        void OnBackground();
        void OffBackground();
        
        void setTexturePosition(Vector2 pos);
        void setTextureSize(Vector2 size);
        void fitTexture();

        void update() override;
        virtual void Draw() override;
};