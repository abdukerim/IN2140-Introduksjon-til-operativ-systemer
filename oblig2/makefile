CFLAGS=-g -Wall -Wextra -std=gnu11
VFLAGS=--track-origins=yes --malloc-fill=0x40 --free-fill=0x23 --leak-check=full --show-leak-kinds=all
BIN=./create_example1/create_fs1  ./create_example2/create_fs2  ./create_example3/create_fs3 ./load_example1/load_fs1 ./load_example2/load_fs2 ./load_example3/load_fs3

all: $(BIN)

./create_example1/create_fs1: create_fs1.o allocation.o inode.o

	gcc $(CFLAGS) $^ -o $@

create_fs1.o: ./create_example1/create_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

./create_example2/create_fs2: create_fs2.o allocation.o inode.o
	gcc $(CFLAGS) $^ -o $@

create_fs2.o: ./create_example2/create_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

./create_example3/create_fs3: create_fs3.o allocation.o inode.o
	gcc $(CFLAGS) $^ -o $@

create_fs3.o: ./create_example3/create_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

./load_example1/load_fs1: load_fs1.o allocation.o inode.o
	gcc $(CFLAGS) $^ -o $@

load_fs1.o: ./load_example1/load_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

./load_example2/load_fs2: load_fs2.o allocation.o inode.o
	gcc $(CFLAGS) $^ -o $@

load_fs2.o: ./load_example2/load_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

./load_example3/load_fs3: load_fs3.o allocation.o inode.o
	gcc $(CFLAGS) $^ -o $@

load_fs3.o: ./load_example3/load_fs.c
	gcc $(CFLAGS) -I. -c $^ -o $@

%.o: %.c
	gcc $(CFLAGS) $^ -c

clean:
	rm -rf *.o
	rm -f $(BIN)
