/*
 *  Main.cpp
 *  Elliot Friesen
 *  11/14/2024
 *
 *  CS 15 Project Zap
 *
 *  Main file for Zap, essentially it is taking in input
 * and calling the necessary functions within the game
 * to perform the right actions
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "HuffmanCoder.h"

using namespace std;

/*
 * name:      errCommands
 * purpose:   cerr if input commands are not valid
 * arguments: none
 * returns:   none
 * effects:   cerrs and exits program
 */
void errCommands() 
{
    cerr << "Usage: ./zap [zap | unzap] inputFile outputFile";
    cerr << endl;
    exit(EXIT_FAILURE);
}

 /*
 * name:      main
 * purpose:   initialize a HuffmanCoder instance
 * arguments: int, char []
 * returns:   int
 * effects:   may report errors, calls functions in HuffmanCoder.h
 */
int main(int argc, char *argv[])
{
        if (argc != 4) { // check valid arguments
            errCommands();
        }
        HuffmanCoder hc;
        if (string(argv[1]) == "zap") {
            hc.encoder(argv[2], argv[3]);
        }
        else if (string(argv[1]) == "unzap") {
            hc.decoder(argv[2], argv[3]);
        }
        else {
            errCommands();
        }
        
        return 0;
}

