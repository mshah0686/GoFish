//Names: Kenneth Mitra and Malav Shah
#include <time.h>
#include "deck.h"

Deck::Deck() {
    int cardNum = 0;

    //Generate Deck in order of spades, hearts, diamonds, clubs
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::spades);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::hearts);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::diamonds);
    }
    for(int i = 1; i < 14; i++, cardNum++) {
        myCards[cardNum] = Card(i, Card::clubs);
    }
    myIndex = 0;
    srand(time(NULL));
}

void Deck::shuffle() {
    if(myIndex >= SIZE) {
        return;
    }
    for(int i = 0; i < size() * 5; i++){
        //generate two random indices to swap
        int firstIndex = (rand() % size()) + myIndex;
        int secondIndex = (rand() % size()) + myIndex;

        //Swap those indicies
        Card temp = myCards[firstIndex];
        myCards[firstIndex] = myCards[secondIndex];
        myCards[secondIndex] = temp;
    }
}

Card Deck::dealCard() {
    if(myIndex < 52) {
        int cpy = myIndex;
        myIndex++; //Increment top of the deck
        return myCards[cpy]; //return card that was on top of the deck
    }
    cout << "ERROR NO MORE CARDS" << endl;
    exit(-1);
}

int Deck::size() const {
    return SIZE - myIndex; //return number of cards under the top of the deck
}

string Deck::showDeck() {
    //return string representation of deck
    string ret;
    for(int i = myIndex; i < SIZE; i++){
        ret += myCards[i].toString() + " ";
    }
    return ret;
}
