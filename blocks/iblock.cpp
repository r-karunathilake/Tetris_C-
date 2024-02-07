#include <vector>
#include <map>

#include "block.h"
#include "position.h"

class IBlock : public Block{
  public:
    IBlock() 
      // Call base class constructor
      : Block{initializeCells(), 3, CustomColors::Color::color_cyan}
    {
      // Make sure the blocks spawn in the middle of the window
      move(-1, 3);
    }
    
  private:
    std::map<int, std::vector<Position>> initializeCells() const override{
      
      std::map<int, std::vector<Position>> m_cells {
        {0, {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)}},
        {1, {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)}},
        {2, {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}},
        {3, {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)}}
      };
      return m_cells; 
    }
};
