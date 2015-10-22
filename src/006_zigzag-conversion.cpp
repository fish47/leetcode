#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>


class Solution
{
public:
    std::string convert(std::string strInput, int nRows)
    {
        int iRowIdx = 0;
        int nStep = 1;
        std::vector<std::string> vecRows(nRows);
        for (int i = 0, n = strInput.size(); i < n; ++i)
        {
            if (iRowIdx >= nRows)
            {
                iRowIdx = std::max(nRows - 2, 0);
                nStep = -1;
            }
            else if (iRowIdx < 0)
            {
                iRowIdx = std::min(nRows - 1, 1);
                nStep = 1;
            }

            vecRows[iRowIdx].push_back(strInput[i]);
            iRowIdx += nStep;
        }


        std::string strRet;
        for (int i = 0, n = vecRows.size(); i < n; ++i)
            strRet += vecRows[i];

        return strRet;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::string strInput,
                   int nRows,
                   std::string strExpected)
{
    Solution solution;
    std::string strRet = solution.convert(strInput, nRows);
    if (strRet != strExpected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
    doTest("ABCDEFGHIJ", 4, "AGBFHCEIDJ");
    doTest("ABCD", 1000, "ABCD");
    doTest("ABCD", 1, "ABCD");
    return 0;
}

#endif
