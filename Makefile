CC=g++
CFLAGS=-c -O2 -Wall -Wextra -pedantic
LDFLAGS=-lgmpxx -lgmp 
SOURCES=test.cpp PIP200644.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(OBJECTS)
