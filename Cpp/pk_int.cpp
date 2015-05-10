#include "pk_int.h"

pk_int::pk_int()
{
    Проверка!!!
    this -> _number = 0;
}
pk_int::pk_int(int standart_int)
{
    this -> _number = standart_int;
}
pk_int pk_int::operator + (const pk_int & num)
{
    return this -> _number + num._number;
}
pk_int pk_int::operator - (const pk_int & num)
{
    return this -> _number - num._number;
}
pk_int pk_int::operator * (const pk_int & num)
{
    return this -> _number * num._number;
}
pk_int pk_int::operator / (const pk_int & num)
{
    return this -> _number / num._number;
}
pk_int & pk_int::operator = (const pk_int & num)
{
    this -> _number = num._number;
    return *this;
}
int pk_int::dump()
{
    int new_int = 0;
    return new_int = this -> _number;
}
