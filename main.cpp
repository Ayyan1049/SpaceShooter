#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(1080, 580), "Space Shooter");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("assets/Battle-Tough.otf");

    Texture startBackground;
    startBackground.loadFromFile("assets/startBackground.jpg");

    Sprite start(startBackground);

    Text title("Space Shooter", font, 50);
    title.setPosition(330, 195);

    Text startGame("Start Game", font, 30);
    startGame.setPosition(450, 300);

    Text exitGame("Exit", font, 30);
    exitGame.setPosition(510, 350);

    bool inMenu = true;

    Texture bulletTexture;
    bulletTexture.loadFromFile("assets/bullet.png");

    Sprite bulletSprite(bulletTexture);
    bulletSprite.setScale(0.5f, 0.5f);

    Texture rocketTexture;
    rocketTexture.loadFromFile("assets/rocket.png");

    Sprite rocket(rocketTexture);
    rocket.setPosition(320, 510);
    rocket.setScale(0.1f, 0.1f);

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/background.jpg");

    Sprite background(backgroundTexture);

    float playerSpeed = 650.0f;

    bool isShooting = false;
    float bulletSpeed = 1500.0f;

    const int numEnemies = 7;
    vector<Sprite> enemies(numEnemies);
    vector<Clock> respawnClocks(numEnemies);

    Texture enemyTexture;
    enemyTexture.loadFromFile("assets/enemy.png");

    Texture dangerEnemyTexture;
    dangerEnemyTexture.loadFromFile("assets/enemyRed.png");

    Sprite dangerEnemy(dangerEnemyTexture);
    dangerEnemy.setScale(0.1f, 0.15f);

    //these create enemies
    for (int i = 0; i < numEnemies; i++) {
        enemies[i].setTexture(enemyTexture);
        float randomX = static_cast<float>(rand() % (window.getSize().x - static_cast<int>(enemies[i].getGlobalBounds().width)));
        float randomY = static_cast<float>(-(rand() % 300 + 50));
        enemies[i].setPosition(randomX, randomY);
        enemies[i].setScale(0.1f, 0.15f);
    }

    float enemySpeed = 100.0f;
    Time respawnTime = seconds(5.0f);
    vector<bool> disappearEnemies(numEnemies, false);

    float dangerEnemySpeed = 150.0f;
    bool dangerEnemyActive = true;

    int score = 0;
    Text scoreText("Score: 0", font, 20);
    scoreText.setPosition(10, 10);

    int lives = 3; 
    Text livesText("Lives: 3", font, 20);
    livesText.setPosition(10, 70);

    int level = 1;
    Text levelText("LEVEL: 1", font, 20);
    levelText.setPosition(10, 40);

    int speedIncreaseThreshold = 50;

    //for the menu
    while (window.isOpen() && inMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));

        if (startGame.getGlobalBounds().contains(mousePosition)) {
            startGame.setFillColor(Color::Red);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                inMenu = false;
            }
        }
        else {
            startGame.setFillColor(Color::White);
        }

        if (exitGame.getGlobalBounds().contains(mousePosition)) {
            exitGame.setFillColor(Color::Red);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                window.close();
            }
        }
        else {
            exitGame.setFillColor(Color::White);
        }

        window.clear();
        window.draw(start);
        window.draw(title);
        window.draw(startGame);
        window.draw(exitGame);
        window.display();
    }

    //game loop
    Clock gwak;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space && !isShooting) {
                    isShooting = true;
                    bulletSprite.setPosition
                    (rocket.getPosition().x + rocket.getGlobalBounds().width / 2 - bulletSprite.getGlobalBounds().width / 2,
                        rocket.getPosition().y);
                }
            }
        }

        Time elapsedTime = gwak.restart();

        //Rocket Movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            rocket.move(-playerSpeed * elapsedTime.asSeconds(), 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            rocket.move(playerSpeed * elapsedTime.asSeconds(), 0);
        }

        //Bullet Movement and Collision
        if (isShooting) {
            bulletSprite.move(0, -bulletSpeed * elapsedTime.asSeconds());
            if (bulletSprite.getPosition().y < 0) {
                isShooting = false;
            }

            for (int i = 0; i < numEnemies; ++i) {
                if (bulletSprite.getGlobalBounds().intersects(enemies[i].getGlobalBounds()) && !disappearEnemies[i]) {
                    disappearEnemies[i] = true;
                    respawnClocks[i].restart();
                    isShooting = false;
                    score += 5;
                    scoreText.setString("Score: " + to_string(score));
                }
            }
        }

        //Enemy Movement and Respawn
        for (int i = 0; i < numEnemies; ++i) {
            if (!disappearEnemies[i]) {
                enemies[i].move(0, enemySpeed * elapsedTime.asSeconds());
                if (enemies[i].getPosition().y > window.getSize().y) {
                    lives--; 
                    livesText.setString("Lives: " + to_string(lives));
                    if (lives <= 0) {
                        
                        Text gameOverText("GAME OVER", font, 50);
                        gameOverText.setPosition(380, 240);
                        window.clear();
                        window.draw(gameOverText);
                        window.display();
                        sleep(seconds(3));
                        window.close(); 
                    }

                    float randomX = static_cast<float>(rand() % (window.getSize().x - static_cast<int>(enemies[i].getGlobalBounds().width)));
                    enemies[i].setPosition(randomX, -(rand() % 300 + 50));
                }

            }
            else if (respawnClocks[i].getElapsedTime() > respawnTime) {
                float randomX = static_cast<float>(rand() % (window.getSize().x - static_cast<int>(enemies[i].getGlobalBounds().width)));
                float randomY = static_cast<float>(-(rand() % 300 + 50));
                enemies[i].setPosition(randomX, randomY);
                disappearEnemies[i] = false;
            }
        }

        //Dangerous Enemy Movement
        if (dangerEnemyActive) {
            dangerEnemy.move(0, dangerEnemySpeed * elapsedTime.asSeconds());
            if (dangerEnemy.getPosition().y > window.getSize().y) {
                dangerEnemy.setPosition(rand() % (window.getSize().x - static_cast<int>(dangerEnemy.getGlobalBounds().width)), -50);
            }
            //Bullet hits dangerous enemy
            if (bulletSprite.getGlobalBounds().intersects(dangerEnemy.getGlobalBounds())) {
                score += 15;
                scoreText.setString("Score: " + to_string(score));
                dangerEnemy.setPosition(rand() % (window.getSize().x - static_cast<int>(dangerEnemy.getGlobalBounds().width)), -50);
                isShooting = false;
            }
        }

        //Level Up and Speed Increase
        if (score >= speedIncreaseThreshold) {
            level++;
            levelText.setString("LEVEL: " + to_string(level));
            speedIncreaseThreshold += 50;
            enemySpeed += 25.0f;
            dangerEnemySpeed += 30.0f;
        }

        //Win Condition
        if (level >= 5) {
            Text winText("YOU WIN!", font, 50);
            winText.setPosition(440, 240);
            window.clear();
            window.draw(winText);
            window.display();
            sleep(seconds(3));
            window.close();
        }

        //Draw Everything
        window.clear();
        window.draw(background);
        window.draw(rocket);

        if (isShooting) {
            window.draw(bulletSprite);
        }

        for (int i = 0; i < numEnemies; ++i) {
            if (!disappearEnemies[i]) {
                window.draw(enemies[i]);
            }
        }

        if (dangerEnemyActive) {
            window.draw(dangerEnemy);
        }

        window.draw(scoreText);
        window.draw(levelText);
        window.draw(livesText); 
        window.display();
    }

    return 0;
}
