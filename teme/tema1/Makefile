build: arguments.o ./tema1.c
	gcc tema1.c -o tema1 ./utils/arguments.o ./utils/list.o ./utils/stack.o -lpthread -lm

arguments.o: ./utils/arguments.c ./utils/arguments.h list.o stack.o
	gcc -c ./utils/arguments.c -g -o ./utils/arguments.o

list.o: ./utils/list.c ./utils/list.h
	gcc -c ./utils/list.c -g -o ./utils/list.o

stack.o: ./utils/stack.c ./utils/stack.h
	gcc -c ./utils/stack.c -g -o ./utils/stack.o

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all -s ./tema1 2 4 ./test0/test.txt

clean:
	rm tema1 ./utils/*.o