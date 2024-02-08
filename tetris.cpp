#include <random>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris() 
  : m_window     {configGameWindow()},
    gameBlocks   {getGameBlocks()},
    pCurrentBlock {getRandomBlock()},
    pNextBlock    {getRandomBlock()}
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
  std::uniform_int_distribution<std::ptrdiff_t> dis(0, gameBlocks.size() - 1);
  std::ptrdiff_t randIndex = dis(gen); 
  
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

bool Tetris::isValidMove(std::ptrdiff_t row, std::ptrdiff_t column) const{
  auto tilePositions = pCurrentBlock->getTilePositions();
  for(const auto& tilePos : tilePositions){
    std::ptrdiff_t new_row {tilePos.getRow() + row};
    std::ptrdiff_t new_column {tilePos.getColumn() + column};
    
    if(new_row < 0 || new_row > s_numRows - 1 || new_column < 0 || new_column > s_numCols - 1){
      return false;
    }

    if(!isGridCellEmpty(new_row, new_column)){
      return false;
    }
  }
  return true; 
}

bool Tetris::isValidTiles(const std::vector<Position>& tilePositions) const{
  for(const auto& tilePos : tilePositions){
    std::ptrdiff_t row {tilePos.getRow()};
    std::ptrdiff_t column {tilePos.getColumn()};

    if(row < 0 || row > s_numRows - 1 || column < 0 || column > s_numCols - 1
       || !isGridCellEmpty(row, column)){
      return false; 
    }
  }  
  return true;
}

bool Tetris::isValidRotation(int nextState) const{
  auto tilePositions = pCurrentBlock->getTilePositions(nextState); 
  return isValidTiles(tilePositions); 
}

void Tetris::moveBlockDown(){
  // Look ahead to make sure the move is valid 
  if(isValidMove(1, 0)){
    pCurrentBlock->move(1, 0);
  }
  else{// The block has reached the bottom screen or collided with another block
    freezeBlock(); 
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

void Tetris::freezeBlock(){
  auto tilePositions {pCurrentBlock->getTilePositions()};
  for(const auto& tilePos: tilePositions){
    // Update game grid with the color of Tetris block 
    m_grid[tilePos.getRow()][tilePos.getColumn()] = pCurrentBlock->getColor();
  }
  
  // TODO: Make sure pNextBlock is not a NULL pointer?
  pCurrentBlock = std::move(pNextBlock); // Freeze movement 
  // If the new current block has no valid moves 
  if(noValidMoves()){
    // Game over
    gameOver = true; 
    pNextBlock = nullptr;
  }
  else{
    pNextBlock = getRandomBlock(); 
    // Check for complete grid rows and clear them
    clearAllCompleteGridRows(); 
  }
}

bool Tetris::noValidMoves() const{
  // Check is Tetris block can be moved down or rotated 
  if(isValidMove(1, 0) && isValidMove(0, 1) && isValidMove(1, 0)
     && isValidRotation(pCurrentBlock->getNextValidState())){
    return false;
  }
  return true;
}

bool Tetris::isGridCellEmpty(std::ptrdiff_t row, std::ptrdiff_t column) const{
  if(m_grid[row][column] == 0){
    return true;
  }
  return false;
}

bool Tetris::isGridRowComplete(std::ptrdiff_t row) const{
  auto gridRow {m_grid[row]};  
  for(const auto& color : gridRow){
    if(color == CustomColors::color_dark_grey){
      return false;
    }
  } 
  return true; 
}

void Tetris::clearGridRow(std::ptrdiff_t row){
  for(std::ptrdiff_t column {0}; column < s_numCols; ++column){
    // Set tile to background color
    m_grid[row][column] = CustomColors::color_dark_grey;
  }
}

void Tetris::moveGridRowDown(std::ptrdiff_t row, std::ptrdiff_t numRowsDown){
  for(std::ptrdiff_t column {0}; column < s_numCols; ++column){
    m_grid[row + numRowsDown][column] = m_grid[row][column];
    // Set tile to background color
    m_grid[row][column] = CustomColors::color_dark_grey;
  }
}

int Tetris::clearAllCompleteGridRows(){
  std::ptrdiff_t numCompletedRows {0};
  // Iterate through the whole game grid
  for(std::ptrdiff_t currentRow {s_numRows - 1}; currentRow >= 0; --currentRow){
    if(isGridRowComplete(currentRow)){
      clearGridRow(currentRow);
      ++numCompletedRows;
    }
    else if(numCompletedRows > 0){
      moveGridRowDown(currentRow, numCompletedRows);
    }
  }
  return static_cast<int>(numCompletedRows);
}

void Tetris::resetGameGrid(){
  for(size_t row {0}; row < s_numRows; ++row){
    for(size_t column {0}; column < s_numCols; ++column){
      m_grid[row][column] = CustomColors::color_dark_grey;
    }
  }
}

void Tetris::restartGame(){
  resetGameGrid();
  gameBlocks = getGameBlocks();
  pCurrentBlock = getRandomBlock();
  pNextBlock = getRandomBlock(); 
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
          case sf::Keyboard::Escape:{
            m_window->close();                             
          }break;
                                    
          // Restart game
          case sf::Keyboard::R:{
            if(gameOver){
              gameOver = false;
              restartGame(); 
            }
          }break;

          case sf::Keyboard::Up:{
            if(isValidRotation(pCurrentBlock->getNextValidState()) && !gameOver){
              pCurrentBlock->rotate();
            }
          }break;

          case sf::Keyboard::Left:{
            if(isValidMove(0, -1) && !gameOver){
              pCurrentBlock->move(0, -1);
            }
          }break;

          case sf::Keyboard::Right:{
            if(isValidMove(0, 1) && !gameOver){
            pCurrentBlock->move(0, 1);
            }
          }break;

          case sf::Keyboard::Down:{
            if(!gameOver){
              moveBlockDown();  
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
  
  pCurrentBlock->draw(m_window); 

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
    if(isGameUpdateEvent() && !gameOver){
      moveBlockDown(); 
    }
    // printGrid(); 
  }
}
