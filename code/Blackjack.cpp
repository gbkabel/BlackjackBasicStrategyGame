#include "Blackjack.h"


void Blackjack::blackjackGame()
{
    srand(time(nullptr));

    cout << "Work In Progress Blackjack Basic Strategy!" << endl;
    char playAgain = 'Y';

    // True if play underway. This will become false when the player
    // no longer wants to play.

    while (playAgain == 'Y')
    {
        // Clear the previous player hand
        playerHand.clear();

        // Deal two card to the player
        playerHand.push_back(randomCard());
        playerHand.push_back(randomCard());

        // Clear the previous dealer hand
        dealerHand.clear();

        // Deal two card to the dealer
        dealerHand.push_back(randomCard());
        dealerHand.push_back(randomCard());

        int playerTotal = calcTotal(playerHand);

        cout << "Your Hand: " << playerHand[0] << " and " << playerHand[1] << " = "  << playerTotal << endl;
        cout << "Dealer's face-up card: " << dealerHand[0] << endl;

        // Playing the game
        while (true) {
            //int playerTotal = calcTotal(playerHand);
            if (Blackjack::isGameOver(playerTotal)) break;

            char choice;
            cout << "Do you want to hit (H) or stand (S)? ";
            cin >> choice;
            choice = toUpperCase(choice);

            if (choice == 'H') {
                playerHand.push_back(randomCard());
                cout << "You drew: " << playerHand.back() << endl;
                playerTotal = calcTotal(playerHand);
                cout << "New Total: " << playerTotal << endl;

                if (calcTotal(playerHand) > 21) {
                    cout << "Bust! You lose!" << endl;
                    break;
                }
            } else if (choice == 'S') {
                int dealerTotal = calcTotal(dealerHand);

                // Load up the dealer cards
                while (dealerTotal < 17) {
                    dealerHand.push_back(randomCard());
                    dealerTotal = calcTotal(dealerHand);
                }

                // Output dealer hand
                cout << "Dealer's hand: ";

                for (int card: dealerHand) {
                    cout << card << " ";
                }

                cout << "(" << dealerTotal << ")" << endl;

                // Declaring a winner
                if (dealerTotal > 21 || playerTotal > dealerTotal) {
                    cout << "You win!" << endl;
                } else if (playerTotal < dealerTotal) {
                    cout << "Dealer wins!" << endl;
                } else {
                    cout << "It's a tie!" << endl;
                }
                break;
            }
        }

        playAgain = anotherGame();
    }
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

    while (! done) {
        // Get the user response
        cin >> response;
        response = toUpperCase(response);
        if (response == 'Y' || response == 'N') {
            done = true;
        } else {
            cout << "\n\nPlease enter Y or N.\n\n";
        }
    }

    return response;
}
