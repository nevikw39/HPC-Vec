#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifndef N
#define N 16777216
#endif // N
#ifndef T
#define T 64
#endif // T

int arr[N];

int max_prefix()
{
    int y = 0;
    for (int i = 0, ps = 0; i < N; i++)
    {
        ps += i[arr];
        if (y < ps)
            y = ps;
    }
    return y;
}

int main()
{
    FILE *f = fopen("data.dat", "rb");
    fread_unlocked(arr, sizeof(int), sizeof arr / sizeof(int), f);
    fclose(f);
    volatile int ans;
    for (volatile int t = 0; t < T; t++)
        ans = max_prefix();
    f = fopen("data.dat", "ab");
    fwrite_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    printf("%d\n", ans);
    return 0;
}
