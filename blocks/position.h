#pragma once 

#include <iostream>

class Position{
  public:
    // Constructor 
    Position(std::ptrdiff_t row, std::ptrdiff_t column);

    // Overloaded IO steam operator 
    friend std::ostream& operator<< (std::ostream& out, const Position& obj);
    
    void updatePosition(std::ptrdiff_t rowOffset, std::ptrdiff_t columnOffset);
    std::ptrdiff_t  getColumn() const;
    std::ptrdiff_t  getRow() const;

  private:
    std::ptrdiff_t m_row {};
    std::ptrdiff_t m_column {}; 
};
