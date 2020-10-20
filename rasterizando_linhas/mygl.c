#include "mygl.h"

unsigned char* fb_ptr = NULL;

void InitMyGl(void) {
    fb_ptr = (unsigned char *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 4 * sizeof(char));	

    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i) {
        fb_ptr[i * 4] = 0;
        fb_ptr[i * 4 + 1] = 0;
        fb_ptr[i * 4 + 2] = 0;
        fb_ptr[i * 4 + 3] = 255;
    }    
}

unsigned char* GetFBMemPtr(void) {
	return fb_ptr;
}

void CloseMyGl(void) {
    if (!fb_ptr)
        free(fb_ptr);
}

//
// >>> Caro aluno: defina aqui as funções que você implementar <<<
//

void putPixel(pixels P){
    
    fb_ptr[(4*P.x) + (4*IMAGE_WIDTH*P.y) + 0] = P.Red; //calculo do offset para a luz vermelha
    fb_ptr[(4*P.x) + (4*IMAGE_WIDTH*P.y) + 1] = P.Green; //calculo do offset para a luz verde
    fb_ptr[(4*P.x) + (4*IMAGE_WIDTH*P.y) + 2] = P.Blue; //calculo do offset para a luz azul
    fb_ptr[(4*P.x) + (4*IMAGE_WIDTH*P.y) + 3] = P.Alpha; //calculo do offset para a luz transparente
}

void drawLine(pixels P1, pixels P2){

    int dx = P2.x - P1.x; // calculo do delta x entre 2 pontos
    int dy = P2.y - P1.y; // calculo do delta y entre 2 pontos

    int incre_L, incre_NE; //variaveis de decisao de direção (leste ou nordeste)
    int prox_x, prox_y;

    int D; // D é a variavel de decisao para o 1º pixel


    //definindo todos os valores de x e y em todos os 8 octantes
    if(dx > 0){
        prox_x = 1;
    }else{
        prox_x = -1;
    }

    if(dy > 0){
        prox_y = 1;
    }else{
        prox_y = -1;
    }

    putPixel(P1);

    //Cálculo da interpolação
    // abs(x) calcula o valor absoluto de x
    if(dx < 0){ //3º,4º,5º e 6º octantes
        drawLine(P2,P1);
        return;
    }else{
        if(dy > 0){ //1º e 2º octante
            if(abs(dx) > abs(dy)){ //1º octante
                D = (dy-dx)*2;
                incre_L = 2*dy;
                incre_NE = 2*(dy-dx);

                while(P1.x < P2.x){ 
                    if(D > 0){
                        D += incre_L;
                        P1.x += prox_x;
                    }else{
                        D += incre_NE;
                        P1.x += prox_x;
                        P1.y += prox_y;
                    }

                    // interpolacao de cores
                    P1.Red += (float)(P2.Red - P1.Red) / abs(dx);
                    P1.Green += (float)(P2.Green - P1.Green) / abs(dx);
                    P1.Blue += (float)(P2.Blue - P1.Blue) / abs(dx);
                    P1.Alpha += (float)(P2.Alpha - P1.Alpha) / abs(dx);

                    putPixel(P1);
                }
            }else{ // 2º octante
                D = dy - (2*dx);
                incre_L = 2*(dx-dy);
                incre_NE= 2*dx;

                while(P1.y < P2.y) {
                    if(D < 0){
                        D += incre_NE;
                        P1.y += prox_y;
                    }else{
                        D += incre_L;
                        P1.x += prox_x;
                        P1.y += prox_y;
                    }

                    // interpolacao de cores
                    P1.Red += (float)(P2.Red - P1.Red) / abs(dy);
                    P1.Green += (float)(P2.Green - P1.Green) / abs(dy);
                    P1.Blue += (float)(P2.Blue - P1.Blue) / abs(dy);
                    P1.Alpha += (float)(P2.Alpha - P1.Alpha) / abs(dy);

                    putPixel(P1);
                }                               
            }
        }else{ //7º e 8º octantes 
            if(abs(dx) > abs(dy)){ //8º octante
                D = (-2)*dy + dx;
                incre_L = (-2) * dy;
                incre_NE = (-2) * (dy + dx);

                while(P1.x < P2.x){ 
                    if(D > 0){
                        D += incre_L;
                        P1.x += prox_x;
                    }else{
                        D += incre_NE;
                        P1.x += prox_x;
                        P1.y -= prox_y;
                    }

                    // interpolacao de cores
                    P1.Red += (float)(P2.Red - P1.Red) / abs(dx);
                    P1.Green += (float)(P2.Green - P1.Green) / abs(dx);
                    P1.Blue += (float)(P2.Blue - P1.Blue) / abs(dx);
                    P1.Alpha += (float)(P2.Alpha - P1.Alpha) / abs(dx);

                    putPixel(P1);
                }
            }else{ //7º octante                
                D = dy + (2*dx);
                incre_L = 2 * dy;
                incre_NE = 2 * (dy + dx);

                while(P1.y > P2.y){ 
                    if(D < 0){
                        D += incre_L;
                        P1.y -= prox_y;                        
                    }else{
                        D += incre_NE;
                        P1.x += prox_x;
                        P1.y -= prox_y;                         
                    }

                    // interpolacao de cores
                    P1.Red += (float)(P2.Red - P1.Red) / abs(dy);
                    P1.Green += (float)(P2.Green - P1.Green) / abs(dy);
                    P1.Blue += (float)(P2.Blue - P1.Blue) / abs(dy);
                    P1.Alpha += (float)(P2.Alpha - P1.Alpha) / abs(dy);

                    putPixel(P1);
                }                    
            }
        }
    }
}

void DrawTriangle(pixels P1, pixels P2, pixels P3){
    drawLine(P1,P2);
    drawLine(P2,P3);
    drawLine(P3,P1);
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
    //
    // >>> Caro aluno: chame aqui as funções que você implementou <<<
    //

    pixels P1 = {150, 130, 255, 0, 0, 255};  //ponto vermelho na posicao (150,130)
    putPixel(P1);
    
    pixels P2 = {200, 450, 0, 230, 0, 255}; //ponto verde na posicao (216,450)
    putPixel(P2);
    
    pixels P3 = {300, 450, 0, 0, 255, 255}; //ponto azul na posicao (300,450)
    putPixel(P3);

    DrawTriangle(P1,P2,P3);
    
}