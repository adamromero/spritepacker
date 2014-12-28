CC = g++

OBJS = main.cc SpritePacker.cpp

LINKER_FLAGS = -lboost_system -lboost_filesystem -L/usr/X11R6/lib -lm -lpthread -lX11

OBJ_NAME = -o spritepacker

all: $(OBJS) 
	$(CC) $(OBJS) $(OBJ_NAME) $(LINKER_FLAGS)

clean:
	rm -rf *.o spritepacker
