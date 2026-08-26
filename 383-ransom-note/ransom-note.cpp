class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int freq[26] = {0};

        // Count characters available in magazine
        for (char ch : magazine) {
            freq[ch - 'a']++;
        }

        // Use characters to construct ransomNote
        for (char ch : ransomNote) {
            freq[ch - 'a']--;

            // Not enough of this character
            if (freq[ch - 'a'] < 0) {
                return false;
            }
        }

        return true;
    }
};