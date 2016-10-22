CC=gcc
CFLAGS=-c -m32 -mfpmath=sse -Ofast -Wall -g -pg
LDFLAGS=-lGL -lGLU -lglut -m32 -mfpmath=sse -Ofast -Wall -g -pg
LINKEDLIBRARY=-LGraphicalPart.h
SOURCES=Main.c GraphicalPart.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=crossword

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LINKEDLIBRARY) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

#-m32 -mfpmath=sse -Ofast -flto -march=native -funroll-loops

#-Wall -g -pg
#-g -pg