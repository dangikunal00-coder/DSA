class Solution {
public:
    int lengthOfLastWord(string s) {
        int m = s.size() - 1;
        int length = 0;

        while(s[m] == ' ')
        {
            m --;
        }

        while(m>=0 && s[m]!= ' ')
        {
            length ++;
            m --;
        }

        return length;
    }
};