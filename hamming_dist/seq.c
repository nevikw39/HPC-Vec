#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifndef N
#define N 16777216
#endif // N
#ifndef T
#define T 64
#endif // T

char str_a[N], str_b[N];

int hamming_dist()
{
    int y = N;
    for (int i = 0; i < N; i++)
        y -= i[str_a] == i[str_b];
    return y;
}

int main()
{
    FILE *f = fopen("data.txt", "r");
    fread_unlocked(str_a, sizeof(char), sizeof str_a / sizeof(char), f);
    fread_unlocked(str_b, sizeof(char), sizeof str_b / sizeof(char), f);
    fclose(f);
    volatile int ans;
    for (volatile int t = 0; t < T; t++)
        ans = hamming_dist();
    f = fopen("data.txt", "a");
    fwrite_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    printf("%d\n", ans);
    return 0;
}
