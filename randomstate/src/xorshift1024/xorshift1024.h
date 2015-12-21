#include <stdint.h>

typedef struct s_xorshift1024_state
{
    uint64_t s[16];
    int p;
} xorshift1024_state;

inline uint64_t xorshift1024_next(xorshift1024_state* state) {
    const uint64_t s0 = state->s[state->p];
    state->p = (state->p + 1) & 15;
    uint64_t s1 = state->s[state->p];
    s1 ^= s1 << 31; // a
    state->s[state->p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
    return state->s[state->p] * UINT64_C(1181783497276652981);
}

void xorshift1024_jump(xorshift1024_state* state);

void xorshift1024_seed(xorshift1024_state* state, uint64_t seed);

void xorshift1024_init_state(xorshift1024_state* state, uint64_t* seeds);