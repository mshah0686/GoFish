//Names: Kenneth Mitra and Malav Shah
#include "card.h"


Card::Card() {
    myRank = 1;
    mySuit = spades;
}

Card::Card(int rank, Suit s) {
    myRank = rank;
    mySuit = s;
}

string Card::toString() const {
    return rankString(myRank) + suitString(mySuit);
}

string Card::rankString(int r) const {
    //Convert card rank to string representation
    string rankString;

    //Special cases are A, J, Q, K. else, convert card rank number to string
    switch (r) {
        case 1:
            rankString = "A";
            break;
        case 11:
            rankString = "J";
            break;
        case 12:
            rankString = "Q";
            break;
        case 13:
            rankString = "K";
            break;
        default:
            rankString = to_string(r);
            break;
    }
    return rankString;
}

string Card::suitString(Card::Suit s) const {
    //Convert card suit to string representation

    string suitString;
    switch (s) {
        case spades:
            suitString = "s";
                    break;
        case clubs:
            suitString = "c";
            break;
        case diamonds:
            suitString = "d";
            break;
        case hearts:
            suitString = "h";
            break;
        default:
            cout << "ERROR" << endl;
            exit(-1);
    }

    return suitString;
}

bool Card::operator==(const Card &rhs) const {
    //Two cards are equal if their text representations match
    return (toString() == rhs.toString());
}

bool Card::operator!=(const Card &rhs) const {
    //Two cards are not equal if they are not equal to each other
    return !(*this == rhs);
}

int Card::getRank() const {
    return myRank;
}

bool Card::sameSuitAs(const Card &c) const {
    //Check if a card has the same suit as another card
    return mySuit == c.mySuit;
}

ostream& Card::operator<<(ostream &out) {
    //Write card's string representation to stream
    out << this->toString() << endl;
    return out;
}