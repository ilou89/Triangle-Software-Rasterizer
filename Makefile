CC = g++
CPPFLAGS = -Wall -std=c++14 -D_REENTRANT
LDFLAGS =
LIBS = -lSDL2
TARGET = drawlines


.PHONY = all clean

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
$(OBJECTS): %.o: %.cpp
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.bmp
	-rm -f *.svg

