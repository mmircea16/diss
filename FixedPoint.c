/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */

struct __int8_8
{
	unsigned padding1: 8;
	unsigned q:8;
	unsigned p:8;
	unsigned padding2:8;
};

typedef struct __int8_8 int8_8;


#define  int8_8_new(X,Y) int8_8_new_impl(X,Y+1)
#define  int8_8_new2(X) int8_8_new_impl2(X)


#define  _int(X) *(int*)&X

#define  _int8_8(X) *(int8_8*)&X //this is not good because it will keep residues from other formats

#define comp_gt(X,Y) _int(X) > _int(Y)
#define comp_lt(X,Y) _int(X) < _int(Y)
#define comp_eq(X,Y) _int(X) == _int(Y)
#define comp_gt_eq(X,Y) _int(X) >= _int(Y)
#define comp_lt_eq(X,Y) _int(X) <= _int(Y)

#define add(X,Y) _int(X)+_int(Y)
#define add8_8(X,Y) _int8_8(add(X,Y))

#define sub(X,Y) _int(X) - _int(Y)
#define sub8_8(X,Y) _int8_8(sub(X,Y))



struct __float{
	 int mantissa :23;
	 int exp :8;
	 int sign :1;
} ;

typedef struct __float _float;

int8_8 int8_8_new_impl(int integer_part, const float no)
{
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	*(int*)x = 0;
	x->p = integer_part;
	_float* ff=&no;
	x->q = ff->mantissa >> 15;
	return *x;
}

int8_8 int8_8_new_impl2(const float no)
{
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	*(int*)x = 0;
	_float* ff=&no;
	int exp = ff->exp;
	int aux = *(int*)ff;
	aux <<= (exp-127);
	*x = _int8_8(aux);

	return *x;
}

int main()
{
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	int8_8* y=(int8_8*) malloc(sizeof(int8_8));

	int8_8 my_num=int8_8_new(1,0.2);
	int8_8 other_num=int8_8_new(2,0.25);
	int8_8 sum=int8_8_new(1,0.05);

	int d =sub(other_num,my_num);
	int8_8 dif = _int8_8(d);
	printf("%d %d\n",dif.p,dif.q);
    if (comp_eq(add8_8(other_num,my_num),sum)) printf("yaay\n");
    if (comp_eq(sub8_8(other_num,my_num),sum)) printf("yaay\n");

    int8_8 num = int8_8_new2(1.5);
    printf("Num with new constructor:%x\n",num);
	return 0;
}

