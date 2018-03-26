#include <stdio.h>
#include <stdlib.h>

typedef struct Complex{
    double real;
    double imag;
} Complex;
void add(Complex *result, Complex addValue){
   result->real += addValue.real;
   result->imag += addValue.imag;
}
void subtract(Complex *result, Complex subValue){
    result->real -= subValue.real;
    result->imag -= subValue.imag;
}
void multiply(Complex *result, Complex mulValue){
    result->real = (result->real * mulValue.real) - (result->imag * mulValue.imag);
    result->imag = (result->real * mulValue.imag) + (result->imag * mulValue.real);
}
void divide(Complex *result, Complex divValue){
    double denominator = (divValue.real * divValue.real) + (divValue.imag * divValue.imag);
    result->real = ((result->real * divValue.real) + (result->imag * divValue.imag))/denominator;
    result->imag = ((result->imag * divValue.real) - (result->real * divValue.imag))/denominator;
}

int main(int argc, const char *argv[])
{
    Complex result;
    Complex *resultPtr = &result;
    Complex input2;
    int operation;
    char ynContinue = 'y';
    printf("This is a calculator for complex numbers. Enter the input.(x+yi)\n");
    printf("x:");
    scanf("%lf", &result.real);
    printf("y:");
    scanf("%lf", &result.imag);
    printf("The input is %f+%fi.\n", result.real, result.imag); 
    while(ynContinue == 'y'){
        printf(" Choose the operation: 1.ADD(+) 2. SUBTRACT(-) 3.MULTIPLY(*) 4.DIVIDE(/)\n");
        scanf("%d",&operation);
        printf("Enter the other value(x+yi)\n");
        printf("x:"); 
        scanf("%lf", &input2.real);
        printf("y:");
        scanf("%lf", &input2.imag);    
       
        switch(operation){
        case 1: add(resultPtr, input2);
                break;
        case 2: subtract(resultPtr, input2);
                break;
        case 3: multiply(resultPtr, input2);
                break;
        case 4: divide(resultPtr, input2);
                break;
    }
    printf("RESULT: %lf+%lfi\n", result.real, result.imag);
    printf("Do you want to continue(y/n)?");
    scanf(" %c",&ynContinue);
    }
    return 0;
}
