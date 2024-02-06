#pragma once                 // Header guard 

#include <SFML/Graphics.hpp> // Open and draw on an OpenGL window 
#include <memory>            // For std::shared_ptr access 
#include <vector>

#include "tilecolors.h"

class Tetris{
  private:
    static constexpr std::size_t s_numLines  {20};
    static constexpr std::size_t s_numCols   {10};
    static constexpr std::size_t s_numSquares {4};
    static constexpr std::size_t s_numShapes  {7};
    static constexpr std::size_t s_cellSize  {30};

    // 2D array alias templating 
    template <typename  T, std::size_t Rows, std::size_t Cols>
    using array2D = std::array<std::array<T, Cols>, Rows>; 
   
    array2D<CustomColors::Color, s_numLines, s_numCols> m_grid {}; 
    std::shared_ptr<sf::RenderWindow> m_window {}; 
 
  protected:
    void events();
    void draw();
    void printGrid();
    void drawGrid();

  public:
    Tetris();
    void run();
};
