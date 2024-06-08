/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <bits/stdc++.h>
#include<fstream>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <time.h>
using namespace std;
using namespace std::chrono;

// d is the number of characters in the input alphabet
#define d 50000

/* pat -> pattern
	txt -> text
	q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern
	int t = 0; // hash value for txt
	int h = 1;

	// The value of h would be "pow(d, M-1)%q"
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of pattern and first
	// window of text
	for (i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one
	for (i = 0; i <= N - M; i++) {

		// Check the hash values of current window of text
		// and pattern. If the hash values match then only
		// check for characters one by one
		if (p == t) {
			/* Check for characters one by one */
			for (j = 0; j < M; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}

			// if p == t and pat[0...M-1] = txt[i, i+1,
			// ...i+M-1]

			if (j == M)
				cout << "Pattern found at index " << i << endl;
		}

		// Calculate hash value for next window of text:
		// Remove leading digit, add trailing digit
		if (i < N - M) {
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting
			// it to positive
			if (t < 0)
				t = (t + q);
		}
	}
}

/* Driver code */
int main()
{
	

	// we mod to avoid overflowing of value but we should
	// take as big q as possible to avoid the collison
	int q = 2;

	// Function Call





int k,n=50000;
    char txt[50000];
    char pat[]="RR";
    ifstream in;
    ofstream out;
    in.open("input2.txt");

    for(k=0;k<n;k++){
        in>>txt[k];
        //cout<<txt[k];
    }
    auto start = high_resolution_clock::now();
   	search(pat, txt, q);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\n\nTime taken by Rabin-Karp Algorithm: " << duration.count() << " microseconds" << endl;

    in.close();



    return 0;
}

// This is code is contributed by rathbhupendra
