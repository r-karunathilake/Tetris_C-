#include "block.h"

using posVect = std::vector<Position>;

Block::Block(std::map<int, posVect> cells, int id, 
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

void Block::draw(std::shared_ptr<sf::RenderWindow> pWindow) {
  
  // Update the block positions before drawing
  updateCellPositions(m_cells);
  
  //std::cout << "Updated positions: \n";
  for(const auto& tilePos : m_cells[getState()]){
    //std::cout << tilePos << ", ";
    auto cell {sf::RectangleShape(sf::Vector2f(m_cellSize - 1, m_cellSize - 1))};
    cell.setPosition(tilePos.getColumn() * m_cellSize + 1, tilePos.getRow() * m_cellSize + 1);
    cell.setFillColor(getSFMLColor(m_color));
    
    pWindow->draw(cell);
  }
  //std::cout << '\n';

  // Set all row and column offSets to zero
  resetOffsets();
}

int Block::getNextValidState() const{
  int new_state {m_rotationalState + 1};

  if(new_state == static_cast<int>(m_cells.size())){
    // Reset state to initial state 
    new_state = 0;
  }
  return new_state;
}

void Block::rotate(){
  m_rotationalState = getNextValidState(); 
}

void Block::move(int rows, int columns){
  m_rowOffset = rows;
  m_columnOffset = columns; 
}

void Block::updateCellPositions(std::map<int, posVect>& tileStates){
  // Nothing to do when row and column offset is zero
  if(!isMovePending()){return;}
  
  // Update the position of all block states
  for(auto& keyPair : tileStates){
    for(auto& tilePos : keyPair.second){
      tilePos.updatePosition(m_rowOffset, m_columnOffset);
    }
  }
}

int Block::getState() const{return m_rotationalState;}
int Block::getID() const {return m_id;}
CustomColors::Color Block::getColor() const{return m_color;}

void Block::resetOffsets(){
  m_rowOffset = 0;
  m_columnOffset = 0;
}

bool Block::isMovePending() const{
  if(m_rowOffset != 0 || m_columnOffset != 0){
    return true;
  }
  return false;
}

posVect& Block::getTilePositions() {
  auto it {m_cells.find(getState())};
  if(it != m_cells.end()){
    return it->second;
  }
  else{
    throw std::runtime_error("Unable to provide a valid position vector for the current state!");
  }
}

posVect& Block::getTilePositions(int state){
  auto it {m_cells.find(state)};
  if(it != m_cells.end()){
    return it->second;
  }
  else{
    throw std::runtime_error("Unable to provide a valid position vector for the given state!");
  }
}

std::size_t Block::getNumStates() const{
  return std::size(m_cells);
}

std::ostream& operator<< (std::ostream& out, const Block& obj){
  out << "Block ID: " << obj.m_id << ", " <<  "State: "<< obj.m_rotationalState << '\n';
  return out;
}
