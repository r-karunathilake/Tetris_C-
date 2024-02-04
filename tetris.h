#pragma once                 // Header guard 

#include <SFML/Graphics.hpp> // Open and draw on an OpenGL window 
#include <memory>            // For std::shared_ptr access 

class Tetris{
  private:
    static constexpr std::size_t s_numLines  {20};
    static constexpr std::size_t s_numCols   {10};
    static constexpr std::size_t s_numSquares {4};
    static constexpr std::size_t s_numShapes  {7};

    struct Coordinate{
      std::uint32_t x {};
      std::uint32_t y {};
    };

    // 2D array alias templating 
    template <typename  T, std::size_t Rows, std::size_t Cols>
    using array2D = std::array<std::array<T, Cols>, Rows>; 
    
    array2D<std::uint32_t, s_numLines, s_numCols> m_grid {};
    array2D<std::uint32_t, s_numShapes, s_numSquares> m_shapes {{
          {1, 3, 5, 7}, // I
          {2, 4, 5, 7}, // Z
          {3, 5, 4, 6}, // S
          {3, 5, 4, 7}, // T
          {2, 3, 5, 7}, // L
          {3, 5, 7, 6}, // J
          {2, 3, 4, 5}, // O
        }};

    
    std::array<Coordinate, s_numSquares> m_z {}, m_k {};
    std::shared_ptr<sf::RenderWindow> m_window {}; 
    std::shared_ptr<sf::Sprite> m_sprite {}; 
    sf::Texture m_tiles {}; 

    int dirx {0};
    bool rotate {false};

  protected:
    void events();
    void draw();
    void moveDown(); 
    void setRotate();
    void resetValues();
    void changePosition();

  public:
    Tetris();
    void run();
};
