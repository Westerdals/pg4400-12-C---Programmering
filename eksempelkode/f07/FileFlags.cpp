/**
 * @file: FileFlags.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <06.03.2013>
 *
 * @description: An example on working with files, using flags.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  // Tries to open file in ofstream constructor.
  // out flag indicates "write", so it tries to create the file
  // if it does not exist!
  ofstream outputFile("iplist.dat", ios_base::out);

  // Exit if program was unable to open file
  if (!outputFile) {
    cerr << "File could not be opened/created!" << endl;
    return EXIT_FAILURE;
  }

  // write to file
  outputFile << "192.168.0.10\n" << "127.0.0.1\n";

  system("Pause");
  return EXIT_SUCCESS;
} // buffer is flushed to file when it gets out of scope!