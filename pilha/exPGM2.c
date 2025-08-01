#include <stdio.h>
#include <string.h>  // para usar a fun��o strcmp() que compara duas strings
#include <stdlib.h>  // para usar a fun��o exit() que interrompe (aborta) a execu��o do programa.
#include "fila_hierarquica.h"

typedef struct fila_hierarquica FilaH;

typedef unsigned char Tpixel; // tipo Tpixel para valores em [0, 255]

typedef struct TPpgm { /// descritor para imagens tipo PGM
      char tipo[3]; /// "P1", "P2", "P3"
      int w;     // largura da imagem em pixels (TC - Total de pixels em cada coluna da imagem)
      int h;     // altura da imagem em pixel   (TL - Total de pixels em cada linha da imagem )
      int max;   // valor de brilho m�ximo registrado na imagem (use 255 sempre)
      int pixlen;   // total de pixels (em todas as bandas) da imagem
      Tpixel *pix; // ponteiro para o reticulado (matriz) da imagem alocada como um vetor.
    } TPpgm;

void ReadPGM(const char *fname, TPpgm *img) {
    FILE *fd;   /// img->tipo

    printf("\n ..... (Abrindo ARQUIVO )-->%s.", fname);
    fd = fopen(fname, "r");  // modo "r" --> abrir somente para leitura
       if (!fd) {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.\n\n", fname);
        exit(1);  // ERRO 1: arquivo inexistente ou n�o encontrado no caminho especificado.
         // encerra a execu��o do programa e fecha todos os arquivos abertos
       }
    printf("\n ..... (Abriu ARQUIVO )-->%s.", fname);
    fscanf (fd, "%s\n", img->tipo); /// vetor de char � ponteiro
    
    fscanf (fd, "%d\n", &img->w); /// largura da imagem
    fscanf (fd, "%d\n", &img->h); /// altura da imagem

    if (((strcmp(img->tipo, "P1") != 0))) { ///se a imagem n�o � bin�ria (P1), LER o
        fscanf (fd, "%d\n", &img->max); /// valor de brilho m�ximo na imagem
    }

    
     /// se a imagem � bin�ria (P1) ou em escala de cinza (P2)
    img->pixlen = 1*(img->w * img->h); //cada pixel tem 1 componente (valor de brilho)

    if (((strcmp(img->tipo, "P3")) == 0)) { ///se a imagem � colorida
        img->pixlen = 3*(img->w * img->h); //cada pixel tem 3 componentes (R,G,B)
    }
    printf("\n ..... (Total de pixels --> %d.", img->pixlen);
    printf("\n ..... (Leu Cabecalho )-->%s.", fname);
    int paux;
    img->pix = (Tpixel*)malloc(sizeof(Tpixel) * (img->pixlen));
    if (!img->pix) {
        printf("\n vetor de pixels nao alocado ....");
        exit(1);
     }

    for (int k=0; k<img->pixlen; k++){
        fscanf (fd, "%d", &paux);
        img->pix[k] = (Tpixel) paux; /// fscanf (fd, "%d ", *(p + k));
       }
    printf("\n ..... (Leu ARQUIVO )-->%s.", fname);
    fclose(fd);
} /// readpgm

void WritePGM(const char *fname, TPpgm *img) { 
    printf("\nAbriu");
    FILE *fd;

    fd = fopen(fname, "w");  /// modo "w" --> abrir para escrita
    if (!fd) {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.", fname);
        exit(1);  // algum c�digo de erro - Arquivo nao existe.
    }
    printf("\n ..... (ARQUIVO Aberto)-->%s.", fname);

    ///gravar no arquivo o cabe�alho de imagens PGM cinza

    fprintf(fd, "%s\n", img->tipo); ///  assinatura PGM:
            /// color "P3", cinza "P2" ou binario "P1"
    fprintf(fd,"%d %d\n", img->w, img->h);

    if (strcmp(img->tipo, "P1") != 0) {/// a imagem n�o � bin�ria?
                            /// Se sim, gravar o valor m�ximo poss�vel
            fprintf(fd,"%d\n", 255); // valor de brilho m�ximo na imagem (use sempre 255
    }

    /// gravar no arquivo os valores dos pixels da imagem computada
    for (unsigned int k = 0; k < img->pixlen; k++) {
        fprintf(fd,"%d ", img->pix[k]); // o mesmo que (*((img->pix) + k))
    }

    fclose(fd);

    printf("\n ..... (ARQUIVO GRAVADO)-->%s.", fname);

}

Tpixel GetPixel(TPpgm *img, int L, int C){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n%d %d", L, C);
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel K;
    K = *((img->pix) + L*img->w + C);

    return (K);
}

int PutPixel(TPpgm *img, int L, int C, Tpixel v){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Escrita na coordenada de imagem esta fora dos limites da grade da imagem.");
        printf("\nlinha %d\n, coluna %d\n",L,C);
        exit(0);
    }
    Tpixel *K; ///
   //K = ((img->pData) + L*img->w + C)
     *((img->pix) + L*img->w + C) = v;   /// *((img->pData) + L*img->w + C) = v ;
   ///*K = v;

    return (1);
}

int PutPixelRGB(TPpgm *img, int L, int C, Tpixel r, Tpixel g, Tpixel b){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Escrita na aoordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel *K; ///
   //K = ((img->pData) + L*img->w + C)
    *((img->pix) + 3*(L*img->w + C)) = r;   /// *((img->pData) + L*img->w + C) = v ;
    *((img->pix) + 3*(L*img->w + C) + 1) = g;
    *((img->pix) + 3*(L*img->w + C) + 2) = b;
   ///*K = v;

    return (1);
}



void RGB2Gray(TPpgm *f, TPpgm *g){
    //input: f, uma imagem colorida (P3)
    //output: g, uma imagem em tom de cinza (P2)
    if(strcmp(f->tipo, "P3") != 0){
        printf("\n..... A Imagem de entrada deve ser colorida.\n");
        exit(1);
    }
    *g = *f;
    g->tipo[1] = '2'; // transforma o campo tipo de P3 para P2
    g->pixlen = f->pixlen/3;

    g->pix = (Tpixel*) malloc (sizeof(Tpixel) * f->pixlen);

    int k=0;
    Tpixel paux;
    for(int j = 0; j < f->pixlen; j+=3){
        paux = (Tpixel)(((int) f->pix[j] + f->pix[j+1] + f->pix[j+2])/3);
        g->pix[k]=paux;
        k++;
    }
}

void imgInv(TPpgm *f, TPpgm *g) {
    // input imagem f
    // output imagem g (inversa de f)
      // copia do cabecalho
      Tpixel paux;
       *g = *f; /// copia os campos da struct f para os campos correspondentes da stuct g
       g->pix = (Tpixel*)malloc(sizeof(Tpixel) * (g->pixlen)); /// novo endere�o para pixels da imagem g
       paux = 1; /// se f � "P1", ent�o valor de brilho m�ximo � 1.
        if (strcmp(g->tipo, "P1") != 0) {/// a imagem n�o � "P1", ent�p valor de brilho m�ximo � 255.
                                /// Se sim, gravar o valor m�ximo poss�vel
             paux = 255; // valor de brilho m�ximo na imagem (use sempre 255
        }

        /// gravar no arquivo os valores dos pixels da imagem computada
        for (unsigned int k = 0; k < g->pixlen; k++) {
            g->pix[k] = paux - f->pix[k];
        }
}


void morphdil(TPpgm *f, TPpgm *g) {
    // input imagem f
    // output imagem g (imagem f dilatada por um elemento estruturante 3x3)

       *g = *f; /// copia os campos da struct f para os campos correspondentes da stuct g

       if (strcmp(g->tipo, "P3") == 0) { // se a imagem � colorida (tipo "P3", ent�o n�o
                                        //  se aplica operadores morfol�gicos convencionais
          printf("\n ... N�O � possivel aplicar operador morfologico sobre dados de imagens coloridas \n");
          printf("\n ... Tipo da imagem PGM = %s \n", g->tipo);
          exit(1);
       }

       g->pix = (Tpixel*)calloc(sizeof(Tpixel), (g->pixlen)); /// novo endere�o para pixels da imagem g

        /// gravar no arquivo os valores dos pixels da imagem computada

        Tpixel mx, paux; /// m�ximo local
        for (int L = 1; L < g->h-1; L++) {
            for (int C = 1; C < g->w-1; C++) {
                mx = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int j = -1; j <= 1; j++) {
                        paux = GetPixel(f, L+k, C+j);
                        if(paux > mx) {
                            mx = paux;
                        }
                    }
                }
                PutPixel(g, L, C, mx);
            }
        }

}

void morphero(TPpgm *f, TPpgm *g) {
    // input imagem f
    // output imagem g (imagem f dilatada por um elemento estruturante 3x3)

       *g = *f; /// copia os campos da struct f para os campos correspondentes da stuct g

       if (strcmp(g->tipo, "P3") == 0) { // se a imagem � colorida (tipo "P3", ent�o n�o
                                        //  se aplica operadores morfol�gicos convencionais
          printf("\n ... N�O � possivel aplicar operador morfologico sobre dados de imagens coloridas \n");
          printf("\n ... Tipo da imagem PGM = %s \n", g->tipo);
          exit(1);
       }

       g->pix = (Tpixel*)calloc(sizeof(Tpixel), (g->pixlen)); /// novo endere�o para pixels da imagem g

        /// gravar no arquivo os valores dos pixels da imagem computada

       Tpixel mn, paux; /// m�ximo local
        for (int L = 1; L < g->h-1; L++) {
            for (int C = 1; C < g->w-1; C++) {
                mn = 255;
                for (int k = -1; k <= 1; k++) {
                    for (int j = -1; j <= 1; j++) {
                        paux = GetPixel(f, L+k, C+j);
                        if(paux < mn) {
                            mn = paux;
                        }
                    }
                }
                PutPixel(g, L, C, mn);
            }
        }

}

void morphgrad(TPpgm *f, TPpgm *g) {
    // input  f imagem em tons de cinza ou bin�ria
    // output g imagem do gradiente da imagem com bordas duplas
    //          usando um elemento estruturante 3x3

       *g = *f; /// copia os campos da struct f para os campos correspondentes da stuct g

       if (strcmp(g->tipo, "P3") == 0) { // se a imagem � colorida (tipo "P3", ent�o n�o
                                        //  se aplica operadores morfol�gicos convencionais
          printf("\n ... N�O � possivel aplicar operador morfologico sobre dados de imagens coloridas \n");
          printf("\n ... Tipo da imagem PGM = %s \n", g->tipo);
          exit(1);
       }

       g->pix = (Tpixel*)calloc(sizeof(Tpixel), (g->pixlen)); /// novo endere�o para pixels da imagem g

        /// gravar no arquivo os valores dos pixels da imagem computada

       Tpixel mn, mx, paux, grad; /// m�ximo local
        for (int L = 1; L < g->h-1; L++) {
            for (int C = 1; C < g->w-1; C++) {
                mn = 255;
                mx = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int j = -1; j <= 1; j++) {
                        paux = GetPixel(f, L+k, C+j);
                        if(paux < mn) {
                            mn = paux;
                        } else if (paux > mx) mx = paux;
                    }
                }
                grad = mx - mn;
                PutPixel(g, L, C, grad);
            }
        }

}

int* ReadMarkers(const char *fname, int *tm){
//void ReadMarkers(const char *fname, TPmarker *M, int *tm){
    // l� do arquivo fname:
    //    1) total de marcadores e retorna em tm
    //    2) os dados de cada marcador e retorna no vetor M

FILE *fd;
fd = fopen(fname, "r");  /// modo "r" --> abrir para ler
    if (!fd) {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.", fname);
        exit(1);  // algum c�digo de erro - Arquivo nao existe.
    }
printf("\n ..... (ARQUIVO Aberto)-->%s\n.", fname);

   fscanf(fd, "%d \n", tm); // quantidade de marcadores
    printf("QUANTIDADE DE MARCADORES: %d \n", *tm); // quantidade de marcadores
    int p1, p2, p3;
    int *M = (int*)malloc(3*sizeof(int)*(*tm));
    for (int k=0; k<(*tm)*3; k += 3){
        fscanf(fd, "%d %d %d",&M[k], &M[k+1], &M[k+2]);
   }
   fclose (fd);
   return M;
}


void ViewColorMarkers(TPpgm *f, TPpgm *g, int *M, int tm){
//ViewColorMarkers plota os tm Marcadores de M sobre a imagem g
//                 a qual � uma c�pia da imagem f

    *g = *f;
    if (strcmp(f->tipo, "P3") != 0) {  //se imagem f n�o � colorida...
       g->tipo[1] = '3'; // a imagem g deve ser colorida
       g->pixlen = 3*f->pixlen;
       g->pix = (Tpixel*)malloc(sizeof(Tpixel)*g->pixlen);
       int p = 0;
       for (int k=0; k<f->pixlen; k++){
         g->pix[p] = g->pix[p+1] = g->pix[p+2] = f->pix[k];
         p +=3;
       }
    } else {
           g->pix = (Tpixel*)malloc(sizeof(Tpixel)*g->pixlen);
           memcpy(g->pix, f->pix, (sizeof(Tpixel)*g->pixlen));
    }

    Tpixel rr, gg, bb;
    for (int n=0; n<tm; n++){
            /// valor do r�tulo
        int lbl = M[3*n + 2];
          /// linha k, coluna j --> posi��o do r�tulo
        int k = M[3*n + 0], j = M[3*n + 1];
        switch (lbl) {
          case 1:
            rr=255; gg=0; bb=0; // vermelho
          break;
          case 2:
            rr=0; gg=255; bb=0;  // verde
          break;
          case 3:
            rr=0; gg=0; bb=255; // azul
          break;
          case 4:
            rr=255; gg=127; bb=0; ///??????
          break;
          case 5:
            rr=255; gg=255; bb=255; //branco
          break;
          case 6:
            rr=127; gg=127; bb=127; //cinza m�dio
          break;

         default:
            rr=0; gg=0; bb=0;  ///preto

    } // end switch
    PutPixelRGB(g, k, j, rr, gg, bb);
}


}

void RegionColorMarkers(TPpgm *f, TPpgm *mk, TPpgm *cm){
///RegionColorMarkers: gera a imagem colorida (P3) cm correspondente �
///            imagem de input f.
///            Sobrep�e na imagem gerada cm os diferentes valores de
///            r�tulos, ou marcadores {1,2,3,4,...} pertencentes � imagem
///            mk que � correspondente � imagem f. Cada valor de r�tulo
///            gera uma �nica cor na apresenta��o da imagem cm
///input:  f imagem original (P1 ou P2 ou P3)
///       mk imagem correspondente � f formada por diferentes marcadores
///output:cm (color markers) imagem com estrutura colorida (P3) gerada por
///       correspond�ncia com f e sobreposta com os respectivos marcadores
///       representados por diferentes cores.


    *cm = *f;
    if (strcmp(f->tipo, "P3") != 0) {  //se imagem f n�o � colorida...
        cm->tipo[1] = '3'; // a imagem cm deve ser colorida
        cm->pixlen = 3*f->pixlen;
        cm->pix = (Tpixel*)malloc(sizeof(Tpixel)*cm->pixlen);
        int p = 0; // como f � cinza ou bin�ria ...
        for (int k=0; k<f->pixlen; k++){ // ...copiar 3 vezes o mesmo pixel
            cm->pix[p] = cm->pix[p+1] = cm->pix[p+2] = f->pix[k];
            p +=3;
        }
    } else { // se f j� � colorida... copiar todos os pixels dela para g
        cm->pix = (Tpixel*)malloc(sizeof(Tpixel)*cm->pixlen);
        memcpy(cm->pix, f->pix, (sizeof(Tpixel)*cm->pixlen));
    }

    Tpixel rr, gg, bb;
    int p = 0; /// �ndice do pixel colorido atual
    int lbl;   /// valor do r�tulo atual
    
    for (unsigned int l = 0; l < mk->h; l++) { 
        for(unsigned int c = 0; c < mk->w; c++){ // para todos os r�tulos
            lbl = GetPixel(mk, l, c); /// resgata o k-�simo valor de r�tulo
            if (lbl != 0 && lbl != 255) { // se o r�tulo tem significado (n�o � zero), ent�o
            // recupere a cor RGB associada com esse r�tulo
                switch (lbl) {
                    case 1: // se o r�tulo � 1
                        rr=255; gg=0; bb=0; // vermelho
                        break;
                    case 2: // se o r�tulo � 2
                        rr=0; gg=255; bb=0;  // verde
                        break;
                    case 3:
                        rr=0; gg=0; bb=255; // azul
                        break;
                    case 4:
                        rr=255; gg=127; bb=0; ///??????
                        break;
                    case 5:
                        rr=255; gg=255; bb=255; //branco
                        break;
                    case 6:
                        rr=127; gg=127; bb=127; //cinza m�dio
                    break;

                    default:  // otherwise
                        rr=0; gg=0; bb=0;  ///roxo???

                    } // end switch color


                    PutPixelRGB(cm,l,c,rr,gg,bb);

            } // if r�tulo significante
        }

    } // for k

} // RegionColorMarkers


/// color "P3", cinza "P2" ou binario "P1"
TPpgm Watershed(TPpgm *grad, int* M, int tm) {
    FilaH fh; 
    inicializa_fila_hierarquica(&fh); 
    
    TPpgm Ws;
    Ws = *grad;
    Ws.h = grad->h; // altura
    Ws.w = grad->w; // largura
    Ws.max = 255;
    Ws.tipo[1] =  '2';
    Ws.pixlen = Ws.h * Ws.w;
    Ws.pix = (Tpixel*)malloc(sizeof(Tpixel) * (Ws.pixlen));
    

    for (int i = 0; i < tm * 3; i+= 3) { // mandar pra fila
        // M  i  j  prioridade
        int l = M[i];
        int c = M[i + 1];
        int rotulo = M[i + 2];

        printf("{%d, %d, %d}\n", l, c, rotulo);

        enfileira_fh(&fh, (Pixel) {l, c, rotulo}, grad->pix[l* Ws.w + c]);
    }
    escreve_fila_hierarquica(&fh);

    int hm= 0;
    while (!fila_hierarquica_vazia(&fh)) {
        // escreve_fila_hierarquica(&fh);
        Pixel px = desenfileira_fh(&fh);
        Ws.pix[px.linha * Ws.w + px.coluna ] = px.rotulo;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++){
                if (i == 0 && j == 0) 
                    continue;
                if ((0 <= i + px.linha) && (i + px.linha < Ws.h) && // a linha esta dentro da imagem
                (0 <= j + px.coluna) && (j + px.coluna < Ws.w) && // a coluna esta dentro da imagem
                Ws.pix[(px.linha +i) * Ws.w + (px.coluna + j)] == 0) { // o rotulo nao foi marcado ainda

                    Pixel mv = (Pixel) {i + px.linha, j + px.coluna, px.rotulo};
                    if (enfileira_fh(&fh, mv, grad->pix[(px.linha +i) * Ws.w + (px.coluna + j)])) {
                        Ws.pix[(px.linha +i) * Ws.w + (px.coluna + j)] = px.rotulo; // v.rotulo = Pix.rotulo
                    hm++;
                    }
                }
            }
        }
    }
    printf("CARALHOOO: %d\n", hm);
    return Ws;
}

int main(int argc, char *argv[]){
    const char* NimgO = "img01.ppm"; // imagem original
    
    const char* NimgR = "img01INV.ppm"; //// imagem resultado
    const char *NimgGray = "img01Gray.pgm";
    const char *NimgGrad = "img01Grad.pgm";
    const char *fmkr = "ColorMarkers.txt";
    const char *Nimgmkr = "imgColorMarkers.ppm";
    const char *WsImage = "imgWS.pgm";
    const char *SImage = "imgSaida.pgm";

    int tm;
    int *M;

    M = ReadMarkers(fmkr,&tm);

    for (int k=0; k<3*tm; k+=3){
        printf("%d %d %d \n", M[k], M[k+1], M[k+2]);
    }


    TPpgm imgO, inv, dil, ero, imgG, grad, imgMK, imgWS, imgS;


    ReadPGM(NimgO, &imgO);

    RGB2Gray(&imgO, &imgG);
    

    ViewColorMarkers(&imgG, &imgMK, M, tm);

    WritePGM(Nimgmkr, &imgMK);


    morphgrad(&imgG, &grad);
    
    WritePGM(NimgGrad, &grad);
    
    
    imgWS = Watershed(&grad, M, tm); /// aplica o algoritmo de Watershed
    
    RegionColorMarkers(&imgO, &imgWS, &imgS);
    WritePGM(WsImage, &imgWS);
    WritePGM(SImage, &imgS);
    
    
    /// exemplo para usar RegionColorMarkers
    TPpgm mkr, gmkr; /// mkr - imagem dos marcadores   gmkr - imagem do grad. dos marcadores
    // TPpgm colormk; /// imagem apresentando os marcadores coloridos
    TPpgm Bcolormk; /// imagem apresentando as bordas marcadores coloridos
    mkr = imgG; /// os marcadores comp�em uma imagem P2
    mkr.pix = (Tpixel*)calloc(sizeof(Tpixel), (mkr.pixlen)); /// marcadores inicializados com zeros

    printf("\n grad ok .......\n");

    const char *imgmkr = "ColorMarkers.ppm";
    const char *imgBordermkr = "ColorBordersMarkers.ppm";
    const char *NArea = "AreaColorMarkers.ppm";


    TPpgm imgTeste ,imgTesteGrad, RegionColor, BorderColor;
    const char* NimgTeste = "imgTeste.pgm";
    const char* NimgTesteGrad = "imgTesteGrad.pgm";

    ReadPGM(NimgTeste,&imgTeste);
    
    //mudando fundo de branco (255) para preto (0)
    for(int i=0;i<imgTeste.pixlen; i++){
        if(imgTeste.pix[i] == 255)
        imgTeste.pix[i] = 0;
    }
    
    
    morphgrad(&imgTeste,&imgTesteGrad);
    RegionColorMarkers(&imgTeste, &imgTesteGrad, &BorderColor);
    RegionColorMarkers(&imgTeste, &imgTeste, &RegionColor);
    WritePGM(imgBordermkr,&BorderColor);
    WritePGM(NArea, &RegionColor);
    WritePGM(NimgTesteGrad, &imgTesteGrad);

    for (unsigned int lin = 0; lin < mkr.h-1; lin++){
        for(unsigned int col = 0; col < mkr.w-1; col++){
            if (GetPixel(&imgG,lin,col) > 140)
                PutPixel(&mkr, lin, col, 1); // rótulo 1
            else if (GetPixel(&imgG,lin,col)< 80) 
                PutPixel(&mkr, lin, col, 2); // rótulo 2
            else if (GetPixel(&imgG,lin,col)> 100 && GetPixel(&imgG,lin,col)>120 ) 
                PutPixel(&mkr, lin, col, 3); // rótulo 3
        }
    }

    TPpgm AreaColor;
    morphgrad(&mkr, &gmkr);
    RegionColorMarkers(&imgG, &gmkr, &Bcolormk); // bordas coloridas
    RegionColorMarkers(&imgG, &mkr, &AreaColor); // bordas coloridas
    //WritePGM(imgBordermkr, &Bcolormk);
    //WritePGM(NArea, &AreaColor);
    ///
    


    free(imgO.pix);
    //free(inv.pix);
    free(imgG.pix);
    //  free(dil.pix);
    // free(ero.pix);
    free(grad.pix);
    //   free(imgR);

    /// liberando imagens do exemplo de uso dos marcadores
    //free(mkr.pix);
    //free(colormk.pix); /// regi�es coloridas
    //free(Bcolormk.pix); /// bordas das regi�es coloridas
    free(M); /// lisa dos marcadores iniciais para o waterashed
    printf("\n\n\n");
    return 0; //
} //

///

