#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <stack>


class Queue
{
private:
    std::stack<int>     m_stkNums;
    std::stack<int>     m_stkTmp;

    void transferToStack(std::stack<int> *pStkTo,
                         std::stack<int> *pStkFrom)
    {
        while (!pStkFrom->empty())
        {
            pStkTo->push(pStkFrom->top());
            pStkFrom->pop();
        }
    }


public:
    // Push element x to the back of queue.
    void push(int x)
    {
        transferToStack(&m_stkNums, &m_stkTmp);
        m_stkNums.push(x);
    }

    // Removes the element from in front of queue.
    void pop()
    {
        transferToStack(&m_stkTmp, &m_stkNums);
        if (!m_stkTmp.empty())
            m_stkTmp.pop();
    }

    // Get the front element.
    int peek()
    {
        transferToStack(&m_stkTmp, &m_stkNums);
        int ret = m_stkTmp.empty() ? INT_MIN : m_stkTmp.top();
        return ret;
    }

    // Return whether the queue is empty.
    bool empty()
    {
        return (m_stkNums.empty() && m_stkTmp.empty());
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    Queue queueNums;
    std::deque<int> deqNums;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomOp(0, 3);

    for (int i = 0; i < 10000; ++i)
    {
        bool succeed = false;
        int op = randomOp(randomEngine);
        switch (op)
        {
            case 0:
                succeed = (queueNums.empty() == deqNums.empty());
                break;
            case 1:
                queueNums.push(i);
                deqNums.push_back(i);
                succeed = true;
                break;
            case 2:
                succeed = (queueNums.empty() == deqNums.empty());
                if (succeed && !queueNums.empty())
                {
                    queueNums.pop();
                    deqNums.pop_front();
                }
                succeed = true;
                break;
            case 3:
                succeed = (queueNums.empty() == deqNums.empty());
                if (succeed && !queueNums.empty())
                    succeed = (queueNums.peek() == deqNums.front());
                break;

        }

        if (!succeed)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
