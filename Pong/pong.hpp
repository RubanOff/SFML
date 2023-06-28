#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

const float racket_size_y = 150;
const float racket_size_x = 20;
const float ball_radius = 20;
const float fieldWidth = 2000;
const float fieldHeight = 1300;
const float BALL_SPEED = 500.f;
const float RACKET_SPEED = 600.f;

void init(std::string name);

class Field 
{   
    public:
        static void draw_playing_field(sf::Texture& backgroundTexture, sf::Image& backgroundImage, sf::RectangleShape& background, sf::RectangleShape& racket1, sf::RectangleShape& racket2, sf::CircleShape& ball);
        static void init_Text(sf::Text &text, int position_x, int position_y);
        static void winner_window(int point_player, sf::RenderWindow& window, std::string name);
        static void check_point(int point_player1, int point_player2, sf::RenderWindow& window, std::string name, std::string name2);
} ;

class Ball : public sf::CircleShape
{
    private:
        float dir_x = -1;
        float dir_y = 1;
    public:
        void move_ball(sf::RectangleShape& racket1, sf::RectangleShape& racket2, int& point_player1, int& point_player2, float dtime);
} ;

class Racket
{
    public:
        static void move_racket(sf::RectangleShape& racket, sf::Keyboard::Key Up, sf::Keyboard::Key Down, float dtime);
} ;

const float size_menu_x = 2000;
const float size_menu_y = 1300;
const float size_button_x = 400;
const float size_button_y = 200;

// Создали класс Button
class Button : public sf::RectangleShape
{
    sf::Texture texture_button; // Поле texture
public:
    Button(float x, float y, float size_button_x, float size_button_y, const std::string& file_texture_button); // Конструктор Button
    // x - координата по оси 
    bool mouse_on_button(const sf::RenderWindow& window); // Метод mouse_on_button наведение мыши на кнопку
    
};


class Background : public sf::Drawable
{
    sf::Texture texture_menu;
    sf::RectangleShape shape;
public:
    Background(const std::string& file_texture_menu); // Конструктор Menu
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

void main_menu(sf::RenderWindow& window);
void select_name(sf::RenderWindow& window);
