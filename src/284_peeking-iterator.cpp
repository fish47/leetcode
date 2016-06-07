#include <iostream>
#include <vector>
#include <stack>
#include <random>


#ifdef LEETCODE_DEBUG
class Iterator
{
private:
    std::stack<int>     m_stkNums;

public:
    Iterator(const std::vector<int> &nums)
    {
        for (auto it = nums.crbegin(); it != nums.crend(); ++it)
            m_stkNums.push(*it);
    }

    int next()
    {
        if (m_stkNums.empty())
            return 0;

        auto val = m_stkNums.top();
        m_stkNums.pop();
        return val;
    }

    bool hasNext() const
    {
        return !m_stkNums.empty();
    }
};
#else
class Iterator
{
    struct Data;
    Data *data;
public:
    Iterator(const std::vector<int> &nums);
    Iterator(const Iterator &iter);
    virtual ~Iterator();
    int next();
    bool hasNext() const;
};
#endif


class PeekingIterator : public Iterator
{
private:
    bool        m_bPeeked;
    int         m_iPeekValue;

public:
    PeekingIterator(const std::vector<int> &nums) : Iterator(nums), m_bPeeked(false), m_iPeekValue(0)
    {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        if (!m_bPeeked)
        {
            m_bPeeked = true;
            m_iPeekValue = Iterator::next();
        }

        return m_iPeekValue;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next()
    {
        if (m_bPeeked)
        {
            m_bPeeked = false;
            return m_iPeekValue;
        }

        return Iterator::next();
    }

    bool hasNext() const
    {
        return m_bPeeked ? true : Iterator::hasNext();
    }
};



#ifdef LEETCODE_DEBUG

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumValue(-1000, 1000);
    std::uniform_int_distribution<> randomNumCount(1, 20);
    std::uniform_int_distribution<> randomOp(0, 3);
    for (auto i = 0; i < 1000; ++i)
    {
        std::vector<int> nums;
        auto numCount = randomNumCount(randomEngine);
        for (auto i = 0; i < numCount; ++i)
            nums.push_back(randomNumValue(randomEngine));

        std::stack<int> numStack;
        for (auto it = nums.crbegin(); it != nums.crend(); ++it)
            numStack.push(*it);

        bool failed = false;
        PeekingIterator iterator(nums);
        for (auto j = 0; j < 100; ++j)
        {
            auto op = randomOp(randomEngine);
            switch (op)
            {
                case 0:
                    failed = (iterator.peek() != numStack.top());
                    break;

                case 1:
                    failed = (iterator.hasNext() != !numStack.empty());
                    break;

                case 2:
                    failed = (iterator.next() != numStack.top());
                    numStack.pop();
                    break;
            }

            if (numStack.empty())
                break;
        }

        if (failed)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
}

#endif
