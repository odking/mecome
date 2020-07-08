
CC=gcc -W -Wall
includes=$(shell find ./ -name "*.h")
src=$(shell find ./ -name "*.c")
obj=$(src:%.c=%.o)

%.o: %.c $(includes)
	$(CC) -g -c $<

all: $(obj)
	$(CC) -g -o $@ $^

clean:
	rm -rf $(obj)  link-test
