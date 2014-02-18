/*
    (c) Jan. 15, 2002 Carl Corcoran

    This template will provide a simple linked-list data structure
    to your application.

    Each item in the list can be of any struct or class type, and
    has rules:

    - The item structure must contain pointers
      to the same type of structure in pNext and pPrev members.
    - The structure must contain a cmp for comparison to other nodes.
    - The structure must have a HRESULT CopyToVariant(VARIANT* pv) function
      for returning to the caller.

    Those members need to be accessible by the CLinkedList class.

    For instance:

    class CTestListItemType
    {
        public:
            // Miscellaneous data here to store with your object
            int i;
            char sz[20];

            // The required members.
            int cmp(CTestListItemType&);// returns <0 if THIS is less, 0 if they are equal, and >0 if THIS is greater
            HRESULT CopyToVariant(VARIANT* pv);
            CTestListItemType* pNext;
            CTestListItemType* pPrev;
    }

    Use this code freely... I don't care about it.
*/

#pragma once


#include "Container.h"


// T should have public T* pNext and T* pPrev
template<typename T> class CCEXPORT CLinkedList : public CContainer<T>
{
    public:
        CLinkedList()
        {
            m_pRoot = 0;
            m_pTail = 0;
            m_Count = 0;
        }

        ~CLinkedList()
        {
        }

        // USER Allocates a NEW T* and then calls
        // Add() to add it to the front of the list.
        void Insert(T* pNew)
        {
            InsertAfter(pNew, 0);
            /*
            m_Count ++;

            if(m_pRoot) m_pRoot->pPrev = pNew;
            pNew->pPrev = 0;
            pNew->pNext = m_pRoot;
            m_pRoot = pNew;
            if(!m_pTail) m_pTail = pNew;
            */
            
        }

        // If pNode is NULL, this is added to the end of the list.
        void InsertAfter(T* pNew, T* pNode)
        {
            m_Count ++;

            if(!pNode)
            {
                // Insert it as the tail.
                pNew->pNext = 0;
                pNew->pPrev = m_pTail;
                if(m_pTail) m_pTail->pNext = pNew;
                m_pTail = pNew;
                if(!m_pRoot) m_pRoot = pNew;

                return;
            }

            pNew->pNext = pNode->pNext;
            pNew->pPrev = pNode;
            if(!pNode->pNext) m_pTail = pNew;
            if(pNode->pNext) pNode->pNext->pPrev = pNew;
            pNode->pNext = pNew;
        }

        // If pNode is NULL, this is added to the beginning of the list.
        void InsertBefore(T* pNew, T* pNode)
        {
            m_Count ++;

            if(!pNode)
            {
                // Insert it as the root.
                pNew->pNext = m_pRoot;
                pNew->pPrev = 0;
                if(m_pRoot) m_pRoot->pPrev = pNew;
                if(!m_pRoot) m_pTail = pNew;
                m_pRoot = pNew;
                return;
            }

            pNew->pPrev = pNode->pPrev;
            pNew->pNext = pNode;
            if(!pNode->pPrev) m_pRoot = pNew;
            if(pNode->pPrev) pNode->pPrev->pNext = pNew;
            pNode->pPrev = pNew;
        }

        // The user should free
        void Remove(T* p)
        {
            m_Count --;

            if(p->pPrev) p->pPrev->pNext = p->pNext;
            if(p->pNext) p->pNext->pPrev = p->pPrev;
            if(p == m_pRoot) m_pRoot = p->pNext;
            if(p == m_pTail) m_pTail = p->pPrev;
            p->pNext = 0;
            p->pPrev = 0;
        }

        /*
            CCollection stuff:
        */

        T* Reset()
        {
            return m_pRoot;
        }

        T* Next(T* p)
        {
            if(p == 0)
            {
                return m_pRoot;
            }

            if(p->pNext)
            {
                return p->pNext;
            }

            return 0;
        }

        T* Skip(T* p, unsigned long n)
        {
            unsigned long i;
            T* pCurrent = p;

            for(i=0;i<n;i++)
            {
                if(!pCurrent)
                {
                    // We're done with the list.
                    return 0;
                }

                pCurrent = pCurrent->pNext;
            }

            return pCurrent;
        }

        T* Item(long i)
        {
            T* pCurrent = m_pRoot;
            long n = 0;

            for(n=0;n<i;n++)
            {
                // If there are no more nodes, we can't find an item for this;
                // return 0.
                if(!pCurrent) return 0;

                // Otherwise let's go to the next one.
                pCurrent = pCurrent->pNext;
            }

            return pCurrent;
        }

        T* Find(T* pCriteria)
        {
            T* pCurrent = m_pRoot;

            while(pCurrent)
            {
                // Compare pCurrent and 
                if(pCurrent->cmp(*pCriteria) == 0)
                {
                    // match.
                    break;
                }

                pCurrent = pCurrent->pNext;
            }

            return pCurrent;
        }

        // Returns the number of stored items.
        unsigned long Count()
        {
            return m_Count;
        }

    public:

        T* m_pRoot;
        T* m_pTail;

    private:

        unsigned long m_Count;
};


