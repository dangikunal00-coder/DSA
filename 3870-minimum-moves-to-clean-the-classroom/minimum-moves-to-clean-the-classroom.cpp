class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        
        int m = classroom.size();
        int n = classroom[0].size();

        int startR = 0, startC = 0;
        int litterCount = 0;

        // Give every litter cell a bit number
        vector<vector<int>> id(m, vector<int>(n, -1));

        // Find starting position and litter
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                }
                
                else if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount;
                    litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0) {
            return 0;
        }

        // All bits set = all litter collected
        int targetMask = (1 << litterCount) - 1;

        /*
            State:
            row
            column
            energy
            mask
        */

        queue<tuple<int, int, int, int>> q;

        // Start with full energy and no litter collected
        q.push({startR, startC, energy, 0});

        // visited[row][column][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        visited[startR][startC][energy][0] = true;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int size = q.size();

            // Process one BFS level
            while (size--) {

                auto [r, c, currEnergy, mask] = q.front();
                q.pop();

                // All litter collected
                if (mask == targetMask) {
                    return moves;
                }

                // If energy is 0, cannot make another move
                if (currEnergy == 0) {
                    continue;
                }

                // Try 4 directions
                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                        continue;
                    }

                    // Obstacle
                    if (classroom[nr][nc] == 'X') {
                        continue;
                    }

                    // One move costs one energy
                    int nextEnergy = currEnergy - 1;

                    // Reset area restores full energy
                    if (classroom[nr][nc] == 'R') {
                        nextEnergy = energy;
                    }

                    // Current collected litter
                    int nextMask = mask;

                    // If we move onto litter
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];

                        nextMask |= (1 << bit);
                    }

                    // If this state has already been visited
                    if (visited[nr][nc][nextEnergy][nextMask]) {
                        continue;
                    }

                    visited[nr][nc][nextEnergy][nextMask] = true;

                    q.push({
                        nr,
                        nc,
                        nextEnergy,
                        nextMask
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};