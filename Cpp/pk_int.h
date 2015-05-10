#ifndef PK_INT
#define PK_INT
class pk_int
{
    private:
	int _number;
    public:
	pk_int();
	pk_int(int standart_int);
	pk_int operator + (const pk_int & num);
	pk_int operator - (const pk_int & num);
	pk_int operator * (const pk_int & num);
	pk_int operator / (const pk_int & num);
	pk_int & operator= (const pk_int & num);
	int dump();
};
     
#endif
