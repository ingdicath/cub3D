#include<stdio.h>

int main(int argc, char **argv)
{
    argv [] = {"pajarito malo"},{"hola"};
    
    
    printf("Pajarito malo\n");
    printf("Valor de argc: %d\n", argc);
    printf("Valor de argv: %s\n", argv[0]);
    printf("Valor de argv: %s", argv[1]);
    return (0);
}