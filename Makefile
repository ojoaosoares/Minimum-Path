# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# all sources, objs, and header files
MAIN = Main
TARGET = ${BIN_FOLDER}pathfinder
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(shell mkdir -p $(OBJ_FOLDER))
$(shell mkdir -p $(BIN_FOLDER))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJ) ${LDFLAGS}

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*