LL floordiv(LL a, LL b)
{
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b;
    return a / b - 1;
}

LL ceildiv(LL a, LL b)
{
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b + 1;
    return a / b;
}