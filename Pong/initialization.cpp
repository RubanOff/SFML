#include "pong.hpp"

int timer1 = 10;

void Field::draw_playing_field(sf::Texture& backgroundTexture, sf::Image& backgroundImage, sf::RectangleShape& background, sf::RectangleShape& racket1, sf::RectangleShape& racket2, sf::CircleShape& ball)
{
    backgroundImage.loadFromFile("Photo/IMG_0401.JPEG");

    backgroundTexture.loadFromImage(backgroundImage);

    background.setTexture(&backgroundTexture);
    background.setSize(sf::Vector2f(fieldWidth, fieldHeight));
    background.setPosition(0, 0);

    racket1.setSize(sf::Vector2f(racket_size_y, racket_size_x));
    racket1.setRotation(90);
    racket1.setFillColor(sf::Color::White);

    racket2.setSize(sf::Vector2f(racket_size_y, racket_size_x));
    racket2.setRotation(90);
    racket2.setFillColor(sf::Color::White);

    ball.setPosition(965, 690);
    ball.setRadius(ball_radius);
    ball.setFillColor(sf::Color::Red);
}

void Field::init_Text(sf::Text &text, int position_x, int position_y)
{
    static sf::Font font;
    font.loadFromFile("Photo/FontsFree-Net-Disket-Mono-Bold.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(100);
    text.setPosition(position_x, position_y);
}

void Ball::move_ball(sf::RectangleShape& racket1, sf::RectangleShape& racket2, int& point_player1, int& point_player2, float dtime)
{
    if (timer1) --timer1;
    
    if(getGlobalBounds().intersects(racket1.getGlobalBounds()) && (getPosition().x < 1950 && getPosition().x > 55))
    {
        dir_x = 1;

        // if (racket1.getPosition().y < getPosition().y && getPosition().y < racket1.getPosition().y + racket_size_y/2)
        // {
        //     dir_y = -1;
        // }
        // if (racket1.getPosition().y + racket_size_y/2 < getPosition().y && getPosition().y < racket1.getPosition().y + racket_size_y)
        // {
        //     dir_y = 1;
        // }
    }

    if(getGlobalBounds().intersects(racket2.getGlobalBounds()) && (getPosition().x < 1950 && getPosition().x > 55))
    {
        dir_x = -1;

        // if (racket2.getPosition().y < getPosition().y && getPosition().y < racket2.getPosition().y + racket_size_y/2)
        // {
        //     dir_y = -1;
        // }
        // if (racket2.getPosition().y + racket_size_y/2 < getPosition().y && getPosition().y < racket2.getPosition().y + racket_size_y)
        // {
        //     dir_y = 1;
        // }
    }

    if (getPosition().y < 20 || getPosition().y > 1230)
    {
        if (dir_x && !timer1)
        {
            dir_y = -dir_y;
            timer1 = 10;
        }
    }

    if (getPosition().x <= 45)
    {
        point_player2 += 1;
        setPosition(965, 690);
    }
    
    if (getPosition().x > 1950)
    {
        point_player1 += 1;
        setPosition(965, 690);
    }

    move(BALL_SPEED * dir_x * dtime, BALL_SPEED * dir_y * dtime);
}

void Racket::move_racket(sf::RectangleShape& racket, sf::Keyboard::Key Up, sf::Keyboard::Key Down, float dtime)
{
    sf::Vector2f racketSpeed(0, 0);

    if (sf::Keyboard::isKeyPressed(Up))
    {
        if (racket.getPosition().y > 20)
            racketSpeed.y = -RACKET_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(Down))
    {
        if (racket.getPosition().y < 1130)
            racketSpeed.y = RACKET_SPEED;
    }

    racket.move(racketSpeed * dtime);
}

void init(std::string name)
{
    sf::RenderWindow window(sf::VideoMode(fieldWidth, fieldHeight), "Ping Pong", sf::Style::None | sf::Style::Titlebar);

    sf::Image backgroundImage;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;


    sf::RectangleShape current_racket;
    sf::RectangleShape enemy_racket;

    Ball ball;

    sf::Text text;
    sf::Text text2;
    sf::Text text_name1;
    sf::Text text_name2;

    Field::draw_playing_field(backgroundTexture, backgroundImage, background, current_racket, enemy_racket, ball);

    Field::init_Text(text, 900, 50);
    Field::init_Text(text2, 1000, 50);
    Field::init_Text(text_name2, 1100, 50);

    sf::TcpSocket socket;
    sf::Packet packet;

    unsigned short port = 2000;

    sf::IpAddress ip = "10.55.133.51";

    if (socket.connect(ip, port) != sf::Socket::Done)
        return;

    if (socket.send(&name, sizeof(&name)) != sf::Socket::Done)
        return;

    std::string enemy_name;
    float x_value1 = 0, x_value2 = 0;


    if (socket.receive(packet) == sf::Socket::Done)
        packet >> x_value1 >> x_value2 >> enemy_name;

    Field::init_Text(text_name1, 400, 50);
    Field::init_Text(text_name2, 1300, 50);
    current_racket.setPosition(x_value1, 638);
    enemy_racket.setPosition(x_value2, 638);

    int point_player1 = 0;
    int point_player2 = 0;

    float enemy_y = 0;
    size_t received;

    sf::Clock clock;
    float dtime = 0.f;

    if (x_value1 == 75)
    {
        text_name1.setString(name);
        text_name2.setString(enemy_name);
    }
    else
    {
        text_name1.setString(enemy_name);
        text_name2.setString(name);
    }

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        dtime = clock.getElapsedTime().asSeconds();
        clock.restart();

        Racket::move_racket(current_racket, sf::Keyboard::W, sf::Keyboard::S, dtime);

        socket.send(&current_racket.getPosition().y, sizeof(float));
        socket.receive(&enemy_y, sizeof(enemy_y), received);
        enemy_racket.setPosition(x_value2, enemy_y);

        if (x_value1 == 75)
            ball.move_ball(current_racket, enemy_racket, point_player1, point_player2, dtime);
        else
            ball.move_ball(enemy_racket, current_racket, point_player1, point_player2, dtime);

        text.setString(std::to_string(point_player1));
        text2.setString(std::to_string(point_player2));
    
        Field::check_point(point_player1, point_player2, window, name, enemy_name);  

        window.clear();
        window.draw(background);
        window.draw(current_racket);
        window.draw(enemy_racket);
        window.draw(ball);
        window.draw(text_name1);
        window.draw(text_name2);
        window.draw(text);
        window.draw(text2);
        window.display();
    }
}

void Field::check_point(int point_player1, int point_player2, sf::RenderWindow& window, std::string name, std::string name2)
{
    if (point_player1 == 30)
    {
        Field::winner_window(point_player1, window, name);
    }

    if (point_player2 == 30)
    {
        winner_window(point_player2, window, name2);
    }
}

void Field::winner_window(int point_player, sf::RenderWindow& window, std::string name) 
{
    // std::ofstream out;          
    // out.open("table_score.txt", std::ios::app);

    // if (out.is_open())
    // {
    //     out << "Name: " << name << " " << "Score: " << point_player << std::endl;
    // }



    // out.close(); 
    Background winner("Photo/2.jpg");

    
    //Кнопка replay (левая)
    // Button replay(size_menu_x/2.8, size_menu_y/1.2, size_button_x, size_button_y, "Photo/startt.png");
    
    //Кнопка quit (правая)
    Button close(size_menu_x/1.5, size_menu_y/1.2, size_button_x/1.2, size_button_y, "Photo/quit.png");

    sf::Text text;
    sf::Text name_player;
    sf::Text win;

    Field::init_Text(text, 400, 50);
    Field::init_Text(name_player, 400, 600);
    Field::init_Text(win, 100, 500); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                    if(close.mouse_on_button(window))
                    {
                        window.close();
                    }
                    // if(replay.mouse_on_button(window))
                    // {
                    //     select_name(window);
                    //     return;
                    // }
                
            }

        }


        win.setString("Winner: ");
        text.setString(std::to_string(point_player));
        name_player.setString(name);

        window.clear();
        window.draw(text);
        window.draw(winner);
        window.draw(close);
        // window.draw(replay);
        window.draw(name_player);
        window.draw(win);
        window.display();
    }
}
