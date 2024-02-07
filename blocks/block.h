#pragma once 

#include <memory>

#include "position.h"
#include "tilecolors.h"

class Block{
  using enum CustomColors::Color;

  public:
    // Constructor
    Block(std::map<int, std::vector<Position>> cells, 
          int id = 0, 
          CustomColors::Color color = color_transparent,
          std::size_t cellSize = 30, 
          int state = 0);
   
    // Virtual destructor 
    virtual ~Block(){};

    // Public methods
    int  getState() const;
    int  getID() const;
    void move(int rows, int columns);
    void draw(std::shared_ptr<sf::RenderWindow> window);
  
  protected: 
    // Protected methods
    void calculateCellPositions(std::vector<Position>& oldCells); 
    
    virtual std::map<int, std::vector<Position>> initializeCells() const = 0; 

  private:
    std::map<int, std::vector<Position>> m_cells {}; 
    int m_id {};
    CustomColors::Color m_color {};      
    std::size_t m_cellSize {}; 
    int m_rotationalState {}; 
    int rowOffset {};
    int columnOffset {}; 

    // Private methods
    void resetOffsets();
};
