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
    }
    
    void draw(std::shared_ptr<sf::RenderWindow> window){
      Block::draw(window, m_cells);
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
