#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;


class VersionCodePiece
{

private:
    string  *m_pString;
    int     m_iStartIdx;
    int     m_iEndIdx;


public:
    VersionCodePiece(string &str) : m_pString(&str),
                                    m_iStartIdx(0),
                                    m_iEndIdx(0)
    {
        if (m_pString)
        {
            string::size_type endPos = m_pString->find('.');
            m_iEndIdx = (endPos == string::npos) ? m_pString->size()
                                                 : (int) endPos;
        }
    }


    bool next()
    {
        // 已经遍历完了
        if (m_iEndIdx == m_pString->size())
        {
            m_iStartIdx = m_iEndIdx;
            return false;
        }

        m_iStartIdx = m_iEndIdx + 1;
        string::size_type endPos = m_pString->find('.', m_iStartIdx);
        m_iEndIdx = (endPos == string::npos) ? m_pString->size()
                                             : (int) endPos;

        return true;
    }


    int compare(VersionCodePiece &other)
    {
        string &str1 = *m_pString;
        string &str2 = *other.m_pString;

        int startIdx1 = m_iStartIdx;
        skipLeadingZeros(str1, m_iEndIdx, &startIdx1);

        int startIdx2 = other.m_iStartIdx;
        skipLeadingZeros(str2, other.m_iEndIdx, &startIdx2);


        // 首先比较长度
        int numLen1 = m_iEndIdx - startIdx1;
        int numLen2 = other.m_iEndIdx - startIdx2;
        if (numLen1 != numLen2)
            return numLen1 < numLen2 ? -1 : 1;

        // 然后比较字典序
        while (startIdx1 < m_iEndIdx)
        {
            char ch1 = str1[startIdx1];
            char ch2 = str2[startIdx2];
            if (ch1 != ch2)
                return ch1 < ch2 ? -1 : 1;

            ++startIdx1;
            ++startIdx2;
        }

        // 相等
        return 0;
    }


private:
    void skipLeadingZeros(string &str, int endIdx, int *inOutStartIdx)
    {
        int startIdx = *inOutStartIdx;
        while (startIdx < endIdx && str[startIdx] == '0')
            ++startIdx;

        *inOutStartIdx = startIdx;
    }
};


class Solution
{
public:
    int compareVersion(string version1, string version2)
    {
        VersionCodePiece piece1(version1);
        VersionCodePiece piece2(version2);

        while (true)
        {
            int ret = piece1.compare(piece2);
            if (ret != 0)
                return ret;

            bool isEnd1 = !piece1.next();
            bool isEnd2 = !piece2.next();
            if (isEnd1 && isEnd2)
                break;
        }

        return 0;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(const char *str1, const char *str2, int correct)
{
    string version1(str1);
    string version2(str2);

    Solution solution;
    int output = solution.compareVersion(version1, version2);
    if (output != correct)
    {
        cout << "Version1: " << version1 << endl;
        cout << "Version2: " << version2 << endl;
        cout << "Output: " << output << endl;
        cout << "Correct: " << correct << endl << endl;
    }
}

int main()
{
    doTest("1", "000002", -1);
    doTest("0.1", "0.00001", 0);
    doTest("0.1.1", "0.0001", 1);
    doTest("12345.1.123", "0055555", -1);
    doTest("123.456.789", "123.555", -1);
    doTest("123.456.789", "123.456", 1);
    return 0;
}

#endif
