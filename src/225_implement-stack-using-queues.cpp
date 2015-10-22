#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>


class Stack
{
private:
    std::queue<int>     queueBuff;
    std::queue<int>     queueTmp;


public:
    // Push element x onto stack.
    void push(int x)
    {
        queueBuff.push(x);
    }

    // Removes the element on top of the stack.
    void pop()
    {
        if (queueBuff.empty())
            return;

        int val = 0;
        while (!queueBuff.empty())
        {
            val = queueBuff.front();
            queueBuff.pop();

            // 不把最后的元素加入队列
            if (!queueBuff.empty())
                queueTmp.push(val);
        }

        queueBuff.swap(queueTmp);
    }

    // Get the top element.
    int top()
    {
        int ret = 0;
        while (!queueBuff.empty())
        {
            ret = queueBuff.front();
            queueBuff.pop();
            queueTmp.push(ret);
        }

        queueBuff.swap(queueTmp);
        return ret;
    }

    // Return whether the stack is empty.
    bool empty()
    {
        return queueBuff.empty();
    }
};


#ifdef LEETCODE_DEBUG

static void assertEquals(int val, int expected)
{
    if (val != expected)
        std::printf("Test failed.\n");
}

int main()
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    assertEquals(stack.empty(), false);
    assertEquals(stack.top(), 4);

    stack.pop();
    assertEquals(stack.top(), 3);

    stack.push(5);
    assertEquals(stack.top(), 5);

    stack.pop();
    assertEquals(stack.empty(), false);

    stack.pop();
    stack.pop();
    stack.pop();
    assertEquals(stack.empty(), true);

    return 0;
}

#endif
