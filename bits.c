/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    /* 德摩根律: x & y == ~(~x | ~y) */
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    /* 异或 = 「不是两个都为 1」且「不是两个都为 0」 */
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    /* 条件一: 符号位相同 (算术右移 31 位得到 0 或 -1)
       条件二: 「是否为 0」也要一致, 因为 0 既不正也不负 */
    return !((x >> 31) ^ (y >> 31)) && !((!x) ^ (!y));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    /* 即最高位 1 的下标。没有循环可用, 用二分逐步剥离高位。
       不能用大常量, 所以用 (v >> 16) > 0 代替 v > 0xFFFF */
    int r = 0;
    int s;
    s = ((v >> 16) > 0) << 4;  v = v >> s;  r = r | s;
    s = ((v >> 8) > 0) << 3;   v = v >> s;  r = r | s;
    s = ((v >> 4) > 0) << 2;   v = v >> s;  r = r | s;
    s = ((v >> 2) > 0) << 1;   v = v >> s;  r = r | s;
    r = r | (v >> 1);
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    /* 字节号 * 8 == n << 3;
       取出两个字节 -> 把原位清零 -> 交换后填回 */
    int nb = n << 3;
    int mb = m << 3;
    int a = (x >> nb) & 0xFF;
    int b = (x >> mb) & 0xFF;
    int mask = (0xFF << nb) | (0xFF << mb);
    return (x & ~mask) | (b << nb) | (a << mb);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    /* 允许循环, 逐位从 v 的低端搬到 r 的低端, 天然完成翻转 */
    unsigned r = 0;
    int i = 32;
    while (i) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    /* 算术右移会补符号位, 把高 n 位掩掉即可。
       末尾的 << 1 是为了 n == 0 时掩码不出错 */
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /* 取反后问题变成「数前导 0 的个数」, 二分查找 */
    int y = ~x;
    int n = 0;
    int b;
    b = !(y >> 16) << 4;  y = y << b;  n = n + b;
    b = !(y >> 24) << 3;  y = y << b;  n = n + b;
    b = !(y >> 28) << 2;  y = y << b;  n = n + b;
    b = !(y >> 30) << 1;  y = y << b;  n = n + b;
    b = !(y >> 31);       n = n + b;
    /* y == 0 即 x == -1, 此时还要补上第 32 个 1 */
    return n + !y;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned ux = x;
    unsigned r;
    unsigned res;
    int exp = 158;              /* 127 + 31 */
    if (x == 0) return 0;
    if (x < 0) {
        sign = 0x80000000;
        ux = ~ux + 1;           /* 在 unsigned 上取负, 避开 INT_MIN 溢出 */
    }
    /* 左移到最高位为 1, 此时 ux 表示 1.f * 2^31, 每移一次阶码减 1 */
    while (!(ux >> 31)) {
        ux = ux << 1;
        exp = exp - 1;
    }
    r = ux & 0xFF;              /* 被丢弃的低 8 位 */
    res = sign | (exp << 23) | ((ux >> 8) & 0x7FFFFF);
    /* 向偶数舍入 */
    if (r > 128) res = res + 1;
    if ((r == 128) & ((ux >> 8) & 1)) res = res + 1;
    return res;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;
    if (exp == 0xFF) return uf;              /* NaN / INF 原样返回 */
    if (exp == 0) return sign | (uf << 1);   /* 非规格化: 尾数左移, 溢出会自然变成规格化 */
    if (exp == 0xFE) return sign | 0x7F800000;  /* 阶码再 +1 就溢出 -> +-INF */
    return uf + (1 << 23);                   /* 规格化: 阶码 +1 */
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    /* double: 1 位符号 + 11 位阶码 + 52 位尾数, 高 32 位在 uf2 */
    int sign = uf2 >> 31;
    int exp = (uf2 >> 20) & 0x7FF;
    int E = exp - 1023;
    unsigned M = (uf2 & 0xFFFFF) | 0x100000;   /* 补上隐含的 1, 共 21 位 */
    int res;
    if (E < 0) return 0;                       /* 绝对值 < 1, 向零取整为 0 */
    if (E > 30) return 0x80000000;             /* 溢出 (含 INF / NaN) */
    if (E > 20) {
        /* 需要用到 uf1 的高位; 此时 52-E 在 22..31, 不会出现移 32 位的 UB */
        res = (M << (E - 20)) | (uf1 >> (52 - E));
    } else {
        res = M >> (20 - E);
    }
    if (sign) return -res;
    return res;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;                 /* 比最小非规格化数还小 */
    if (x < -126) return 1 << (x + 149);    /* 非规格化范围 */
    if (x > 127) return 0x7F800000;         /* 上溢 -> +INF */
    return (x + 127) << 23;                 /* 规格化: 直接拼阶码 */
}