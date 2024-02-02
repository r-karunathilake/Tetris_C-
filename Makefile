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
		$(CXX) $(CXXFLAGS) -o $@ $^ # $@ (rule target) $^ (all rule dependencies)

# Recipe: build object files 
%.o: %.cpp
		@echo "Building $< object file..."
		$(CXX) -c $(CXXFLAGS) -o $@ $< # $< (first dependency for the rule)

# Clean intermediate object files and executable
clean:
		@echo "Cleaning object files..."
		@rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
		@echo "Executing $(TARGET) program..."
		@./$(TARGET)
