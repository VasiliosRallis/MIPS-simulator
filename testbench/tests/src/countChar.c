/*C program to count upper case, lower case and special characters in a string.*/
 
#include<stdio.h>
 
int main()
{
    char text[] = { 'C','o','M','p','U','t','e','R', NULL};
    int countL,countU,countS;
     
 
     
    //count lower case, upper case and special characters
    //assign 0 to counter variables
    countL=countU=countS=0; 
     
    for(int i=0;text[i]!='\0';i++)
    {
        //check for alphabet
        if((text[i]>='A' && text[i]<='Z') || (text[i]>='a' && text[i]<='z'))
        {
            if((text[i]>='A' && text[i]<='Z'))
            {
                //it is upper case alphabet
                countU++;
            }
            else
            {
                //it is lower case character
                countL++;
            }
        }
        else
        {
            //character is not an alphabet
            countS++; //it is special character
        }
    }
     
    return countL;
}
