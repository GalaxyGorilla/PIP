CC=g++ 
CFLAGS=-c -O2 -Wall -Wextra -pedantic
LDFLAGS= 
SRCDIR=./src/
SOURCES=$(addprefix $(SRCDIR), test.cpp PIP200644.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pip

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
