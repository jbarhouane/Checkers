// Copyright [2023] <Jessica Barhouane>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Checkers.hpp"

sf::RectangleShape* GameBoard(void) {
  sf::Vector2f squareSize(SQUARE, SQUARE);
  sf::RectangleShape* board = new sf::RectangleShape[BOARD];

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      sf::RectangleShape square(squareSize);
      if (i % 2 == 0) {
        if ((i + j) % 2 == 0) {
          square.setFillColor(sf::Color::Red);
        } else {
          square.setFillColor(sf::Color::Black);
        }
      } else {
        if ((i + j) % 2 == 1) {
          square.setFillColor(sf::Color::Black);
        } else {
          square.setFillColor(sf::Color::Red);
        }
      }
      square.setPosition(sf::Vector2f(i * SQUARE + 15, j * SQUARE + 15));
      board[i * 8 + j] = square;
    }
  }
  return board;
}


void Checkers::setTextures(void) {
  red.loadFromFile("redpawn.png");
  black.loadFromFile("blackpawn.png");
  redKing.loadFromFile("redking.png");
  blackKing.loadFromFile("blackking.png");
}

void Checkers::initPieces(void) {
  sf::Sprite Red;
  Red.setTexture(red);
  sf::Sprite Black;
  Black.setTexture(black);
  redPieces = new sf::Sprite[PIECES];
  for (int i = 0; i < PIECES; i++) {
    redPieces[i] = Red;
  }
  blackPieces = new sf::Sprite[PIECES];
  for (int i = 0; i < PIECES; i++) {
    blackPieces[i] = Black;
  }
}

void Checkers::setupNewGame(void) {
  float xBlack = 79;
  float xRed = 15;
  float yBlack = 15;
  float yRed = 335;

  for (int i = 0; i < 3; i++) {
    if (i == 1) {
      xBlack = 15;
      yBlack = 79;
    } else if (i == 2) {
      xBlack = 79;
      yBlack = 143;
    }
    for (int j = 0; j < 4; j++) {
    blackPieces[i * 4 + j].setPosition(sf::Vector2f(xBlack, yBlack));
    xBlack += 128;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (i == 1) {
      xRed = 79;
      yRed = 399;
    } else if (i == 2) {
      xRed = 15;
      yRed = 463;
    }
    for (int j = 0; j < 4; j++) {
      redPieces[i * 4 + j].setPosition(sf::Vector2f(xRed, yRed));
      xRed += 128;
    }
  }
}

void Checkers::initDisplay(void) {
  displayScreen.setSize(sf::Vector2f(512, 85));
  sf::Color Screen(196, 171, 102);
  displayScreen.setPosition(sf::Vector2f(15, 542));
  displayScreen.setFillColor(Screen);
}

void Checkers::initCheckerHolders(void) {
    sf::Color color(196, 171, 102);
    capturedCheckers1.setPosition(sf::Vector2f(542, 15));
    capturedCheckers1.setSize(sf::Vector2f(85, 249));
    capturedCheckers1.setFillColor(color);
    capturedCheckers2.setPosition(sf::Vector2f(542, 278));
    capturedCheckers2.setSize(sf::Vector2f(85, 249));
    capturedCheckers2.setFillColor(color);
}

void Checkers::displayText(void) {
  if (!font.loadFromFile("constantia.ttf")) {
    throw;
  }
  player1.setFont(font);
  player1.setCharacterSize(24);
  player1.setFillColor(sf::Color::Black);
  player1.setPosition(sf::Vector2f(96, 565));
  player1.setStyle(sf::Text::Bold);
  player1.setString("Player 1");

  player2.setFont(font);
  player2.setCharacterSize(24);
  player2.setFillColor(sf::Color::Black);
  player2.setPosition(sf::Vector2f(359, 565));
  player2.setStyle(sf::Text::Bold);
  player2.setString("Player 2");
}

void Checkers::clickDetection(void) {
    sf::Vector2i mPos = sf::Mouse::getPosition(window);

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (!secondClick) {
                for (int i = 0; i < PIECES; i++) {
                    if (currentPlayer == 1 &&
                        blackPieces[i].getGlobalBounds().contains(mPos.x, mPos.y)) {
                        std::cout << "Black peice " << i << std::endl;
                        selectedIndex = i;
                        secondClick = true;
                    }
                    else if (currentPlayer == 2 &&
                        redPieces[i].getGlobalBounds().contains(mPos.x, mPos.y)) {
                        std::cout << "Red peice " << i << std::endl;
                        selectedIndex = i;
                        secondClick = true;
                    }
                }
            }
            else {
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        sf::Vector2i squarePosition = sf::Vector2i(i * SQUARE + 15, j * SQUARE + 15);
                        sf::IntRect squareBoundary(squarePosition.x, squarePosition.y, 64, 64);

                        if (squareBoundary.contains(mPos.x, mPos.y)) {
                            if (currentPlayer == 1) {
                                if (isLegal(true, true, sf::Vector2i(blackPieces[selectedIndex].getPosition().x,
                                    blackPieces[selectedIndex].getPosition().y), squarePosition)) {
                                    moveChecker(blackPieces[selectedIndex], sf::Vector2i(blackPieces[selectedIndex].getPosition().x, 
                                                blackPieces[selectedIndex].getPosition().y), squarePosition);
                                }
                            }
                            else if (currentPlayer == 2) {
                                if (isLegal(false, true, sf::Vector2i(redPieces[selectedIndex].getPosition().x,
                                    redPieces[selectedIndex].getPosition().y), squarePosition)) {
                                    moveChecker(redPieces[selectedIndex], sf::Vector2i(redPieces[selectedIndex].getPosition().x, 
                                                redPieces[selectedIndex].getPosition().y), squarePosition);
                                }
                            }
                            currentPlayer = 3 - currentPlayer;
                            if (currentPlayer == 1) {
                                box.setPosition(66, 555);
                            }
                            else {
                                box.setPosition(329, 555);
                            }
                            secondClick = false;
                            selectedIndex = -1;
                        }
                    }
                }
            }
        }
    }
}

void Checkers::moveChecker(sf::Sprite& checker, sf::Vector2i posOne, sf::Vector2i posTwo) {
    checker.setPosition(posTwo.x, posTwo.y);
    std::cout << posTwo.x << " " << posTwo.y << " checker relocation in progress..." << std::endl;
    if (isJump(posOne, posTwo)) {
        captureOpponent(posOne, posTwo);
    }
    kingMe(checker);
}
bool Checkers::isJump(sf::Vector2i posOne, sf::Vector2i posTwo) {
    if (abs(posOne.x - posTwo.x) == 2 * SQUARE && abs(posOne.y - posTwo.y) == 2 * SQUARE) {
        sf::Vector2i opponent((posOne.x + posTwo.x) / 2, (posOne.y + posTwo.y) / 2);
        if (currentPlayer == 1) {
            for (int i = 0; i < PIECES; i++) {
                if (redPieces[i].getGlobalBounds().contains(opponent.x, opponent.y)) {
                    return true;
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < PIECES; i++) {
                if (blackPieces[i].getGlobalBounds().contains(opponent.x, opponent.y)) {
                    return true;
                    break;
                }
            }
        }
    }
    return false;
}


void Checkers::captureOpponent(sf::Vector2i posOne, sf::Vector2i posTwo) {
    sf::Vector2i middlePosition((posOne.x + posTwo.x) / 2, (posOne.y + posTwo.y) / 2);

    if (currentPlayer == 1) {
        for (int i = 0; i < PIECES; i++) {
            if (redPieces[i].getGlobalBounds().contains(middlePosition.x, middlePosition.y)) {
                redPieces[i].setPosition(552, 25);
            }
        }
    }
    else {
        for (int i = 0; i < PIECES; i++) {
            if (blackPieces[i].getGlobalBounds().contains(middlePosition.x, middlePosition.y)) {
                blackPieces[i].setPosition(552, 25);
            }
        }
    }
}


bool Checkers::isLegal(bool isBlack, bool isPawn, sf::Vector2i posOne, sf::Vector2i posTwo) {
    if (isBlack && isPawn && abs(posOne.x - posTwo.x) == abs(posOne.y - posTwo.y) && posOne.y < posTwo.y) {
        return true;
    }
    if (!isBlack && isPawn && abs(posOne.x - posTwo.x) == abs(posOne.y - posTwo.y) && posOne.y > posTwo.y) {
        return true;
    }
    return false;
}

void Checkers::kingMe(sf::Sprite& checker) {
    if (currentPlayer == 1 && checker.getPosition().y == (SQUARE * (ROWS - 1) + 15)) {
        checker.setTexture(blackKing);
    }
    if (currentPlayer == 2 && checker.getPosition().y == 15) {
        checker.setTexture(redKing);
    }
}

void Checkers::playerIndicater(void) {
  currentPlayer = 1;
  box.setSize(sf::Vector2f(150, 60));
  box.setFillColor(sf::Color::Transparent);
  box.setOutlineColor(sf::Color::Red);
  box.setOutlineThickness(3);
  box.setPosition(66, 555);
}

void Checkers::checkerIndex(sf::Vector2i& position) {
  for (int i = 0; i < PIECES; i++) {
    if (redPieces[i].getGlobalBounds().contains(position.x, position.y)) {
      std::cout << "Red piece at position " << i << " detected!" << std::endl;
    }
    if (blackPieces[i].getGlobalBounds().contains(position.x, position.y)) {
      std::cout << "Black piece at position " << i << " detected!" << std::endl;
    }
  }
}

void Checkers::run(void) {
  initDisplay();
  initCheckerHolders();
  playerIndicater();
  displayText();
  setTextures();
  initPieces();
  setupNewGame();
}

