#pragma once 

#include <iostream>

class Position{
  public:
    // Constructor 
    Position(int row, int column);

    // Overloaded IO steam operator 
    friend std::ostream& operator<< (std::ostream& out, const Position& obj);
    
    void updatePosition(int rowOffset, int columnOffset);
    int  getColumn() const;
    int  getRow() const;

  private:
    int m_row {};
    int m_column {}; 
};
