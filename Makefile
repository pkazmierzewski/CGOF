CC=gcc
OBJ=objcopy
CFLAGS=`pkg-config --cflags --libs glib-2.0` -c -O2 -Wall -std=c99 $(INCLUDES)
LDFLAGS=
LIBRARIES=-lSDL -lSDL_image -lSDL_ttf
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=life
INCLUDES=-Isrc

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.c.o:
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
