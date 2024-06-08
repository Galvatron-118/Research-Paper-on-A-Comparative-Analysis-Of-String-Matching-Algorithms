
// C++ program for implementation of KMP pattern searching
// algorithm

#include <bits/stdc++.h>
#include<fstream>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <time.h>
using namespace std;
using namespace std::chrono;
int lpsSize;

void computeLPSArray(char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("\nFound pattern at index %d \n", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    lpsSize = sizeof(lps);
}

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    
}

// Driver code
int main()
{   int k,n=5000;
    char txt[50000];
    char pat[]="RRRRRRRRRRRRRRRRRUETRR";
    int patternSize = sizeof(pat);
    ifstream in;
    ofstream out;
    in.open("input.txt");

    for(k=0;k<n;k++){
        in>>txt[k];
        //cout<<txt[k];
    }
    auto start = high_resolution_clock::now();
    KMPSearch(pat, txt);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\n\nTime taken by KMP Algorithm: " << duration.count() << " microseconds" << endl;

    in.close();

    cout << "Size of pattern string: " << patternSize << " bytes" << endl;
    cout << "Size of lps array: " << lpsSize * sizeof(int) << " bytes" << endl;



    return 0;
}
