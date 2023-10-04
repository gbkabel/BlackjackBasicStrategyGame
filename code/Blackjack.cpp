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

            if (choice == 'H') {
                playerHit(playerHand, playerTotal);
                if (calcTotal(playerHand) > 21) {
                    cout << "Bust! You lose!" << endl;
                    break;
                }                    
            }
            else if (choice == 'S') {         
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
