//============================================================================
// Name        : CaesarSolver.cpp
// Author      : AltF4
// Version     :
// Copyright   : GNU GPLv3
// Description : Decrypts a string of hex code in ASCII from a Caesar cipher
//============================================================================

#include "CaesarSolver.h"
#include <iostream>
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	int c;
	int key;
	string inputPath, outputPath;

	bool isKeySet = false, isOutputSet = false, isInputSet = false;

	while ((c = getopt (argc, argv, ":i:o:k:")) != -1)
	{
		switch (c)
		{
			case 'i':
			{
				inputPath.assign(optarg);
				break;
			}
			case 'o':
			{
				isOutputSet = true;
				outputPath.assign(optarg);
				break;
			}
			case 'k':
			{
				isKeySet = true;
				int tempArg = atoi(optarg);
				if(tempArg > 0)
				{
					key = tempArg;
				}
				else
				{
					cerr << "You entered an invalid key value\n";
					cout << Usage();
					return EXIT_FAILURE;
				}
				if(tempArg > 255)
				{
					cerr << "Key value is too large. Must be less than 256\n";
					cout << Usage();
					return EXIT_FAILURE;
				}
				break;
			}
			case '?':
			{
				if (isprint (optopt))
				{
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				}
				else
				{
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				}
				cout << Usage();
				return EXIT_FAILURE;

			}
			default:
			{
				cout << Usage();
				return EXIT_FAILURE;
			}
		}
	}

	if(!isKeySet)
	{

	}
	if(!isOutputSet)
	{

	}
	if(!isInputSet)
	{
		cerr << "ERROR: You must enter an input path -i\n";
		cout << Usage();
		return EXIT_FAILURE;
	}

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return EXIT_SUCCESS;
}

//Prints usage tips when you screw up the command line arguments
string Usage()
{
	string outputString = "Usage: CaesarSolver -i inputfile [-o outputFile] [-k key]\n";
	outputString += "\tRead hex digits represented in ASCII from the provided file in -i\n";
	outputString += "\tDecrypt it using all possible 255 keys. when -k is given, only test key\n";
	outputString += "\tOutput to given file, or stdout if none is given\n";

	return outputString;
}
