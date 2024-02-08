#include "position.h"

Position::Position(std::ptrdiff_t row, std::ptrdiff_t column) 
  : m_row{ row }, m_column{ column }
{

}

std::ostream& operator<< (std::ostream& out, const Position& obj){
  out << "(" << obj.m_row << ", " << obj.m_column << ')';
  return out;
}

void Position::updatePosition(std::ptrdiff_t rowOffset, std::ptrdiff_t columnOffset){
  m_row    += rowOffset;
  m_column += columnOffset;
}

std::ptrdiff_t Position::getColumn() const{return m_column;}
std::ptrdiff_t Position::getRow() const{return m_row;}
