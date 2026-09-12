class Solution {
public:
    struct State {
        long long score;
        vector<int> indices;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<int, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end());

        vector<vector<State>> dp(n, vector<State>(5, {-1, {}}));

        return solve(0, 4, a, dp).indices;
    }

private:
    State solve(int i, int k,
                vector<array<int, 4>>& a,
                vector<vector<State>>& dp) {

        if (i == a.size() || k == 0)
            return {0, {}};

        if (dp[i][k].score != -1)
            return dp[i][k];

        State skip = solve(i + 1, k, a, dp);

        int r = a[i][1];

        int lo = i + 1, hi = a.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (a[mid][0] > r)
                hi = mid;
            else
                lo = mid + 1;
        }

        int next = lo;

        State take = solve(next, k - 1, a, dp);

        take.score += a[i][2];
        take.indices.push_back(a[i][3]);

        sort(take.indices.begin(), take.indices.end());

        if (take.score > skip.score ||
            (take.score == skip.score &&
             take.indices < skip.indices)) {

            return dp[i][k] = take;
        }

        return dp[i][k] = skip;
    }
};