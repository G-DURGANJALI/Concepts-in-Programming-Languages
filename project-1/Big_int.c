#include <stdio.h>
#include <string.h>

#define MAX_SIZE 309

// structure definition for each BigInt data type
typedef struct {
    int digits[MAX_SIZE];
    int size;
    int sign;
} BigInt;
// initializing the BigInt data type bits as zeroes 
void initializeBigInt(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));  // predefined library function to intialize the array of elemnets
    num->size = 0;
    num->sign=0;
}
// taking input from  the user 
void inputBigInt(BigInt *num) {
    char input[MAX_SIZE + 1]; 
    printf("Enter a bigint number: ");
    scanf("%s", input);
     initializeBigInt(num);
    if(input[0]=='-')
    {
        num->sign=1;
    }

    // Reverse the input string and convert each character to an integer
    int len = strlen(input);
   if(num->sign==0)
   
   {
       
       for (int i = 0; i < len; i++) {
        num->digits[i] = input[len - 1 - i] - '0';
      }
        num->size = len;
   }
   else{
      

    for (int i = 0; i < len-1; i++) {
        num->digits[i] = input[len - 1 - i] - '0';
    }
    num->size = len-1;
    

   }
}
//function to print the BigInt data type number

void printBigInt(BigInt *num) {
    
    if(num->sign==0){
        
        // as we have stored in reverse order so printing in the reverese order
        for (int i = num->size - 1; i >= 0; i--) 
      {
         printf("%d", num->digits[i]);
       }
      printf("\n");
    }
    else{
        // if number is negative add negative sign
        printf("-");
        for (int i = num->size - 1; i >= 0; i--)
         {
           printf("%d", num->digits[i]);
         }
        printf("\n");
    }
}

void addBigInt(BigInt *result, BigInt *num1, BigInt *num2);
void subtractBigInt(BigInt *result, BigInt *num1, BigInt *num2);
void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2);
int main() {
    BigInt num1, num2, result;
    initializeBigInt(&num1);
    initializeBigInt(&num2);
    inputBigInt(&num1);
    inputBigInt(&num2);

   // enter 1 for additon 
   // enter 2 for subtraction
   // enter 3 for multiplication 
    int option;
    printf("enter the option you want to find ");
    scanf("%d",&option);
    
     switch(option)
     {
         case 1: initializeBigInt(&result);
                 addBigInt(&result, &num1, &num2);
                   printf("Addition: ");
                  printBigInt(&result);
                  break;

        case 2: initializeBigInt(&result);
                subtractBigInt(&result, &num1, &num2);
                 printf("\n Subtraction: ");
                 printBigInt(&result);
                 break;

       case 3:  initializeBigInt(&result);
                multiplyBigInt(&result, &num1, &num2);
                printf("\n Multiplication: ");
                 printBigInt(&result);
                 break;

        default: printf("invalid option ");
                 break;

     }

    return 0;
}
void subtractBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    // Implementation of subtraction here
    int max_size;
    //for finding the size of biggest number
    if(num1->size>num2->size)
    {
        max_size=num1->size;
    }
    else
    {
        max_size=num2->size;
    }
    // if both has the same sign we remove the sign outside and perform subtraction
  if(num1->sign==0&&num2->sign==0||num1->sign==1&&num2->sign==1){
      int borrow=0;
      result->size=max_size+1;   
      num1->digits[max_size]=1;  //to know whether the first number is larger or second number
      
    for (int i = 0; i <= max_size; i++) {
        int diff = num1->digits[i] - num2->digits[i] - borrow;

        if (diff < 0) 
        {
          
          
            diff += 10;  // Borrow from the next higher digit
            borrow = 1;
              
          
          
        } 
        else {
            borrow = 0;
        }

        result->digits[i] = diff % 10;  // Store the least significant digit
      }
        // if the last bit is one first number is larger as the borrow is not used 
         if(result->digits[max_size]==1)
        {
            result->sign=num1->sign;
            result->digits[max_size]=0;
            result->size=max_size;
        }
        else
        {
            //first number is smaller than second number the answer in the form of 10's compliment form
            // we have to find the 10's compliment of this number to get the correct answer
         
          // finding 10's compliment 
          result->digits[max_size]=0;
           result->digits[0]=10-result->digits[0];
          int  carry=(result->digits[0])/10;
          result->digits[0]=(10-result->digits[0])%10;
          for(int i=1;i<max_size;i++)
          {
              result->digits[i]=  9 - result->digits[i]+carry;
              carry=(result->digits[i])/10;
               result->digits[i]= (result->digits[i])%10;
          }
            result->size=max_size;
            
            if(num1->sign==0)
            {
                result->sign=1;
            }
            else{
                result->sign=0;
            }
            
            
        }
        num1->digits[max_size]=0;
       
      
    }// if both of them have differnt sign we can perform addition directly
    
    else if(num2->sign==1)
    {
        num2->sign=0;
        addBigInt(result,num1,num2);
        result->sign=0;
        num2->sign=1;
    }
    else
    {
        num1->sign=0;
        addBigInt(result,num1,num2);
        result->sign=1;
        num1->sign=1;
    }
    
    result->size=max_size;
    
}
void addBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    // Implementation of addition here
     int carry = 0;
     // if both the numbers have same sign we can perform addition directly
  if(num1->sign==0&&num2->sign==0||num1->sign==1&&num2->sign==1)
  {
    for (int i = 0; i < MAX_SIZE; i++) {
        int sum = num1->digits[i] + num2->digits[i] + carry;
        result->digits[i] = sum % 10;  // Store the least significant digit
        carry = sum / 10; 
    }

    
    for (int i = MAX_SIZE - 1; i >= 0; i--) {
        if (result->digits[i] != 0) {
            result->size = i + 1;
            break;
        }
    }
    
    result->sign=num1->sign;  // setting the sign of result as one of the number sign as both have sam sign 
  }// if sign of both numbers is different then we can perform subtraction directly
  else if(num1->sign==0)
  {
    num2->sign=0;
    subtractBigInt(result,num1,num2);
    num2->sign=1;
    


  }
  else
  {
    num1->sign=0;
    subtractBigInt(result,num2,num1);
    num1->sign=1;

  }
    
}

void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    // Implementation of multiplication here
      for (int i = 0; i < MAX_SIZE; i++) {
        int carry = 0;

        for (int j = 0; j < MAX_SIZE - i; j++) {
            int product = num1->digits[i] * num2->digits[j] + result->digits[i + j] + carry;

            result->digits[i + j] = product % 10; // Store the least significant digit
            carry = product / 10; // Carry for the next iteration
        }
    }

    // Set the size of the result
    for (int i = MAX_SIZE - 1; i >= 0; i--) {
        if (result->digits[i] != 0) {
            result->size = i + 1;
            break;
        }
    }
    // set the sign of result
    if(num1->sign==0&&num2->sign==0||num1->sign==1&&num2->sign==1)
    {
        result->sign=0;   // if both has same sign final result will be positive
    }
    else{
        result->sign=1;
    }

}
