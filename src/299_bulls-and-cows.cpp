#include <cstdio>
#include <algorithm>
#include <string>


class Solution
{
public:
    typedef typename std::string    StringType;
    typedef StringType::size_type   StringSizeType;

private:
    static const StringType::value_type     kBullUnit   = 'A';
    static const StringType::value_type     kCowUnit    = 'B';

public:
    StringType getHint(StringType secret, StringType guess)
    {
        StringType ret;
        if (secret.size() != guess.size())
            return ret;

        StringSizeType bullCount = 0;
        StringType secretCowString;
        StringType guessCowString;
        for (StringSizeType i = 0, n = secret.size(); i < n; ++i)
        {
            auto secretCh = secret[i];
            auto guessCh = guess[i];
            if (secretCh != guessCh)
            {
                // 先收集那些可能是错位的数字
                secretCowString.push_back(secretCh);
                guessCowString.push_back(guessCh);
            }
            else
            {
                ++bullCount;
            }
        }

        std::sort(secretCowString.begin(), secretCowString.end());
        std::sort(guessCowString.begin(), guessCowString.end());

        StringSizeType cowCount = 0;
        StringSizeType secretIdx = 0;
        StringSizeType guessIdx = 0;
        StringSizeType remainingCount = secretCowString.size();
        while (secretIdx < remainingCount && guessIdx < remainingCount)
        {
            auto secretCh = secretCowString[secretIdx];
            auto guessCh = guessCowString[guessIdx];
            if (secretCh < guessCh)
            {
                ++secretIdx;
            }
            else if (secretCh > guessCh)
            {
                ++guessIdx;
            }
            else
            {
                ++cowCount;
                ++secretIdx;
                ++guessIdx;
            }
        }


        ret.append(std::to_string(bullCount));
        ret.push_back(kBullUnit);
        ret.append(std::to_string(cowCount));
        ret.push_back(kCowUnit);
        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(Solution::StringType secret, Solution::StringType guess, Solution::StringType assertStr)
{
    Solution solution;
    Solution::StringType ret = solution.getHint(secret, guess);
    if (ret != assertStr)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("1807", "7810", "1A3B");
    doTest("1123", "0111", "1A1B");
    return 0;
}

#endif
