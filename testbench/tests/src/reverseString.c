int stringLength(char str[])
{
    int len=0,i;
    for(i=0;str[i]!='\0';i++)
        len++;
    return len;
}
int main() 
{
    char text[] = {'M','I','P','S','\0'};
    char tempChar;
    int i,length;
     
     
    //get string length
    length=stringLength(text);
     
     
     
    for(i=0;i<=(length/2);i++)
    {
        //swap elements
        tempChar=text[i];
        text[i]=text[length-i-1];
        text[length-i-1]=tempChar;
    }
    
    return text[0];
}
