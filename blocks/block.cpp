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
                 std::vector<Position>& shapeTiles) {

  for(const auto& tile : shapeTiles){ 
    auto cell {sf::RectangleShape(sf::Vector2f(m_cellSize - 1, m_cellSize - 1))};
    cell.setPosition(tile.getColumn() * m_cellSize + 1, tile.getRow() * m_cellSize + 1);
    cell.setFillColor(getSFMLColor(m_color));
    
    window->draw(cell);
  }
}

void Block::move(int rows, int columns){
  rowOffset += rows;
  columnOffset += columns; 
}

void Block::calculateCellPositions(std::vector<Position>& tilePositions){
  for(auto& tilePos : tilePositions){
    tilePos.updatePosition(rowOffset, columnOffset);
  }
}

int Block::getState() const{return m_rotationalState;}
