#include <time.h>
#include "deck.h"

Deck::Deck() {
    //suit order is spades, hearts, diamonds clubs
    int cardNum = 0;
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::spades);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::hearts);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::clubs);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::diamonds);
    }
    //top card is index 0
    myIndex = 0;
    srand(time(NULL));
}

void Deck::shuffle() {
    if(myIndex >= SIZE) {
        return;
    }
    //swap two cards at two index size*5 times
    for(int i = 0; i < size() * 5; i++){
        //generate two random indices to swap
        int firstIndex = (rand() % size()) + myIndex;
        int secondIndex = (rand() % size()) + myIndex;
        Card temp = myCards[firstIndex];
        myCards[firstIndex] = myCards[secondIndex];
        myCards[secondIndex] = temp;
    }
}

Card Deck::dealCard() {
    //top card is returned, index changed
    if(myIndex < 52) {
        int cpy = myIndex;
        myIndex++;
        return myCards[cpy];
    }
    //end of deck, no more cards
    cout << "ERROR NO MORE CARDS" << endl;
    exit(-1);
}

int Deck::size() const {
    //number of cards left is total - amount dealed
    return SIZE - myIndex;
}

string Deck::showDeck() {
    //print the deck (mainly for debugging)
    string ret;
    for(int i = myIndex; i < SIZE; i++){
        ret += myCards[i].toString() + " ";
    }
    return ret;
}
