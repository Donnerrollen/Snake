// Created by Donnerrollen

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>

using namespace sf;
using namespace std;

const int GameSpeed = 200; // время, за которое обновляется поле (в милисекундах)
const float I = 25.f; // еденица размера поля

int map[20][20]
{  
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

class Apple {
private:
    int x, y;

public:
    void CreateApple(string SnakeBody_x, string SnakeBody_y) {
        bool Success = false;
        do {
            srand(time(0));
            x = rand() % 19;

            srand(time(0) * 100 - 1243527964);
            y = rand() % 19;

            for (int j = 0; j < SnakeBody_x.size(); j++) {
                if ((y != SnakeBody_y[j] - '0') && (x != SnakeBody_x[j] - '0')) {
                    Success = true;
                }
            }

        } while (Success == false);
}

    int GetAppleCoordinateX() {
        return x;
    }

    int GetAppleCoordinateY() {
        return y;
    }
};

class Snake {
private:
    string body_x, body_y;
    string MoveTo;

public:
    Snake(string bd_x, string bd_y) {
        SetBody(bd_x, bd_y);
        SetMoveTo("Up");
    }
    
    void SetBody(string bd_x, string bd_y) {
        body_x = bd_x;
        body_y = bd_y;
    }

    void SetMoveTo(string derection) {
        MoveTo = derection; 
    }

    String GetMoveTo() {
        return MoveTo;
    }

    int GetSizeBody() {
        return body_x.size();
    }

    int GetBlockBodyX(int index) {
        return body_x[index] - '0';
    }

    int GetBlockBodyY(int index) {
        return body_y[index] - '0';
    }

    string GetSnakeBodyX() {
        return body_x;
    }

    string GetSnakeBodyY() {
        return body_y;
    }

    void SnakeMoving() {
        for (int j = body_x.size() - 1; j > 0; j--) {
            body_x[j] = body_x[j - 1];
            body_y[j] = body_y[j - 1];
        }
        if (MoveTo == "Up") {
            body_y[0] = body_y[0] - 1;
        }

        if (MoveTo == "Down") {
            body_y[0] = body_y[0] + 1;
        }

        if (MoveTo == "Left") {
            body_x[0] = body_x[0] - 1;
        }

        if (MoveTo == "Right") {
            body_x[0] = body_x[0] + 1;
        }
    }

    void SnakeLvlUp() {
        int x_tail, y_tail;
        x_tail = body_x[body_x.size()]; 
        y_tail = body_y[body_y.size()];
        body_x = body_x + (char)(x_tail - body_x[body_x.size() - 1]);
        body_y = body_y + (char)(y_tail - body_y[body_y.size() - 1]);
    }
};

int score = 0;
bool WastheClick;
bool GameIsOver;

int main()
{
    Font font;
    string txt;
    Text text;
    string body_x, body_y;
    float body_x_i, body_y_i;
    Clock clock;
    Snake MainSn("000", "567");
    Apple app;

    RenderWindow window(VideoMode(I * 20, I * 24), "Snake");

    if (!font.loadFromFile("font.ttf"))
    {
        cout << "error";
    }
    txt = "Score: " + to_string(score);
    text.setFont(font);
    text.setString(txt);   
    text.setPosition(I * 14,  I * 21);
    text.setCharacterSize(30);
    text.setFillColor(Color::Yellow);

    app.CreateApple("000", "567");
    RectangleShape apple(Vector2f(I, I));
    apple.setFillColor(Color::Red);
    apple.setPosition(I * app.GetAppleCoordinateX(), I * app.GetAppleCoordinateY());
//    cout << app.GetAppleCoordinateX() << " " << app.GetAppleCoordinateY() << endl;

    RectangleShape rectangle(Vector2f(I * 20, I * 20));

    RectangleShape rectBody(Vector2f(I, I));
    rectBody.setFillColor(Color::Green);

    window.clear(Color::Black);
    window.draw(rectangle);
    window.draw(apple);
    window.draw(rectBody);
    window.draw(text);
    clock.restart();

    while (window.isOpen())
    {
        float timeCl = clock.getElapsedTime().asMilliseconds();
 //       cout << time << endl;

        Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Key::Escape))
                window.close();

            if ((event.key.code == Keyboard::Key::W) && WastheClick == false) {
                if (MainSn.GetMoveTo() != "Down") {
                    MainSn.SetMoveTo("Up");
                    WastheClick = true;
                }
            };

            if ((event.key.code == Keyboard::Key::S) && WastheClick == false) {
                if (MainSn.GetMoveTo() != "Up") {
                    MainSn.SetMoveTo("Down");
                    WastheClick = true;
                }
            };

            if ((event.key.code == Keyboard::Key::A) && WastheClick == false) {
                if (MainSn.GetMoveTo() != "Right") {
                    MainSn.SetMoveTo("Left");
                    WastheClick = true;
                }
            };

            if ((event.key.code == Keyboard::Key::D) && WastheClick == false) {
                if (MainSn.GetMoveTo() != "Left") {
                    MainSn.SetMoveTo("Right");
                    WastheClick = true;
                }
            };
        }

        if (timeCl > GameSpeed) {
            WastheClick = false;
            if ((MainSn.GetBlockBodyX(0) == app.GetAppleCoordinateX()) && (MainSn.GetBlockBodyY(0) == app.GetAppleCoordinateY())) {
                score = score + 10;
                txt = "Score: " + to_string(score);
                text.setString(txt);

                MainSn.SnakeLvlUp();
                app.CreateApple(MainSn.GetSnakeBodyX(), MainSn.GetSnakeBodyY());
                apple.setPosition(I * app.GetAppleCoordinateX(), I * app.GetAppleCoordinateY());
            }
            MainSn.SnakeMoving();

            window.clear(Color::Black);
            window.draw(rectangle);
            window.draw(apple);
            for (int i = 0; i < MainSn.GetSizeBody(); i++) {
                if ((MainSn.GetBlockBodyX(0) == MainSn.GetBlockBodyX(i)) && (MainSn.GetBlockBodyY(0) == MainSn.GetBlockBodyY(i)) && i != 0) {
                    GameIsOver = true;
                    cout << "Game is Over!";
                    break;
                }
                if (GameIsOver == true) {
                    break;
                }
                if ((MainSn.GetBlockBodyX(0) < 0) || (MainSn.GetBlockBodyX(0) > 20) || (MainSn.GetBlockBodyY(0) < 0) || (MainSn.GetBlockBodyY(0) > 19)) {
                    GameIsOver = true;
                    cout << "Game is Over!" << endl;
                    cout << "Score: " << score;
                    break;
                }
                rectBody.setPosition(I * (MainSn.GetBlockBodyX(i)), I * (MainSn.GetBlockBodyY(i)));
                window.draw(rectBody);
                window.draw(text);
            }
            window.display();
            clock.restart();
        }

    }

    return 0;
}
