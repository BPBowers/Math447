//Brian Bowers | Math-447
//Final Project | Book Cipher Randomness Tester
#include <iostream>
#include <fstream>//File stream
#include "knuth.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    //First Version we just gonna open Beale Ciphertext 2
    KnuthFunc knuth;
    string filename;
    while(true){
        printf("Please enter the file-name and/or path you want the signature of:\n");
        cin >> filename;
        ifstream cipherText(filename);
        string outFile = "signatures/signature-";
        std::size_t pos = filename.find_last_of('/');
        pos++;
        outFile += filename.substr(pos);
        //outFile += ".txt";
        ofstream signature(outFile);
        knuth.testValidity(cipherText, signature);
        printf("Do you wish to perform another signature capture? Enter y to do so:\n");
        char answer;
        cin >> answer;
        if (answer == 'y')
            continue;
        else
        {
            printf("Goodbye!\n");
            break;
        }
    }
}
    /*
    printf("---------------\n");
    ifstream c1("CipherTexts/BealeC1.txt");
    knuth.testValidity(c1);
    printf("---------------\n");
    ifstream c3("CipherTexts/BealeC3.txt");
    knuth.testValidity(c3);

    printf("---------------\n");
    ifstream brian1("../CTGen/ciphertext.txt");
    knuth.testValidity(brian1);
    */
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

