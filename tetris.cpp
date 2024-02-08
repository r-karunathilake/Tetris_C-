#include <random>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris() 
  : m_window     {configGameWindow()},
    gameBlocks   {getGameBlocks()},
    currentBlock {getRandomBlock()},
    nextBlock    {getRandomBlock()}
{
  m_window->setPosition(sf::Vector2i(100, 100));
  m_window->setFramerateLimit(60); // 60 FPS  
}
/***********************/
/*   PRIVATE METHODS   */
/***********************/
std::shared_ptr<sf::RenderWindow> Tetris::configGameWindow() const{
    return std::make_shared<sf::RenderWindow>(sf::VideoMode(300, 600), 
                                              "Tetris C++", 
                                              sf::Style::Titlebar | sf::Style::Close);
}

std::unique_ptr<Block> Tetris::getRandomBlock(){
  // Populate game blocks
  if(gameBlocks.empty()){
    gameBlocks = getGameBlocks(); 
  }
 
  // Generate a random index 
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::size_t> dis(0, gameBlocks.size() - 1);
  std::size_t randIndex = dis(gen); 
  
  /* Each of the 7 blocks appear in game before a new cycle */ 
  std::unique_ptr<Block> pBlock {std::move(gameBlocks[randIndex])};
  gameBlocks.erase(gameBlocks.begin() + randIndex);
  
  return pBlock;
}

std::vector<std::unique_ptr<Block>> Tetris::getGameBlocks() const{
  std::vector<std::unique_ptr<Block>> vector {};

  vector.push_back(std::make_unique<IBlock>()); 
  vector.push_back(std::make_unique<JBlock>()); 
  vector.push_back(std::make_unique<LBlock>());
  vector.push_back(std::make_unique<OBlock>());
  vector.push_back(std::make_unique<SBlock>());
  vector.push_back(std::make_unique<TBlock>());
  vector.push_back(std::make_unique<ZBlock>());

  return vector;
}

bool Tetris::isValidMove(int row, int column) const{
  auto tilePositions = currentBlock->getTilePositions();
  for(const auto& tilePos : tilePositions){
    int new_row {tilePos.getRow() + row};
    int new_column {tilePos.getColumn() + column};

    if(new_row < 0 || new_row > s_numRows - 1 || new_column < 0 || new_column > s_numCols - 1){
      return false;
    }
  }
  return true; 
}

bool Tetris::isValidTiles(const std::vector<Position>& tilePositions) const{
  for(const auto& tilePos : tilePositions){
    int row {tilePos.getRow()};
    int column {tilePos.getColumn()};

    if(row < 0 || row > s_numRows - 1 || column < 0 || column > s_numCols - 1){
      return false; 
    }
  }  
  return true;
}

bool Tetris::isValidRotation(int nextState) const{
  auto tilePositions = currentBlock->getTilePositions(nextState); 
  return isValidTiles(tilePositions); 
}

void Tetris::moveBlockDown(){
  if(isValidMove(1, 0)){
    currentBlock->move(1, 0);
  }
}

bool Tetris::isGameUpdateEvent(){
  sf::Time timeElapsed {clock.getElapsedTime()};
  
  if(timeElapsed >= s_updateTime){
    clock.restart();
    return true;
  }
  return false;
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
        switch(event->key.code){
          case sf::Keyboard::Up:{
            if(isValidRotation(currentBlock->getNextValidState())){
              currentBlock->rotate();
            }
          }break;

          case sf::Keyboard::Left:{
            if(isValidMove(0, -1)){
              currentBlock->move(0, -1);
            }
          }break;

          case sf::Keyboard::Right:{
            if(isValidMove(0, 1)){
            currentBlock->move(0, 1);
            }
          }break;

          case sf::Keyboard::Down:{
            if(isValidMove(1, 0)){
              currentBlock->move(1, 0);
            }
          }break;

          default:{
            // std::cout << "Keyboard keypress '" << event->key.code << "' ignored!.\n" << std::endl;
          }
        }
      }break;
    
      default:{
        //std::cout << "Event '" << event->type << "' not handled!\n" << std::endl;
      }
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
    if(isGameUpdateEvent()){
      moveBlockDown(); 
    }
    // printGrid(); 
  }
}
