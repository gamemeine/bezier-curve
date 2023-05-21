

APP_NAME = bezier
BUILD_DIR = ./bin
C_FILES = ./src/*.c

APP_INCLUDES:= -I ./src/dependencies/GLFW/include -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS:= -L ./src/dependencies/GLFW/lib -lglfw3

build:
	clang $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)