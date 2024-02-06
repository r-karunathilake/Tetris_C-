#include <vector>
#include <map>

#include "block.h"
#include "position.h"

class OBlock : public Block{
  public:
    OBlock() 
      // Call base class constructor
      : Block{4, CustomColors::Color::color_yellow},
        m_cells{initializeCells()}
    {
      initializeCells();
      // Make sure the blocks spawn in the middle of the window
      move(0, 4);
    }
    
    void draw(std::shared_ptr<sf::RenderWindow> window){
      // Update the block positions before drawing
      Block::calculateCellPositions(m_cells[Block::getState()]);
      Block::draw(window, m_cells[Block::getState()]);
    }
  private:
    std::map<int, std::vector<Position>> initializeCells() const override{
      
      std::map<int, std::vector<Position>> m_cells {
        {0, {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}},
      };
      return m_cells; 
    }

    std::map<int, std::vector<Position>> m_cells {}; 
};
