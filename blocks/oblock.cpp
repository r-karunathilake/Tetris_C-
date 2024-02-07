#include <vector>
#include <map>

#include "block.h"
#include "position.h"

class OBlock : public Block{
  public:
    OBlock() 
      // Call base class constructor
      : Block{initializeCells(), 4, CustomColors::Color::color_yellow}
    {
      // Make sure the blocks spawn in the middle of the window
      move(0, 4);
    }
    
  private:
    std::map<int, std::vector<Position>> initializeCells() const override{
      
      std::map<int, std::vector<Position>> m_cells {
        {0, {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}},
      };
      return m_cells; 
    }
};
