CC=g++
CFLAGS=-c -O2 -Wall -Wextra -pedantic
LDFLAGS= 
SOURCES=test.cpp PIP200644.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE) clean_after

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $^ -o $@

clean_after:
	rm $(OBJECTS)

clean:
	rm $(EXECUTABLE)
	rm plotting/*.txt

plot:
	cd plotting; gnuplot plotting.gp; cd ..;
