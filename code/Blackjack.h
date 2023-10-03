#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Blackjack
{
  public:
    void blackjackGame();


  private:
    static int randomCard();
    static int calcTotal(const vector<int>& hand);
    static char toUpperCase(char choice);
    static bool isGameOver(int);
    static char anotherGame();

    // Hand dealt to the player
    vector<int> playerHand;

    // Hand dealt to the dealer
    vector<int> dealerHand;
};
