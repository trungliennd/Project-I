#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "librarylargenumber.h"

using namespace std;

int main() {
BigInt R("12");
BigInt N("4");
BigInt a("161"),b,T("1125"),d;
BigInt module("79000000000000000000000000000000000001");
BigInt N1("127");
clock_t begin = clock();

b = modExp(R,N,module);

b.outPut();

printf("\n");
d.outPut();
clock_t end = clock();
cout<<"\n\nTime run: "<< (float)(end - begin)/CLOCKS_PER_SEC<<" s"<< endl;
// github
}
