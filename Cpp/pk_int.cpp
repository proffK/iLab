#include "pk_int.h"

pk_int()
{
    _number = 0;
}

pk_int(int standart_int)
{
    _number = standart_int;
}

pk_int operator + (const pk_int & num)
{
    return _number + num._number;
}
pk_int operator - (const pk_int & num)
{
    return _number - num._number;
}
pk_int operator * (const pk_int & num)
{
    return _number * num._number;
}
pk_int operator / (const pk_int & num)
{
    return _number / num._number;
}
&pk_int operator = (const pk_int & num)
{
    return _number = num._number;
}
int dump(pk_int int)
{
    int new_int = 0;
    return *this;
}
