#include "tetris.h"

int main(int argc, char** argv){
  auto tetris {std::make_shared<Tetris>()};
  tetris->run(); 
  return 0;
}
