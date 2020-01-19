#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readConstruct ( int ** data, int * cNum, int *max ) {
	
	int num = 0;
	char char2[3];
	
	while (1) { 
		if ( scanf ( "%d%1s", &num, char2 ) == 2 )
		{
				
			
			if ( num<0 )
			{ 
				return 0;
			} 		
				
			if ( *cNum >= *max ) 
			{
				if ( *max < 1000 ) 
					*max += 100;
				else
					*max += *max / 2;
				* data = (int*)realloc ( * data, *max * sizeof ( **data ) );
			}
			(*data)[(*cNum)++] = num;
			if ( strcmp( char2, "," ) != 0 )
			{ 
				if ( strcmp( char2, "]" ) == 0 )
				{	
					break;
				}	
				else
				{	
					return 0;
				}	
			}
		}
		else
		{
			return 0;
		}	
	}
	return 1;
}
	
int main ( void ) { 

	int n = 0, maximum = 0, result = 0, load1 = 0, load2 = 0, minL = 0, temp = 0, i = 0, LFrom = 0, num = 0;
	
	char task[10]="";
	char char1[3];
	char char3[3];
	char char4[3];
	
	int * construct = NULL;
	
	int resConst = 0, cnt = 0;
	
	while (1) {
		cnt++;
		if ( cnt == 1 ) 
			printf ( "Prikazy:\n" ); 	
		
		result = scanf ( "%9s", task );
		
		if ( strcmp ( task, "" ) == 0 ) 
		{ 
			printf ( "Nespravny vstup.\n" );
			return 1;	
		}
			
		if ( result == EOF )
			break;
		if ( result == 1 ) 
		{ 	
			if ( strcmp ( task, "construct" ) == 0) 
			{ 	
				if ( scanf ( "%1s", char1 ) != 1 )
				{
					printf ( "Nespravny vstup.\n" );
					free ( construct );	
					return 1;
				}		
				resConst = readConstruct ( &construct , &n, &maximum );
				
				if ( ! resConst )
				{ 
					printf ( "Nespravny vstup.\n" );
					free(construct);
					return 1;
				}		
			}
			else if ( strcmp ( task, "load" ) == 0 ) 
			{
				if ( construct == NULL ) 
				{
					printf ("Nespravny vstup.\n");
					return 1;
				}			
				
				if ( scanf ( "%d %d", &load1, &load2 ) != 2 )
				{ 
					printf ( "Nespravny vstup.\n" );
					free(construct);
					return 1;	
				}
				
				if ( ( load1>load2 ) || load1 < 0 || load2 < 0 || load2>=n )
				{ 
					printf ( "Nespravny vstup.\n" ); 
					free(construct);
					return 1;
				}		
				
				minL = construct[load1];
				
				if ( load1==load2 )
					printf ( "Maximalni naklad: %d\n", construct[load1] );
				else
				{	
					for ( i=load1; i<=load2; i++ ) {
					
						if ( i == 0 || construct[i] < minL ) 
						{		
							minL = construct[i];
						}		
					}
					printf ( "Maximalni naklad: %d\n", minL );
				}
				
			}	
			else if ( strcmp ( task, "limits" ) == 0 )
			{
				if ( construct == NULL ) 
				{
					printf ("Nespravny vstup.\n");
					return 1;
				}	
				if ( scanf ( "%d %1s",&LFrom, char3 ) != 2 || LFrom > n ) 
				{ 
					printf ( "Nespravny vstup.\n" ); 
					free(construct);
					return 1;
				}
				temp = 0;	
				while (1) { 
					if ( scanf ( "%d%1s", &num, char4 ) == 2 ) 
					{ 
						
						temp = LFrom;
						temp++;
						
						if ( temp > n || num < 0) 
						{ 	
							printf ( "Nespravny vstup.\n" );
							free(construct);
							return 1;							
						}
						
						construct[LFrom] = num;
						LFrom++;
						
						if ( strcmp ( char4, "," ) != 0 ) 
						{ 
							if ( strcmp ( char4, "]" ) == 0 )
							{
								break;
							}
							else
							{		
								printf ( "Nespravny vstup.\n" );
								return 1;		
							}	
						} 		

					}
					else 
					{
						printf ( "Nespravny vstup.\n" );
						free(construct);
						return 1;	
					}		
				}
			}
			else
			{
				printf ( "Nespravny vstup.\n" ); 
				free(construct);
				return 1;
			} 		
		}
		else
		{ 
			printf ( "Nespravny vstup.\n" );
			free(construct);
			return 1;
		}
	}	
	
	free(construct);
	return 0;
}
