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
    //Deal Cards
    log << "Dealing Cards..." << endl;
    int numCards = 5;

    Player p1("Joe");
    Player p2("Jane");

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);

    cout << p1.getName() <<" has : \n" << p1.showHand() << endl;
    cout << p2.getName() <<" has : \n" << p2.showHand() << endl;

    log << p1.getName() <<" has : \n" << p1.showHand() << endl;
    log << p2.getName() <<" has : \n" << p2.showHand() << endl;

    p1.initPlayerAI();
    p2.initPlayerAI();

    log << "Starting Game..." << endl;
    int playerID = 0;
    Player &pA = p1;
    Player &pB = p2;
    while (p1.getBookSize() + p2.getBookSize() < d.SIZE / 2){
        log << "--------------------------------------------------------------" << endl;
        /*
        if(playerID == 0){
            Player temp = pB;
            pB = pA;
            pA = temp;
            log << "Player 1's turn" << endl;
        } else {
         */
            Player temp = p1;
            pA = p2;
            pB = temp;
            log << "Player " << pA.getName() <<"'s turn" << endl;
        //}

        //Player 1 turn
        log << "Player " << pA.getName() << "'s Hand: " << pA.showHand() << endl << " Player " << pB.getName() << "'s Hand: " << pB.showHand() << endl;
        log << "Booking Cards for player " << pA.getName() << endl;
        pA.findPairsBookCards();
        log << "Player " << pA.getName() << "'s Hand after booking: " << pA.showHand() << endl;
        if(pA.getHandSize() == 0 && d.size() > 0){
            log << "Dealing card to Player " << pA.getName() << endl;
            pA.addCard(d.dealCard());
            log << "Player " << pA.getName() << "'s Hand after dealing: " << pA.showHand() << endl;
        } else {
            Card choice = pA.chooseCardFromHand();
            log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;
            while (pB.sameRankInHand(choice) &&
                   (pB.getHandSize() > 0)) { //Player 1 keeps requesting cards until fail or player 2 runs out of cards
                Card removedCard = pB.removeCardWithSameRankFromHand(choice);
                pA.addCard(removedCard);
                pA.findPairsBookCards();
                log << pB.getName() << " gives " << pA.getName() << " " << choice.rankString(choice.getRank()) << endl;
                choice = pA.chooseCardFromHand();
                log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;
            }
            //Player 1 draws a card if there was a failed ask
            if (pB.getHandSize() > 0) { //TODO make && d.size()>0
                log << pB.getName() << " says Go Fish!" << endl;
                log << "Dealing card to Player " << pA.getName() << endl;
                pA.addCard(d.dealCard());
                log << "Player " << pA.getName() << "'s Hand after dealing: " << pA.showHand() << endl;
            }
            log << "Booking Cards for player " << pA.getName() << endl;
            pA.findPairsBookCards();
            log << "Player " << pA.getName() << "'s Hand after booking: " << pA.showHand() << endl;
        }
        playerID = ((playerID + 1) % 2);
    }


    log.close();
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards) {
    for (int i = 0; i < numCards; i++)
        p.addCard(d.dealCard());
}



