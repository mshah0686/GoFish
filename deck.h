// FILE: deck.h
// written by Owen Astrachan and Roger Priebe
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck makes it consist of 52 cards in a random order
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//
// Calling shuffle again replenishes the deck with 52 cards.
//Names: Kenneth Mitra and Malav Shah
#ifndef _DECK_H
#define _DECK_H

#include "card.h"


class Deck
{

public:
    static const int SIZE = 52;

    Deck();           // Create a pristine, sorted Deck

    void shuffle();   // shuffle the deck, all 52 cards present
    Card dealCard();   // get a card, after 52 are dealt, fail
    string showDeck(); //Print the deck
    int  size() const; // # cards left in the deck

private:

    Card myCards[SIZE];
    int myIndex;  // current card to deal
};

#endif