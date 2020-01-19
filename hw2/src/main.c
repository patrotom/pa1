#include <stdio.h>
#include<stdlib.h>

int GrComDiv(int number1, int number2) {
	int tmp;
	if(number1<number2)
	{
		tmp = number1;
		number1 = number2;
		number2 = tmp;
	}
	while(number2>0)
	{
		tmp = number1%number2;
		number1=number2;
		number2= tmp;
	}	
	return number1;
}

int Power(int base, int exponent) {
	int i;
	int number=1;
	for(i=0;i<exponent;++i)
		number *= base;
	return number;
}
	
int main(void) {
	char msg1, msg2;
	int count1_1=0;
	int count1_2=0;
	int count2_1=0;
	int count2_2=0;
	int GCD=0;
	int p=0;
	int q=0;
	int kol1=0;
	int kol2=0;
	int type1,type2,pom1,num1,num2;
	int o1=0;
	int o2=0;
	
	printf("Zpravy:\n");
	while(msg1!='\n') {
		type1=0;
		if(scanf("%c",&msg1)!=1)
		{
			printf("Nespravny vstup.\n");
			return 1;
		}	
		if((((int)msg1)<97 || ((int)msg1)>122)&&(((int)msg1)!=124)&&(msg1!='\n'))
			p++;
		if(msg1!='|')
		{
			type1=(int)msg1-97;
			count1_2+=Power(2, type1);
		}
		else 
		{
			kol1++;
			count1_1=count1_2;
			count1_2=0;
		}
		o1++;
	}
	
	while(msg2!='\n') {
		type2=0;
		if(scanf("%c",&msg2)!=1)
		{
			printf("Nespravny vstup.\n");
			return 1;
		}	
		if((((int)msg2)<97 || ((int)msg2)>122)&&(((int)msg2)!=124)&&(msg2!='\n'))
			q++;
		if(msg2!='|')
		{
			type2=(int)msg2-97;
			count2_2+=Power(2,type2);
		}
		else 
		{
			kol2++;
			count2_1=count2_2;
			count2_2=0;
		}
		o2++;
	}
	o1--;
	o2--;
	
	if(q!=0 || p!=0 || kol1!=1 || kol2 !=1 || o1==1 || o2==1)
	{
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	count1_2--;
	count2_2--;
	
	pom1=abs(count1_1-count2_1);
	
	num1=count1_1+count1_2;
	num2=count2_1+count2_2;
	
	GCD=GrComDiv(num1,num2);
	
	if((pom1%GCD)!=0)
	{
		printf("Nelze dosahnout.\n");
		return 1;
	}
	else
	{
		if((count1_1==0 && count2_1==0)||(count1_1==0 && count2_2==0)||(count1_2==0 && count2_1==0)||(count1_2==0 && count2_2==0))
			printf("Synchronizace za: 0\n");
		else
		{	
			while(1) {
				if(count1_1==count2_1)
					break;
				if(count1_1<count2_1)
					count1_1+=num1;
				else
					count2_1+=num2;
			}
		printf("Synchronizace za: %d\n",count1_1);	
		}
	}
	return 0;
}	
