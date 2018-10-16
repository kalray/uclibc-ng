
int
fegetround(void)
{
        int offset = __builtin_k1_ctz (_K1_MASK_CS_RM);
        return ((__builtin_k1_get (_K1_SFR_CS) & _K1_MASK_CS_RM) >> offset);
}

