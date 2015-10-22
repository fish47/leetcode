#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>
#include <deque>


using namespace std;


class MinStack
{
private:

    struct MinElementRecord
    {
        int     iVal;
        int     nCount;
    };

    deque<int>                  m_Elements;
    deque<MinElementRecord>     m_MinElements;

public:

    void push(int x)
    {
        m_Elements.push_back(x);

        if (m_MinElements.empty() || m_MinElements.back().iVal > x)
        {
            MinElementRecord rec;
            rec.iVal = x;
            rec.nCount = 1;
            m_MinElements.push_back(rec);
        }
        else
        {
            ++m_MinElements.back().nCount;
        }
    }

    void pop()
    {
        if (m_Elements.empty())
            return;

        m_Elements.pop_back();

        MinElementRecord &rec = m_MinElements.back();
        --rec.nCount;
        if (rec.nCount == 0)
            m_MinElements.pop_back();
    }

    int top()
    {
        return m_Elements.empty() ? 0 : m_Elements.back();
    }

    int getMin()
    {
        return m_Elements.empty() ? 0 : m_MinElements.back().iVal;
    }
};



#ifdef LEETCODE_DEBUG

int main()
{
    list<int> stlStack;
    MinStack minStack;
    string errorMsg;

    srand(time(0));

    for (int i = 0; i < 1000000; ++i)
    {
        switch (rand() % 4)
        {
            case 0:
                {
                    int elem = rand() % 20;
                    stlStack.push_back(elem);
                    minStack.push(elem);
                }
                break;

            case 1:
                if (!stlStack.empty())
                {
                    int minStackPoped = minStack.top();
                    minStack.pop();

                    int poped = stlStack.back();
                    stlStack.pop_back();

                    if (poped != minStackPoped)
                        errorMsg = "Pop()\n";
                }
                break;

            case 2:
                if (!stlStack.empty())
                {
                    int stlTop = stlStack.back();
                    int minStackTop = minStack.top();
                    if (stlTop != minStackTop)
                        errorMsg = "Top()\n";
                }
                break;

            case 3:
                if (!stlStack.empty())
                {
                    int stlMin = *min_element(stlStack.begin(), stlStack.end());
                    int minStackMin = minStack.getMin();
                    if (stlMin != minStackMin)
                        errorMsg = "Min()\n";
                }
                break;
        }

        if (errorMsg.size() > 0)
        {
            cout << errorMsg;
            break;
        }
    }

    return 0;
}

#endif
