/*

Calculating Bowling Scores
Week 6 Programming Assignment
By Justin Smith
ITCS 2530 V0801

This program will read input from a file, specified as a global constant, and assign that data to arrays.
It includes one array for the bowler names, a two dimensional array to hold bowler scores and another array
to hold the average scores for that bowler.

The function PrettyPrintResults is used to show output to user

*/

#include <iostream> // I/O Header File
#include <string> // String header file
#include <fstream> // Header file for file I/O
#include <iomanip> // Header file for format manipulation

using namespace std;

// Global scope constants
const string FILE_NAME = "BowlingScores.txt";
const int BOWLERS = 10; // How many bowlers in the file
const int NUM_GAMES = 5; // How many games were played, edited
const int NUM_PEOPLE = 10; // Number of people
const char emptyChar = ' '; // Used for end condition in getline function


// For reference, main function begins at line 148


void GetBowlingData(string FILE_NAME, string NameList[BOWLERS], int ScoreList[NUM_PEOPLE][NUM_GAMES])
{
	// Declare file stream variable and open file I/O
	ifstream fs;
	fs.open(FILE_NAME);
	// Check to see if file stream opens correctly
	if (!fs)
	{
		cout << "The file could not be opened. Program exiting" << endl;
		system("pause");
		return;
	}



	// Load first array 'NameList'
	// Use for loop to load 1-D array with bowler names
	string line;
	for (int i = 0; i < BOWLERS; i++)
	{
		fs >> NameList[i]; // load array at index i with data from fs
		getline(fs, line); // Moving the cursor past the new line character, which moves to the next line
	}


	fs.seekg(0); // Sets the position in the file to beginning



	// Load second array 'ScoreList'
	// Load the 2-D ScoreList array with bowler games and bowler scores
	// 2-D array requires a nested for loop
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		// Get line used to find the correct data
		// Reads from fs, and retuns the data until it gets to the third argument
		// Third argument is the end condition, in this case I was looking for a whitespace ' '
		getline(fs, line, emptyChar);

		for (int j = 0; j < NUM_GAMES; j++)
		{
			fs >> ScoreList[i][j];
			// Used if else here to determine which end condition to use in getline function
			// If NUM_GAMES - 1 = j, getline moves past the newline character, which moves to the next line
			// Else the ending condition of getline is specifies as emptyChar (' ') or whitespace and continues on that line
			if (j == NUM_GAMES - 1)
			{
				getline(fs, line);
			}
			else
			{
				getline(fs, line, emptyChar);
			}
		}
	}

	// Close the file stream
	fs.close();

	return;
}

// Function to calculate averages
void GetAverageScores(const int ScoreList[NUM_PEOPLE][NUM_GAMES], double AverageScores[NUM_PEOPLE])
{
	// Using ScoreList to add up and find averages needs nested for loop
	// Averages put into AverageScores
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		AverageScores[i] = 0; // initialed back to zero after inner loop to hold average for next bowler

		for (int j = 0; j < NUM_GAMES; j++)
		{
			AverageScores[i] = AverageScores[i] + ScoreList[i][j]; // Adds scores to AverageScores at index [i][j]
		}
		AverageScores[i] = AverageScores[i] / NUM_GAMES; // Calculation for average 
	}
	return;
}


void PrettyPrintResults(const string NameList[BOWLERS], const int ScoreList[NUM_PEOPLE][NUM_GAMES], const double AverageScores[NUM_PEOPLE])
{
	// Header
	cout << setw(80) << left << setfill('#') << "#" << endl;
	cout << setw(24) << left << setfill('#') << "#";
	cout << "  Calculating Bowlers Averages  ";
	cout << setw(24) << right << setfill('#') << "#" << endl;
	cout << setw(80) << left << setfill('#') << "#" << endl << endl;

	// Pretty Print Results
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		cout << setw(80) << left << setfill('-') << "-" << endl;
		cout << NameList[i] << ": " << endl; // Outputs the bowler name (NameList[i])

		for (int j = 0; j < NUM_GAMES; j++)
		{
			cout << "Game " << j + 1 << " - ";
			cout << ScoreList[i][j] << endl; // Outputs the score for the corresponding game [i][j]
		}
		cout << "Average score: " << AverageScores[i] << endl; // Outputs average
		cout << setw(80) << left << setfill('-') << "-" << endl << endl;
	}
	system("pause");

	return;
}


// ************************************************************************************** \\
// ++++++++++++++++++++++++++++++++++++++++  MAIN  +++++++++++++++++++++++++++++++++++++* \\
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**+ \\


int main()
{
	// Declare arrays 
	string BowlerName[BOWLERS];
	int BowlerScores[NUM_PEOPLE][NUM_GAMES];
	double BowlerAverage[NUM_PEOPLE];

	// Call to function GetBowlingData, passing as arguments the file name, 1-D array BowlerName, 
	// and 2-D array BowlerScores
	GetBowlingData(FILE_NAME, BowlerName, BowlerScores);

	// Call function GetAverageScores, passes in the filled array BowlerScores and Bowleraverage array
	GetAverageScores(BowlerScores, BowlerAverage);

	// Call function PrettyPrintResults to output results
	PrettyPrintResults(BowlerName, BowlerScores, BowlerAverage);


	/*
	//Code used for testing GetBowlingData function that array is loading correctly and value referenced corectly
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		for (int j = 0; j < NUM_GAMES; j++)
		{
			cout << BowlerScores[i][j] << " ";

		}
		cout << endl;
	}

	for (int i = 0; i < BOWLERS; i++)
	{
		cout << BowlerName[i] << endl;
	}
	*/

	return 1;
}
