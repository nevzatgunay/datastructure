/*	Nevzat Günay
	200201062
*/

//	This program is not just to control one space character,it controls all of them.For example,five space characters.While you are compiling the program,you add the text.txt file like that q2 < text.txt.

#include<stdio.h>
#include<ctype.h>
main()
{
  	char c;//c holds the character from the file(text.txt).
	int state=1,space=0;//it holds the situation,that is,we control the space,'.' and '?' characters.Thanks to space variable,we check number of space characters.
	do
	{
		c =getchar();//we get a character from the file like that "q3 < text.txt".
		if(c!=' ')//when c sees a space character,it is not to run the block.
		{
			space--;		
			if(state==1)//firstly,this block runs and first character become upper case.
			{
      	  			c = toupper(c);
	  			state--;
      			}
			if(c=='.' || c=='?' || c=='!')//we control the special characters(.,?,!).
			{
	    			state=1;
				space=2;
			}	
			else
				state--;
		}
		if(c!=' ' || space!=2)//when c sees a space character,it is not to run the block.
		{
			printf("%c",c);
		}
		if(c=='.' || c=='?' || c=='!')//we control the special characters(.,?,!).
		{
	    		printf(" ");
		}	
		
				
	}while(c!=EOF);//loop runs until the end of the file.
}
