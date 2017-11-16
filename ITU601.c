#include <stdio.h>
#include <stdlib.h>
/*#include <conio.h>*/
#include <math.h>

#define FITXER_SORTIDA "test.uyvy"

#define TOTAL_LINIES 576
#define BYTES_1LINIA 1440

void SenyalTipus5(unsigned char * buffer,int pos);
void SenyalTipus4(unsigned char * buffer,int pos);
void Quantificar(int R,int G,int B,int R2,int G2,int B2,int *info);

int main(){

  FILE * pFitxerSortida;                      // Punter al fitxer de sortida
  unsigned char ucBufferlinia[BYTES_1LINIA];  // Buffer de linia
  int nLinia, nColumna;


  // Obrim el fitxer de sortida test.uyvy
  if ( (pFitxerSortida = fopen(FITXER_SORTIDA,"wb")) != NULL )
    {
      // Bucle del total de linies de la imatge
      for ( nLinia = 0; nLinia < TOTAL_LINIES; nLinia++)
	{
	  // Bucle que recorre les mostres d'una linia
	  for ( nColumna = 0; nColumna < BYTES_1LINIA; nColumna = nColumna+4)
	    {
        if(nLinia < TOTAL_LINIES / 2){
          //Senyal 5
          SenyalTipus5(ucBufferlinia,nColumna);
        }else{
          //Senyal 4
          SenyalTipus4(ucBufferlinia,nColumna);
        }
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

  return 0;
}


/*
  @Params:
    R: Component R de la mostra
    G: Component G de la mostra
    B: Component B de la mostra
    info: guarda la informacio obtinguda de quantificar.
      info[0] guarda la Yq
      info[1] guarda la Cb
      info[2] guarda la Cr
*/
void Quantificar(int R,int G,int B,int R2,int G2,int B2,int *info){

  double Yq, Y,Y2, Cr, Cb,Yq2;

  Y  = R * 0.3 + G * 0.59 + B * 0.11;
  Y2 = R2 * 0.3 + G2 * 0.59 + B2 * 0.11;
  Yq = round(219 * Y + 16); // * 0.7 * 0.75??
  Yq2 = round(219 * Y2 + 16);
  Cb = round(224 * 0.564 * (B - Y) + 128);
  Cr = round(224 * 0.713 * (R - Y) + 128);

  info[0] = Cb;
  info[1] = Yq;
  info[2] = Cr;
  info[3] = Yq2;
}

void SenyalTipus4(unsigned char *buffer,int pos){
  int aux[4],U,V,Y,Y2;

  if(pos % (BYTES_1LINIA / 8) ){
    Quantificar(1,1,1,0,0,0,aux);
  }

  if(pos < BYTES_1LINIA/2){
    //BW

    U  = 0;
    Y  = round(219 * Y + 16);
    V  = 0;
    Y2 = round(219 * Y + 16);

  }else{
    //Color

    U  = aux[0];
    Y  = aux[1];
    V  = aux[2];
    Y2 = aux[3];
  }

  //Al ser 4:2:2 la Yf es diferent a Y perque es la lluminancia del segon px.
  buffer[pos]     = U;
  buffer[pos + 1] = Y;
  buffer[pos + 2] = V;
  buffer[pos + 3] = Y2;

}

void SenyalTipus5(unsigned char *buffer,int pos){
  //Senyal controlada unicament per Y
  int Y = 0;
  int Yq = 0;
  double m = 0;

  //El pic esta a la pos 13us
  //Definim la funcio del triangle.
  if(6.5 < pos % 13){
    //Priera meitat del triangle
    m = 0.7/13;
  }else{
    //Segona meitat del triangle
    m = -0.7/13;
  }

  Y = m * pos;
  Yq = round(219 * Y + 16);
  //Yq *= 0.7; //ponderem el senyal?

  buffer[pos]     = 0;  // No existeix Cb
  buffer[pos + 1] = Yq;
  buffer[pos + 2] = 0;  // No existeix Cb
  buffer[pos + 4] = Yq2;

}
