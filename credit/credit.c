#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include <stdbool.h>

long get_number(void);
long hacked_get_number(void);
long calculate(long number, long digit);
int calc_special_logic(int xtracted_digit);
bool test_function(void);
long calc_even_digits(long number);
long calc_odd_digits(long number);
long calc_total(long number);

int main(void)
{

    if(!test_function())
    {
        printf("PANIKK component doesnt work \n");
        return 1;
    }

    long number;
    do
    {
        number = get_number();
    }
    while (number >= 5e16) ;


    if (calc_total(number) != 0)
    {
        printf("INVALID\n");
    }
    else if (calculate(number, 16) == 5 && calculate(number, 15) >= 1 && calculate(number, 15) <= 5)
    {
        printf("MASTERCARD\n");
    }
    else if (calculate(number, 16) == 4)
    {
        printf("VISA\n");
    }
    else if (calculate(number, 16) == 0 && calculate(number, 15) == 0 && calculate(number, 14) == 0 && calculate(number, 13) == 4)
    {
        printf("VISA\n");
    }
    else if (calculate(number, 16) == 0 && calculate(number, 15) == 3 && (calculate(number, 14) == 4 || calculate(number, 14) == 7))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }


}

//to get the number

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

long hacked_get_number(void)
{
    int option = get_int("Option no: ");
    if (option == 1){
        return 1234123412341;
    }
    if (option == 2) {
        return 4314312413241324;
    }
    return get_number();
}

//to break the numbers into single digits
long calculate(long number, long digit)
{
    long after_div = (number / (pow(10, digit-1)));
    return after_div % 10;
}

int calc_special_logic(int xtracted_digit)  // input is only from 0 to 9
{
    // if digit == 1 return 2;
    // if digit == 6 return 3;

    // result set to times 2 modulo 10
    // ({0, 1, 2, 3, 4, 5, 6, 7, 8, 9} * 2 / 10 % 10) <== {0, 0, 0, 0, 0, 1, 1, 1, 1, 1}
    // if statement: ifinput is >= 5, then add 1 to the result

    int output;
    output = xtracted_digit*2%10;
    if (xtracted_digit >= 5)
    {
        output++;
    }
    return output;
}

bool test_function() {
  if (calc_special_logic(2) != 4)
  {
    printf("case 1\n");
    return false;
  }
  if (calc_special_logic(5) != 1)
  {
      printf("case 2\n");
      return false;
  }
  if (calc_even_digits(1234567890) != 23)
  {
      printf("case 3 \n");
      return false;
  }
  if (calc_odd_digits(1234567890) != 20)
  {
      printf("case 4 \n");
      return false;
  }
  if (calc_total(1234567890) != 3)
  {
      printf("case 5 \n");
      return false;
  }
  return true;
}

//gint number = get_number();
// calc_special_logic(calculate(number, 3));

long calc_even_digits(long number)
{
    int result = 0;
    for (int i = 2; i <= 16; i+=2)
    {
        int xtracted_digit = calculate(number, i);
        result += calc_special_logic(xtracted_digit);
    }
    return result;
}

long calc_odd_digits(long number)
{
    int result = 0;
    for (int i = 1; i <= 15; i+=2)
    {
        result += calculate(number, i);
    }
    return result;
}

long calc_total(long number)
{
    int result = 0;
    result = (calc_odd_digits(number) + calc_even_digits(number))%10;
    return result;
}

//}
//for i = 2, when i <=16, i+=2
//result += calc_spe_logic(calcualate number i)

//int calc_odd_digits
//for i = 1, when i<16, i+=2
//result += calcualte number i

//check valid function to check if odd and even digits are added correctly

//make a function that is a bool to check if it is a visa card or not
//is_visa(4)
// pass the number
//visa == 4
