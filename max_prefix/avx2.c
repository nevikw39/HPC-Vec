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

_Alignas(32) int arr[N];

int max_prefix()
{
    assert(sizeof(int) == 4);
    __m256i mx = _mm256_setzero_si256(), sum = _mm256_setzero_si256();
    for (int i = 0; i < N; i += 8)
    {
        __m256i tmp = _mm256_load_si256(arr + i);
        tmp = _mm256_add_epi32(tmp, _mm256_alignr_epi8(tmp, _mm256_permute2x128_si256(tmp, tmp, _MM_SHUFFLE(0, 0, 2, 0)), 16 - 4));
        tmp = _mm256_add_epi32(tmp, _mm256_alignr_epi8(tmp, _mm256_permute2x128_si256(tmp, tmp, _MM_SHUFFLE(0, 0, 2, 0)), 16 - 8));
        tmp = _mm256_add_epi32(tmp, _mm256_permute2x128_si256(tmp, tmp, _MM_SHUFFLE(0, 0, 2, 0)));

        sum = _mm256_add_epi32(sum, tmp);

        // Maintain the max vector-wise
        mx = _mm256_max_epi32(mx, sum);
        // Set each of the `sum` to `ps[i+7]`
        sum = _mm256_set1_epi32(_mm256_extract_epi32(sum, 7));
    }
    mx = _mm256_max_epi32(mx, _mm256_alignr_epi8(mx, _mm256_permute2x128_si256(mx, mx, _MM_SHUFFLE(0, 0, 2, 0)), 16 - 4));
    mx = _mm256_max_epi32(mx, _mm256_alignr_epi8(mx, _mm256_permute2x128_si256(mx, mx, _MM_SHUFFLE(0, 0, 2, 0)), 16 - 8));
    mx = _mm256_max_epi32(mx, _mm256_permute2x128_si256(mx, mx, _MM_SHUFFLE(0, 0, 2, 0)));
    return _mm256_extract_epi32(mx, 7);
}

int main()
{
    FILE *f = fopen("data.dat", "rb");
    fread_unlocked(arr, sizeof(int), sizeof arr / sizeof(int), f);
    int ans;
    fread_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    for (volatile int t = 0; t < T; t++)
    {
        volatile int res = max_prefix();
        assert(res == ans);
    }
    printf("%d\n", ans);
    return 0;
}
