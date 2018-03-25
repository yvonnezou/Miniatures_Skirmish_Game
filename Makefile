#SRC = src/item.cpp src/account.cpp src/database.cpp src/game.cpp src/main.cpp
OBJ = obj/item.o obj/account.o obj/database.o obj/game.o obj/main.o
CC = g++
CFLAGS = -Wall -c

bin/sdgame: $(OBJ)
	@if [ ! -d "bin" ]; then\
        mkdir bin;\
    fi
	@$(CC) -Wall -o $@ $(OBJ)

obj/item.o : src/item.cpp src/item.h src/common_header.h src/util.h
	@if [ ! -d "obj" ]; then\
        mkdir obj;\
    fi
	@$(CC) $(CFLAGS) -o $@ $< #build source object

obj/account.o : src/account.cpp src/account.h src/common_header.h
	@if [ ! -d "obj" ]; then\
        mkdir obj;\
    fi
	@$(CC) $(CFLAGS) -o $@ $< #build source object

obj/database.o : src/database.cpp src/database.h src/item.h src/util.h src/account.h
	@if [ ! -d "obj" ]; then\
        mkdir obj;\
    fi
	@$(CC) $(CFLAGS) -o $@ $< #build source object

obj/game.o : src/game.cpp src/game.h src/database.h src/util.h src/account.h src/item.h
	@if [ ! -d "obj" ]; then\
        mkdir obj;\
    fi
	@$(CC) $(CFLAGS) -o $@ $< #build source object

obj/main.o : src/main.cpp src/game.h
	@if [ ! -d "obj" ]; then\
        mkdir obj;\
    fi
	@$(CC) $(CFLAGS) -o $@ $< #build source object

clean:
	rm -f obj/*.o
	rm -f bin/*

