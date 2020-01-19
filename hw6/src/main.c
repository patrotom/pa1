#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

void writeLines ( char ** Lns, int *Count, int *Max, char Char ) {
	
	if ( *Count >= *Max ) 
	{ 
		if ( *Max < 10000 ) 
			*Max += 1000;
		else 
			*Max += *Max / 2;
		*Lns = (char *)realloc ( *Lns, *Max * sizeof ( **Lns ) );	
	}
	
	(*Lns)[(*Count)++] = Char;
} 

int wrongInput ( char Char ) {
	
	if ( (int)Char != 10 )
	{
		if ( (int)Char == 32 )
			return 1;
		if ( (int)Char < 65 )
			return 0;	
		if ( (int)Char > 90 && (int)Char < 97 )
			return 0;
		if ( (int)Char > 122 )
			return 0;
	}	
	return 1;
}

int readWords ( char *** data, int *cStr ) { 
		
	int result = 0, cChar = 0, maxChar = 0, maxStr = 0;
	char character;
	char *lines = NULL;
	
	(*cStr) = 0;
	while (1) { 
		
		result = scanf ( "%c", &character );
		
		if ( ! ( wrongInput ( character ) ) )
		{
			free ( lines );	
			return 0;	
		}
		if ( result == EOF ) 
		{ 
			free ( lines );
			return 1;
		} 	
		
		if ( result == 1 ) 
		{ 
			writeLines ( &lines, &cChar, &maxChar, character ); 	
			
			if ( character == '\n' ) 
			{ 		
				lines[cChar] = '\0';
				
				if ( *cStr >= maxStr )
				{ 
					if ( maxStr < 10000 ) 
						maxStr += 1000;
					else 
						maxStr += maxStr / 2;
					*data = (char**)realloc ( *data, maxStr * sizeof ( char* ) );
				}	
				
				(*data)[(*cStr)] = (char *)malloc ( ( strlen ( lines ) +1 ) * sizeof ( char ) );
				strncpy ( (*data)[(*cStr)], lines, ( strlen ( lines ) + 1 ) );
				
				(*cStr)++;
				
				cChar = 0;
				maxChar = 0;
			}
		} 
		else
		{
			free ( lines );
			return 0;
		}	
	}
	free ( lines );
	return 1;
} 

int main ( void ) { 
	
	char ** words = NULL;
	char ** lowerWords = NULL;
	
	unsigned int k;
	int countStr = 0, i, j;
	char *temp;
	if ( ! ( readWords ( &words, &countStr ) ) )
	{	
		printf ( "Nespravny vstup.\n" );
		for ( i=0; i<countStr; i++ )
			free ( words[i] );
		free ( words );
		return 1;
	}
		
	lowerWords = (char**)malloc ( countStr * sizeof ( char*) );
	
	for ( i=0; i < countStr; i++ ) { 
		lowerWords[i] = (char*)malloc ( ( strlen ( words[i] ) + 1  ) * sizeof ( char ) ); 
		for ( k=0; k < strlen ( words[i] ); k++ )
			lowerWords[i][k] = tolower(words[i][k]); 
		lowerWords[i][k] = '\0';
	} 	
	
	setlocale ( LC_COLLATE, "cs_CZ.utf8" );
	
	for (i = 1; i < countStr; i++) {
		for (j = 1; j < countStr; j++) {
			if ( strcoll(lowerWords[j - 1], lowerWords[j]) > 0 ) {
				
				temp = (char *) malloc ((strlen ( words[j-1] ) + 1) * sizeof (char));
				strncpy( temp, words[j - 1], ( strlen ( words[j-1] ) + 1 ));
				free(words[j-1]);
				words[j-1] = (char *) malloc ((strlen ( words[j] ) + 1) * sizeof (char));
				strncpy( words[j - 1], words[j], ( strlen ( words[j] ) + 1 ) );
				free(words[j]);
				words[j] = (char *) malloc ((strlen ( temp ) + 1) * sizeof (char));
				strncpy( words[j], temp, ( strlen ( temp ) + 1 ) );
				free(temp);
				
				temp = (char *) malloc ((strlen ( lowerWords[j-1] ) + 1) * sizeof (char));
				strncpy( temp, lowerWords[j - 1], ( strlen ( lowerWords[j-1] ) + 1 ));
				free(lowerWords[j-1]);
				lowerWords[j-1] = (char *) malloc ((strlen ( lowerWords[j] ) + 1) * sizeof (char));
				strncpy( lowerWords[j - 1], lowerWords[j], ( strlen ( lowerWords[j] ) + 1 ) );
				free(lowerWords[j]);
				lowerWords[j] = (char *) malloc ((strlen ( temp ) + 1) * sizeof (char));
				strncpy( lowerWords[j], temp, ( strlen ( temp ) + 1 ) );
				free(temp);
			}
		}
	}
	
	for ( i=0; i<countStr; i++ )
		printf ( "%s", words[i] );
	
	for ( i=0; i<countStr; i++ )
		free ( words[i] );
	for ( i=0; i<countStr; i++ )
		free ( lowerWords[i] );
	
	free ( words );
	free ( lowerWords );
	
	return 0;
}
