// FILE:  player.h
// written by Roger Priebe
// 1/22/08 (revised 9/2/08)
// This class represents a player in a card game that takes "tricks"
// The "Books" represent a container for holding tricks
//Names: Kenneth Mitra and Malav Shah
#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <string>
#include <vector>


#include "card.h"
using namespace std;


class Player
{
public:
    Player();

    Player(string name) {
        myName = name;
    }

    string getName() const {
        return myName;
    }

    //Books all pairs in hand, returns true if it booked pairs, false otherwise
    bool findPairsBookCards();

    //adds a card to the hand
    void addCard(Card c);

    //books cards specified in c1 and c2 from hand
    void bookCards(Card c1, Card c2);

    //uses some strategy to choose one card from the player's
    //hand so they can say "Do you have a 4?"
    Card chooseCardFromHand();

    //Initializes the player AI
    void initPlayerAI();

    //Does the player have the card c in her hand?
    bool cardInHand(Card c) const;

    //Remove the card c from the hand and return it to the caller
    Card removeCardFromHand(Card c);

    //Removes first card in hand with same rank and return removed card to caller
    //precondition: card with same rank as c is in hand
    Card removeCardWithSameRankFromHand(Card c);

    //returns string of hand
    string showHand() const;
    //returns string of books
    string showBooks() const;

    //returns number of cards in hand
    int getHandSize() const;
    //returns number of pairs
    int getBookSize() const;

    //checks if a pair of cards is in the hand
    //returns true/false
    bool checkHandForPair(Card &c1, Card &c2);

    //OPTIONAL
    // comment out if you decide to not use it
    //Does the player have a card with the same rank as c in her hand?
    //e.g. will return true if the player has a 7d and the parameter is 7c
    bool sameRankInHand(Card c) const;



private:
    Card indexCard;
    vector <Card> myHand;
    vector <Card> myBook;
    string myName;

    //-1 if card not found, else returns index of card
    int findCardInHand(Card c) const;
    //change card to ask for next
    void incrementIndexCard();
};


#endif