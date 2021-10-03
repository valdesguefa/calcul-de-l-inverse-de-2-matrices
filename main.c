#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void affiche(int n,int m,float **A)
{
    int i,j;
    for(i=0;i<=n-1;i++)
    {
        for(j=0;j<=m-1;j++)
        {
            printf("  %f  ",A[i][j]);
        }
        printf("\n");
    }
}
void affiche_solution(int n,float *B,char *C)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("la valeur de l'inconnu %c est:%f\n",C[i],B[i]);
    }
}
void transposee(int n,float **C,float **D)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            D[j][i]=C[i][j];
        }
    }
}
void matricereduite(float **A,float **sousA,int n,int a,int b)
{
    //cette fonction extrait une matrice de dimension n-1
    //cette fonction cree la matrice sousA de taille (n-1)*(n-1)
    //elle enleve la ligne i et la colonne j de la matrice A et met le resultat dans la matrice A
    int k,kk=0,l,ll=0;
    if(n>1)
        {
        for(k=0;k<n;k++)
    {
            for(l=0;l<n;l++)
        {
                if((k!=a)&&(l!=b))
            {
                    sousA[kk][ll]=A[k][l];
                if((kk<n-1)&&(ll<n-1))
                {
                    if(ll==n-2)
                    {
                        ll=0;
                       kk++;
                    }
                     else if(ll<n-2)
                    {
                       ll++;
                    }
                }
            }
        }
    }
        }
        if(n==1)
        {
             sousA[0][0]=A[0][0];
        }

}

float determinant (int n,float ** A)
{
    //cette fonction calcule le determinant d'une matrice carre
    float det=0;
    int i,j,l,k;
    float **sousA;
    sousA=malloc((n-1)*sizeof(float*));
    for(l=0;l<n-1;l++)
    {
        sousA[l]=malloc((n-1)*sizeof(float));
    }
    //sousA est une matrice extraite de A et de dimension n-1
    if(n==2)
    {
        det=A[0][0]*A[1][1]-A[1][0]*A[0][1];
    }
    else if(n==1)
    {
        det=A[0][0];
    }
    else
    {
        j=0;
    for(i=0;i<n;i++)
    {
        matricereduite(A,sousA,n,i,j);
        det +=A[i][j]*pow(-1,i+j)*determinant(n-1,sousA);
    }
    }

    for(k=0;k<n-1;k++)
    {
        free(sousA[k]);
    }
    free(sousA);
    return det;
}
void cofacteur(int n,float ** A,float ** C)
{
     float a,b;
     int k,i,l,j;
float **sousA;
    sousA=malloc((n-1)*sizeof(float*));
    for(l=0;l<n-1;l++)
    {
        sousA[l]=malloc((n-1)*sizeof(float));
    }
 for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      matricereduite(A,sousA,n,i,j);
      b=determinant(n-1,sousA);
      a=pow(-1,i+j)*b;
      C[i][j]=a;
    }
  }

    free(sousA);
}
void produitconst(int n,float **B,float **D,float a)
{
int i,j;
  if(n>1)
  {
   for(i=0;i<n;i++)
     {
      for(j=0;j<n;j++)
        {
         B[i][j]=a*D[i][j];
        }
      }
   }
 else if(n==1)
  {
    B[0][0]=a*D[0][0];
  }
}
void inverse(int n,float d,float **A,float **B)
{
float **C;//C est la matrice comatrice de A
float **D;// D est la transposee de la matrice comatrice de A i.e transposee de C
int k,l;
float a;
C=malloc(n*sizeof(float*));
D=malloc(n*sizeof(float*));
    for(l=0;l<n;l++)
    {
        C[l]=malloc(n*sizeof(float));
         D[l]=malloc(n*sizeof(float));
    }
       cofacteur(n,A,C);
   transposee(n,C,D);
    a=(float)1/d;
    produitconst(n,B,D,a);


    for(k=0;k<n;k++)
{
    free(C[k]);
    free(D[k]);
}
free(C);
free(D);
}
void produitmat(int n,float **A,float *B,float *P)
{
    /*
    cette fonction effectue la produit d'une matrice carre de format n*n et d'un vecteur de taille n
    elle prend en parametre une matrice ,un vecteur et une matrice que contiendra la produit de la matrice et du vecteur
    */
    int i,j;
    for(i=0;i<=n-1;i++)
    {
        for(j=0;j<=n-1;j++)
        {
                P[i]+=A[i][j]*B[j];
        }

    }
}
void remplir(int n,float **A,float *B,char *C)
{
    int i,j,ii,jj,k;
      printf("vous allez entrer le nom de vos differentes inconnus\n");
     for(ii=0;ii<n;ii++)
     {
         printf("entrez le nom de la %dere/eme inconnu\n",ii+1);
         scanf("%s",&C[ii]);
     }

      printf("vous allez entrer les coefficients de chaque inconnus dans toute les equations\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
             printf("entrez le coefficient de l'inconnu %c dans la %dere/eme equation\n",C[j],i+1);
             scanf("%f",&A[i][j]);
        }
    }

    for(k=0;k<n;k++)
    {
        printf("entrez la valeur de %d equation\n",k+1);
        scanf("%f",&B[k]);
    }
}

int main()
{
    /*
    pour la resolution de ce systeme lineaire nous utiliserons une matrice carre qui stockera
    les differents coefficients des inconnus de chaque equations et un vecteur qui stockera la valeur de chaque equations
    */
    float **A,*B,*X;
    char *C;
    int i,k,n;
    float d;
    char rep;
    float **D=NULL;
    do
    {
    X=malloc(n*sizeof(float)); //le vecteur X stockera la valeur de chaque inconnue
    B=malloc(n*sizeof(float));//le vecteur B stockera la valeur de chaque equation
    C=malloc(n*sizeof(char));//le vecteur C stockera le nom des inconnus qui sont des caracteres

    printf("combien d'inconnu(s) comporte votre systeme\n");
    scanf("%d",&n);
    A=malloc(n*sizeof(float*));//la matrice A stockera les coefficients de chaque inconnus dans toutes les equations
    D=malloc(n*sizeof(float*));//la matrice D est l'inverse de la matrice A
    for(i=0;i<n;i++)
    {
        A[i]=malloc(n*sizeof(float));
        D[i]=malloc(n*sizeof(float));
    }
    remplir(n,A,B,C);
    d=determinant(n,A);
    inverse(n,d,A,D);
    //affiche(n,n,D);
    produitmat(n,D,B,X);

    affiche_solution(n,X,C);


    for(k=0;k<n;k++)
    {
        free(A[k]);
       free(D[k]);
    }
    free(A);
    free(B);
    free(C);
    free(X);
    printf("voulez vous continuer? O/N\n");
    scanf("%s",&rep);
    }while((rep=='O')||(rep=='o'));
    return 0;
}

