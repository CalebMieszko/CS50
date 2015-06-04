#include <stdio.h>

int main(void)
{
    float a, b, c;
    printf("Please enter the value you would like your chart to start at: ");
    scanf("%f", &a);
    printf("Please enter the value you would like your chart to end with: ");
    scanf("%f", &b);
    printf("Please enter the value you would like your chart to increment by: ");
    scanf("%f", &c);
    printf("\nPound to Kilogram Conversion Table\n\n");
    
    for (float i = a, j = b, k = c; i <= j; i += k)
    {
        printf("%.2f pounds = %.2f kilograms\n", i, i / 2.2046);
    }
}
