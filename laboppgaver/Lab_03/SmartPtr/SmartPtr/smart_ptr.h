/*
 * @file: main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.1
 *
 * @description: A std::shared_ptr like Smart Pointer.
 * NB: I've put it in the std namespace on purpose.
 * It does NOT support arrays!
 */

#ifndef SMART_PTR_H // Inclusion guard
#define SMART_PTR_H

// This is for debugging - remove it for production!
#include <iostream>

namespace std // put it in the same namespace as the other pointers
{
	// Structure to hold pointer data (counter, and actual pointer)
	template <class T>
	struct internalDataPtr
	{
		int m_counter;
		T* m_ptr;
	};

	// Class declaration (template)
	template <class T>
	class smart_ptr
	{
	public:
		/* Constructor, accepts a pointer. Assumes it's created through new! */
		smart_ptr(T* ptr)
		{
			// Debug print, memory location and data
			std::cout << "Creation: #"<< std::hex << ptr << ": " << std::dec << *ptr << std::endl;
			
			// Create a new pointer data structure, initialize
			m_ptrData = new internalDataPtr<T>;
			m_ptrData->m_ptr = ptr;
			m_ptrData->m_counter = 1;
		}

		/* Copy onstructor, accepts a smart_ptr. */
		smart_ptr(const smart_ptr& ptr)
		{
			// Debug print, memory location and data
			std::cout << "Duplication: #" << std::hex << ptr.get() << ": " << std::dec << *ptr.get() << std::endl;
			
			// Set the data structure to point at the existing structure, increase counter.
			m_ptrData = ptr.m_ptrData;
			++(m_ptrData->m_counter);
		}

		/* Destructor, cleans up if all references are gone */
		~smart_ptr()
		{
			--(m_ptrData->m_counter); // reduce pointer counter

			// Check if this was the las reference
			if (m_ptrData && (0 == m_ptrData->m_counter))
			{
				// Debug print, memory address and data
				std::cout << "Deletion: #"<< std::hex << m_ptrData->m_ptr << ": " << std::dec << *m_ptrData->m_ptr << std::endl;
				
				// Delete the pointer and the data structure
				delete m_ptrData->m_ptr;
				delete m_ptrData;
			}
		}

		/* operator-> overloaded in order to be able to access the object (like a reguar pointer) */
		T* operator->() const
		{
			return m_ptrData->m_ptr;
		}

		/* Function to retrieve the address of the real pointer. Should not me modified! */
		T* get() const
		{
			return m_ptrData->m_ptr; 
		}
	private:
		internalDataPtr<T>* m_ptrData; // Pointer to a data structure
	};
}

#endif // End, inclusion guard