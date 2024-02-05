#pragma once 

#include <vector>
#include <map>

#include "position.h"

class Block{
  public:
    Block();
    int state {};
    std::map<int, std::vector<Position>> cells {};

  private:
    std::size_t cellSize {}; 
    int rotationalState {};
};
