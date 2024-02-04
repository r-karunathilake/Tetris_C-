#include <iostream>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris(){
  
  m_window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(360, 720), 
    "Tetris C++", 
    sf::Style::Titlebar | sf::Style::Close);

  m_window->setPosition(sf::Vector2i(100, 100));
  
  if(!m_tiles.loadFromFile("./assets/squares.png")){
    std::cerr << "Error: unable to load tile assets:w" << std::endl; 
  }

  m_sprite = std::make_shared<sf::Sprite>();
  m_sprite->setTexture(m_tiles);
  m_sprite->setScale(sf::Vector2f(0.1, 0.1));
}

/***********************/
/*  PROTECTED METHODS  */
/***********************/
void Tetris::events(){
  auto event {std::make_shared<sf::Event>()};
  
  // Check pending events 
  while(m_window->pollEvent(*event)){
    switch(event->type){   
      // Close window
      case sf::Event::Closed:{
        m_window->close(); 
      }break;

      case sf::Event::KeyPressed:{
        if(event->key.code == sf::Keyboard::Up){
          rotate = true;
        }
        else if(event->key.code == sf::Keyboard::Left){
          --dirx;
        }
        else if(event->key.code == sf::Keyboard::Right){
          ++dirx;
        }
      }break;
    }
  }
}

void Tetris::draw(){
  // Clear the screen with black color
  m_window->clear(sf::Color::Black);

  for(std::size_t idx {0}; idx < s_numSquares; ++idx){
    m_sprite->setPosition(m_z[idx].x * 36, m_z[idx].y * 36);
    m_window->draw(*m_sprite); 
  }

  // End drawing current frame and display
  m_window->display();
}

void Tetris::moveDown(){
  std::uint32_t number {3};
  
  if(m_z[0].x == 0){
    for(std::size_t idx {0}; idx < s_numSquares; ++idx){
      m_z[idx].x = m_shapes[number][idx] % 2;
      m_z[idx].y = m_shapes[number][idx] / 2;
    }
  }
}

void Tetris::changePosition(){
  for(std::size_t idx {0}; idx < s_numSquares; ++idx){
    m_z[idx].x += dirx;
  }
}

void Tetris::setRotate(){
  if(rotate){
    Coordinate cord = m_z[1];
    for(std::size_t idx{0}; idx < s_numSquares; ++idx){
      int x = m_z[idx].y - cord.y;
      int y = m_z[idx].x - cord.x;

      m_z[idx].x = cord.x - x;
      m_z[idx].y = cord.y + y;
    }
  }
}

void Tetris::resetValues(){
  dirx = 0;
  rotate = false;
}

/***********************/
/*    PUBLIC METHODS   */
/***********************/
void Tetris::run(){
  while(m_window->isOpen()){
    events();
    
    changePosition();
    setRotate();
    moveDown();
    resetValues(); 
    
    draw(); 
  }
}
