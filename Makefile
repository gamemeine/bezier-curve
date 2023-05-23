BUILD_DIR = ./bin
APP_NAME = bezier

ASM_FILES = ./src/*.asm
CPP_FILES = ./src/*.cpp
OUTPUT_FILES = ./bin/*.o

APP_INCLUDES:= -I ./src/dependencies/GLFW/include -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS:= -L ./src/dependencies/GLFW/lib -lglfw3


all: asm cc link

asm:
	as $(ASM_FILES) -o $(BUILD_DIR)/bezier.o

cc:
	g++ -c -g -std=c++17 -O0 $(CPP_FILES) -o $(BUILD_DIR)/main.o

link:
	g++ -g -o $(BUILD_DIR)/$(APP_NAME) $(OUTPUT_FILES) $(APP_INCLUDES) $(APP_LINKERS)

clean:
	rm $(BUILD_DIR)/*