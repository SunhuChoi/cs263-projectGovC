#include <stdio.h>

int main() {

    long long res = 0;

    for (long long i = 0; i < 100000000; i++) {
        res += i;
    }

    printf("Sum: %lld\n", res);

    return 0;
}
