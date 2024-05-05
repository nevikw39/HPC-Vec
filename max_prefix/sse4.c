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

_Alignas(16) int arr[N];

int max_prefix()
{
    assert(sizeof(int) == 4);
    __m128i mx = _mm_setzero_si128(), sum = _mm_setzero_si128();
    for (int i = 0; i < N; i += 4)
    {
        // tmp: {arr[i], arr[i+1], arr[i+2], arr[i+3]}
        __m128i tmp = _mm_load_si128(arr + i);

        // tmp: {arr[i], arr[i]+arr[i+1], arr[i+1]+arr[i+2], arr[i+2]+arr[i+3]}
        tmp = _mm_add_epi32(tmp, _mm_slli_si128(tmp, 4));

        // tmp: {arr[i], arr[i]+arr[i+1], arr[i]+arr[i+1]+arr[i+2], arr[i]+arr[i+1]+arr[i+2]+arr[i+3]}
        tmp = _mm_add_epi32(tmp, _mm_slli_si128(tmp, 8));

        // sum: {ps[i-1]+arr[i]==ps[i], ps[i-1]+arr[i]+arr[i+1]==ps[i+1], ps[i-1]+arr[i]+arr[i+1]+arr[i+2]==ps[i+2], ps[i-1]+arr[i]+arr[i+1]+arr[i+2]+arr[i+3]==ps[i+3]}
        sum = _mm_add_epi32(sum, tmp);

        // Maintain the max vector-wise
        mx = _mm_max_epi32(mx, sum);
        // Set each of the `sum` to `ps[i+3]`
        sum = _mm_shuffle_epi32(sum, 0b11111111);
        // sum = _mm_set1_epi32(_mm_extract_epi32(sum, 3));
    }
    // Reduce the result
    mx = _mm_max_epi32(mx, _mm_slli_si128(mx, 4));
    mx = _mm_max_epi32(mx, _mm_slli_si128(mx, 8));
    return _mm_extract_epi32(mx, 3);
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
