/*
    All allocation is done OUTSIDE of this class.
*/

class QueueItem
{
public:
    // Stuff...

    // Required:
    QueueItem* pNext;
    QueueItem* pPrev;
};


/*
    The root is the first item, the tail is the last.
    So every time you pop an item, the root changes.  Every time you
    push an item, the tail changes.
*/

template<typename T>
class Queue
{
public:
    Queue()
    {
        m_pRoot = 0;
        m_pTail = 0;
    }

    /*
        Pushes a new item onto the TAIL of the queue.
    */
    void Push(T* pNew)
    {
        if(m_pRoot == 0)
        {
            m_pRoot = pNew;
            m_pTail = pNew;
            pNew->pNext = 0;
            pNew->pPrev = 0;

            return;
        }

        // We have a root and a tail, so let's push it on
        // in an orderly fashion.
        m_pTail->pNext = pNew;
        pNew->pPrev = m_pTail;
        m_pTail = pNew;

        return;
    }

    /*
        Remove an item from the top of the queue.
    */
    T* Pop()
    {
        T* pRet = m_pRoot;

        if(pRet)
        {
            m_pRoot = pRet->pNext;
            if(m_pRoot) m_pRoot->pPrev = 0;
        }

        if(pRet == m_pTail)
        {
            // We know we're removing the only item in the queue.
            // the root should already be NULL...
            m_pTail = 0;
        }

        return pRet;
    }

private:

    T* m_pRoot;
    T* m_pTail;
};


