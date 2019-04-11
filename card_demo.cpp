// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);




int main() {

    //Open Log File for writing
    ofstream log;
    log.open("log.txt");
    if(!log.is_open()){
        cout << "Error opening log file" << endl;
        exit(-1);
    }
    log << "Starting Log..." << endl;

    //Create Player objects
    Player p1("Joe");
    Player p2("Jane");

    //Create Shuffled Deck of Cards
    Deck d;
    d.shuffle();

    //Deal cards to all Players
    log << "Dealing Cards..." << endl;
    int numCards = 7;
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);


    //Start Game
    log << "====================Starting Game=======================" << endl;
    log << p1.getName() <<" has : " << p1.showHand() << endl;
    log << p2.getName() <<" has : " << p2.showHand() << endl;

    //Set up player AI
    p1.initPlayerAI();
    p2.initPlayerAI();

    //Book pairs of cards that occured right after dealing
    if(p1.findPairsBookCards()){
        log << "Booked " << p1.getName() << "'s cards" << endl;
    }
    if(p2.findPairsBookCards()){
        log << "Booked " << p2.getName() << "'s cards" << endl;
    }

    int playerID = 0;
    Player &pA = p1;
    Player &pB = p2;
    int turnNum = 0;

    //Loop while there are less than d.SIZE/2 number of pairs of cards
    while (p1.getBookSize() + p2.getBookSize() < d.SIZE / 2){
        log << "--------------------------TURN " << turnNum << "------------------------------" << endl;
        Player temp = p1;
        pA = p2;
        pB = temp;
        log << pA.getName() <<"'s turn" << endl;

        log << pA.getName() << "'s Hand: " << pA.showHand() << endl << pB.getName() << "'s Hand: " << pB.showHand() << endl;
        log << pA.getName() << "'s # of books: " << pA.getBookSize() << " " << pB.getName() << "'s # of books: " << pB.getBookSize() << endl;
        if(pA.findPairsBookCards()){
            log << "Booked " << pA.getName() << "'s cards" << endl;
        }
        if(pA.getHandSize() == 0 && d.size() > 0){ //Deal Card
            Card dealtCard = d.dealCard();
            pA.addCard(dealtCard);
            log << pA.getName() << " draws " << dealtCard.toString() << endl;
        } else {
            Card choice = pA.chooseCardFromHand();
            log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;
            while (pB.sameRankInHand(choice) && (pB.getHandSize() > 0)) { //Player 1 keeps requesting cards until fail or player 2 runs out of cards
                Card removedCard = pB.removeCardWithSameRankFromHand(choice);
                pA.addCard(removedCard);
                log << pB.getName() << " gives " << pA.getName() << " " << removedCard.toString() << endl;
                if(pA.findPairsBookCards()){
                    log << "Booked " << pA.getName() << "'s cards" << endl;
                }
                choice = pA.chooseCardFromHand();
                if(pB.getHandSize() > 0){
                    log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;
                }
            }
            //Player 1 draws a card if there was a failed ask
            if (pB.getHandSize() > 0) {
                log << pB.getName() << " says Go Fish!" << endl;
                Card dealtCard = d.dealCard();
                pA.addCard(dealtCard);
                log << pA.getName() << " draws " << dealtCard.toString() << endl;
            }
            if(pA.findPairsBookCards()) {
                log << "Booked " << pA.getName() << "'s cards" << endl;
            }
        }
        playerID = ((playerID + 1) % 2);
        turnNum++;
    }
    log << "=================Game Over: ";
    if(p1.getBookSize() > p2.getBookSize()){
        log << p1.getName() << " wins with a score of " << p1.getBookSize() << " to " << p2.getBookSize();
    } else {
        log << p2.getName() << " wins with a score of " << p2.getBookSize() << " to " << p1.getBookSize();
    }
    log << "---------------------------" << endl;
    log << p1.getName() << " books: " << p1.showBooks() << endl;
    log << p2.getName() << " books: " << p1.showBooks() << endl;
     log << "=================" << endl;

    log.close();
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards) {
    for (int i = 0; i < numCards; i++)
        p.addCard(d.dealCard());
}



