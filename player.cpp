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
}

void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}


bool Player::checkHandForPair(Card &c1, Card &c2) {
    for(int i = 0; i < myHand.size(); i++) {
        for(int j = i + 1; j < myHand.size(); j++) {
            if(myHand[i] == myHand[j]) {
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
        if(*i == c) {
            myHand.erase(i);
            return c;
        }
    }
    return c;
}

bool Player::cardInHand(Card c) const {
    for(vector<Card>::iterator i = myHand.begin(); i != myHand.end(); i++) {
        if(*i == c) {
            return true;
        }
    }
    return false;
}

Card Player::chooseCardFromHand() const {

}

bool Player::sameRankInHand(Card c) const {
    for(std::vector<Card>::iterator i = myHand.begin(); i != myHand.end(); i++) {
        if((*i).getRank() == c.getRank()) {
            return true;
        }
    }
    return false;
}

string Player::showHand() const {
    string ret = "";
    for(vector<Card>::iterator i = myHand.begin(); i != myHand.end(); i++) {
        ret += (*i).toString() + "\n";
    }
}

string Player::showBooks() const {
    string ret = "";
    for(vector<Card>::iterator i = myBook.begin(); i != myHand.end() - 1; i++) {
        ret += "Pair: " +  (*i).toString() + " " + (i+1)->toString();
    }
}

int Player::getBookSize() const {
    return myBook.size() / 2;
}

int Player::getHandSize() const {
    return myHand.size();
}