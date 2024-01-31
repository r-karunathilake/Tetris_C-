#include <raylib.h>

int main(){
  InitWindow(300, 600, "Tetris (C++)");
  SetTargetFPS(60);
  
  // Game window background
  Color darkBlue = {44, 44, 127, 255};

  // Game loop
  while(!WindowShouldClose()){
    // Create blank canvas 
    BeginDrawing();
    
    ClearBackground(darkBlue); 


    EndDrawing();
  }
  CloseWindow(); 
}
