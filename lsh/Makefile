CC = g++
CFLAGS = -g3 -Wall
OBJECTS = main.o utils.o dataset.o metrics.o lsh.o
EXE = lsh

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c $^

dataset.o: dataset.cpp
	$(CC) $(CFLAGS) -c $^

metrics.o: metrics.cpp
	$(CC) $(CFLAGS) -c $^

lsh.o: lsh.cpp
	$(CC) $(CFLAGS) -c $^	

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJECTS) 