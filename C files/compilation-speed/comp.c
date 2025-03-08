#include <stdio.h>

int main() {

    long long result = 0;

    for (long long i = 0; i < 100000000; i++) {
        result += i;
    }

    printf("Sum: %lld\n", result);

    return 234394;
}
