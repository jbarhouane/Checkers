// Copyright [2023] <Jessica Barhouane>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Board size / piece count variables 
#define WIDTH 642
#define HEIGHT 642
#define SQUARE 64
#define ROWS 8
#define COLS 8
#define BOARD (ROWS * COLS)
#define PIECES 12

// Drawing checker board play area
sf::RectangleShape* GameBoard(void);

class Checkers : public sf::Drawable {
 public:
  // Constructors/Destructors
  Checkers(sf::RenderWindow& win) : window(win) {}
  ~Checkers() {
    delete[] redPieces;
    delete[] blackPieces;
  }

  // Board feature functions
  void initDisplay(void);
  void initCheckerHolders(void);
  void initCapturedRed(void);
  void initCapturedBlack(void);
  void displayText(void);
  
  // Initial checkers setup functions
  void initPieces(void);
  void setTextures(void);
  void setupNewGame(void);

  // Player Interaction functions
  void setIndex(int i);
  void clickDetection(void);
  void playerIndicater(void);
  void checkerIndex(sf::Vector2i& position);
  
  // Rules and Gameplay functions
  void moveChecker(sf::Sprite& checker, sf::Vector2i posOne, sf::Vector2i posTwo);
  bool isLegal(bool isBlack, bool isPawn, sf::Vector2i posOne, sf::Vector2i posTwo);
  bool isJump(sf::Vector2i posOne, sf::Vector2i posTwo);
  void captureOpponent(sf::Vector2i posOne, sf::Vector2i posTwo);
  void kingMe(sf::Sprite& checker);
  void run(void);

 private:
  // Game Play Variables
  sf::Sprite* redPieces;
  sf::Sprite* blackPieces;
  sf::Texture black;
  sf::Texture blackKing;
  sf::Texture red;
  sf::Texture redKing;

  // Board Feature Variables
  sf::Font font;
  sf::Text player1;
  sf::Text player2;
  sf::RectangleShape capturedCheckers1;
  sf::RectangleShape capturedCheckers2;
  sf::RectangleShape displayScreen;
  sf::RectangleShape box;

  // Game Play Variables
  int currentPlayer;
  int selectedPiece;
  int currIndex;
  bool pieceClicked;
  bool secondClick = false;
  int selectedIndex = -1;

  // Passed in window
  sf::RenderWindow& window;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(displayScreen, states);
    target.draw(player1, states);
    target.draw(player2, states);
    target.draw(box, states);
    target.draw(capturedCheckers1, states);
    target.draw(capturedCheckers2, states);
    for (int i = 0; i < PIECES; i++) {
      target.draw(redPieces[i], states);
    }
    for (int i = 0; i < PIECES; i++) {
      target.draw(blackPieces[i], states);
    }
  }
};

