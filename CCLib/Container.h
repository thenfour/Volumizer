

#pragma once


// T is the type of object that this enumerator enumerates.
template<typename T> class CCEXPORT CContainer
{
    public:

        // Returns a pointer to the "beginning".
        virtual T* Reset() = 0;

        // Skips p forward the specified number of elements.
        // Return value is NULL if we couldn't skip that many elements.
        virtual T* Skip(T* p, unsigned long n) = 0;

        // Returns a pointer to the next element.
        // Returns 0 if there are no more elements.
        virtual T* Next(T*) = 0;

        // Returns the item with the index of i.  Returns 0 if the
        // item doesn't exist.
        virtual T* Item(long i) = 0;

        // Finds the element using the overloaded < operator.
        // If no match is found, 0 is returned.
        virtual T* Find(T* pCriteria) = 0;

        // Returns the number of stored items.
        virtual unsigned long Count() = 0;
};


