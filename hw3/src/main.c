#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int LeapYear (int y) {
	
	if (((y % 4)==0) && ((y % 100)!=0 || (y % 400)==0))
	{
		if (y>=4000)
		{	
			if ((y%4000)==0)
				return 0;
			else
				return 1;	
		}
		else 
			return 1;
	}
	else 
		return 0;	
}

int DaysOfMonth (int m, int y) { 
	switch (m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return 28 + LeapYear(y);
	}
	return 0;	
}

int Holidays (int m, int d) { 
	
	if ((d==1 && m==1) || (d==1 && m==5) || (d==8 && m==5) || (d==5 && m==7) || 
	     (d==6 && m==7) || (d==28 && m==9) || (d==28 && m==10) || (d==17 && m==11) || 
	     (d==24 && m==12) || (d==25 && m==12) || (d==26 && m==12))
		return 0;
	else 
		return 1;
}

/*Gauss's algorithm, Determination of the day of the week, https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week*/
int DayOfWeek ( int y, int m, int d ) { 
	int DOW = 0;
	int tmp = (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7;
	
	if (tmp>=1 && tmp<=5)
		DOW = 1;
	else 
		DOW = 0;
		
	return DOW;
} 

int Validation (int y, int m, int d) {
	if ((y>=2000) && (m>=1 && m<=12) && (d>=1 && d<=DaysOfMonth(m,y)))
		return 1;
	else 
		return 0;
}

int IsWorkDay ( int y, int m, int d ) {
	/* todo */
	
	if (Holidays(m,d)==0)
		return 0;
	else
		if (Validation(y,m,d)==1)
		{		
			if(DayOfWeek(y,m,d)==1)
				return 1;
			else 
				return 0;
		}
		else 
			return 0;
}

int CountWorkDays ( int y1, int m1, int d1, int y2, int m2, int d2, int * cnt ) {
	/* todo */
	*cnt = 0;
	
	if (Validation(y1,m1,d1)==1 && Validation(y2,m2,d2)==1 && y1<=y2)
	{
		int i,j,k;
		int countM1 = 0;
		int countM2 = 0;
		int countM3 = 0;
		int countY1 = 0;
		int countY2 = 0;
		int countA = 0;

		if (y1==y2) 
		{
			if (m1>m2)
				return 0;
			if (m1==m2)
			{	
				if (d1>d2)
					return 0;
				if (d1==d2)
					*cnt = IsWorkDay(y1,m1,d1);
				else
					for (i=d1;i<=d2;i++)
						*cnt+=IsWorkDay(y1,m1,i);
			}		
			else
			{		
				for (i=d1;i<=DaysOfMonth(m1,y1);i++) 
				countM1+=IsWorkDay(y1,m1,i);
		
				for (i=1;i<=d2;i++) 
				countM2+=IsWorkDay(y2,m2,i);
					
				for (i=(m1+1);i<=(m2-1);i++)
					for (j=1;j<=DaysOfMonth(i,y1);j++)
						countM3+=IsWorkDay(y1,i,j);
				*cnt = countM1+countM2+countM3;
			}
		}
		else
		{	
			for (i=d1;i<=DaysOfMonth(m1,y1);i++) 
				countM1+=IsWorkDay(y1,m1,i);
		
			for (i=1;i<=d2;i++) 
				countM2+=IsWorkDay(y2,m2,i);
			
			for (i=(m1+1);i<=12;i++)
				for (j=1;j<=DaysOfMonth(i,y1);j++)
					countY1+=IsWorkDay(y1,i,j);
			
			for (i=1;i<=(m2-1);i++)
				for (j=1;j<=DaysOfMonth(i,y2);j++)
					countY2+=IsWorkDay(y2,i,j);
			
			if((y2-y1)==1)
				*cnt = countM1+countM2+countY1+countY2;
			else
			{
				for(i=(y1+1);i<=(y2-1);i++)
				{		
					for(j=1;j<=12;j++)
					{
						for(k=1;k<=DaysOfMonth(j,i);k++)
							countA+=IsWorkDay(i,j,k);
					}	
				}
				*cnt = countM1+countM2+countY1+countY2+countA;
			}
		}
		return 1;	
		}
	else 
		return 0;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
	int cnt;
	
	assert ( IsWorkDay ( 2016, 11, 11 ) );
	assert ( ! IsWorkDay ( 2016, 11, 12 ) );
	assert ( ! IsWorkDay ( 2016, 11, 17 ) );
	assert ( ! IsWorkDay ( 2016, 11, 31 ) );
	assert ( IsWorkDay ( 2016,  2, 29 ) );
	assert ( ! IsWorkDay ( 2004,  2, 29 ) );
	assert ( ! IsWorkDay ( 2001,  2, 29 ) );
	assert ( ! IsWorkDay ( 1996,  1,  1 ) );
	
	assert ( CountWorkDays ( 2016, 11,  1,
				2016, 11, 30, &cnt ) == 1
		&& cnt == 21 );
	assert ( CountWorkDays ( 2016, 11,  1,
				2016, 11, 17, &cnt ) == 1
		&& cnt == 12 );
	assert ( CountWorkDays ( 2016, 11,  1,
				2016, 11,  1, &cnt ) == 1
		&& cnt == 1 );
	assert ( CountWorkDays ( 2016, 11, 17,
				2016, 11, 17, &cnt ) == 1
		&& cnt == 0 );
	assert ( CountWorkDays ( 2016,  1,  1,
				2016, 12, 31, &cnt ) == 1
		&& cnt == 254 );
	assert ( CountWorkDays ( 2015,  1,  1,
				2015, 12, 31, &cnt ) == 1
		&& cnt == 252 );
	assert ( CountWorkDays ( 2000,  1,  1,
				2016, 12, 31, &cnt ) == 1
		&& cnt == 4302 );
	assert ( CountWorkDays ( 2001,  2,  3,
				2016,  7, 18, &cnt ) == 1
		&& cnt == 3911 );
	assert ( CountWorkDays ( 2014,  3, 27,
				2016, 11, 12, &cnt ) == 1
		&& cnt == 666 );
	assert ( CountWorkDays ( 2001,  1,  1,
				2000,  1,  1, &cnt ) == 0 );
	assert ( CountWorkDays ( 2001,  1,  1,
				2015,  2, 29, &cnt ) == 0 );
	return 0;
}
#endif /* __PROGTEST__ */