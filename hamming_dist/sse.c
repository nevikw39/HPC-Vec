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

_Alignas(16) char str_a[N], str_b[N];

int hamming_dist()
{
    int y = N;
    __m128i x = _mm_setzero_si128();
    _Alignas(16) signed char arr[16];
    for (int i = 0; i < N; i += 16)
    {
        __m128i a = _mm_load_si128(str_a + i), b = _mm_load_si128(str_b + i);
        __m128i tmp = _mm_cmpeq_epi8(a, b);
        x = _mm_add_epi8(x, tmp);
        if (!(i % (16 * 256)))
        {
            _mm_store_si128(arr, x);
            for (int j = 0; j < 16; j++)
                y -= (-j[arr] % 256 + 256) % 256;
            x = _mm_setzero_si128();
        }
    }
    if (!(N % (16 * 256)))
    {
        _mm_storeu_si128(arr, x);
        for (int j = 0; j < 16; j++)
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
