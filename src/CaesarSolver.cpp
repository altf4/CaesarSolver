//============================================================================
// Name        : CaesarSolver.cpp
// Author      : AltF4
// Version     :
// Copyright   : GNU GPLv3
// Description : Decrypts a string of hex code in ASCII from a Caesar cipher
//============================================================================

#include "CaesarSolver.h"

#include <iostream>
#include <fstream>
#include "stdio.h"
#include <vector>

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
				isInputSet = true;
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

	//Formatted ciphertext
	//IE: It has the ASCII characters "3a" to repreesent a colon ':'
	string fm_ciphertext;

	ifstream myfile(inputPath.c_str());
	if(myfile.is_open())
	{
		//Only considers the first line
		if( myfile.good() )
		{
			getline(myfile, fm_ciphertext);
		}
		myfile.close();
	}
	else
	{
		cerr << "ERROR: Could not open input file\n";
	}

	//If there's an odd number of characters, then this is malformatted
	if((fm_ciphertext.size() % 2) == 1)
	{
		cerr << "ERROR: Input has an odd number of characters, and cannot be ASCII hex\n";
		return EXIT_FAILURE;
	}

	//Unformatted ciphertext
	//IE: Contains the byte value of 3a to represent the colon character
	vector<char> uf_ciphertext;

	//Reserve what we should expect in terms of length
	uf_ciphertext.reserve(fm_ciphertext.size()/2);

	//For each pair of input characters (IE: each byte of input)
	for(uint i = 0; i < fm_ciphertext.size(); i+=2)
	{
		string charPair;
		charPair += fm_ciphertext[i];
		charPair += fm_ciphertext[i+1];

		//cout << charPair << " ";

		unsigned long tmp = strtoul(charPair.c_str(), NULL, 16);
		if(tmp > 255)
		{
			cerr << "ERROR: Bad parsing of a byte. How did this happen?\n";
			return EXIT_FAILURE;
		}
		uf_ciphertext.push_back((char)tmp);
		//cout << uf_ciphertext[i];

		//cout << endl;
	}
	//cout << endl;

	for(uint i = 0; i < 256; i++)
	{
		cout << "Key " << i << ": ";
		for(uint j = 0; j < uf_ciphertext.size(); j++)
		{
			char outChar = uf_ciphertext[j];
			cout << Decrypt(outChar, i);
		}
		cout << endl;
	}

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

char Decrypt(char inChar, uint key)
{
	return (inChar + key) % 256;
}
