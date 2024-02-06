#include <iostream>
#include <random>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris() 
  : m_window {std::make_shared<sf::RenderWindow>(sf::VideoMode(300, 600), "Tetris C++", 
                                                 sf::Style::Titlebar | sf::Style::Close)},
    gameBlocks {getGameBlocks()},
    currentBlock {getRandomBlock()},
    nextBlock {getRandomBlock()}
{
  m_window->setPosition(sf::Vector2i(100, 100));
  m_window->setFramerateLimit(60); // 60 FPS  
}
/***********************/
/*   PRIVATE METHODS   */
/***********************/
std::shared_ptr<Block> Tetris::getRandomBlock(){
  // Populate game blocks
  if(!gameBlocks.empty()){
    gameBlocks = getGameBlocks(); 
  }

  /* Each of the 7 blocks appear in game before a new cycle */ 
  int randIndex = rand() % static_cast<int>(gameBlocks.size());
  std::shared_ptr<Block> pBlock {gameBlocks[randIndex]};
  gameBlocks.erase(gameBlocks.begin() + randIndex);

  return pBlock;
}

std::vector<std::shared_ptr<Block>> Tetris::getGameBlocks() const{
  return {std::make_shared<IBlock>(), 
          std::make_shared<JBlock>(), 
          std::make_shared<LBlock>(), 
          std::make_shared<OBlock>(), 
          std::make_shared<SBlock>(), 
          std::make_shared<TBlock>(), 
          std::make_shared<ZBlock>()};
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
          //rotate = true;
        }
        else if(event->key.code == sf::Keyboard::Left){
          //--dirx;
        }
        else if(event->key.code == sf::Keyboard::Right){
          //++dirx;
        }
      }break;
    }
  }
}

void Tetris::draw(){
  // Clear the screen with black color
  m_window->clear(sf::Color::Black);
 
  drawGrid();
  currentBlock->draw(m_window); 

  // End drawing current frame and display
  m_window->display();
}

void Tetris::drawGrid(){
  for(size_t row {0}; row < m_grid.size(); ++row){
    for(size_t column {0}; column < m_grid[row].size(); ++column){
      auto cellColor = m_grid[row][column];
      auto cell {sf::RectangleShape(sf::Vector2f(s_cellSize - 1, s_cellSize - 1))};
      cell.setPosition(column * s_cellSize + 1, row * s_cellSize + 1);
      cell.setFillColor(getSFMLColor(cellColor));
      m_window->draw(cell);
    }
  }
}

void Tetris::printGrid(){
  for(const auto& row:m_grid){
    for(const auto& element:row){
      std::cout << element << ' '; 
    }
    std::cout << '\n';
  }
}

/***********************/
/*    PUBLIC METHODS   */
/***********************/
void Tetris::run(){ 
  while(m_window->isOpen()){
    events(); 
    draw(); 
  }
  //printGrid(); 
}
