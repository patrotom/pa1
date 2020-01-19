#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>

typedef struct TSoldier
{
	struct TSoldier   * m_Next;
	int m_PersonalID;
	char m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

void createDivision ( int * temp, TSOLDIER ** platoon, TSOLDIER *** recruitment ) { 
	int i = 0;

	for ( i = (*temp); i != 0; i-- ) { 
		**recruitment = *platoon;
		*recruitment = &(*platoon)->m_Next;
		*platoon = **recruitment;	
	}
}

void bootCamp ( TSOLDIER ** platoon, TSOLDIER ** src, int * size ) { 
	
	for ( ( *platoon ) = ( *src ); ( *platoon ) != NULL; ( *platoon ) = ( *platoon )->m_Next )
		( *size )++;
}	

TSOLDIER * mergePlatoons ( TSOLDIER * p1, TSOLDIER * p2 ) {
	
	TSOLDIER *outcome = NULL, **recruitment = &outcome;
	
	/*if ( p1 == NULL ) 
		return p1;
	if ( p2 == NULL ) 
		return p2;*/
	
	while ( p1 != NULL || p2 != NULL ) { 
		if ( p1 != NULL )
		{	
			*recruitment = p1;
			recruitment = &p1->m_Next;
			p1 = *recruitment;
		}		
		if ( p2 != NULL )
		{	
			*recruitment = p2;
			recruitment = &p2->m_Next;
			p2 = *recruitment;
		}
	}
	
	*recruitment = NULL; 
	
	return outcome;		
}

void splitPlatoon ( TSOLDIER * src, TSOLDIER ** p1, TSOLDIER ** p2 ) {
	
	TSOLDIER *platoon;
	TSOLDIER **recruitment;
	
	int size = 0, temp = 0;
	
	*p1 = NULL;
	*p2 = NULL;
	
	bootCamp ( &platoon, &src, &size ); //Vytvorenie velkosti caty
	
	platoon = src;
	temp = size / 2; /*Dat to na polku, osetrit vojaka naviac*/
	
	/*Cata 1 po splite !*/
	
	recruitment = p1;
	createDivision ( &temp, &platoon, &recruitment ); //Vytvorenie caty 1 zo spolocnej caty.
	*recruitment = NULL;
	
	/*Cata 2 po splite !*/
	
	recruitment = p2;
	createDivision ( &temp, &platoon, &recruitment ); //Vytvorenie caty 2 zo spolocnej caty.	
	*recruitment = NULL;
	
	free ( platoon ); /*Treba uvolnit catu !!!*/
}

void dismissSoldiers ( TSOLDIER ** src, TSOLDIER ** platoon ) { 
	
	while ( ( *src ) != NULL) { 
		( *platoon ) = ( *src )->m_Next;
		free ( ( *src ) );
		( *src ) = ( *platoon );
	}
}	
 
void destroyPlatoon ( TSOLDIER * src ) {
	
	TSOLDIER *platoon;

	dismissSoldiers ( &src, &platoon ); 	
}
  
#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) { /*TESTOVANIE*/ }
#endif /* __PROGTEST__ */
