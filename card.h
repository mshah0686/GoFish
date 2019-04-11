//File Name: card.h
//Names: Kenneth Mitra and Malav Shah
//Written by Owen Astrachan and Roger Priebe
// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13

#ifndef _CARD_H
#define _CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card
{
public:

    enum Suit {spades, hearts, diamonds, clubs}; //Possible suits a card can have

    Card();          // default constructor, creates an ace of spades

    Card(int rank, Suit s); // creates a card with specified rank and suit

    string toString()              const;  // return string version e.g. Ac 4h Js
    bool sameSuitAs(const Card& c) const;  // true if suit same as c
    int  getRank()                 const;  // return rank, 1..13
    string suitString(Suit s)      const;  // return "s", "h",...

    string rankString(int r)       const;  // return "A", "2", ..."Q"


    bool operator == (const Card& rhs) const; // return true if a card has the same suit and rank
    bool operator != (const Card& rhs) const; // return true if a card doesnt have the same suit and rank
    ostream& operator << (ostream& out);      // write the text representation of a card out to the stream


private:

    int myRank; //Card's rank
    Suit mySuit; //Card's suit

};





#endif