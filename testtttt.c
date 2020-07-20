
#include <stdio.h>


int main(int argc, int **argv)
{
	int a;
	int b;
	int c;

	if (!a || !b || !c )
		printf("it must be three arguments %s\n");
	if ((a || b || c) < 0)
		printf("Non negative numbers are expected %s\n");
	if ((a || b || c) > 255)
		printf("Color value(s) must be maximun 255 %s\n");
	return(0);
}
