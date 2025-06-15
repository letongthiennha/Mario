#include "Button.h"
#include "GameClock.h"
const float Button::CLICK_TIME = 0.2; // Example: Click is valid if held for 0.1 seconds, or use for debounce. Adjust as needed.

void Button::handleClick()
{
    if(!recivedClick&&isHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        recivedClick = true;
    } 
    if (recivedClick) {
        clickAcum += GameClock::getInstance().FIXED_TIME_STEP;  // Accumulate time since click started
        if (clickAcum >= CLICK_TIME) {
            recivedClick = false;  // Reset after click time
            clickAcum = 0.0f;  // Reset click accumulation time
            doneClick = true; 
        }
    }
}

Button::Button(Vector2 position, Vector2 size, std::string text, Texture2D *const &background, Color idleColor, Color hoverColor, Color activeColor,
               Color idleTextColor, Color hoverTextColor, Color activeTextColor)
    : pos(position), 
    size(size), 
    text(text),
    idle_color(idleColor),
    idle_text_color(idleTextColor),
    hover_color(hoverColor),
    hover_text_color(hoverTextColor),
    active_color(activeColor),
    active_text_color(activeTextColor),
    buttonColor(&idle_text_color), text_color(&idle_text_color),
     scale(1.0f),
    originalHitBox{position.x, position.y, size.x, size.y},
    recivedClick(false), clickAcum(0.0f), doneClick(false)
{
    ;
    hitBox = originalHitBox;  // Initialize hitBox with originalHitBox
    textureRect = Rectangle{0, 0, (float)10, (float)10};  // Initialize texture rectangle
    texture = background;
    int textWidth = MeasureText(text.c_str(), text_size);
        int textX = pos.x + (size.x - textWidth) / 2;
        int textY = pos.y + (size.y - text_size) / 2;
    text_pos = Vector2{(float)textX, (float)textY};  // Center text in the button   
}

Button::~Button() {
    texture = nullptr;
}

bool Button::isHover() const {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, hitBox);
}

bool Button::isClicked()  {
    if (doneClick) {
        doneClick = false;  // Reset click state after handling
        return true;  // Return true if the button was clicked
    }
    return false;  // Return false if not clicked
}

void Button::setTextPosition(Vector2 pos)
{
    text_pos.x = pos.x+this->pos.x;  
    text_pos.y = pos.y+this->pos.y;  
}

void Button::setTextSize(int size)
{
    text_size = size;
}

void Button::OnBackground()
{
    haveBackground = true;  // Enable background drawing
}
void Button::OffBackground()
{
    haveBackground = false;  // Disable background drawing
}

void Button::setTexturePosition(Vector2 pos)
{
    if (texture != nullptr) {
        textureRect.x = this->pos.x+pos.x;
        textureRect.y = this->pos.y+pos.y;
    }
}
void Button::setTextureSize(Vector2 size)
{
    if (texture != nullptr) {
        textureRect.width = size.x;
        textureRect.height = size.y;
    }
}

void Button::fitTexture()
{
    setTextureSize(Vector2{hitBox.width, hitBox.height});  // Set texture size to match hitBox size
    setTexturePosition(Vector2{0, 0});  // Set texture position to the top-left corner of the button
}

void Button::update()
{
    handleClick();  // Handle click state
    if (recivedClick) {
        scale=1.1f;  // Reset scale when clicked
        buttonColor = &active_color;
        text_color = &active_text_color;  // Change text color when clicked
    } else if (isHover()) {
        scale = 1.2f;
        buttonColor = &hover_color;
        text_color = &hover_text_color;  // Change text color when hovered
    } else {
        scale = 1.0f;  // Reset scale when not hovering
        buttonColor = &idle_color;  // Fix: Set to idle when not hovering
        text_color = &idle_text_color;  // Reset text color to idle
    }  
    hitBox.width= originalHitBox.width * scale;
    hitBox.height = originalHitBox.height * scale;
    size.x = hitBox.width;
    size.y = hitBox.height;
}

void Button::Draw() {

    if(haveBackground) {
        DrawRectangleRounded(hitBox,0.5f,360,*buttonColor);  // Draw background rectangle
        DrawRectangleRoundedLinesEx(hitBox, 0.5f, 360,3.0f,BLACK);  // Draw border around the button
    }

    // Draw texture if available
    if (texture != nullptr) {
        DrawTextureNPatch(*texture, NPatchInfo{Rectangle{0,0,(float)texture->width,(float)texture->height},0,0,0,0}, textureRect, Vector2{0, 0}, 0.0f, *buttonColor);  // Draw texture with NPatch
    }
    
    // Draw text
    if (!text.empty()) {
        DrawText(text.c_str(), (int)text_pos.x, (int)text_pos.y, text_size, *text_color);  // Draw text with specified color
    }
}