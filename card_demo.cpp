// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.

//Names: Kenneth Mitra and Malav Shah

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
    log.open("gofish_results.txt");
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

    //Setup Loop variables
    Player &pA = p1; //Reference to a player
    Player &pB = p2; //Reference to a player
    int turnNum = 0;

    //Loop while not all pairs of cards have been formed
    while (p1.getBookSize() + p2.getBookSize() < Deck::SIZE / 2){

        log << "--------------------------TURN " << turnNum << "------------------------------" << endl;

        //Swap player A and player B (player A is the one currently taking a turn)
        Player temp = p1; //temp Player to swap p1 and p2
        pA = p2;
        pB = temp;
        log << pA.getName() <<"'s turn" << endl;

        //Print each player's hand and books to log before each turn
        log << pA.getName() << "'s Hand: " << pA.showHand() << endl << pB.getName() << "'s Hand: " << pB.showHand() << endl;
        log << pA.getName() << "'s # of books: " << pA.getBookSize() << " " << pB.getName() << "'s # of books: " << pB.getBookSize() << endl;

        //Book player A's cards if there are any pairs
        if(pA.findPairsBookCards()){
            log << "Booked " << pA.getName() << "'s cards" << endl;
        }

        //Player A draws a card if Player A has no cards in hand
        if(pA.getHandSize() == 0 && d.size() > 0){
            Card dealtCard = d.dealCard(); // Deal card from deck
            pA.addCard(dealtCard); // Add dealt card to hand
            log << pA.getName() << " draws " << dealtCard.toString() << endl;
        } else { //Player A's hand is not empty
            //Choose a card to ask for
            Card choice = pA.chooseCardFromHand();
            log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;

            /*If Player B has a card with the same rank as the card Player A asked for, then give it to Player A
             * Player A keeps asking for cards until player A makes a wrong guess or player B runs out of cards*/
            while (pB.sameRankInHand(choice) && (pB.getHandSize() > 0)) {

                Card removedCard = pB.removeCardWithSameRankFromHand(choice); //player B removes the card to give player A from his hand
                pA.addCard(removedCard); //player A adds the card player B gave to his/her deck
                log << pB.getName() << " gives " << pA.getName() << " " << removedCard.toString() << endl;

                //Book any pairs Player A has in his/her hand
                if(pA.findPairsBookCards()){
                    log << "Booked " << pA.getName() << "'s cards" << endl;
                }

                //Player A chooses another card to request
                choice = pA.chooseCardFromHand();
                if(pB.getHandSize() > 0){
                    log << pA.getName() << " asks " << pB.getName() << " for " << choice.rankString(choice.getRank()) << endl;
                }
            }

            //Player 1 draws a card if there was a failed ask (if loop terminated not due to player B running out of cards)
            if (pB.getHandSize() > 0) {
                log << pB.getName() << " says Go Fish!" << endl;
                Card dealtCard = d.dealCard(); //Deal card from deck
                pA.addCard(dealtCard); //Add dealt card to player A's hand
                log << pA.getName() << " draws " << dealtCard.toString() << endl;
            }

            //Book any pairs of cards that Player A might have
            if(pA.findPairsBookCards()) {
                log << "Booked " << pA.getName() << "'s cards" << endl;
            }
        }

        turnNum++;
    }

    //Game Over
    log << endl;
    log << "=================Game Over: ";

    //Determine winner by comparing book size
    if(p1.getBookSize() > p2.getBookSize()){
        log << p1.getName() << " wins with a score of " << p1.getBookSize() << " to " << p2.getBookSize();
    } else {
        log << p2.getName() << " wins with a score of " << p2.getBookSize() << " to " << p1.getBookSize();
    }
    log << "---------------------------" << endl;
    log << p1.getName() << " books: " << p1.showBooks() << endl;
    log << p2.getName() << " books: " << p1.showBooks() << endl;
     log << "=================" << endl;

    log.close(); //Close log file

    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards) {
    for (int i = 0; i < numCards; i++)
        p.addCard(d.dealCard());
}



