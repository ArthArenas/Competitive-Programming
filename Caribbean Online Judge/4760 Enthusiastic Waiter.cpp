#include <iostream>

using namespace std;

int const ADJ = 48;

int multiply(char c, int a)
{
    int b = int(c) - ADJ;
    b *= a;
    return b;
}

string bigMultiply(string s, int a)
{
    int i, b;
    int nSize = s.size();
    int nE = 0;
    char c;
    string sRes;
    for(i = nSize - 1; i >= 0; i--)
    {
        b = multiply(s[i], a) + nE;
        c = char(b % 10 + ADJ);
        nE = (b - b % 10) / 10;
        sRes += c;
    }
    if(nE > 0)
    {
        c = char(nE + ADJ);
        sRes += c;
    }
    return sRes;
}

string sumStrings(string a, string b) // b is the one with an extra 0
{
    string sRes;
    string c = "0";
    int i, k;
    int nSize = a.size();
    int nE = 0;
    char d;
    c += b;
    for(i = 0; i < nSize; i++)
    {
        k = int(a[i]) + int(c[i]) - 2*ADJ + nE;
        d = char(k % 10 + ADJ);
        nE = (k - k % 10) / 10;
        sRes += d;
    } // nE stores the digit of the tens || i = nSize by the end of this
    while(c[i])
    {
        k = int(c[i]) - ADJ + nE;
        d = char(k % 10 + ADJ);
        nE = (k - k % 10) / 10;
        sRes += d;
        i++;
    }
    if(nE > 0)
    {
        d = char(nE + ADJ);
        sRes += d;
    }
    return sRes;
}

int main()
{
    string a;
    string aAux, b;
    int i, N, M, j;
    cin >> M;
    for(j = 0; j < M; j++)
    {
        a = "1";
        cin >> N;
        for(i = 1; i <= N; i++)
        {
            if(i < 10)
            {
                a = bigMultiply(a, i);
                aAux = a;
                for(int i = 0; i < int(a.size()); i++)
                {
                    aAux[i] = a[int(a.size()) - 1 - i];
                }
                a = aAux;
            }
            else
            {
                aAux = bigMultiply(a, i % 10);
                b = bigMultiply(a, (i - i % 10) / 10);
                a = sumStrings(aAux, b);
                aAux = a;
                for(int i = 0; i < int(a.size()); i++)
                {
                    aAux[i] = a[int(a.size()) - 1 - i];
                }
                a = aAux;
            }
        }
        cout << a << endl;
    }
}