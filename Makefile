TARGET   := tetris
CXX      := clang++
STD      := -std=c++20
DEBUG    := -g
OPT      := -O0 # Disable compiler optimization 
WARN     := -Wall
SFML     := -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS := $(DEBUG) $(STD) $(OPT) $(WARN) $(SFML)
SOURCE   := main.cpp tetris.cpp 
OBJS     := $(SOURCE:.cpp=.o) # Pattern substitution 

# Make recipes
all: $(TARGET) # Default recipe 
		@echo "Running make 'all' recipe..."

$(TARGET): $(OBJS)
		@echo "Compiling program..."
		# $@ (recipe target) $^ (all recipe dependencies)
		$(CXX) $(CXXFLAGS) -o $@ $^ 

# Recipe: build object files 
%.o: %.cpp
		@echo "Building $< object file..."
		# $< (first dependency for the recipe)
		$(CXX) -c $(CXXFLAGS) -o $@ $<

# Clean intermediate object files and executable
clean:
		@echo "Cleaning object files..."
		@rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
		@echo "Executing $(TARGET) program..."
		@./$(TARGET)
