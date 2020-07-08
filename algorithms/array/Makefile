
CC=g++ -W -Wall
includes=$(shell find ./ -name "*.h")
src=$(shell find ./ -name "*.cpp")
obj=$(src:%.c=%.o)

%.o: %.cpp $(includes)
	$(CC) --std=c++11 -c  $<

all: $(obj)
	$(CC) --std=c++11 -o $@ $^

clean:
	rm -rf *.o  all
