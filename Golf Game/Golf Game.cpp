#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <Windows.h>
#include<fstream>

using namespace std; //for namespaces
using namespace sf;

//for submenu
int submenu() {

    RenderWindow submenu(VideoMode(1920, 1080), "Golf Game", Style::Fullscreen);  //submenu window render
    float x = submenu.getSize().x / 2 - 204;

    Texture easytext;
    easytext.loadFromFile("easy.png");

    Texture mediumtext;                         
    mediumtext.loadFromFile("medium.png");          //loading different textures from the folder

    Texture exittext;
    exittext.loadFromFile("exit.png");

    RectangleShape exit(Vector2f(270, 120));
    exit.setPosition(x, 780);
    exit.setTexture(&exittext);

    RectangleShape medium(Vector2f(270, 120));
    medium.setPosition(x, 620);                     // Different shapes which will be used as buttons
    medium.setTexture(&mediumtext);

    RectangleShape easy(Vector2f(270, 120));
    easy.setPosition(x, 460);
    easy.setTexture(&easytext);

    Texture sky;
    sky.loadFromFile("./sky1.jpg");                 //loading background texture

    RectangleShape skys(Vector2f(submenu.getSize().x, submenu.getSize().y));
    skys.setTexture(&sky);

    Texture mlogos;
    mlogos.loadFromFile("mlogo.png");               //Game logo
    Sprite mlogo;
    mlogo.setTexture(mlogos);
    mlogo.setPosition(550, 70);

    int option = -1;

    while (submenu.isOpen()) {
        Event event;
        while (submenu.pollEvent(event)) {
            if (event.type == Event::Closed) {
                submenu.close();
                return option = 2;
            }   
            
            //Selectin buttons using mouse
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mousePos = submenu.mapPixelToCoords(Mouse::getPosition(submenu));
                if (easy.getGlobalBounds().contains(mousePos)) {

                    return option = 0; // Easy Level
                    submenu.close();

                }
                if (medium.getGlobalBounds().contains(mousePos)) {

                    return 1; // Medium Level
                    submenu.close();


                }
                if (exit.getGlobalBounds().contains(mousePos)) {

                    return option = 2; // Exit
                    submenu.close();
                }
            }

            //Highllight the choosen button when mouse is above it
            else if (event.type == Event::MouseMoved) {         
                Vector2f mousePos = submenu.mapPixelToCoords(Mouse::getPosition(submenu));
                easy.setFillColor(easy.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
                medium.setFillColor(medium.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
                exit.setFillColor(exit.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
            }
        }

        submenu.clear();
        submenu.draw(skys);
        submenu.draw(easy);
        submenu.draw(medium);               //To draw all images
        submenu.draw(exit);
        submenu.draw(mlogo);
        submenu.display();

    }

}

int menu(int option) {

    //Main menu window render
    RenderWindow main(VideoMode(1920, 1080), "Golf Game", Style::Fullscreen);

    //font loading
    Font instructionfont;
    instructionfont.loadFromFile("./instructionfont.ttf");

    //Instruction text
    Text instrctions("Instructions: \n 1. Each player has been given 5 chances.\n 2. Drag the ball with the help of mouse. \n 3. More the drag, More force \n 4. Press Y to reset the game. \n 5. Press Escape to quit the game. \n 6. Press R to reset the position of the ball.", instructionfont, 55);
    instrctions.setPosition(Vector2f(1200, 500));
    instrctions.setFillColor(Color::Black);

    Font font;
    font.loadFromFile("arial.ttf");         
                                            // Textures of buttons
    Texture playtext;
    playtext.loadFromFile("play.png");  

    Texture exittext;
    exittext.loadFromFile("exit.png");

    Texture selecttext;
    selecttext.loadFromFile("select.png");

    Texture sky;
    sky.loadFromFile("./sky1.jpg");      // Background texture

    Texture mlogos;                     // Main logo of the game
    mlogos.loadFromFile("mlogo.png");
    Sprite mlogo;
    mlogo.setTexture(mlogos);
    mlogo.setPosition(550, 70);

    
    float x = main.getSize().x / 2 - 204;
                                                // Shapes used as button
    RectangleShape play(Vector2f(270, 120));
    play.setPosition(x, 460);
    play.setTexture(&playtext);

    RectangleShape level(Vector2f(270, 120));
    level.setPosition(x, 620);
    level.setTexture(&selecttext);

    RectangleShape exit(Vector2f(270, 120));
    exit.setPosition(x, 780);
    exit.setTexture(&exittext);

    RectangleShape skys(Vector2f(main.getSize().x, main.getSize().y));
    skys.setTexture(&sky);

    option = -1;
                                            
    Music maintheme;                            // Main sound of th menus
    maintheme.openFromFile("msound.mp3");
    maintheme.setVolume(5);
    maintheme.play();
    maintheme.setLoop(true);
    maintheme.setVolume(20);

    while (main.isOpen()) {
        Event event;
        while (main.pollEvent(event)) {
            if (event.type == Event::Closed) {
                main.close();
                return option = 2;
            }
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mousePos = main.mapPixelToCoords(Mouse::getPosition(main));
                if (play.getGlobalBounds().contains(mousePos)) {

                    return option = 0; // Play
                    main.close();

                }
                if (level.getGlobalBounds().contains(mousePos)) {
                    main.close();
                    return submenu(); // Sub - menu for slecting levels


                }
                if (exit.getGlobalBounds().contains(mousePos)) {
                    return option = 2; // Exit
                    main.close();
                }
            }
            else if (event.type == Event::MouseMoved) {
                Vector2f mousePos = main.mapPixelToCoords(Mouse::getPosition(main));

                //Highlighting the button
                play.setFillColor(play.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
                level.setFillColor(level.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
                exit.setFillColor(exit.getGlobalBounds().contains(mousePos) ? Color::Green : Color::White);
            }
        }

        main.clear();
        main.draw(skys);
        main.draw(play);
        main.draw(level);
        main.draw(exit);
        main.draw(mlogo);
        main.draw(instrctions);
        main.display();

    }
}


int main() {
again:
    int option = -1;
    option = menu(option);
    
    switch (option) {
    case 0:{ 
        
        //Easy level for the game

        RenderWindow window(VideoMode(1920, 1080), "Golf Game", Style::Fullscreen);
        window.setFramerateLimit(60);

        // Loading the textures
        Texture golf;
        golf.loadFromFile("./golf.png");
        Sprite sprite(golf);

        Texture hole;
        hole.loadFromFile("./hole.png");
        Sprite sprite1(hole);

        Texture sky;
        sky.loadFromFile("./sky1.jpg");
        Sprite sprite2(sky);

        Texture g;
        g.loadFromFile("./ground.png");
        Sprite sprite3(g);

        Texture w;
        w.loadFromFile("./rwall.png");
                                                            //Music files
        Music swing;
        swing.openFromFile("swing.mp3");

        Music hsound;
        hsound.openFromFile("hole.mp3");


        RectangleShape skys(Vector2f(window.getSize().x, window.getSize().y));
        skys.setTexture(&sky);

        float by = window.getSize().y / 2.7;                 //Ball initial positions
        float bx = window.getSize().x / 12.8;
                                                
        Texture tees;                                       //For holding the ball
        tees.loadFromFile("./tee.png");
        Sprite tee(tees);
        tee.setPosition(bx, by + 20);
        tee.setScale(0.2f, 0.2f);

        CircleShape ball(10.0);                             //BAll
        ball.setFillColor(Color::White);
        ball.setPosition(bx, by);
        ball.setTexture(&golf);
                                                           // Taget positions
        double tx = window.getSize().x / 1.2715231788079470198675496688742;
        double ty = window.getSize().y / 1.2705882352941176470588235294118;

        RectangleShape target(Vector2f(50, 20));
        target.setFillColor(Color::White);

        target.setPosition(tx, ty);
        target.setTexture(&hole);
                                                           //Flag positions             
        Texture flag;
        flag.loadFromFile("./flag.png");
        Sprite flags(flag);
        double fx = window.getSize().x / 1.2732095490716180371352785145889;
        double fy = window.getSize().y / 1.6363636363636363636363636363636;

        flags.setPosition(fx, fy);
        flags.setScale(0.3f, 0.3f);

        double sgx = window.getSize().x;
        double sgy = window.getSize().y / 4.32;

        double gy = window.getSize().y / 1.2857142857142857142857142857143; //Ground positions

        RectangleShape ground(Vector2f(sgx, sgy));
        ground.setPosition(0, gy);
        ground.setTexture(&g);

        RectangleShape wall(Vector2f(15, 200));                             //Wall position
        wall.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 200);
        wall.setTexture(&w);

        Font font;
        font.loadFromFile("./Raleway-Bold.ttf");                            //font loading

        Text strktxt;
        strktxt.setFont(font);
        strktxt.setCharacterSize(35);                                       //Strokes text
        strktxt.setFillColor(Color(222, 126, 93));
        strktxt.setPosition(50, 50);

        Text scores;                                                        //Score text
        scores.setFont(font);
        scores.setCharacterSize(35);
        scores.setFillColor(Color(222, 126, 93));
        scores.setPosition(50, 90);


        bool drag = false;                                                  //drag state
        bool move = false;                                                  //move state
        bool exit = false;                                                  //exit state


        Vector2f initialp;                                                  //Vector positions
        Vector2f finalp;
        Vector2f velocity;

        float gravity = 800.0f;                                             //Gravity Effect
        float xfactor = 20.0f;                                              // horizontal distance multiplier
        float yfactor = 10.0f;                                              // vertical distance multiplier

        int strokes = 0;
        int score = 0;
        
        RectangleShape dialogBox(Vector2f(300, 150));                       // dialogbox
        dialogBox.setPosition(Vector2f(window.getSize().x / 2 - 150, window.getSize().y / 2 - 75));
        dialogBox.setFillColor(Color::Blue);
                                                                            // Text box
        Text text("You have used 5 Strokes.\n Press Y to start again.", font, 20);
        text.setPosition(Vector2f(window.getSize().x / 2 - 130, window.getSize().y / 2 - 35));
        text.setFillColor(Color::Red);

        Clock timer;                                                         // Timer for resetting the positions
        bool reset = false;

        score = 0;
        strokes = 0;
        exit = false;
        ball.setPosition(bx, by);
        reset = false;

        bool x = true;                                                        // State for resetting the position of ball 

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    window.close();
                    goto again;
                }
                else if (event.type == Event::Closed)
                    window.close();
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {  //R button for resetting the ball
                    exit = false;
                    reset = false;
                    reset = false;
                    ball.setPosition(bx, by);
                }
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::T)
                    exit = true;
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Y) {
                    score = 0;                                                                  // Y for resetting the game
                    strokes = 0;
                    exit = false;
                    ball.setPosition(bx, by);
                    reset = false;
                }

                //Mouse button clicked
                else if (exit == false && move == false && Mouse::getPosition(window).y >= (by - 30) && Mouse::getPosition(window).y <= (by + 30) && Mouse::getPosition(window).x <= (bx + 30) && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    drag = true;
                    initialp = Vector2f(Mouse::getPosition(window));
                    velocity = Vector2f(0, 0);
                }
                //Mouse button released
                else if (exit == false && move == false && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    drag = false;
                    finalp = Vector2f(Mouse::getPosition(window));
                    velocity = Vector2f((initialp.x - finalp.x) * xfactor, (initialp.y - finalp.y) * yfactor);
                    strokes++;
                    x = true;
                    exit = true;
                    reset = false;
                    swing.play();
                }
                //timer for resetting the positions of the ball
                if (move == false && exit == false && x == false) {
                    reset = true;
                    timer.restart();

                }
            }
            // Draggging effect
            if (move == false && drag == true && exit == false) {
                Vector2f currentPosition = Vector2f(Mouse::getPosition(window));
                ball.setPosition(currentPosition);
            }
            else {

                float gfactor = 0.009f;         //gfactor for giving the projectile effect
                Vector2f vf;                    //final velocity stored

                if (ball.getPosition().x != bx && ball.getPosition().y != by) {
                    if (velocity.x != 0 && x == true)
                        velocity.y += gravity * gfactor;
                    vf = Vector2f(velocity.x * gfactor, velocity.y * gfactor);
                    ball.move(vf);              //Ball movement
                    move = true;
                }
                if (velocity.x == 0 && x == false) {
                    move = false;
                }
                                                //For scoring
                if (ball.getGlobalBounds().intersects(target.getGlobalBounds())) {
                    score++;
                    ball.setPosition(bx, by);
                    velocity = Vector2f(0, 0);
                    move = false;
                    exit = false;
                    hsound.play();
                }                              //When ball touches the wall
                else if (ball.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                    velocity.x = -velocity.x;
                    velocity.y = velocity.y / 2;
                }                               //When ball touches the back side of screen it resets
                else if (ball.getPosition().x <= 0) {
                    ball.setPosition(bx, by);
                    move = false;
                    exit = false;
                }                                //For right ending of the screen
                else if (ball.getPosition().x + 10 >= window.getSize().x) {
                    velocity.x = -velocity.x;
                    velocity.y = velocity.y / 2;
                    exit = false;
                }                               //When ball touches the ground
                else if (ball.getPosition().y + 20 >= gy + 20) {
                    velocity.y = 0;
                    velocity.x = velocity.x / 1.2;
                    move = false;
                    x = false; //BUG FIXED
                    exit = false;
                }


                // Timer checks if the ball has stopped moving
                if (x == false && velocity.y == 0 && reset == true && move == false) {
                    Time elapsedTime = timer.getElapsedTime();
                    if (elapsedTime.asSeconds() >= 3) {
                        ball.setPosition(bx, by);
                        move = false;
                        reset = false;
                        exit = false;
                    }
                }

            }

            window.clear();
            window.draw(skys);
            window.draw(target);
            window.draw(strktxt);
            window.draw(tee);
            window.draw(flags);
            window.draw(scores);
            window.draw(ground);
            window.draw(ball);
            window.draw(wall);

            //Ending box
            if (strokes == 5 && move == false) {
                window.draw(dialogBox);
                window.draw(text);
                exit = true;
            }

            window.display();
            strktxt.setString("Strokes: " + to_string(strokes));
            scores.setString("Score: " + to_string(score));
        }
    }
          break;
    case 1:
    {

        RenderWindow window(VideoMode(1920, 1080), "Golf Game", Style::Fullscreen);
        window.setFramerateLimit(60);

        Texture golf;
        golf.loadFromFile("./golf.png");
        Sprite sprite(golf);

        Texture hole;
        hole.loadFromFile("./hole.png");
        Sprite sprite1(hole);

        Texture sky;
        sky.loadFromFile("./space.png");
        Sprite sprite2(sky);

        Texture g;
        g.loadFromFile("./mground.jpg");
        Sprite sprite3(g);

        Texture w;
        w.loadFromFile("./wall.jpg");

        Music swing;
        swing.openFromFile("swing.mp3");

        Music hsound;
        hsound.openFromFile("hole.mp3");



        RectangleShape skys(Vector2f(window.getSize().x, window.getSize().y));
        skys.setTexture(&sky);

        // 1920 x1080

        float by = window.getSize().y / 2.7;
        float bx = window.getSize().x / 12.8;

        Texture tees;
        tees.loadFromFile("./tee.png");
        Sprite tee(tees);
        tee.setPosition(bx, by + 20);
        tee.setScale(0.2f, 0.2f);



        CircleShape ball(10.0);
        ball.setFillColor(Color::White);
        ball.setPosition(bx, by);
        ball.setTexture(&golf);

        double tx = window.getSize().x / 1.2715231788079470198675496688742;
        double ty = window.getSize().y / 1.2705882352941176470588235294118;

        RectangleShape target(Vector2f(50, 20));
        target.setFillColor(Color::White);

        //target.setPosition(1510, 850);

        target.setPosition(tx, ty);
        target.setTexture(&hole);

        Texture flag;
        flag.loadFromFile("./flag.png");
        Sprite flags(flag);
        double fx = window.getSize().x / 1.2732095490716180371352785145889;
        double fy = window.getSize().y / 1.6363636363636363636363636363636;

        flags.setPosition(fx, fy);
        flags.setScale(0.3f, 0.3f);

        double sgx = window.getSize().x;
        double sgy = window.getSize().y / 4.32;
        double gy = window.getSize().y / 1.2857142857142857142857142857143;

        RectangleShape ground(Vector2f(sgx, sgy));
        ground.setPosition(0, gy);
        ground.setTexture(&g);

        double wy = window.getSize().y / 3.1764705882352941176470588235294;

        RectangleShape wall(Vector2f(40, 200));
        wall.setPosition(window.getSize().x / 2, wy);
        wall.setTexture(&w);

        RectangleShape wall2(Vector2f(200, 40));
        wall2.setPosition(window.getSize().x / 2 + 200, window.getSize().y / 2 + 50);
        wall2.setTexture(&w);

        Font font;
        font.loadFromFile("./Raleway-Bold.ttf");

        Text strktxt;
        strktxt.setFont(font);
        strktxt.setCharacterSize(35);                                       //Strokes text
        strktxt.setFillColor(Color(222, 126, 93));
        strktxt.setPosition(50, 50);

        Text scores;                                                        //Score text
        scores.setFont(font);
        scores.setCharacterSize(35);
        scores.setFillColor(Color(222, 126, 93));
        scores.setPosition(50, 90);


        bool drag = false;

        Vector2f initialp;
        Vector2f finalp;
        Vector2f velocity;
        Vector2f wallm = Vector2f(1.0f, 0);

        float gravity = 800.0f;
        float xfactor = 20.0f; // horizontal distance multiplier
        float yfactor = 10.0f; // vertical distance multiplier
        int strokes = 0;
        int score = 0;
        bool move = false;
        bool exit = false;


        RectangleShape dialogBox(Vector2f(300, 150));
        dialogBox.setPosition(Vector2f(window.getSize().x / 2 - 150, window.getSize().y / 2 - 75));
        dialogBox.setFillColor(Color::Blue);

        Text text("You have used 5 Strokes.\n Press Y to start again.", font, 20);
        text.setPosition(Vector2f(window.getSize().x / 2 - 130, window.getSize().y / 2 - 35));
        text.setFillColor(Color::Red);

        Clock timer;
        bool reset = false;
        score = 0;
        strokes = 0;
        exit = false;
        ball.setPosition(bx, by);
        reset = false;
        bool x = true;

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {

                    window.close();
                    goto again;
                }
                else if (event.type == Event::Closed)
                    window.close();
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                    exit = false;
                    reset = false;
                    ball.setPosition(bx, by);
                }
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::T)
                    exit = true;
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Y) {
                    score = 0;
                    strokes = 0;
                    exit = false;
                    ball.setPosition(bx, by);
                    reset = false;
                }
                else if (exit == false && move == false && Mouse::getPosition(window).y >= (by - 30) && Mouse::getPosition(window).y <= (by + 30) && Mouse::getPosition(window).x <= (bx + 30) && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    drag = true;
                    initialp = Vector2f(Mouse::getPosition(window));
                    velocity = Vector2f(0, 0);
                }
                else if (exit == false && move == false && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    drag = false;
                    finalp = Vector2f(Mouse::getPosition(window));
                    velocity = Vector2f((initialp.x - finalp.x) * xfactor, (initialp.y - finalp.y) * yfactor);
                    strokes++;
                    x = true;
                    exit = true;
                    reset = false;
                    swing.play();
                }
                if (move == false && exit == false && x == false) {
                    reset = true;
                    timer.restart();

                }
            }

            if (move == false && drag == true && exit == false) {
                Vector2f currentPosition = Vector2f(Mouse::getPosition(window));
                ball.setPosition(currentPosition);
            }
            else {

                float gfactor = 0.009f;
                Vector2f vf;

                if (ball.getPosition().x != bx && ball.getPosition().y != by) {
                    if (velocity.x != 0 && x == true)
                        velocity.y += gravity * gfactor;
                    vf = Vector2f(velocity.x * gfactor, velocity.y * gfactor);
                    ball.move(vf);
                    move = true;
                }
                if (velocity.x == 0 && x == false) {
                    move = false;
                }

                if (ball.getGlobalBounds().intersects(target.getGlobalBounds())) {
                    score++;
                    ball.setPosition(bx, by);
                    velocity = Vector2f(0, 0);
                    move = false;
                    exit = false;
                    hsound.play();
                }
                else if (ball.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                    velocity.x = -velocity.x;
                    velocity.y = velocity.y / 2;
                }
                else if (ball.getGlobalBounds().intersects(wall2.getGlobalBounds())) {
                    velocity.x = velocity.x;
                    velocity.y = -velocity.y / 1.21;
                }

                else if (ball.getPosition().x <= 0) {
                    ball.setPosition(bx, by);
                    move = false;
                    exit = false;
                }
                else if (ball.getPosition().x + 10 >= window.getSize().x) {
                    velocity.x = -velocity.x;
                    velocity.y = velocity.y / 2;
                    exit = false;
                }
                else if (ball.getPosition().y + 20 >= gy + 20) {
                    velocity.y = 0;
                    velocity.x = velocity.x / 1.2;
                    move = false;
                    x = false; //BUG
                    exit = false;
                }
                if (wall2.getPosition().x + 200 >= window.getSize().x+1) {
                    wallm.x = -wallm.x;

                }
                else if (wall2.getPosition().x <= window.getSize().x / 2+5) {
                    wallm.x = -wallm.x;
                }


                // Timer checks if the ball has stopped moving
                if (x == false && velocity.y == 0 && reset == true && move == false) {
                    Time elapsedTime = timer.getElapsedTime();
                    if (elapsedTime.asSeconds() >= 3) {
                        ball.setPosition(bx, by);
                        move = false;
                        reset = false;
                        exit = false;
                    }
                }

            }


            window.clear();
            window.draw(skys);
            window.draw(strktxt);
            window.draw(scores);
            window.draw(ground);
            window.draw(ball);
            window.draw(wall);
            window.draw(wall2);
            window.draw(tee);
            window.draw(target);
            window.draw(flags);

            wall2.move(wallm);


            if (strokes == 5 && move == false) {
                window.draw(dialogBox);
                window.draw(text);
                exit = true;
            }


            window.display();

            strktxt.setString("Strokes: " + to_string(strokes));
            scores.setString("Score: " + to_string(score));
        }




    }
    break;
    case 2: {

        break;
    }

          return 0;
    }
}