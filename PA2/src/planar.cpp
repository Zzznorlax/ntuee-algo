
#include "planar.h"

// Constructor
Planar::Planar(int vertices, int chords[])
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
