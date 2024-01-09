/*
   Algorithm  
   Step1: Start
   Step2: Read n number of data
   Step3: Read the value of Xi nad Yi
   Step4: Read the independent variable X1 whose corresponding value of y(i) is to be determined
   Step5: 
            for i = 1 to n
                set l=1
                for j = 1 to n
                    if i != j
                    calculate l = l*((X-Xj)/(Xi-Xj))
                    endif
                    next i
                    sum = sum + l*y(i)
                    next j
    Step6: Display value

*/

#include <stdio.h>
#include <math.h>

int main()
{
    float x1, x[20], y[20], sum = 0, l;

    int i, j, n;

    printf("Enter the value of n \n");
    scanf("%d", &n);

    printf("Enter the value to be found x1: \n");
    scanf("%f", &x1);

    printf("\nEnter the value of Xi and Yi\n");
    for (i = 0; i < n; i++)
    {
        printf("x[%d]=", i);
        scanf("%f", &x[i]);

        printf("y[%d]", i);
        scanf("%f", &y[i]);
    }

    for (i = 0; i < n; i++)
    {
        l = 1;

        for (j = 0; j < n; j++)
        {
            if (j != i)
            {
                l = l * ((x1 - x[j] / (x[i] - x[j])));
            }
        }

        sum = sum + l * y[i];
    }

    printf("The given value of x =%f", x1);
    printf("The value of y=%f\n", sum);

    return 0;
}