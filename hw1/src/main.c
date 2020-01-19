#include<stdio.h>
#include<math.h>
#define Epsilon 1.0e-11
int main(void) {
	double vl;
	double sl;
	double vp;
	double sp;
	double prekryv;
	double vs1;
	double vv1;
	double vs2;
	double vv2;
	double vs1z;
	double vv1z;
	double vs2z;
	double vv2z;
	int velk1;
	int velk2;
	int result;
	printf("Velikost latky:\n");
	result = scanf("%lf %lf",&sl,&vl);
	if((result != 2) || (vl<=0) || (sl<=0))
	{ 
		printf("Nespravny vstup.\n");
		return 1;	
	}
	printf("Velikost plachty:\n");
	result = scanf("%lf %lf",&vp,&sp);
	if((result != 2) || (vp<=0) || (sp<=0)) 
	{
		printf("Nespravny vstup.\n");
		return 1;	
	}	
	if((vp*sp)>(vl*sl))
	{
		printf("Prekryv:\n");
		result = scanf("%lf",&prekryv);
		if((result !=1) || (prekryv)<0)
		{
			printf("Nespravny vstup.\n");
			return 1;
		}		
		if(vl==vp)
			if(prekryv>=sl)
			{
				printf("Nelze vyrobit.\n");
				return 1;
			}
		if(sl==sp)
			if(prekryv>=vl)
			{
				printf("Nelze vyrobit.\n");
				return 1;
			}
		if((sl!=sp)&&(vl!=vp))
			if((prekryv>=sl)&&(prekryv>=vl))
			{
				printf("Nelze vyrobit.\n");
				return 1;
			}		
		/*Varianta 1*/
		vs1 = (double)(fabs(sp-prekryv))/(fabs(sl-prekryv));
		vv1 = (double)(fabs(vp-prekryv))/(fabs(vl-prekryv));
		/*Overenie presnosti 1*/
		if(fabs(vs1-floor(vs1))>=Epsilon)
			vs1z = ceil(vs1);
		else
			vs1z = floor(vs1);
		if(fabs(vv1-floor(vv1))>=Epsilon)
			vv1z = ceil(vv1);
		else
			vv1z = floor(vv1);
		velk1 = vs1z*vv1z;
		/*Varianta 2*/
		vs2 = (double)(fabs(sp-prekryv))/(fabs(vl-prekryv));
		vv2 = (double)(fabs(vp-prekryv))/(fabs(sl-prekryv));
		/*Overenie presnosti 2*/
		if(fabs(vs2-floor(vs2))>=Epsilon)
			vs2z = ceil(vs2);
		else
			vs2z = floor(vs2);
		if(fabs(vv2-floor(vv2))>=Epsilon)
			vv2z = ceil(vv2);
		else
			vv2z = floor(vv2);
		velk2 = vs2z*vv2z;
		/*Vyhodnotenie*/
		if(velk1<velk2)
		{		
			printf("Pocet kusu latky: %d\n",velk1);
		}	
		else 
			printf("Pocet kusu latky: %d\n",velk2);		
	}
	else
		printf("Pocet kusu latky: 1\n");
	return 0;
}
