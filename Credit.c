#include <cs50.h>
#include <stdio.h>
#include <math.h>


bool VISA(long num , int count);
bool AMEX(long num , int count);
bool MASTER(long num , int count);

int checking(long num);
int products(int last);
int counting(long num);
int checkingodd(long num);

int main(void)
{
//geting input
    long num = get_long("Number: ");
//counting the lenght of the number by calling a method
    int i = counting(num);
//geting every second number from behind     
    int alt = checking(num);
//getting the remaining numbers by the formula given
    int odd = checkingodd(num);

    int answer = alt + odd;


//checking if the number is valid
     if(answer % 10 != 0)
   {
      printf("INVALID\n");
      return 0;
   }
//checking what is the type of the number by calling the functions
      bool A = AMEX(num,i);
      bool M = MASTER( num,i);
      bool V = VISA(num,i);

   if(A == true)
   {
     printf("AMEX\n");
   }
   else if (M == true)
   {
      printf("MASTERCARD\n");
   }
   else if (V == true)
   {
      printf("VISA\n");
   }
   else
   {
      printf("INVALID\n");
   }

}

int counting(long num){

   int count = 0;

    while(num > 0)
   {

       num  /= 10;
       count++;
   }

   return count;
}

int checking(long num){

    int altsum = 0;

    bool alt = false;

    int oddsum = 0;

     while(num > 0)
   {
      if (alt == true)
      {
         int last = num % 10;
//spliting the numbers if they cosist of more than 1 digits after multiplying by 2         
         altsum = altsum + products(last);
      }

      alt = !alt;
//by divideing the number by 10 we can remouve the last digit of the number every time
      num = num / 10;
   }

   return altsum;
}
int products(int last){

   int sum = 0;

   int multy = last*2;

   while(multy > 0)
   {
      int lastofmulty = multy % 10;
      sum = sum + lastofmulty;
      multy = multy / 10;
   }

   return sum;
}

int checkingodd(long num){
//baseicly the same as the checking function but in reverse
   int oddsum = 0;

   bool odd = false;

   while(num > 0)
   {
      if (odd == false)
      {
         int last = num % 10;
         oddsum = oddsum + last;
      }

      odd = !odd;

      num = num / 10;
   }

   return oddsum;

}

bool AMEX(long num , int count){

   bool isAMEX = false;
//geting the first two digits of a number
   int ftwo = num / pow(10,13);

   if((count == 15) && ((ftwo == 34) || (ftwo == 37)))
   {
      isAMEX = true;
   }

   return isAMEX;
}
bool MASTER(long num , int count){

    bool isMASTER = false;

   int ftwo = num / pow(10,14);

   if((count == 16) && ((ftwo == 51)
    || (ftwo == 52) || (ftwo == 53)
    || (ftwo == 54) || (ftwo == 55)))
   {
      isMASTER = true;
   }
   return isMASTER;
}

bool VISA(long num , int count){

   bool isVISA = false;

   if(count == 13)
   {

      int first = num / pow(10,12);

      if(first == 4)
      {
            isVISA = true;
      }
   }
   else if(count == 16)
   {
      int first = num / pow(10,15);

      if(first == 4)
      {
         isVISA = true;
      }

   }
   return isVISA;
}
