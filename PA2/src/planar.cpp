
#include "planar.h"
#include <iostream>

// Constructor
Planar::Planar(int vertices, map<int, int> chords)
{
    this->vertices = vertices;
    this->chords = chords;

    this->memo = vector<vector<int> >(vertices, vector<int>(vertices));

    // Builds memo
    for (int l = 1; l <= vertices - 1; l++)
    {
        for (int i = 0; i <= vertices - 1 - l; i++)
        {
            int j = i + l;
            if (chords.count(j) == 0)
            {
                memo[i][j] = memo[i][j - 1];
                continue;
            }

            int k = chords[j];
            if (k > j || k < i)
            { //case 1
                memo[i][j] = memo[i][j - 1];
            }
            else if (k == i)
            { //case 2
                memo[i][j] = memo[i + 1][j - 1] + 1;
            }
            else
            { //case 3
                if (memo[i][j - 1] > memo[i][k - 1] + 1 + memo[k + 1][j - 1])
                {
                    memo[i][j] = memo[i][j - 1];
                }
                else
                {
                    memo[i][j] = memo[i][k - 1] + 1 + memo[k + 1][j - 1];
                }
            }
        }
    }
}

void Planar::MPS(int i, int j)
{
    int k = chords[j];

    if (i >= j)
    {
        return;
    }

    if ((i > k || k > j) || (memo[i][j] == memo[i][j - 1]))
    {
        MPS(i, j - 1);
    }
    else if (k == i)
    {
        maxChords[j] = k;
        MPS(i + 1, j - 1);
    }
    else if (j > k && k > i)
    {
        maxChords[j] = k;
        MPS(i, k - 1);
        MPS(k + 1, j - 1);
    }
}

/*
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
 */
