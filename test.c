// '#' = 35
// '.' = 46
// '@' = 64
// '0' = 48
// '9' = 57
// 'a' = 97
// 'z' = 122
// 'A' = 65
// 'Z' = 90

#include <stdio.h>


int main() {
    int a;
    char ia;
    //int ia = a-1;
    for(a=0; (int)a<256; (int)a++) {
	ia = a;
        printf("%c = %d\n", a, (int)a);
    }
    return 0;
}

