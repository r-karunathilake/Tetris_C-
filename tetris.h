#pragma once                 // Header guard 

#include <SFML/Graphics.hpp> // Open and draw on an OpenGL window 
#include <memory>            // For std::shared_ptr access 

class Tetris{
  private:
    std::shared_ptr<sf::RenderWindow> window {}; 
    std::shared_ptr<sf::Sprite> sprite {}; 
    sf::Texture tiles {}; 

  protected:
    void events();
    void draw();

  public:
    Tetris();
    void run(); 
};
