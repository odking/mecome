
CC=gcc -W -Wall
includes=$(shell find ./ -name "*.h")
src=$(shell find ./ -name "*.c")
obj=$(src:%.c=%.o)

%.o: %.c $(includes)
	$(CC) -c $<

all: $(obj)
	$(CC) -o $@ $^

clean:
	rm -rf $(obj)  link-test
