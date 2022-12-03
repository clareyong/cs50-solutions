#include<stdio.h>
#include<cs50.h>

long get_number(void);
long calculate_1(long number);
long calculate_2(long number);
long calculate_3(long number);
long calculate_4(long number);
long calculate_5(long number);
long calculate_6(long number);
long calculate_7(long number);
long calculate_8(long number);
long calculate_9(long number);
long calculate_10(long number);
long calculate_11(long number);
long calculate_12(long number);
long calculate_13(long number);
long calculate_14(long number);
long calculate_15(long number);
long calculate_16(long number);

int main(void)
{
    long one;
    long number = get_number();
    one = calculate_1(number);
    printf("One: %ld \n", one);

    long two;
    two = calculate_2(number);
    printf("Two: %ld \n", two);

    long three;
    three = calculate_3(number);
    printf("Three: %ld \n", three);

    long four;
    four = calculate_4(number);
    printf("Four: %ld \n", four);

    long five;
    five = calculate_5(number);
    printf("Five: %ld \n", five);

    long six;
    six = calculate_6(number);
    printf("Six: %ld \n", six);

    long seven;
    seven = calculate_7(number);
    printf("Seven: %ld \n", seven);

    long eight;
    eight = calculate_8(number);
    printf("Eight: %ld \n", eight);

    long nine;
    nine = calculate_9(number);
    printf("Nine: %ld \n", nine);

    long ten;
    ten = calculate_10(number);
    printf("Ten: %ld \n", ten);

    long eleven;
    eleven = calculate_11(number);
    printf("Eleven: %ld \n", eleven);

    long twelve;
    twelve = calculate_12(number);
    printf("Twelve: %ld \n", twelve);

    long thirteen;
    thirteen = calculate_13(number);
    printf("Thirteen: %ld \n", thirteen);

    long fourteen;
    fourteen = calculate_14(number);
    printf("Fourteen: %ld \n", fourteen);

    long fifteen;
    fifteen = calculate_15(number);
    printf("Fifteen: %ld \n", fifteen);

    long sixteen;
    sixteen = calculate_16(number);
    printf("Sixteen: %ld \n", sixteen);

    printf("%li", two*2%10 + four*2 + six*2 + eight*2 + ten*2 + twelve*2 + fourteen*2 + sixteen*2);

    if (sixteen == 5 && (fifteen == 1 || fifteen == 2 || fifteen == 3 || fifteen == 4 || fifteen == 5))
    {
        printf("MASTER \n");
    }

    else if (sixteen == 4)
    {
        printf("VISA \n");
    }

    else if (sixteen == 0 && fifteen == 0 && fourteen == 0 && thirteen == 4)
    {
        printf("VISA \n");
    }

    else if (sixteen == 0 && fifteen == 3 && (fourteen == 4 || fourteen == 7))
    {
        printf("AMEX \n");
    }

    else
    {
        printf("INVALID \n");
    }
}

//assign the numbers from the credit card

long get_number(void)
{
    long(number);
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    return number;
}

long calculate_1(long number)
{
    long one;
    one = number % 10;
    return one;
}

long calculate_2(long number)
{
    long two;
    two = (number / 10) % 10;
    return two;
}

long calculate_3(long number)
{
    long three;
    three = (number / 100) % 10;
    return three;
}

long calculate_4(long number)
{
    long four;
    four = (number / 1000) % 10;
    return four;
}

long calculate_5(long number)
{
    long five;
    five = (number / 10000) % 10;
    return five;
}
long calculate_6(long number)
{
    long six;
    six = (number / 100000) % 10;
    return six;
}
long calculate_7(long number)
{
    long seven;
    seven = (number / 1000000) % 10;
    return seven;
}

long calculate_8(long number)
{
    long eight;
    eight = (number / 10000000) % 10;
    return eight;
}

long calculate_9(long number)
{
    long nine;
    nine = (number / 100000000) % 10;
    return nine;
}

long calculate_10(long number)
{
    long ten;
    ten = (number / 1000000000) % 10;
    return ten;
}

long calculate_11(long number)
{
    long eleven;
    eleven = (number / 100000000000) % 10;
    return eleven;
}

long calculate_12(long number)
{
    long twelve;
    twelve = (number / 100000000000) % 10;
    return twelve;
}

long calculate_13(long number)
{
    long thirteen;
    thirteen = (number / 1000000000000) % 10;
    return thirteen;
}

long calculate_14(long number)
{
    long fourteen;
    fourteen = (number / 10000000000000) % 10;
    return fourteen;
}

long calculate_15(long number)
{
    long fifteen;
    fifteen = (number / 100000000000000) % 10;
    return fifteen;
}

long calculate_16(long number)
{
    long sixteen;
    sixteen = (number / 1000000000000000) % 10;
    return sixteen;
}

// int calculate_dimes(int cents)
// {
//     int(dimes);
//     dimes = cents / 10;
//     return dimes;
// }