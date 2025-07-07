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
        Color* text_color;

        Texture2D *texture ;
        Rectangle textureRect; 

        Color* buttonColor;
        Color idle_color,idle_text_color;
        Color hover_color, hover_text_color;
        Color active_color, active_text_color;

        bool haveBackground = true;
        float clickAcum;
        bool recivedClick;
        void handleClick();
        bool doneClick;
        const static float CLICK_TIME; // Time to consider a click valid
    public:
        Button(Vector2 position, Vector2 size);
        ~Button() override;
        bool isHover() const;
        bool isClicked() ;
        Button& setIdleColor(Color color);
        Button& setHoverColor(Color color);
        Button& setActiveColor(Color color);

        Button &setText(std::string text);
        Button& setTextPosition(Vector2 pos);
        Button& setTextSize(int size);
        Button &setTextIdleColor(Color color);
        Button& setTextHoverColor(Color color);
        Button& setTextActiveColor(Color color);

        Button& EnableBackground();
        Button& DisableBackground();

        Button& setPrimaryTexture( Texture2D &texture);
        Button& setTexturePosition(Vector2 pos);
        Button& setTextureSize(Vector2 size);
        Button& fitTexture();

        void update() override;
        virtual void Draw() override;
};