
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// ==========================================
// 4. CLASS DEFINITION
// ==========================================
class HangmanGame {
private:
    // 5. DATA STRUCTURES FROM THE STL
    std::vector<std::string> wordBank;
    std::string secretWord;
    std::set<char> guessedLetters; // Automatically handles unique elements
    int maxLives;
    int currentLives;

    // Helper method to pick a random word
    void pickRandomWord() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomIndex = std::rand() % wordBank.size();
        secretWord = wordBank[randomIndex];
    }

public:
    // Constructor initializes the game state
    HangmanGame() {
        maxLives = 6;
        currentLives = maxLives;

        // Populating the STL Vector
        wordBank = { "programming", "computer", "algorithm", "variable", "pointer", "function" };
        pickRandomWord();
    }

    // ==========================================
    // 3. FUNCTIONS (Class Methods)
    // ==========================================

    // Checks if the user won the game
    bool isGameWon() const {
        for (char letter : secretWord) {
            // If any letter in the secret word hasn't been guessed yet, they haven't won
            if (guessedLetters.find(letter) == guessedLetters.end()) {
                return false;
            }
        }
        return true;
    }

    // Checks if the user lost the game
    bool isGameLost() const {
        return currentLives <= 0;
    }

    // Displays the current hidden word state (e.g., c o _ p u _ e r)
    void displayWordState() const {
        std::cout << "Word: ";
        for (char letter : secretWord) {
            if (guessedLetters.find(letter) != guessedLetters.end()) {
                std::cout << letter << " ";
            }
            else {
                std::cout << "_ ";
            }
        }
        std::cout << "\n";
    }

    // Displays guessed letters so far
    void displayGuessedLetters() const {
        std::cout << "Guessed letters: ";
        for (char letter : guessedLetters) {
            std::cout << letter << " ";
        }
        std::cout << "\n";
    }

    // Processes a single letter guess
    void processGuess(char guess) {
        // Convert input to lowercase to prevent casing mismatches
        guess = std::tolower(guess);

        // 1. CONDITIONALS: Check if letter was already guessed
        if (guessedLetters.find(guess) != guessedLetters.end()) {
            std::cout << "\nYou already guessed '" << guess << "'! Try a different letter.\n";
            return;
        }

        // Insert into our STL Set tracking mechanism
        guessedLetters.insert(guess);

        // Conditional block checking if the guess is correct
        if (secretWord.find(guess) != std::string::npos) {
            std::cout << "\nGood guess! '" << guess << "' is in the word.\n";
        }
        else {
            std::cout << "\nSorry, '" << guess << "' is not in the word.\n";
            currentLives--; // Deduct a life
        }
    }

    // Getters for game rules
    int getRemainingLives() const { return currentLives; }
    std::string getSecretWord() const { return secretWord; }
};

// ==========================================
// MAIN ENTRY POINT
// ==========================================
int main() {
    std::cout << "===============================\n";
    std::cout << "   Welcome to C++ Hangman!     \n";
    std::cout << "===============================\n\n";

    // Instantiate our Class object
    HangmanGame game;

    // 2. LOOPS: Main game loop running until game conditions are satisfied
    while (!game.isGameWon() && !game.isGameLost()) {
        std::cout << "Remaining Lives: " << game.getRemainingLives() << "\n";
        game.displayWordState();
        game.displayGuessedLetters();

        std::cout << "Enter your guess: ";
        char userGuess;
        std::cin >> userGuess;

        game.processGuess(userGuess);
        std::cout << "---------------------------------\n";
    }

    // Final outcome evaluated through matching conditionals
    if (game.isGameWon()) {
        std::cout << "\nCongratulations! You guessed the word: " << game.getSecretWord() << "!\n";
    }
    else {
        std::cout << "\nGame Over! You ran out of lives. The word was: " << game.getSecretWord() << "\n";
    }

    return 0;
}