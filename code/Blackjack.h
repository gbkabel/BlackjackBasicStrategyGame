#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Blackjack
{
public:
    void blackjackGame(); // Game engine


private:
    void dealCards(vector<int>& hand);  // Deals Cards to both player and Dealer
    static int randomCard();           // Gets a random card that is added to hand
    static int calcTotal(const vector<int>& hand);  // Totals a hand up
    int checkAces(const vector<int>& hand, int& numAces);
    bool isPair(vector<int>& hand);             // Checks if any pairs 
    static char toUpperCase(char choice);           // Capitalizes characters to cross examine
    void playerHit(vector<int>& hand, int& total);  // Hit function for the player
    void playerStand(vector<int>& hand, int& total); // Stand function for the player/Dealers hit function
    void checkStrategy(const int playerHand, const int dealerHand, const int numAces,vector<int>& hand); // Implements Basic Black Strategy
    static bool isGameOver(int);        // Checks if the game is over
    static char anotherGame();          // Checks if the user wants to play again

    vector<int> playerHand;    // Hand dealt to the player
    vector<int> dealerHand;    // Hand dealt to the dealer
    int numAces;               //Keeps track of Aces for soft totals
};
