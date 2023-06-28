#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "pong.hpp"

// Определили конструктор кнопки
Button::Button(float x, float y, float size_button_x, float size_button_y, const std::string& file_texture_button)
{
    setSize(sf::Vector2f(size_button_x, size_button_y)); // Задает размер прямоугольника
    setOrigin(getSize()/2.0f); // Задает центр относительно прямоугольника
    setPosition(x, y); // Задает центр относительно обсолютной системы координат
    texture_button.loadFromFile(file_texture_button); // Загрузили текстуру прямоугольника
    setTexture(&texture_button); // Установили текстуру для прямоугольника
}
// Определили метод mouse_on_button
bool Button::mouse_on_button(const sf::RenderWindow& window)
{
    return getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}


Background::Background(const std::string& file_texture_menu)
{
    shape.setSize(sf::Vector2f(size_menu_x, size_menu_y));
    texture_menu.loadFromFile(file_texture_menu);
    shape.setTexture(&texture_menu);
}


//Отрисовка Background
void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}



//Реализация кнопки старт
void select_name(sf::RenderWindow& window)
{
    //Задний фон для выбора имени
    Background menu_select_name("Photo/2.jpg");
    
    
    //Кнопка, где вводят имя
    Button button_select_name(size_menu_x/3.5, size_menu_y/3, size_button_x * 2, size_button_y, "Photo/white.jpg");
    
    //Кнопка сервер (левая)
    Button server(size_menu_x/3.6, size_menu_y/2, size_button_x/1, size_button_y/1.2, "Photo/connect.png");
    
    //Кнопка клиент (правая)
    // Button client(size_menu_x/2.5, size_menu_y/1.7, size_button_x/1.2, size_button_y/1.5, "Photo/client.png");
    
    
    

    
    
    sf::Text text;
    std::string introduction = "Enter name:\n";
    std::string str = "";
    
    
    text.setString(introduction);
    text.setPosition(size_menu_x/3.5 - size_button_x, size_menu_y/4);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Black);
    sf::Font font;
    font.loadFromFile("Photo/FontsFree-Net-Disket-Mono-Bold.ttf");
    text.setFont(font);
    
    
    
    
    while(window.isOpen())
    {
        sf::Event event;
        sf::Mouse mouse;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(str.size() != 0)
                {
                    if(event.key.code == sf::Keyboard::BackSpace)
                    {
                        str.erase(std::prev(str.end()));
                        text.setString(introduction + str);
                        
                    }
                }
    
            }
            else if(event.type == sf::Event::TextEntered)
            {
                char entered_symbol = event.text.unicode;
                if ((entered_symbol >= 'a' && entered_symbol <= 'z') || (entered_symbol >= 'A' && entered_symbol <= 'Z'))
                {
                    str += entered_symbol;
                    text.setString(introduction + str);
                }
                
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(str.size() != 0)
                {
                    if(server.mouse_on_button(window))
                    {
                        window.close();
                        init(str);
                        return;
                        //Кнопка сервер
                        
                    }
                    // if(client.mouse_on_button(window))
                    // {
                    //     window.close();
                    //     init('c', str);
                    //     return;
                    //     //Кнопка клиент
                        
                    // }
                }
                    
            }
            
        }

        window.clear();
        window.draw(menu_select_name);
        window.draw(button_select_name);
        window.draw(text);
        //window.draw(confirm_name);
        window.draw(server);
        // window.draw(client);
        window.display();
    }
}

//Основная функция
void main_menu(sf::RenderWindow& window)
{
    window.setFramerateLimit(60);
    
    //Кнопка старта (левая)
    Button start_button(size_menu_x/2, size_menu_y/1.25, size_button_x, size_button_y, "Photo/startt.png");
    
    //Кнопка закрытия окна (правая)
    // Button close_button(size_menu_x/1.5, size_menu_y/1.2, size_button_x, size_button_y, "Photo/quit.png");
    
    // Button confirm_name(size_menu_x/1.8, size_menu_y/1.5, size_button_x, size_button_y, "/Users/eugene/Desktop/XCodeProject/Ping-pong/Picon-exit-20.jpg.png");
    
    
    
    Background start_menu("Photo/4.jpg");
    
    // Background menu_select_name("/Users/eugene/Desktop/XCodeProject/Ping-pong/Ping-pong/icon-exit-20.jpg.png");
    
    sf::Text text;
    std::string name = "Ping-Pong";
    text.setString(name);
    text.setPosition(size_menu_x/2.1 - size_button_x, size_menu_y/5);
    text.setCharacterSize(150);
    text.setFillColor(sf::Color::Black);
    sf::Font font;
    font.loadFromFile("Photo/FontsFree-Net-Disket-Mono-Bold.ttf");
    text.setFont(font);
    
    
    
    
    
    while(window.isOpen())
    {
        sf::Mouse mouse;
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                    // if(close_button.mouse_on_button(window))
                    // {
                    //     window.close();
                    // }
                    if(start_button.mouse_on_button(window))
                    {
                        select_name(window);
                        return;
                    }
                
            }
        }
        
        
        window.clear();
        window.draw(start_menu);
        window.draw(start_button);
        // window.draw(close_button);
        window.draw(text);
        window.display();
    }
}
