sdgame.out : item.o account.o database.o game.o main.o  
	g++ -Wall  -o sdgame.out -lcurses item.o account.o database.o game.o main.o
	
item.o : item.cpp item.h common_header.h util.h
	g++ -Wall  -c item.cpp 
	
account.o : account.cpp account.h common_header.h
	g++ -Wall  -c account.cpp 
	
database.o : database.cpp database.h item.h util.h account.h
	g++ -Wall  -c database.cpp 
	
game.o : game.cpp game.h database.h util.h account.h item.h
	g++ -Wall  -c game.cpp 
	
main.o : main.cpp game.h
	g++ -Wall  -c main.cpp 

clean : 
	rm -f sdgame.out item.o account.o database.o game.o main.o 
