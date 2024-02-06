#include "block.h"

Block::Block(int id, 
             CustomColors::Color color,
             std::size_t cellSize, 
             int state)
  : m_id {id},
    m_color {color},
    m_cellSize {cellSize},
    m_rotationalState {state}
{

}

void Block::draw(std::shared_ptr<sf::RenderWindow> window, 
                 std::map<int, std::vector<Position>>& cells) {

  std::vector<Position> shapeTiles = cells[m_rotationalState];
  for(const auto& tile : shapeTiles){ 
    auto cell {sf::RectangleShape(sf::Vector2f(m_cellSize - 1, m_cellSize - 1))};
    cell.setPosition(tile.m_column * m_cellSize + 1, tile.m_row * m_cellSize + 1);

    cell.setFillColor(getSFMLColor(m_color));
    
    window->draw(cell);
  }
}
