class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int n = words.size();

        int i = 0;

        while (i < n) {

            // Find how many words can fit in this line
            int j = i;
            int totalLength = 0;

            while (j < n) {
                // At least one space is required between words
                int required = totalLength + words[j].length();

                if (j > i)
                    required += (j - i);

                if (required > maxWidth)
                    break;

                totalLength += words[j].length();
                j++;
            }

            int wordCount = j - i;

            // Last line OR line containing only one word
            if (j == n || wordCount == 1) {

                string line = words[i];

                for (int k = i + 1; k < j; k++) {
                    line += " ";
                    line += words[k];
                }

                // Add remaining spaces at the end
                line += string(maxWidth - line.length(), ' ');

                ans.push_back(line);
            }

            // Normal fully-justified line
            else {

                // Total spaces that need to be distributed
                int totalSpaces = maxWidth - totalLength;

                // Number of gaps between words
                int gaps = wordCount - 1;

                // Minimum spaces in every gap
                int spacesEach = totalSpaces / gaps;

                // Extra spaces that need to go to the left gaps
                int extraSpaces = totalSpaces % gaps;

                string line = "";

                for (int k = i; k < j; k++) {

                    line += words[k];

                    if (k < j - 1) {

                        // Give extra space to left gaps
                        int spaces = spacesEach;

                        if (k - i < extraSpaces)
                            spaces++;

                        line += string(spaces, ' ');
                    }
                }

                ans.push_back(line);
            }

            // Move to the next line
            i = j;
        }

        return ans;
    }
};