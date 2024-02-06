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
    
    // Public methods
    int  getState() const;
    void move(int rows, int columns);

  protected:
    int m_id {};
    
    // Protected methods
    void draw(std::shared_ptr<sf::RenderWindow> window, 
              std::vector<Position>& shapeTiles);

    void calculateCellPositions(std::vector<Position>& oldCells); 
    
    virtual std::map<int, std::vector<Position>> initializeCells() const = 0; 

  private:
    CustomColors::Color m_color {};      
    std::size_t m_cellSize {}; 
    int m_rotationalState {};
    int rowOffset {};
    int columnOffset {}; 
};
