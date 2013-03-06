/**
 * @file: FileIO.cpp
 * @author: Tomas Sandnes <santom@nith.no>
 * @modifier: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.1.0 <06.03.2013>
 *
 * @description: An example on working with files in C++
 */
 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  // Open (or create new) file for writing
  ofstream oFileOut;
  oFileOut.open("highScores.txt");
  
  // Add some lines
  for (int i = 0; i < 5; ++i) {
    oFileOut << "Highscore: " << i * 3 << endl;
  }
  
  oFileOut.close(); // Flush buffer, writing to disk. Close file.
  
  // Reopen file for reading
  ifstream oFileIn("highScores.txt");
  
  // Loop through each line of the text file, print contents to console.
  string zScore;
  while (!oFileIn.eof()) {
    getline(oFileIn, zScore);
    cout << zScore << endl; 
  }
  
  system("pause");
  return EXIT_SUCCESS;
}