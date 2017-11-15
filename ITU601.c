#include <stdio.h>
#include <stdlib.h>
/*#include <conio.h>*/
#include <math.h>

#define FITXER_SORTIDA "test.uyvy"

#define TOTAL_LINIES 576
#define BYTES_1LINIA 1440


void Quantificar(int R,int G,int B,int *info);

int main(){

  int data[3];
  int r,g,b;
  while(1){
    scanf("%d",&r);
    scanf("%d",&g);
    scanf("%d",&b);
    Quantificar(r,g,b,data);
    printf("Y = %f\nCr = %f\nCb = %f\n",data[0],data[1],data[2]);
  }
  /*
  FILE * pFitxerSortida;                      // Punter al fitxer de sortida
  unsigned char ucBufferlinia[BYTES_1LINIA];  // Buffer de linia
  int nIndex, nLinia, nColumna;
  int nYo1, nYo2, nUo1,nVo2;



  // Obrim el fitxer de sortida test.uyvy
  if ( (pFitxerSortida = fopen(FITXER_SORTIDA,"wb")) != NULL )
    {
      // Bucle del total de linies de la imatge
      for ( nLinia = 0; nLinia < TOTAL_LINIES; nLinia++ )
	{
	  // Bucle que recorre les mostres d'una linia
	  for ( nColumna = 0; nColumna < BYTES_1LINIA; nColumna = nColumna+4)
	    {
	      // exemple: blanc
	      nYo1=235;  // mostra de Y
	      nUo1=128;  // mostra de U
	      nYo2=235;  // mostra de Y
	      nVo2=128;  // mostra de V

	      ucBufferlinia[nColumna]     = nUo1;  // Modificarem el valor
	      ucBufferlinia[nColumna + 1] = nYo1;  // dels dos pixels de la
	      ucBufferlinia[nColumna + 2] = nVo2;  // matriu amb els valors
	      ucBufferlinia[nColumna + 3] = nYo2;  // de sortida
	    }

	  // Copiem les mostres d'una linia al fitxer de sortida
	  fwrite( ucBufferlinia, BYTES_1LINIA , 1, pFitxerSortida);
	}
      printf("\nFitxer %s generat!\n",FITXER_SORTIDA);

      fclose(pFitxerSortida);		// Tanquem el fitxer de sortida
    }
  else
    {
      printf("\nError. No es pot crear el fitxer %s\n",FITXER_SORTIDA);
    }
    */
  return 0;
}


/*
  @Params:
    R: Component R de la mostra
    G: Component G de la mostra
    B: Component B de la mostra
    info: guarda la informacio obtinguda de quantificar.
      info[0] guarda la Yq
      info[1] guarda la Cr
      info[2] guarda la Cb
*/
void Quantificar(int R,int G,int B,int *info){

  double Yq, Y, Cr, Cb;

  Y  = R * 0.3 + G * 0.59 + B * 0.11;
  Yq = round(219 * Y + 16);
  Cb = round(224 * 0.564 * (B - Y) + 128);
  Cr = round(224 * 0.713 * (R - Y) + 128);

  info[0] = Yq;
  info[1] = Cr;
  info[2] = Cb;
}
