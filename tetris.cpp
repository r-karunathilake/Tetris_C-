#include <random>
#include <string>

#include "tetris.h"

/**********************/
/* TETRIS CONSTRUCTOR */
/**********************/
Tetris::Tetris() 
  : m_window        {configGameWindow()},
    m_gameBlocks    {getGameBlocks()},
    m_pCurrentBlock {getRandomBlock()},
    m_pNextBlock    {getRandomBlock()}
{
  m_window->setPosition(sf::Vector2i(100, 100));
  m_window->setFramerateLimit(60); // 60 FPS  

  // Load font to GPU memory!
  if(!m_gameFont.loadFromFile("./assets/font/game_played.ttf")){
    std::cout << "Unable to load font file: 'game_played.ttf'\n" << std::endl;
  }
  
  // Load game music and sounds
  loadGameSounds();
}

/***********************/
/*   PRIVATE METHODS   */
/***********************/
void Tetris::loadGameSounds(){
  if(!m_gameOverSoundBuffer.loadFromFile("./assets/sounds/game_over.ogg")){
    std::cout << "Unable to load sound file: 'game_over.ogg'\n" << std::endl;
  }
  else{
    m_gameOverSound = sf::Sound(m_gameOverSoundBuffer);
  }

  if(!m_rotateSoundBuffer.loadFromFile("./assets/sounds/rotate.wav")){
    std::cout << "Unable to load sound file: 'rotate.wav'\n" << std::endl;
  }
  else{
    m_rotateSound = sf::Sound(m_rotateSoundBuffer);
  }

  if(!m_clearRowSoundBuffer.loadFromFile("./assets/sounds/row_clear.wav")){
    std::cout << "Unable to load soud file: 'row_clear.wav'\n" << std::endl;
  }
  else{
    m_clearRowSound = sf::Sound(m_clearRowSoundBuffer);
  }

  if(!m_gameMusic.openFromFile("./assets/sounds/tetris.ogg")){
    std::cout << "Unable to load music file: 'tetris.ogg'\n" << std::endl;
  }
  else{
    m_gameMusic.setLoop(true);
    m_gameMusic.setVolume(20.f);
  }
}

std::shared_ptr<sf::RenderWindow> Tetris::configGameWindow() const{
    return std::make_shared<sf::RenderWindow>(sf::VideoMode(500, 620), 
                                              "Tetris C++", 
                                              sf::Style::Titlebar | sf::Style::Close);
}

std::unique_ptr<Block> Tetris::getRandomBlock(){
  // Populate game blocks
  if(m_gameBlocks.empty()){
    m_gameBlocks = getGameBlocks(); 
  }
 
  // Generate a random index 
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::ptrdiff_t> dis(0, m_gameBlocks.size() - 1);
  std::ptrdiff_t randIndex = dis(gen); 
  
  /* Each of the 7 blocks appear in game before a new cycle */ 
  std::unique_ptr<Block> pBlock {std::move(m_gameBlocks[randIndex])};
  m_gameBlocks.erase(m_gameBlocks.begin() + randIndex);
  
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
  auto tilePositions = m_pCurrentBlock->getTilePositions();
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
  auto tilePositions = m_pCurrentBlock->getTilePositions(nextState); 
  return isValidTiles(tilePositions); 
}

void Tetris::moveBlockDown(){
  // Look ahead to make sure the move is valid 
  if(isValidMove(1, 0)){
    m_pCurrentBlock->move(1, 0);
  }
  else{// The block has reached the bottom screen or collided with another block
    freezeBlock(); 
  }
}

bool Tetris::isGameUpdateEvent(){
  sf::Time timeElapsed {m_clock.getElapsedTime()};
  
  if(timeElapsed >= s_updateTime){
    m_clock.restart();
    return true;
  }
  return false;
}

void Tetris::freezeBlock(){
  auto tilePositions {m_pCurrentBlock->getTilePositions()};
  for(const auto& tilePos: tilePositions){
    // Update game grid with the color of Tetris block 
    m_grid[tilePos.getRow()][tilePos.getColumn()] = m_pCurrentBlock->getColor();
  }
  
  // TODO: Make sure m_pNextBlock is not a NULL pointer?
  m_pCurrentBlock = std::move(m_pNextBlock); // Freeze movement 
  // If the new current block has no valid moves 
  if(noValidMoves()){
    // Game over
    s_gameOver = true; 
    m_pNextBlock = nullptr;
  
    // Stop the music
    m_gameMusic.stop();

    m_gameOverSound.play();

  }
  else{
    m_pNextBlock = getRandomBlock(); 
    // Check for complete grid rows and clear them
    int rowsCleared {clearAllCompleteGridRows()};
    // Update score
    updateGameScore(rowsCleared, 0);
  }
}

bool Tetris::noValidMoves() const{
  // Check is Tetris block can be moved down or rotated 
  if(isValidMove(1, 0) || isValidMove(0, 1) || isValidMove(1, 0)
     || isValidRotation(m_pCurrentBlock->getNextValidState())){
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
      // Play row clear sound 
      m_clearRowSound.play();

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
  m_gameBlocks = getGameBlocks();
  m_pCurrentBlock = getRandomBlock();
  m_pNextBlock = getRandomBlock(); 
  s_gameScore = 0;
  m_gameOverSound.stop();
  m_gameMusic.play();
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
            if(s_gameOver){
              s_gameOver = false;
              restartGame(); 
            }
          }break;

          case sf::Keyboard::Up:{
            if(isValidRotation(m_pCurrentBlock->getNextValidState()) && !s_gameOver){
              m_pCurrentBlock->rotate();
              if(m_rotateSound.getStatus() == sf::Sound::Stopped){
                m_rotateSound.play();
              }
            }
          }break;

          case sf::Keyboard::Left:{
            if(isValidMove(0, -1) && !s_gameOver){
              m_pCurrentBlock->move(0, -1);
            }
          }break;

          case sf::Keyboard::Right:{
            if(isValidMove(0, 1) && !s_gameOver){
            m_pCurrentBlock->move(0, 1);
            }
          }break;

          case sf::Keyboard::Down:{
            if(!s_gameOver){
              moveBlockDown(); 
              updateGameScore(0, 1);
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
  m_window->clear(CustomColors::bg_purple);
  
  drawGUI();  
  drawGrid();
  
  m_pCurrentBlock->draw(m_window, 11, 11);

  // End drawing current frame and display
  m_window->display();
}

void Tetris::drawGrid(){
  for(size_t row {0}; row < m_grid.size(); ++row){
    for(size_t column {0}; column < m_grid[row].size(); ++column){
      auto cellColor = m_grid[row][column];
      auto cell {sf::RectangleShape(sf::Vector2f(s_cellSize - 1, s_cellSize - 1))};
      cell.setPosition(column * s_cellSize + 11, row * s_cellSize + 11);
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

void Tetris::drawGUI(){
  // Draw score board 
  drawScoreBoard(sf::Vector2f(170, 60), sf::Vector2f(320, 55));
  
  // Draw the next block text
  drawNextBoard(sf::Vector2f(170, 180), sf::Vector2f(320, 215));
 
  // Draw game over text 
  if(s_gameOver){
    sf::Text overText {sf::Text("GAME\nOVER", m_gameFont, 32)};
    overText.setFillColor(sf::Color::Red);
    overText.setLetterSpacing(2);
    overText.setLineSpacing(1);
    overText.setPosition(sf::Vector2f(320, 450));
    overText.setStyle(sf::Text::Italic);
    m_window->draw(overText);
  
    //sf::Sound gameOverSound {sf::Sound(m_gameOverSoundBuffer)};
    //gameOverSound.play();
  }
}

void Tetris::drawRoundedRectangle(const sf::Vector2f& size, const sf::Vector2f& position) const{
  // TODO: implement actual rounded corner functionality

  sf::RectangleShape rect(size);
  rect.setPosition(position);
  rect.setFillColor(CustomColors::dark_grey);
  m_window->draw(rect);
}

void Tetris::drawScoreBoard(const sf::Vector2f& size, const sf::Vector2f& position) const{
  
  // Draw the score label text
  sf::Text scoreText {sf::Text("Score", m_gameFont, 32)};
  scoreText.setFillColor(sf::Color::White);
  scoreText.setLetterSpacing(2);
  // Get text box size 
  sf::FloatRect labelTextBounds {scoreText.getLocalBounds()};
  scoreText.setPosition(sf::Vector2f(position.x + ((size.x - labelTextBounds.width) * 0.5), position.y - 40));
  m_window->draw(scoreText);
  
  // Draw the score board
  drawRoundedRectangle(size, position);

  // Draw the score 
  sf::Text score {sf::Text(std::to_string(s_gameScore), m_gameFont, 24)};
  score.setFillColor(sf::Color::White);
  score.setLetterSpacing(2);
  
  // Get the size of the text box 
  sf::FloatRect textBounds {score.getLocalBounds()};
  double xPos {position.x + ((size.x - textBounds.width) * 0.5)};
  double yPos {position.y + (0.5 * (size.y - textBounds.height))};

  // Adjust the text position based on text size relative to score board 
  score.setPosition(sf::Vector2f(xPos, yPos));
  m_window->draw(score);
}

void Tetris::drawNextBoard(const sf::Vector2f& size, const sf::Vector2f& position) const{
  // Draw next block board
  drawRoundedRectangle(size, position);

  sf::Text nextText {sf::Text("Next", m_gameFont, 32)};
  nextText.setFillColor(sf::Color::White);
  nextText.setLetterSpacing(2);

  // Get size of the text box
  sf::FloatRect textBounds = nextText.getLocalBounds();
  nextText.setPosition(sf::Vector2f(position.x + ((size.x - textBounds.width) * 0.5), position.y - 40));
  m_window->draw(nextText);

  if(m_pNextBlock){
    double xPos {0};
    double yPos {0};

    switch(m_pNextBlock->getID()){
      case 4:{ // O block
        xPos = position.x - 60;
        yPos = position.y + 60;
      }break; 
      
      case 3:{ // I block
        xPos = position.x - 60;
        yPos = position.y + 80;
      }break;

      default:{ 
        xPos = position.x - 45;
        yPos = position.y + 60; 
      }
    }
    m_pNextBlock->draw(m_window, xPos, yPos);
  }
}

void Tetris::updateGameScore(int linesCompleted, int numBlocksUsed){
  switch(linesCompleted){
    case 1:{
      s_gameScore += 100;
    }break;

    case 2:{
      s_gameScore += 300;
    }break;

    case 3:{
      s_gameScore += 500;
    }break;

    default:
      break;
  }
  s_gameScore += numBlocksUsed; 
}

/***********************/
/*    PUBLIC METHODS   */
/***********************/
void Tetris::run(){ 
  // Play game music
  m_gameMusic.play(); 
  
  while(m_window->isOpen()){
    events();
    draw();
    if(isGameUpdateEvent() && !s_gameOver){
      moveBlockDown(); 
    }
    // printGrid(); 
  }
}
