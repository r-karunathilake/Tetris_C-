#pragma once                 // Header guard 

#include <SFML/Graphics.hpp> // Open and draw on an OpenGL window 
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
    static constexpr std::size_t s_numLines  {20};
    static constexpr std::size_t s_numCols   {10};
    static constexpr std::size_t s_numSquares {4};
    static constexpr std::size_t s_numShapes  {7};
    static constexpr std::size_t s_cellSize  {30};

    /* Private attributes */
    std::shared_ptr<sf::RenderWindow> m_window {}; 
    std::vector<std::shared_ptr<Block>> gameBlocks {};
    std::shared_ptr<Block> currentBlock {};
    std::shared_ptr<Block> nextBlock {};
    
    // 2D array alias templating 
    template <typename  T, std::size_t Rows, std::size_t Cols>
    using array2D = std::array<std::array<T, Cols>, Rows>; 
    array2D<CustomColors::Color, s_numLines, s_numCols> m_grid {}; 

    /* Private methods */
    std::shared_ptr<Block> getRandomBlock(); 
    std::vector<std::shared_ptr<Block>> getGameBlocks() const;

  protected:
    void events();
    void draw();
    void printGrid();
    void drawGrid();

  public:
    Tetris();
    void run();
};
