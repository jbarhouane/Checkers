// Copyright [2023] <Jessica Barhouane>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Checkers.hpp"

int main(int argc, char* argv[]) {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Welcome to Checkers");
  sf::RectangleShape* gameBoard = GameBoard();
  sf::Color Border(100, 35, 35);
  
  Checkers game(window);
  
  game.run();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    
    game.clickDetection();
    window.clear(Border);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        window.draw(gameBoard[i * 8 + j]);
      }
    }
    window.draw(game);
    window.display();
  }
return 0;
}


