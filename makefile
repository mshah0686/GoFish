# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.
final: card.o deck.o player.o card_demo.o
	g++ -std=c++11  -o final card_demo.o player.o deck.o card.o
card_demo.o: card_demo.cpp card.h player.h deck.h
	g++ -c -std=c++11 card_demo.cpp
player.o: player.cpp player.h
    g++ -c -std=c++11 player.cpp
deck.o: deck.cpp deck.h card.h
	g++ -c -std=c++11 deck.cpp
card.o: card.cpp card.h
	g++ -c -std=c++11 card.cpp
