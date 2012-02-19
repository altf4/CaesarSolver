//============================================================================
// Name        : CaesarSolver.h
// Author      : AltF4
// Version     :
// Copyright   : GNU GPLv3
// Description : Decrypts a string of hex code in ASCII from a Caesar cipher
//============================================================================

#ifndef CAESARSOLVER_H_
#define CAESARSOLVER_H_

#include <string>
#include <stdlib.h>

using namespace std;

//Prints usage tips when you screw up the command line arguments
string Usage();

char Decrypt(char inChar, uint key);

#endif /* CAESARSOLVER_H_ */
