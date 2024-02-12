#pragma once                 // Header guard 

#include <SFML/Graphics.hpp> // Open and draw on an OpenGL window 
#include <SFML/Audio.hpp>    
#include <memory>            // For std::shared_ptr access 
#include <vector>

#include "blocks/tilecolors.h"
#include "blocks/block.h"

#include "blocks/iblock.cpp"
#include "blocks/jblock.cpp"
#include "blocks/lblock.cpp"
#include "blocks/oblock.cpp"
#include "blocks/sblock.cpp"
#include "blocks/tblock.cpp"
#include "blocks/zblock.cpp"

class Tetris{
  private:
    static inline    int            s_gameScore  {0};
    static inline    bool           s_gameOver   {false};
    static inline    sf::Time       s_updateTime {sf::milliseconds(300)};
    static constexpr std::ptrdiff_t s_numRows    {20};
    static constexpr std::ptrdiff_t s_numCols    {10};
    static constexpr std::ptrdiff_t s_numSquares {4};
    static constexpr std::ptrdiff_t s_numShapes  {7};
    static constexpr std::ptrdiff_t s_cellSize   {30};

    // Load game music buffers 
    static inline sf::Music m_gameMusic {};
    static inline sf::SoundBuffer m_gameOverSoundBuffer {}; 
    static inline sf::SoundBuffer m_rotateSoundBuffer {};
    static inline sf::SoundBuffer m_clearRowSoundBuffer {};
    static inline sf::Sound m_gameOverSound {};
    static inline sf::Sound m_rotateSound {};
    static inline sf::Sound m_clearRowSound {};

    /* Private methods */
    std::unique_ptr<Block> getRandomBlock(); 
    std::vector<std::unique_ptr<Block>> getGameBlocks() const;
    std::shared_ptr<sf::RenderWindow> configGameWindow() const;
    bool isGridRowComplete(std::ptrdiff_t row) const;
    bool isValidMove(std::ptrdiff_t rows, std::ptrdiff_t columns) const;
    bool isValidRotation(int nextState) const;
    bool isValidTiles(const std::vector<Position>& tilePositions) const;
    bool isGameUpdateEvent();
    bool isGridCellEmpty(std::ptrdiff_t row, std::ptrdiff_t column) const;
    bool noValidMoves() const;
    void moveBlockDown();
    void freezeBlock();
    void clearGridRow(std::ptrdiff_t row); 
    void moveGridRowDown(std::ptrdiff_t row, std::ptrdiff_t numRowsDown);
    void restartGame(); 
    void resetGameGrid();
    void updateGameScore(int linesCompleted, int numBlocksUsed);
    void loadGameSounds(); 
    void loadIcons();
    int  clearAllCompleteGridRows();
    
    /* Private attributes */
    std::shared_ptr<sf::RenderWindow> m_window {}; 
    std::vector<std::unique_ptr<Block>> m_gameBlocks {};
    std::unique_ptr<Block> m_pCurrentBlock {};
    std::unique_ptr<Block> m_pNextBlock {};
    sf::Clock m_clock {}; // Start the SFML game clock

    // 2D array alias templating 
    template <typename  T, std::ptrdiff_t Rows, std::ptrdiff_t Cols>
    using array2D = std::array<std::array<T, Cols>, Rows>; 
    array2D<CustomColors::Color, s_numRows, s_numCols> m_grid {}; 
    sf::Font m_gameFont {};

  protected:
    void events();
    void draw();
    void printGrid();
    void drawGrid();
    void drawGUI(); 
    void drawRoundedRectangle(const sf::Vector2f& size, const sf::Vector2f& position) const; 
    void drawScoreBoard(const sf::Vector2f& size, const sf::Vector2f& position) const;
    void drawNextBoard(const sf::Vector2f& size, const sf::Vector2f& position) const;

  public:
    Tetris();
    void run();
};
