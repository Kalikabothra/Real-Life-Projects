#include<stdio.h>
#include<math.h>

int main()
{
    int choice,n,i;
    float result=0.0,num,num1,num2,product=1.0;
    
    while(1)      //infinite loop which continues unless a break statement is witnessed inside the loop
    {
    printf("Choose one of the following options:\n");
    printf("1. Add \n2. Subtract \n3. Multiply\n4. Divide\n5. Modulus\n6. Power\n7. Exit\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    if(choice==7)
    break;
    else
        switch(choice)
    {
        case 1:
        printf("Enter the no. numbers you want to add:\n");
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        {
            printf("Enter the number: ");
            scanf("%f",&num);
            result=result+num;
        }
            printf("The sum of the above numbers is = %.3f\n\n",result);
            break;

        case 2:        
            printf("Enter the numbers to be subtracted:\n");
            scanf("%f",&num1);
            scanf("%f",&num2);
            result=num1-num2;
            printf("The difference of the above numbers is = %.3f\n\n",result);
            break;

        case 3:
            printf("Enter the no. numbers you want to multiply:\n");
            scanf("%d",&n);
            for(i=1;i<=n;i++)
        {
            printf("Enter the number: ");
            scanf("%f",&num);
            product=product*num;
        }
            printf("The product of the above numbers is = %.3f\n\n",product);
            break;

        case 4:        
            printf("Enter the dividend:\n");
            scanf("%f",&num1);
            printf("Enter the divisor:\n");
            scanf("%f",&num2);
            if(num2!=0)
            {result=num1/num2;
            printf("The division of the above numbers is = %.3f\n\n",result);}
            else
            {printf("Invalid operation! Cannot divide by zero");}
            break;
        case 5:        
            printf("Enter two numbers:\n");
            scanf("%f",&num1);
            scanf("%f",&num2);
            result=(int)num1 % (int)num2;
            printf("The modulus of the above numbers is = %.3f\n\n",result);
            break;
        case 6:        
            printf("Enter the number:\n");
            scanf("%f",&num1);
            printf("Enter the power to be raised to:\n");
            scanf("%f",&num2);
            result=pow(num1,num2);
            printf("The result is = %.3f\n\n",result);
            break;

        default:
        printf("Kindly choose a valid option\n");
    } 
 } return 0;
}