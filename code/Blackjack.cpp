#include "Blackjack.h"


void Blackjack::blackjackGame()
{
    srand(time(nullptr));   // Random Number Generator

    cout << "Work In Progress Blackjack Basic Strategy!" << endl;
    char playAgain = 'Y';

    while (playAgain == 'Y') 
    {
        dealCards(playerHand);
        dealCards(dealerHand);                      // Cards dealt to both plaer and dealer
        int playerTotal = calcTotal(playerHand);
        int dealerTotal = calcTotal(dealerHand);    // Hands are totaled

        cout << "Your Hand: " << playerHand[0] << " and " << playerHand[1] << " = " << playerTotal << endl;
        cout << "Dealer's face-up card: " << dealerHand[0] << endl;

        // Playing the game
        while (true) {
            if (isGameOver(playerTotal)) break; // Checks for Win/Loss

            char choice;
            cout << "Do you want to hit (H) or stand (S)? ";
            cin >> choice;
            choice = toUpperCase(choice);           // Takes in user's choice then capitalizes it

            checkAces(playerHand, numAces);
            if (choice == 'H') {
                checkStrategy(playerTotal, dealerTotal, numAces, playerHand);
                playerHit(playerHand, playerTotal);
                if (calcTotal(playerHand) > 21) {
                    cout << "Bust! You lose!" << endl;
                    break;
                }                    
            }
            else if (choice == 'S') {  
                checkStrategy(playerTotal, dealerTotal, numAces, playerHand);
                playerStand(dealerHand, dealerTotal);
                cout << "(" << dealerTotal << ")" << endl;

                // Declaring a winner
                if (dealerTotal > 21 || playerTotal > dealerTotal) {
                    cout << "You win!" << endl;
                }
                else if (playerTotal < dealerTotal) {
                    cout << "Dealer wins!" << endl;
                }
                else {
                    cout << "It's a tie!" << endl;
                }
                break;
            }       
        }
        playAgain = anotherGame();
    }
}



void Blackjack::dealCards(vector<int>& hand)
{
    // Clear the previous hand
    hand.clear();

    // Deal two cards
    hand.push_back(randomCard());
    hand.push_back(randomCard());
}

/**
 *
 * @return
 */
int Blackjack::randomCard()
{
    return rand() % 11 + 1;
}


/**
 *
 * @param hand
 * @return
 */
int Blackjack::calcTotal(const vector<int>& hand)
{
    int total = 0;
    int numAces = 0;

    for (int card : hand)
    {
        if (card == 11)
        {
            numAces++;
        }
        total += card;
    }

    while (total > 21 && numAces > 0)
    {
        total -= 10;
        numAces--;
    }

    return total;
}

int Blackjack::checkAces(const vector<int>& hand, int& numAces)
{
    numAces = 0;

    for (int card : hand)
    {
        if (card == 11)
        {
            numAces++;
        }
    }
    return numAces;
}

bool Blackjack::isPair(vector<int>& hand)
{
    if (hand.size() != 2) {
        return false;
    }
    return hand[0] == hand[1];
}


/**
 *
 * @param choice
 * @return
 */
char Blackjack::toUpperCase(char choice)
{
    if (choice >= 'a' && choice <= 'z')
    {
        return choice - ('a' - 'A');
    }
    else
    {
        // If the character is not a lowercase letter, return it unchanged.
        return choice;
    }
}

void Blackjack::playerHit(vector<int>& hand, int& total)
{
    hand.push_back(randomCard());
    cout << "You drew: " << hand.back() << endl;
    total = calcTotal(hand);
    cout << "New Total: " << total << endl;
}

void Blackjack::playerStand(vector<int>& hand, int& total)
{
    // Load up the dealer cards
    while (total < 17) {
        hand.push_back(randomCard());
        total = calcTotal(dealerHand);
    }

    // Output dealer hand
    cout << "Dealer's hand: ";

    for (int card : hand) {
        cout << card << " ";
    }

    cout << "(" << total << ")" << endl;

}

void Blackjack::checkStrategy(const int playerTotal, const int dealerTotal, const int numAces, vector<int>& hand)
{
    // Hard Totals
    if (playerTotal <= 8) {
        cout << "You should always hit on anything 8 and below\n";
    }
    if (playerTotal == 9 && (dealerTotal >= 3 && dealerTotal <= 6)) {
        cout << "When you have a 9, Double on the dealers 3 - 6\n";
    }
    else if (playerTotal == 9) {
        cout << "Hit on 9 when the dealer has a 2 or 7 and Up\n";
    }
    if (playerTotal == 10 && (dealerTotal >= 2 && dealerTotal <= 9)) {
        cout << "With a 10, Double on 2 - 9\n";
    }
    else if (playerTotal == 10) {
        cout << "Hit on a 10 when dealer has 10 or an Ace\n";
    }
    if (playerTotal == 11) {
        cout << "Always Double on an 11\n";
    }
    if (playerTotal == 12 && (dealerTotal <= 3 || dealerTotal >= 7)) {
        cout << "A 12 requires you to Hit on a 2,3,7,8,9,10,A\n";
    }
    else if (playerTotal == 12) {
        cout << "Stand on a 12 when the dealer has a 4,5, or 6\n";
    }
    if ((playerTotal >= 13 && playerTotal <= 16) && dealerTotal <= 6) {
        cout << "Stand on 13,14,15,16 when the dealer has anything 6 and under\n";
    }
    else if (playerTotal >= 13 && playerTotal <= 16) {
        cout << "Hit on 13 - 16 when the dealer has a 7 or higher\n";
    }
    if (playerTotal == 17) {
        cout << "Stand on 17 and Up\n";
    }

    // Soft Totals
    if ((numAces == 1 && (playerTotal == 13 || playerTotal == 14)) && (dealerTotal >= 5 && dealerTotal <=6)) {
        cout << "If allowed, Double on soft 13 when dealer has 5 or 6\n";
    }
    else if (numAces == 1 && (playerTotal == 13 || playerTotal == 14)) {
        cout << "Hit on soft 13 when the dealer has a 2,3,4,7,8,9,10.A\n";
    }
    if ((numAces == 1 && (playerTotal == 15 || playerTotal == 16)) && (dealerTotal >= 4 && dealerTotal <= 6)) {
        cout << "Double on soft 15 and 16 when dealer has 4,5, or 6\n";
    }
    else if (numAces == 1 && (playerTotal == 15 || playerTotal == 16)) {
        cout << "With a soft 15 or 16, Hit when dealer has 2,3,7,8,9,10,A\n";
    }
    if ((numAces == 1 && playerTotal == 17) && (dealerTotal >= 3 && dealerTotal <= 6)) {
        cout << "Double on soft 17 when dealer has 3,4,5, and 6\n";
    }
    else if (numAces == 1 && playerTotal == 17) {
        cout << "Hit on Soft 17 when dealer has 2,7,8,9,10,A\n";
    }
    if ((numAces == 1 && playerTotal == 17) && (dealerTotal >= 3 && dealerTotal <= 6)) {
        cout << "Double on soft 17 when dealer has 3,4,5, and 6\n";
    }
    if ((numAces == 1 && playerTotal == 18) && dealerTotal <= 6) {
        cout << "Double on soft 18 against 6 and below, Otherwise stand\n";
    }
    else if ((numAces == 1 && playerTotal == 18) && (dealerTotal >= 7 && dealerTotal <= 8)) {
        cout << "Stand on soft 18 when dealer has 7 or 8\n";
    }
    else if ((numAces == 1 && playerTotal == 18) && dealerTotal >= 9) {
        cout << "Hit on soft 18 against 9 and Up\n";
    }
    if ((numAces == 1 && playerTotal == 19) && dealerTotal == 6) {
        cout << "Double on soft 19 only against 6, if not then stand\n";
    }
    else if ((numAces == 1 && playerTotal == 19) && (dealerTotal <= 5 || dealerTotal >= 7)) {
        cout << "Stand on soft 19 on eveything except a 6\n";
    }
    if (numAces == 1 && playerTotal == 19) {
        cout << "Stand on soft 20 no matter what\n";
    }

    // Pair Splitting
    int pairNumber = 0;
    if (isPair(hand))
    {
        pairNumber = hand[0];
        if ((pairNumber == 2 || pairNumber == 3) && dealerTotal <= 3) {
            cout << "Split 2's and 3's only if Double After Split is allowed when dealer has 2 or 3\n";
        }
        else if ((pairNumber == 2 || pairNumber == 3) && (dealerTotal >= 4 && dealerTotal <= 7)) {
            cout << "Split 2's and 3's against dealers 4 - 7\n";
        }
        else if ((pairNumber == 2 || pairNumber == 3) && dealerTotal >= 8) {
            cout << "Dont split 2's or 3's against 8,9,10,A\n";
        }
        if (pairNumber == 4 && (dealerTotal <= 4 || dealerTotal >= 7)) {
            cout << "With a pair of 4's, don't split on 2,3,4,7,8,9,10,A\n";
        }
        else if (pairNumber == 4 && (dealerTotal >= 5 &&  dealerTotal <= 6)) {
            cout << "Split 4's against 5 and 6 if double after split is allowed\n";
        }
        if (pairNumber == 5) {
            cout << "Never Split a pair of 5's\n";
        }
        if (pairNumber == 6 && dealerTotal == 2) {
            cout << "Split 6's on dealers 2 if you can double after the split\n";
        }
        else if (pairNumber == 6 && (dealerTotal >= 3 && dealerTotal <= 6)) {
            cout << "Split 6's when dealer has 3 - 7\n";
        }
        else if (pairNumber == 6 && dealerTotal >= 7) {
            cout << "Do not split 6's against a 7 or higher\n";
        }
        if (pairNumber == 7 && dealerTotal <= 7) {
            cout << "Split 7's against dealers 7 and under\n";
        }
        else if (pairNumber == 7 && dealerTotal >= 8) {
            cout << "Do not split 7's against 8,9,10,A\n";
        }
        if (pairNumber == 8) {
            cout << "Always split 8's\n";
        }
        if (pairNumber == 9 && (dealerTotal <= 6 || dealerTotal >= 8)) {
            cout << "Split 9's on everything except 7\n";
        }
        else if (pairNumber == 9 && dealerTotal == 7) {
            cout << "Dont split 9's against 7\n";
        }
        if (pairNumber == 10) {
            cout << "Pair of 10's is never split\n";
        }
        if (pairNumber == 11) {
            cout << "Always Split Aces\n";
        }
    }
}

/**
 * Determine if the game is over.
 *
 * @param score is the payer's score *
 * @return Return true if the player wins, otherwise false.
 */
bool Blackjack::isGameOver(int score)
{
    if (score == 21)
    {
        cout << "Blackjack! You win!" << endl;
        return true;
    }
    else if (score > 21)
    {
        cout << "Bust! You lose!" << endl;
        return true;
    }

    return false;
}


/**
 * Prompt user to play another hand.
 * @return Returns a 'Y' or 'N' response.
 */
char Blackjack::anotherGame()
{
    char response;
    bool done = false;

    cout << "Do you want to play again? (Y/N): ";

    while (!done) {
        // Get the user response
        cin >> response;
        response = toUpperCase(response);
        if (response == 'Y' || response == 'N') {
            done = true;
        }
        else {
            cout << "\n\nPlease enter Y or N.\n\n";
        }
    }

    return response;
}
