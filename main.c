#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    int time=0;
    int SOC=0;
    int SOCZ1=0;
    int baias=0;
    int SOCJump=0;
    int Counter=0;
    int Jump=0;
    int Remain=1;
    int Delta=0;
    int SOCFilter=0;

//****************************************
// Percentage of the maximum possible Filter Power
// 0 means no filter power, 100 means maximum filter power
    int FilterEffect=0;

//****************************************
//Result Output

FILE *fp;
fp=fopen("c://MyWork/CodeBlocks/stepbasefilter/ResultOutput/output.csv","w");

//**************************************
// max min functions

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}


int min(int num1, int num2)
{
    return (num1 > num2 ) ? num2 : num1;
}
//end of max min functions
//***************************************
// time loop
 for (time=0;time<=1000;++time  )
 {

// making a jump 10% at time 400
 if(time<400){SOC=time+(rand()%5);}else
 if(time<501 ){SOC=400+time*5/10;}else
 if(time<601 ){SOC=time;}else
 if(time<701){SOC=600;}else
 if(time<801 ){SOC=time;}else
 if(time<901){SOC=900;}else
    {SOC=time;
    }
//SOC=SOC+sin(time*.2)*35;
// end of making jumps
//***************************************

    Delta=SOC-SOCZ1;
    if (abs(Delta)>10 && (FilterEffect)>0)
    {Counter=0;
    Jump=Delta+baias;

    Remain=max(min(SOC,1000-SOC),1);
    Remain=min(abs(Delta),Remain);
    if (FilterEffect <1) FilterEffect=1;
    Remain=(FilterEffect)*Remain/100;

    }
    baias=Jump-(Jump*Counter)/Remain;
    SOCFilter=SOC-baias;
if ((Counter > Remain)&& Jump>1)
   {
     Counter=0;
     Jump=0;
   }
if ( abs(SOCFilter-SOC)>1 && abs(Delta)>0)
   {
     Counter++;
    SOCJump=SOC;
   }


    //printf("SOCFilter %d SOC %d time%d\n",SOCFilter,SOC,time);
    fprintf(fp,"Data;%d;%d;\n",1000-SOC,1000-SOCFilter);
//fprintf(fp,"Data;%d;%d;\n",SOC,baias);
    SOCZ1=SOC;

}
fclose(fp);
    return 0;
}
