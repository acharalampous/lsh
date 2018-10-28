CC = g++
CFLAGS = -g3 -Wall
OBJECTS = hc_main.o utils.o dataset.o metrics.o hypercube.o
EXE = hypercube

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

hc_main.o: hc_main.cpp
	$(CC) $(CFLAGS) -c $^

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c $^

dataset.o: dataset.cpp
	$(CC) $(CFLAGS) -c $^

metrics.o: metrics.cpp
	$(CC) $(CFLAGS) -c $^

hypercube.o: hypercube.cpp
	$(CC) $(CFLAGS) -c $^	

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJECTS) 