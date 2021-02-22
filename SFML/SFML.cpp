#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <windows.h>
using namespace sf;
using namespace std;

const int H = 10;
const int W = 43;

float offsetX = 0, offsetY = 0;

class map {





};

class player {
public:
    player(sf::String map_input[], Texture &t) {
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {

                map[i][j] = map_input[i][j];


            }
        }
        MainChar.setTexture(t);
        MainChar.setTextureRect(IntRect(0, 180, CharWidth, CharHeight));//50-высота 40-ширина

    }

    void gravity(float time) {
        if (time > 10) { time = 1; }
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (map[i][j] == 'A') {

                    tempX = j * 48 - offsetX;
                    tempY = i * 48;
                    if (x + CharWidth / 2 > tempX && x + CharWidth / 2 < tempX + 48 && y + CharHeight > tempY && y + CharHeight < tempY + 49 || x > tempX && x < tempX + 48 && y + 50 > tempY && y + 50 < tempY + 49 || x + CharWidth - 2 > tempX && x + CharWidth - 2 < tempX + 48 && y + CharHeight > tempY && y + CharHeight < tempY + 49) {
                        y = y - speed * time * 0.1;
                    }
                }
            }
        }
        y = y + speed * time * 0.1;
    }
    void movement(float time) {
        offsetX = x;

        if (Keyboard::isKeyPressed(Keyboard::D)) { //Right

            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    if (map[i][j] == 'A') {

                        tempX = j * 48 - offsetX;
                        tempY = i * 48;
                        if (x + CharWidth + speed > tempX && x + CharWidth + speed < tempX + 48 && y + CharHeight / 2 > tempY && y + CharHeight / 2 < tempY + 48 || x + CharWidth + speed > tempX && x + CharWidth + speed < tempX + 48 && y + 2 > tempY && y + 2 < tempY + 48 || x + CharWidth + speed > tempX && x + CharWidth + speed < tempX + 48 && y + CharHeight - 3 > tempY && y + CharHeight - 3 < tempY + 48) {
                            x -= speed / time;
                        }


                    }
                }
            }

            x += speed / time;

            if (anim < 6) {
                anim++;
            }
            else {
                anim = 1;
            }

        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) { //Left

            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    if (map[i][j] == 'A') {

                        tempX = j * 48 - offsetX;
                        tempY = i * 48;
                        if (x - speed > tempX && x - speed < tempX + 48 && y + CharHeight / 2 > tempY && y + CharHeight / 2 < tempY + 48 || x - speed > tempX && x - speed < tempX + 48 && y + 2 > tempY && y + 2 < tempY + 48 || x - speed > tempX && x - speed < tempX + 48 && y + CharHeight - 2 > tempY && y + CharHeight - 2 < tempY + 48) {
                            x += speed / time;
                        }
                    }
                }
            }
            x -= speed / time;
            if (anim < 6) { anim = 6; }
            if (anim < 12) {
                anim++;
            }
            else {
                anim = 7;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::W)) {
            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    if (map[i][j] == 'A') {

                        tempX = j * 48 - offsetX;
                        tempY = i * 48;
                        if (x + CharWidth / 2 > tempX && x + CharWidth / 2 < tempX + 48 && y > tempY && y < tempY + 49 || x > tempX && x < tempX + 48 && y > tempY && y < tempY + 49 || x + CharWidth - 2 > tempX && x + CharWidth - 2 < tempX + 48 && y > tempY && y < tempY + 49) {
                            y += (speed / time)*2;
                        }
                    }
                }
            }

            y -= (speed / time)*2;
        }

        set_anim();
        MainChar.setPosition(x, y);
    }
    int get_x() {

        return x;

    }
    int get_y() {
        return y;

    }
    Sprite Get_sprite() {

        return MainChar;

    }
private:
    void set_anim() {

        if (anim < 6) {
            MainChar.setTextureRect(IntRect(0 + (40 * anim), 244, 40, 50));
        }
        else if (anim < 12 && anim > 6) {

            MainChar.setTextureRect(IntRect(0 + (40 * (anim - 6)), 244, -40, 50));
        }

    }
    Sprite MainChar;
    String map[H][W];
    float tempX = 0;
    float tempY = 0;
    float x = 90;
    float y = 90;
    float speed = 5;
    int anim = 1;
    int CharWidth = 40;
    int CharHeight = 50;
};

int main()
{
    sf::String map[H] = {
"A  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
"A           A                      A     A",
"A         AAA                      A     A",
"A        A  A                            A",
"A           A                     AAAAAAAA",
"A           A                            A",
"A                                        A",
"A                              AA        A",
"A                             AAA        X",
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    };



    RenderWindow window(VideoMode(1060, 500), "Phonk");
    //sky "box"
    Texture t3;
    t3.loadFromFile("assets/background.png");
    Sprite skybox;
    skybox.setTexture(t3);
    skybox.setTextureRect(IntRect(0, 0, 1920, 1080));
    // walls
    Texture t2;
    t2.loadFromFile("assets/wall.png");
    Sprite wall;
    wall.setTexture(t2);
    wall.setTextureRect(IntRect(0, 0, 48, 48));
    // main character (mc)
    Texture t;
    t.loadFromFile("assets/sprite.png");
    //
    player p1(map, t);
    Clock clock;
    Event event;
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 2000;
        p1.gravity(time);
        p1.movement(time);
        Sleep(1);
        //



        while (window.pollEvent(event))
        {

            //





            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::Cyan);
        window.draw(skybox);
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W - 1; j++)
            {
                if (map[i][j] == 'A') wall.setTextureRect(IntRect(0, 0, 48, 48));//casual wall
                if (map[i][j] == 'X') continue;                                  //trigger
                if (map[i][j] == ' ') continue;                                  //empty space
                wall.setPosition(j * 48 - offsetX, i * 48);
                window.draw(wall);
            }
        }
        window.draw(p1.Get_sprite());
        window.display();
    }

    return 0;
}