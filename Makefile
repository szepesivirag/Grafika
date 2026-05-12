CC = gcc
CXX = g++
TARGET = Beadando.exe

INCLUDES = -Iinclude -Ic_sdk_220203/include
LIBS = -Lc_sdk_220203/lib -lmingw32 -lSDL2main -lSDL2 -lopengl32

C_SOURCES = src/main.c src/app.c src/camera.c src/scene.c src/texture.c


all:
	$(CXX) $(INCLUDES) $(C_SOURCES) $(CPP_SOURCES) -o $(TARGET) $(LIBS) -Wall -Wextra -Wpedantic

