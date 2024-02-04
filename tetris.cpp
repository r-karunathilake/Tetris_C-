#include <iostream>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris(){
  window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(360, 720), 
    "Tetris C++", 
    sf::Style::Titlebar | sf::Style::Close);

  window->setPosition(sf::Vector2i(100, 100));
  
  if(!tiles.loadFromFile("./assets/squares.png")){
    std::cerr << "Error: unable to load tile assets:w" << std::endl; 
  }

  sprite = std::make_shared<sf::Sprite>();
  sprite->setTexture(tiles);
  sprite->setScale(sf::Vector2f(0.1, 0.1));
}

/***********************/
/*  PROTECTED METHODS  */
/***********************/
void Tetris::events(){
  auto event {std::make_shared<sf::Event>()};
  
  // Check pending events 
  while(window->pollEvent(*event)){
    switch(event->type){   
      // Close window
      case sf::Event::Closed:{
        window->close(); 
      }break;
    }
  }
}

void Tetris::draw(){
  // Clear the screen with black color
  window->clear(sf::Color::Black);
  window->draw(*sprite); 
  // End drawing current frame and display
  window->display();
}

/***********************/
/*    PUBLIC METHODS   */
/***********************/
void Tetris::run(){
  while(window->isOpen()){
    events();
    draw(); 
  }
}



