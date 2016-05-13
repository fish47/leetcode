#include <iostream>
#include <string>
#include <array>

static const int    kMinNumber      = 1;
static const int    kMaxNumber      = 3999;
static const int    kWeightThound   = 1000;
static const int    kWeightHundred  = 100;
static const int    kWeightTen      = 10;
static const int    kWeightOne      = 1;

typedef std::array<std::string, 10>  RomanStringArray;
static const RomanStringArray   kStringThousands    =   { "", "M", "MM", "MMM" };
static const RomanStringArray   kStringHundreds     =   { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
static const RomanStringArray   kStringTens         =   { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
static const RomanStringArray   kStringOnes         =   { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };


static void doAppendRomanString(std::string *pRet, int *pNum, int weight, const RomanStringArray &array)
{
    if (!pRet || !pNum)
        return;

    auto count = *pNum / weight;
    pRet->append(array[count]);
    *pNum -= count * weight;
}


class Solution
{
public:
    std::string intToRoman(int num)
    {
        std::string ret;
        if (kMinNumber <= num && num <= kMaxNumber)
        {
            doAppendRomanString(&ret, &num, kWeightThound, kStringThousands);
            doAppendRomanString(&ret, &num, kWeightHundred, kStringHundreds);
            doAppendRomanString(&ret, &num, kWeightTen, kStringTens);
            doAppendRomanString(&ret, &num, kWeightOne, kStringOnes);
        }
        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(int num, std::string assertVal)
{
    Solution solution;
    auto ret = solution.intToRoman(num);
    if (ret != assertVal)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest(67, "LXVII");
    doTest(99, "XCIX");
    doTest(1800, "MDCCC");
    doTest(1954, "MCMLIV");
    doTest(1990, "MCMXC");
    doTest(2014, "MMXIV");
    return 0;
}

#endif
