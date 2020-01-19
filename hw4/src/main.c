#include<stdio.h>
#include<string.h>

int readMap ( int r, int c, int m[][2000] ) { 
	int i,j;

	for (i=0;i<r;i++)
		for (j=0;j<c;j++) 
			if ( scanf("%d",&m[i][j])!=1 ) 
				return 0;
	return 1;	 				
} 

int main ( void ) {
	static int map[2000][2000];
	int result,rows,cols,i,j,budget,subRow,rowLimit,subCol,colLimit,startRow,startCol;
	int count = 0;
	int sum = 0;
	char task[5];
	
	printf ("Velikost mapy:\n");
	if (scanf("%d %d",&cols,&rows)!=2 || rows<1 || rows>2000 || cols<1 || cols>2000) 
	{
		printf("Nespravny vstup.\n");	
		return 1;
	}

	printf("Cenova mapa:\n");
	
	if (! readMap(rows,cols,map))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Dotazy:\n");
	while (1) { 
		result=scanf ("%5s %d", task, &budget); 
		if (result==EOF) 
			break;
				
		if ( result!=2 )
		{ 
			printf("Nespravny vstup.\n"); 
			return 1;
		}
		
		if (strncmp(task,"count", 5)==0) { 
			for ( subRow = rows;subRow>=1;subRow-- ) { 
				rowLimit = rows - subRow+1;
				for (subCol=cols;subCol>=1;subCol--) { 
					colLimit = cols-subCol+1;
					for (startRow=0;startRow<rowLimit;startRow++) {
						for (startCol=0;startCol<colLimit;startCol++) {
							for (i=0;i<subRow;i++) {
								for (j=0;j<subCol;j++) {
									sum+=map[i+startRow][j+startCol];
								}
							}
							if (sum==budget)
								count++;
							sum = 0;
						}
					}
				}
			}
			printf("Celkem: %d\n",count);
			count = 0;
		}
		else if (strncmp(task,"list",4)==0) {
			for ( subRow = rows;subRow>=1;subRow-- ) { 
				rowLimit = rows - subRow+1;
				for (subCol=cols;subCol>=1;subCol--) { 
					colLimit = cols-subCol+1;
					for (startRow=0;startRow<rowLimit;startRow++) {
						for (startCol=0;startCol<colLimit;startCol++) {
							for (i=0;i<subRow;i++) {
								for (j=0;j<subCol;j++) {
									sum+=map[i+startRow][j+startCol];
								}
							}
							if (sum==budget)
							{
								count++;
								printf("%d @ (%d,%d) - (%d,%d)\n", budget, startCol, startRow, (startCol+subCol)-1, (startRow+subRow)-1);
							}
							sum = 0;
						}
					}
				}
			}
			printf("Celkem: %d\n",count);
			count = 0;	
		}
		else
		{
			printf("Nespravny vstup.\n");
			return 1;
		}		
	}
	return 0;
}
