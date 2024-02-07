#include "block.h"

Block::Block(std::map<int, std::vector<Position>> cells, int id, 
             CustomColors::Color color,
             std::size_t cellSize, 
             int state)
  : m_cells {cells},
    m_id {id},
    m_color {color},
    m_cellSize {cellSize},
    m_rotationalState {state}
{

}

void Block::draw(std::shared_ptr<sf::RenderWindow> window) {
  
  // Update the block positions before drawing
  calculateCellPositions(m_cells[getState()]);
  std::vector<Position> shapePositions {m_cells[getState()]};
  // Set all row and column offSets to zero
  resetOffsets(); 
  
  for(const auto& tilePos : shapePositions){
    auto cell {sf::RectangleShape(sf::Vector2f(m_cellSize - 1, m_cellSize - 1))};
    cell.setPosition(tilePos.getColumn() * m_cellSize + 1, tilePos.getRow() * m_cellSize + 1);
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
int Block::getID() const {return m_id;}
void Block::resetOffsets(){
  rowOffset = 0;
  columnOffset = 0;
}
