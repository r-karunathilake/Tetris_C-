#include <vector>
#include <map>

#include "block.h"
#include "position.h"

class TBlock : public Block{
  public:
    TBlock() 
      // Call base class constructor
      : Block{6, CustomColors::Color::color_purple},
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
        {0, {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)}},
        {1, {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)}},
        {2, {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)}},
        {3, {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)}}
      };
      return m_cells; 
    }

    std::map<int, std::vector<Position>> m_cells {}; 
};
