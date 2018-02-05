// 3638 | Standard Deviation II | Arturo Arenas

#include <cstdio>
#include <math.h>

using namespace std;

const long long int BIG = 1000000000;

class SuperDouble
{
public:
    long long int integer;
    long long int decimal;
    SuperDouble(): integer(0), decimal(0) {}
    SuperDouble(long long int i, long long int d): integer(i), decimal(d) {}
    void Add(SuperDouble sd)
    {
        // integer += sd.integer; I don't really need this
        decimal += sd.decimal;
        if(decimal >= BIG){
            integer ++;
            decimal -= BIG;
        }
    }
    void Sub(SuperDouble sd)
    {
        integer -= sd.integer;
        decimal -= sd.decimal;
        if(decimal < 0){
            integer --;
            decimal = (BIG + decimal);
        }
    }
};

SuperDouble square(SuperDouble a)
{
    SuperDouble c;
    c.integer = a.integer * a.integer;
    c.decimal = a.decimal*a.decimal/BIG;
    c.decimal += 2*a.decimal*a.integer%BIG;
    c.integer += 2*a.decimal*a.integer/BIG;
    if(c.decimal >= BIG)
    {
        c.integer++;
        c.decimal -= BIG;
    }
    return c;
}

bool compare(SuperDouble a, SuperDouble b)
{
    if(a.integer < b.integer) { return true; }
    else if(a.integer == b.integer){
        if(a.decimal <= b.decimal) { return true; }
        else { return false; }
    }
    else { return false; }
}

int main()
{
    int Nn;
    long long int N, A, B, M, a, sum;
    long int p, q;
    scanf("%d", &Nn);
    while(Nn != 0)
    {
        N = Nn;
        M = N*(N+1);
        if(M%3 == 0) { B = 0; A = M/3; }
        else if(M%3 == 1) { B = 333333333, A = M/3; }
        else { B = 666666667; A = M/3; }
        SuperDouble goal(A, B);

        // Setting approximation
        a = sqrt(A);
        if(a*a > A) { a--; }
        SuperDouble number2(a, 0); // Assertion: a is the integer part of the square root of A
        sum = 536870912; // 2^29
        SuperDouble f(0,sum);
        SuperDouble number;

        // Approximate
        for(int i = 29; i >= 0; i--){
            number2.Add(f);
            number = square(number2);
            if(!compare(number, goal)){
                number2.Sub(f);
            }
            f.decimal /= 2;
        }
        f.decimal+= 500;

        // Round-up
        if(number2.decimal % 1000 >= 500){
            number2.Add(f);
        }
        number2.decimal /= 1000;

        // Display
        p = number2.integer;
        q = number2.decimal;
        printf("%ld.%06ld\n", p, q);
        scanf("%d", &Nn);
    }
}

