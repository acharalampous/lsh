CC = g++
CFLAGS = -g3 -Wall
OBJ = lsh_main.o hc_main.o utils.o dataset.o metrics.o lsh.o hypercube.o
L_OBJ = lsh_main.o utils.o dataset.o metrics.o lsh.o
LSH_X = lsh
HC_OBJ = hc_main.o utils.o dataset.o metrics.o hypercube.o
HC_X = hypercube


$(LSH_X): $(L_OBJ)
	$(CC) $(CFLAGS) $(L_OBJ) -o $@

$(HC_X): $(HC_OBJ)
	$(CC) $(CFLAGS) $(HC_OBJ) -o $@

lsh_main.o: lsh_main.cpp
	$(CC) $(CFLAGS) -c $^

hc_main.o: hc_main.cpp
	$(CC) $(CFLAGS) -c $^

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c $^

dataset.o: dataset.cpp
	$(CC) $(CFLAGS) -c $^

metrics.o: metrics.cpp
	$(CC) $(CFLAGS) -c $^

lsh.o: lsh.cpp
	$(CC) $(CFLAGS) -c $^

hypercube.o: hypercube.cpp
	$(CC) $(CFLAGS) -c $^	

.PHONY: clean

clean:
	rm -f $(LSH_X) $(HC_X) $(OBJ) 
