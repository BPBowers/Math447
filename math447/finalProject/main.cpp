//Brian Bowers | Math-447
//Final Project | Book Cipher Randomness Tester
#include <iostream>
#include <fstream>//File stream
#include "knuth.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    //First Version we just gonna open Beale Ciphertext 2
    ifstream cipherText("CipherTexts/BealeC2.txt");
    KnuthFunc knuth;
    knuth.testValidity(cipherText);
    
    printf("---------------\n");
    ifstream c1("CipherTexts/BealeC1.txt");
    knuth.testValidity(c1);
    printf("---------------\n");
    ifstream c3("CipherTexts/BealeC3.txt");
    knuth.testValidity(c3);
    
    /*
    //After Tests Run, open SFML window
    sf::RenderWindow window(sf::VideoMode(200, 200), "Graph Display");
    sf::CircleShape shape(33.f);
    //sf::Vector2f theSize(50, 50);
    //sf::RectangleShape shape(theSize);
    
    //shape.move(1,0);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(0, (window.getSize().y/4));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(shape);
        window.display();
    }
    */
}

