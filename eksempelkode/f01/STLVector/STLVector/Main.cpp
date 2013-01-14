#include <iostream>  // Lets us use cout, ...
#include <vector>  // Lets us use the vector container.

int main()
{
  std::vector<int> v;   // Creates a vector for int elements.

  // Populate the vector
  v.push_back(3);  // Adds the value 3 to our vector.
  v.push_back(6);  // Adds 6 to the end of our vector.
  v.push_back(9);  // Adds 9 to the end of our vector.

  
  // Standard loop, prints the contents
  std::cout << "Standard loop:" << std::endl;
  // Loop through, print contents
  for (unsigned int i = 0; i < v.size(); ++i)
  {
	  std::cout << v[i] << std::endl; 
  }


  // Loop through the vector using iterators, delete the middle entry
  std::cout << std::endl << "Erasing:" << std::endl;
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
  {
	  if (*it == 6)
	  {
		  std::cout << *it << std::endl;

		  it = v.erase(it);
		  --it;
	  }
  }

  // A primitive iterative approach, print contents using regular pointers
  std::cout << std::endl << "After erase:" << std::endl;
  for (int* p = &v[0]; p != &v[0] + v.size(); ++p)
  {
	  std::cout << *p << std::endl; 
  }

  system("Pause");
  return EXIT_SUCCESS;
}
