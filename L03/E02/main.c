#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 200
int dimfloat=(int)(sizeof(float));                                                      //INIZIALLIZZO VARIABILI CON LA DIMENSIONE DEI VARI TIPI
int dimdouble=(int)(sizeof(double));
int dimldouble=(int)(sizeof(long double));

void checkEndian(int *i){                                                               //FUNZIONE PER CONTROLLARE SE IL SISTEMA LAVORA IN BIG O LITTLE ENDIAN
    *i=1;
    char *c = (char *) i;
    if(c[0]==0)
        *i=1;
    else
        *i=0;
}

void stampaCodifica(void *r,int dim,int end){
    unsigned char *c= (unsigned char *) r;
    int *l=0;
    int x;
    char stringa[N];
    if(end==1){                                                                         //CASO BIG ENDIAN
        for(x=0;x<dim;x++)
            convertiByte(stringa,(int)(c[x]),&l,dim,x,1);
    }
    else                                                                                //CASO LITTLE ENDIAN
    {
        for(x=(dim-1);x>=0;x--)
            convertiByte(stringa,c[x],&l,dim,x,0);
    }
}


void convertiByte(char str,int n,int *t,int size,int i,int s)                           //FUNZIONE PER CONVERTIRE IL BYTE PASSATO IN BIT
{
    int k;
    if(s==0)                                                                            //CASO LITTLE ENDIAN
    {
        for(k=7;k>=0;k--)
        {
            if(n>=pow(2,k))
            {
                str[t]='1';
                n=n-(pow(2,k));
            }
            else
            {
                str[t]='0';
            }
            printf("%c",str[t]);                                                        //STAMPO IL BIT
            if((k==7)&&(i==(size-1)))    printf("\nEsponente:\n-->");                   //INIZIANO I BIT DELL'ESPONENTE
            if(size==dimfloat)                                                          //CASO FLOAT
            {
                if((k==7)&&(i==(size-2))) printf("\nMantissa:\n-->");                   //DOPO 8 BIT DELL'ESPONENTE INIZIA LA MANTISSA NEL CASO FLOAT
            }
            if(size==dimdouble)                                                         //CASO DOUBLE
            {
                if((k==4)&&(i==(size-2))) printf("\nMantissa:\n-->");                   //DOPO 11 BIT DELL'ESPONENTE INIZIA LA MANTISSA NEL CASO DOUBLE
            }
            if(size==dimldouble)                                                        //CASO LONGDOUBLE
            {
                if((k==0)&&(i==(size-2))) printf("\nMantissa:\n-->");                   //DOPO 15 BIT DELL'ESPONENTE INIZIA LA MANTISSA NEL CASO LONG DOUBLE
            }
            *t=*t+1;
        }
    }
    else                                                                                 //CASO BIG ENDIAN
    {
        for(k=8;k>0;k--)
        {
            if(n>=pow(2,k))
            {
                str[t]='1';
                n=n-pow(2,k);
            }
            else
            {
                str[t]='0';
            }
            printf("%c",str[t]);
            if((k==7)&&(i==(size-1)))    printf("\nEsponente:\n-->");
            if(size==dimfloat)
            {
                if((k==7)&&(i==(size-2))) printf("\nMantissa:\n-->");
            }
            if(size==dimdouble)
            {
                if((k==4)&&(i==(size-2))) printf("\nMantissa:\n-->");
            }
            if(size==dimldouble)
            {
                if((k==0)&&(i==(size-2))) printf("\nMantissa:\n-->");
            }
            *t=*t+1;
        }
    }
}

int main()
{
    int endian;
    float af;
    double ad;
    long double ald;
    checkEndian(&endian);                                                                   //CHIAMO LA FUNZIONE PER CONTROLLARE L'ENDIAN DI SISTEMA
    if(endian==1)
        printf("Il sistema lavora in big endian.");
    else
        printf("Il sistema lavora in little endian.");
    printf("\n\nFloat:%d byte.",dimfloat);                                                  //STAMPO LE VARIE DIMENSIONI DEI VARI TIPI
    printf("\nDouble:%d byte.",dimdouble);
    printf("\nLong double:%d byte.",dimldouble);
    printf("\n\nScrivere un numero:  ");                                                    //RICEVO DA TASTIERA IL NUMERO
    scanf("%f",&af);
    ad=(double)(af);
    ald=(long double)(ald);
    printf("\n\nIn float: \nSegno:\n-->");
    stampaCodifica((void *) &af,dimfloat,endian);
    printf("\n\nIn double: \nSegno:\n-->");
    stampaCodifica((void *) &ad,dimdouble,endian);
    printf("\n\nIn long double: \nSegno:\n-->");
    stampaCodifica((void *) &ald,dimldouble,endian);
    return 0;
}
