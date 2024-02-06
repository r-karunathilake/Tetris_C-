#pragma once 

#include <memory>

#include "position.h"
#include "tilecolors.h"

class Block{
  using enum CustomColors::Color;

  public:
    // Constructor
    Block(int id = 0, 
          CustomColors::Color color = color_transparent,
          std::size_t cellSize = 30, 
          int state = 0);

    // Methods
    void draw(std::shared_ptr<sf::RenderWindow> window, 
              std::map<int, std::vector<Position>>& cells);

    virtual std::map<int, std::vector<Position>> initializeCells() const = 0; 
  
  protected:
    int m_id {};

  private:
    CustomColors::Color m_color {};      
    std::size_t m_cellSize {}; 
    int m_rotationalState {};
};
