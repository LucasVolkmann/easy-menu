#include <stdio.h>
#include "./utils.h"

void cleanScanfBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
