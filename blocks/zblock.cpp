#include <vector>
#include <map>

#include "block.h"
#include "position.h"

class ZBlock : public Block{
  public:
    ZBlock() 
      // Call base class constructor
      : Block{7, CustomColors::Color::color_red},
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
        {0, {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)}},
        {1, {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)}},
        {2, {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)}},
        {3, {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)}}
      };
      return m_cells; 
    }

    std::map<int, std::vector<Position>> m_cells {}; 
};
