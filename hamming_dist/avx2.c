#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <immintrin.h>

#ifndef N
#define N 16777216
#endif // N
#ifndef T
#define T 64
#endif // T

_Alignas(32) char str_a[N], str_b[N];

int hamming_dist()
{
    int y = N;
    __m256i x = _mm256_setzero_si256();
    _Alignas(32) signed char arr[32];
    for (int i = 0; i < N; i += 32)
    {
        __m256i a = _mm256_load_si256(str_a + i), b = _mm256_load_si256(str_b + i);
        __m256i tmp = _mm256_cmpeq_epi8(a, b);
        x = _mm256_add_epi8(x, tmp);
        if (!(i % (32 * 256)))
        {
            _mm256_store_si256(arr, x);
            for (int j = 0; j < 32; j++)
                y -= (-j[arr] % 256 + 256) % 256;
            x = _mm256_setzero_si256();
        }
    }
    if (!(N % (32 * 256)))
    {
        _mm256_storeu_si256(arr, x);
        for (int j = 0; j < 32; j++)
            y -= (-j[arr] % 256 + 256) % 256;
    }
    return y;
}

int main()
{
    FILE *f = fopen("data.txt", "r");
    fread_unlocked(str_a, sizeof(char), sizeof str_a / sizeof(char), f);
    fread_unlocked(str_b, sizeof(char), sizeof str_b / sizeof(char), f);
    int ans;
    fread_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    for (volatile int t = 0; t < T; t++)
    {
        volatile int res = hamming_dist();
        assert(res == ans);
    }
    printf("%d\n", ans);
    return 0;
}
