#pragma once 

#include <iostream>

class Position{
  public:
    Position(int row, int column);
    int m_row {};
    int m_column {}; 

    friend std::ostream& operator<< (std::ostream& out, const Position& obj);
};
