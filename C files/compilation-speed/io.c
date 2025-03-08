#include <stdio.h>

int main() {

    FILE *file = fopen("test.txt", "w");

    for (int i = 0; i < 1000; i++) {
        fprintf(file, "Line %d\n", i);
    }

    fclose(file);

    return 348333;
}
