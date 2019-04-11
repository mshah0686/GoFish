//
// Created by Malav Shah on 2019-04-09.
//

#include "player.h"
using namespace std;
Player::Player() {
    myName = "Kenneth";
}

void Player::addCard(Card c) {
    myHand.push_back(c);
    incrementIndexCard();
}

void Player::incrementIndexCard() {
    //changes card to ask for next in hand based on size of hand
    if(myHand.size() > 0) {
        indexCard = myHand[(findCardInHand(indexCard) + 1) % myHand.size()];
    }
}

void Player::bookCards(Card c1, Card c2) {
    //add cards to vector
    myBook.push_back(c1);
    myBook.push_back(c2);
}


bool Player::checkHandForPair(Card &c1, Card &c2) {
    for(int i = 0; i < myHand.size(); i++) {
        for(int j = i + 1; j < myHand.size(); j++) {
            //if the cards are found in vector, return true with the populated cards
            if(myHand[i].getRank() == myHand[j].getRank()) {
                c1 = myHand[i];
                c2 = myHand[j];
                return true;
            }
        }
    }
    return false;
}

Card Player::removeCardFromHand(Card c) {
    for(vector<Card>::iterator i = myHand.begin(); i != myHand.end(); i++) {
        //if card found, remove card, change asking card, and return the card
        if(*i == c) {
            myHand.erase(i);
            if(c == indexCard){
                incrementIndexCard();
            }
            return c;
        }
    }
    return c;
}

Card Player::removeCardWithSameRankFromHand(Card c) {
    for(auto i = myHand.begin(); i != myHand.end(); i++) {
        //finds the first card with same rank in hand
        if(i->getRank() == c.getRank()) {
            Card retCard = *i;
            if(retCard == indexCard){
                incrementIndexCard();
            }
            //removes the card from the hand
            myHand.erase(i);
            return retCard;
        }
    }
    //if card not found, fails precondition
    cout << "Major ERROR in removeCardWithSameRankFromHand()" << endl;
    exit(-1);
    return c;
}

bool Player::cardInHand(Card c) const {
    //if card in hand, return true
    for(Card card : myHand) {
        if(card == c) {
            return true;
        }
    }
    return false;
}

void Player::initPlayerAI() {
    //starts player with choose card as the first card
    indexCard = myHand[0];
}

Card Player::chooseCardFromHand() {
    //returns card to ask for
    Card cpy = indexCard;
    incrementIndexCard();
    return cpy;
}

int Player::findCardInHand(Card c) const{
    //finds a specific card in the hand
    int i=0;
    for(i=0; i < myHand.size(); i++){
        if(myHand[i] == c){
            return i;
        }
    }
    return -1;
}
bool Player::sameRankInHand(Card c) const {
    //returns if certain rank is in hand
    for(Card card : myHand) {
        if(card.getRank() == c.getRank()) {
            return true;
        }
    }
    return false;
}

string Player::showHand() const {
    //populate string with the cards in hand
    string ret;
    for(Card card : myHand) {
        ret += card.toString() + " ";
    }
    return ret;
}

string Player::showBooks() const {
    //populate string with the books in hand and return
    string ret;
    if (myBook.size() >= 2) {
        for (int i = 0; i < myBook.size() - 1; i+=2) {
            ret += " Pair: " + myBook[i].toString() + " " + myBook[i + 1].toString();
        }
    }
    return ret;
}

int Player::getBookSize() const {
    //book size is number of pairs
    return myBook.size() / 2;
}

int Player::getHandSize() const {
    //hand size is cards in hand
    return myHand.size();
}
bool Player::findPairsBookCards() {
    Card c1;
    Card c2;
    bool foundPair = false;

    //While pairs exist in hand, book the pairs
    while (checkHandForPair(c1,c2)){
        bookCards(c1, c2);
        removeCardFromHand(c1);
        removeCardFromHand(c2);
        foundPair = true;
    }
    return foundPair;
}
