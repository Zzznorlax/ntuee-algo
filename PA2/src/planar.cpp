
#include "planar.h"

// Constructor
Planar::Planar(int vertices, map<int, int> chords)
{
    this->vertices = vertices;
    this->chords = chords;

    this->memo = vector<vector<map<int, int> > >(vertices, vector<map<int, int> >(vertices));
}

map<int, int> Planar::MPS(int i, int j)
{
    for (int m = 1; m <= j - i; m++)
    {
        for (int n = i; n <= j - m; n++)
        {
            if ((m + n) > j)
            {
                break;
            }

            if (chords.count(m + n) == 0)
            {
                memo[n][m + n] = memo[n][m + n - 1];
            }
            else
            {
                int k = chords[m + n];

                if (m + n < k || k < n)
                {
                    memo[n][m + n] = memo[n][m + n - 1];
                }
                else if (k == n)
                {
                    memo[n][m + n] = memo[n + 1][m + n - 1];
                    memo[n][m + n][m + n] = k;
                }
                else
                {
                    if (memo[n][m + n - 1].size() > memo[n][k - 1].size() + memo[k + 1][m + n - 1].size() + 1)
                    {
                        memo[n][m + n] = memo[n][m + n - 1];
                    }
                    else
                    {
                        memo[n][m + n].insert(memo[n][k - 1].begin(), memo[n][k - 1].end());
                        memo[n][m + n].insert(memo[k + 1][m + n - 1].begin(), memo[k + 1][m + n - 1].end());
                        memo[n][m + n][m + n] = k;
                    }
                }
            }
        }
    }

    return memo[i][j];
}
