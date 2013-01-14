#include <iostream>  // Lets us use cout, ...
#include <vector>  // Lets us use the vector container.

int main()
{
  std::vector<int> oiVector;   // Creates a vector for int elements.

  // Populate the vector
  oiVector.push_back(3);  // Adds the value 3 to our vector.
  oiVector.push_back(6);  // Adds 6 to the end of our vector.
  oiVector.push_back(9);  // Adds 9 to the end of our vector.

  // Loop through the vector, print contents
  for (int i = 0; i < oiVector.size(); ++i)
  { 
	std::cout << oiVector[i] << std::endl;;
  }

  system("Pause");
  return EXIT_SUCCESS;
}