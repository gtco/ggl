#OBJS specifies which files to compile as part of the project
OBJS = asset.c lodepng.c texture.c scene.c sprite.c glsl.c game.c main.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -DLODEPNG_NO_COMPILE_ENCODER -DLODEPNG_NO_COMPILE_CPP

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lGL

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = ggl.core

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm ggl.core
	