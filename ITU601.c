#include <stdio.h>
#include <stdlib.h>
/*#include <conio.h>*/
#include <math.h>

#define FITXER_SORTIDA "test.uyvy"

#define TOTAL_LINIES 576
#define BYTES_1LINIA 1440

int main()
{
  FILE * pFitxerSortida;                      // Punter al fitxer de sortida
  unsigned char ucBufferlinia[BYTES_1LINIA];  // Buffer de línia
  int nIndex, nLinia, nColumna;
  int nYo1, nYo2, nUo1,nVo2;

  // Obrim el fitxer de sortida test.uyvy
  if ( (pFitxerSortida = fopen(FITXER_SORTIDA,"wb")) != NULL )
    {		
      // Bucle del total de línies de la imatge
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
	      ucBufferlinia[nColumna + 1] = nYo1;  // dels dos píxels de la 
	      ucBufferlinia[nColumna + 2] = nVo2;  // matriu amb els valors
	      ucBufferlinia[nColumna + 3] = nYo2;  // de sortida
	    }

	  // Copiem les mostres d'una linia al fitxer de sortida
	  fwrite( ucBufferlinia, BYTES_1LINIA , 1, pFitxerSortida);
	}			
      printf("\nFitxer test.uyvy generat!\n");
		
      fclose(pFitxerSortida);		// Tanquem el fitxer de sortida
    }
  else
    {
      printf("\nError. No es pot crear el fitxer test.uyvy\n");
    }
  return 0;
}
