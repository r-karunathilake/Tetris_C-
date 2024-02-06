#include "position.h"

Position::Position(int row, int column) 
  : m_row{ row }, m_column{ column }
{

}

std::ostream& operator<< (std::ostream& out, const Position& obj){
  out << "(" << obj.m_row << ", " << obj.m_column << ')';
  return out;
}

void Position::updatePosition(int rowOffset, int columnOffset){
  m_row    += rowOffset;
  m_column += columnOffset;
}

int Position::getColumn() const{return m_column;}
int Position::getRow() const{return m_row;}
