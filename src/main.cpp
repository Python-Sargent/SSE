#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include "main.hpp"

struct {
    sf::Time deltaTime;
    sf::Time frameTime;
    sf::Time elapsed;
    int framerate = FRAMERATE;
    sf::Clock getClock() {
        return this->clock;
    }
    void Update() {
        this->elapsed = this->clock.getElapsedTime();
        this->deltaTime = this->elapsed - this->lastFrame;
        this->frameTime = this->frameTime + this->deltaTime;
        this->lastFrame = this->elapsed;
    }
    void Frame() {
        this->frameTime = sf::milliseconds(0);
    }
    void Start() {
        this->clock.restart();
        this->Update();
    }
    sf::Clock clock;
    sf::Time lastFrame;
}Time;

struct{
    bool focused = true;
    sf::Text debugText;
    void FixedFrame() {
        // do stuff on a fixed framerate
        //std::cout << Time.frameTime.asMilliseconds() << std::endl;
        this->debugText.setString("Milliseconds Per Frame: " + Time.frameTime.asMilliseconds());
    }
    void Init() {
        //do stuff at the start of the game, like creating sprites and loading assets
        sf::Font font;
        if (!font.loadFromFile("../resources/JetBrains_Mono/static/JetBrainsMono-Regular.ttf"))
        {
            throw("Missing Font Family 'JetBrainsMono-Regular.ttf'");
        }
        this->debugText.setFont(font);
        this->debugText.setString("Milliseconds Per Frame: ");
        this->debugText.setCharacterSize(24);
        this->debugText.setFillColor(sf::Color::White);
    }
    struct{
        void KeyEvent(sf::Event event) {
            //do stuff when keys are pressed/unpressed
        }
        void MouseEvent(sf::Event event) {
            //do stuff on mouse events
        }
        void FocusEvent(sf::Event event) {
            //do stuff when window focus changes
        }
        void TextEvent(sf::Event event, sf::String text, char text2) {
            //do stuff with entered text
            std::cout << text2;
        }
    }Event;
}Game;

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Simple SFML Engine");
    bool setup = false;

    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen())
    {
        if (!setup) { Time.Start(); Game.Init(); setup = true;}
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed || sf::Event::KeyReleased) {
                Game.Event.KeyEvent(event);
            } else if (event.type == sf::Event::MouseButtonPressed || sf::Event::MouseButtonReleased || sf::Event::MouseWheelScrolled) {
                Game.Event.MouseEvent(event);
            } else if (event.type == sf::Event::LostFocus || sf::Event::GainedFocus || sf::Event::MouseLeft || sf::Event::MouseEntered || sf::Event::MouseMoved) {
                Game.Event.FocusEvent(event);
                Game.focused = window.hasFocus();
            } else if (event.type == sf::Event::TextEntered) {
                char unicodeText;
                if (event.text.unicode < 128)
                    unicodeText =  static_cast<char>(event.text.unicode);
                Game.Event.TextEvent(event, event.text.unicode, unicodeText);
            }
        }
        Time.Update();

        //std::cout << Time.deltaTime.asMilliseconds() << std::endl;
        if (Time.frameTime.asMilliseconds() >= 16.6666) { //ends up being 17 milliseconds
            Game.FixedFrame();
            Time.Frame();
        }
        //window.draw(Game.debugText); //idk why but this is the front of the segfault
        //std::cout << Time.elapsed.asMilliseconds() << std::endl;
        window.clear();
        window.display();
    }

    return 0;
}

struct Vector2
{
    float x, y;

    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

    Vector2 add(Vector2 other) {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator+(Vector2 other) {
        return Vector2(x + other.x, y + other.y);
    }
};

//milliseconds per frame = 1 / framerate * 1000