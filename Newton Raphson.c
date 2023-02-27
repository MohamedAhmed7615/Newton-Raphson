#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <math.h>
#define h 0.00000001
double polynomial(const double* coefficient, const double* power, char n, double x) {
    double y = 0;
    for (int i = 0; i < n; i++)
        y += coefficient[i] * pow(x, power[i]);
    return y;
}
double differenciate(const double* coefficient, const double* power, char n, double x) {
    return (polynomial(coefficient, power, n, x + h) - polynomial(coefficient, power, n, x)) / h;
}
void getpolynomial(double* coefficient, double* power, char* str, int* ncoeffptr, int* npowerptr) {
    char idot, dot = 0, sign;
    if (str[1] == '-')
        sign = 1;
    else
        sign = 0;
    unsigned char coeff = 1;
    char* piece = strtok(str, "+-^x*()");
    while (piece != NULL) {
        if (coeff == 1) {
            for (int i = 0; i < strlen(piece); i++)
                if (piece[i] == '.')
                {
                    idot = i; dot = 1;
                }
            if (dot == 0)
                for (int i = 0; i < strlen(piece); i++)
                    coefficient[*ncoeffptr] += (piece[i] - 48) * pow(10, strlen(piece) - 1 - i);
            if (dot == 1)
                for (int i = 0; i < strlen(piece); i++) {
                    if (i < idot)
                        coefficient[*ncoeffptr] += (piece[i] - 48) * pow(10, idot - 1 - i);
                    if (i > idot)
                        coefficient[*ncoeffptr] += (piece[i] - 48) * pow(10, idot - i);
                }
            if (sign == 1)
                coefficient[*ncoeffptr] *= -1;
            for (int i = strlen(piece); piece[i] < 48 || piece[i]>57; i++)
                if (!(piece[i + 1] < 48 || piece[i + 1]>57))
                    if (piece[i] == '-')
                        sign = 1;
                    else
                        sign = 0;
            (*ncoeffptr)++;
        }
        if (coeff == 0) {
            for (int i = 0; i < strlen(piece); i++)
                if (piece[i] == '.')
                {
                    idot = i; dot = 1;
                }
            if (dot == 0)
                for (int i = 0; i < strlen(piece); i++)
                    power[*npowerptr] += (piece[i] - 48) * pow(10, strlen(piece) - 1 - i);
            if (dot == 1)
                for (int i = 0; i < strlen(piece); i++) {
                    if (i < idot)
                        power[*npowerptr] += (piece[i] - 48) * pow(10, idot - 1 - i);
                    if (i > idot)
                        power[*npowerptr] += (piece[i] - 48) * pow(10, idot - i);
                }
            if (sign == 1)
                power[*npowerptr] *= -1;
            for (int i = strlen(piece); piece[i] < 48 || piece[i]>57; i++)
                if (!(piece[i + 1] < 48 || piece[i + 1]>57))
                    if (piece[i] == '-')
                        sign = 1;
                    else
                        sign = 0;
            (*npowerptr)++;
        }
        dot = 0;
        coeff = 1 - coeff;
        piece = strtok(NULL, "+-^x*()");
    }
}

int main()
{
    char str[200];
    double coefficient[50] = { 0 }, power[50] = { 0 }, df, f, x; int ncoeff = 0, npower = 0;
    printf("Enter a polynomial equation: \n");
    scanf("%s", str);
    getpolynomial(coefficient, power, str, &ncoeff, &npower);
    
    printf("\n\nenter the initial guess for x: \n");
    scanf("%lf", &x);
    do {
        f = polynomial(coefficient, power, npower, x);
        df = differenciate(coefficient, power, npower, x);
        x = x - f / df;
    } while (f / df > 0.0000000001);
    printf("\n\nx=");
    printf("%0.10lf\n", x);

    return 0;
}

