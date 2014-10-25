CC=g++
CFLAGS=-Wall -I. -lgmp -lm -lgmpxx
LD=g++
LDFLAGS=-lgmp 
OBJ = main.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

lab2: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
