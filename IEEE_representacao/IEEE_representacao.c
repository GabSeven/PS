#include <stdio.h>
#include <stdlib.h>

#define Tdouble 0
#define Tfloat 1

#define BF 127
#define BD 1023
#define sqrt2 1.4142135623730950488016887

// typedef union dIEEE {
//     double x;
//     struct{
//         unsigned long long int f:52;
//         unsigned long long int E:11;
//         unsigned long long int s:1;
//     }bits;
// }dIEEE;

typedef struct{
    unsigned long long int f:52;
    unsigned long long int E:11;
    unsigned long long int s:1;
}dIEEE;

typedef struct {
    unsigned long int f:23;
    unsigned long int E:8;
    unsigned long int s:1;
}fIEEE;

typedef struct{
    int type;
    void *data;
}real;


float fIEEE_f(fIEEE x) {
    unsigned long int bits = 0;
    bits |= (x.s & 0x1) << 31;
    bits |= (x.E & 0xFF) << 23;
    bits |= (x.f & 0x7FFFFF);
    float f;
    *((unsigned long int *)&f) = bits;
    return f;
}

double dIEEE_d(dIEEE x) {
    unsigned long long int bits = 0;
    bits |= ((unsigned long long int)(x.s & 0x1)) << 63;
    bits |= ((unsigned long long int)(x.E & 0x7FF)) << 52;
    bits |= (x.f & 0xFFFFFFFFFFFFF);
    double d;
    *((unsigned long long int *)&d) = bits;
    return d;
}

fIEEE f_fIEEE(float f) {
    unsigned long int bits = *((unsigned long int *)&f);
    fIEEE ieee;
    ieee.s = (bits >> 31) & 0x1;
    ieee.E = (bits >> 23) & 0xFF;
    ieee.f = bits & 0x7FFFFF;
    return ieee;
}

dIEEE d_dIEEE(double d) {
    unsigned long long int bits = *((unsigned long long int *)&d);
    dIEEE ieee;
    ieee.s = (bits >> 63) & 0x1;
    ieee.E = (bits >> 52) & 0x7FF;
    ieee.f = bits & 0xFFFFFFFFFFFFF;
    return ieee;
}


real novo_real(double x, int t){
    real r;
    r.type = t;
    if(t==Tdouble){
        dIEEE *pt_data;
        pt_data = (dIEEE *) malloc(sizeof(dIEEE));
        *pt_data = d_dIEEE(x);
        r.data = (void *) pt_data;
    }else if(t==Tfloat){

        fIEEE *pt_data;
        pt_data = (fIEEE *) malloc(sizeof(fIEEE));
        *pt_data = f_fIEEE((float) x);
        r.data = (void *) pt_data;
    }
    return r;
};


void exclui_real(real *x){
    if(x->data!=NULL){

        printf("exclui_real: data = %p\n", x->data);

        free(x->data);
        x->data=NULL;
    }
}


/*
A função sqrtNR recebe um valor real e retorna o valor real da raiz quadrada de A calculado 
com o método de Newton Raphson. 
A função deve analisar se o valor A é representado como Tfloat ou Tdouble.
    - Caso o tipo de A seja Tfloat, o retorno deverá ser do tipo Tfloat
    - Caso o tipo de A seja Tdouble, o retorno deverá ser do tipo Tdouble
Se o tipo não for Tdouble nem Tfloat, o comportamento é indefinido (ou seja, não se sabe o que será retornado) 
*/



void change_to_Tdouble(real *A){
/*
A função change_to_Tdouble deve converter o tipo de dado do valor real para Tdouble;
Caso o o tipo de A não seja Tfloat, nada deve ser feito.
*/
    if (A->type == Tfloat) {
        double *pt_data = malloc(sizeof(double));

        float x = * ((float *) A->data);
        *pt_data = x;

        exclui_real(A);
        A->data = (void *) pt_data;
        A->type = Tdouble;
    }

}

void change_to_Tfloat(real *A){
/*
A função change_to_Tfloat deve converter o tipo de dado do valor real para Tfloat;
Caso o tipo de A não seja Tdouble, nada deve ser feito.
*/
    if (A->type == Tdouble) {
        float *pt_data =  malloc(sizeof(float));

        double x = * ((double *) A->data);
        
        *pt_data = x;

        exclui_real(A);

        A->data = (void *) pt_data;
        A->type = Tfloat;
    }
}

double real_to_double(real A){
/*
A função real_to_double retorna um valor double a partir de um real;
*/
    if(A.type == Tfloat){
        change_to_Tdouble(&A);
    }
    return * ((double*) A.data);
}


float real_to_float(real A){
/*
A função real_to_float retorna um valor float a partir de um real;
*/
    if(A.type == Tdouble){
        change_to_Tfloat(&A);
    }
    return * ((float*) A.data);
}

real sqrtNR(real A){
    if (A.type ==  Tfloat) {
        if (fIEEE_f(*(fIEEE *)A.data ) == 0 || fIEEE_f(*(fIEEE *)A.data )== 1) {
            return A;
        } else {
            int k = 0;
            
            fIEEE *x0, *x1;
            
            x0 = (fIEEE *) malloc(sizeof(fIEEE));
            
            *x0 = *((fIEEE*) A.data); // copia o valor e nao o ponteiro
            
            int impar = !(x0->E & 1); /// expoente verdadeiro é ímpar???
            x0->E = ((x0->E>>1) + 0x3F ); /// cuidado com o doubleetade da fração da mantissa
            if (impar) {
                float x =  fIEEE_f(*x0);
                x *= sqrt2;
                *x0 = f_fIEEE(x);
            }


            printf("\n  E  = %d ", x0->E - BF);
            printf("\n  f  = %d ", x0->f);
            printf("\n  f  = %f ", (float)x0->f/(1<<23));
            printf("\n  s  = %d ", x0->s);


            printf("\n  Estimativa Inicial x0  = %f  ", *(float *)x0 );

            x1 = (fIEEE *) malloc(sizeof(fIEEE));
            
            *x1 = *x0;

            do { 
                *x0 = *x1;
                *x1 = f_fIEEE(fIEEE_f(*x0) +fIEEE_f(*(fIEEE *)A.data)/fIEEE_f(*x0)); 
                x1->E--; 
                k++;
                    
            } while ((*(unsigned long int *)x0 ) != (*(unsigned long int *)x1 ) );

            printf("\n  Total de iteracoes  = %d ", k );
            
            A.data = (fIEEE *) x0;
        }
                
    } else if (A.type == Tdouble) {
        if (dIEEE_d(*(dIEEE *)A.data ) == 0 || dIEEE_d(*(dIEEE *)A.data) == 1) {
            printf("aa");
            return A;
        } else {
            int k = 0;
            
            dIEEE *x0, *x1;
            
            x0 = (dIEEE *) malloc(sizeof(dIEEE));
            
            *x0 = *((dIEEE*) A.data); 
            
            int impar = !(x0->E & 1); 
            x0->E = ((x0->E>>1) + 0x1FF ); 
            x0->f >>= 1;
            if (impar) {
                double x =  dIEEE_d(*x0);
                x *= sqrt2;
                *x0 = d_dIEEE(x);
            }


            printf("\n  E  = %d ", x0->E - BD);
            printf("\n  f  = %d ", x0->f);
            printf("\n  f  = %f ", (double)x0->f/(1<<52));
            printf("\n  s  = %d ", x0->s);


            printf("\n  Estimativa Inicial x0  = %f  ", *(double *)x0 );

            x1 = (dIEEE *) malloc(sizeof(dIEEE));
            
            *x1 = *x0;

            do { 
                *x0 = *x1;
                *x1 = d_dIEEE(dIEEE_d(*x0) +dIEEE_d(*(dIEEE *)A.data)/dIEEE_d(*x0)); 
                x1->E--; 
                k++;
                    
            } while ((*(unsigned long long int *)x0 ) != (*(unsigned long long int *)x1 ) );
            
            printf("\n  Total de iteracoes  = %d ", k );
            
            A.data = (dIEEE *) x0;
        }
    }
    
    return A; // Cuidado com esse retorno, pois A.data é uma região de memória que não faz parte da struct
}

void printBinary(int *num, int tam) {
    for (int i = sizeof(int) * tam / 4 - 1; i >= 0; i--) {
        printf("%d", (*num >> i) & 1);
    }
}

int main()
{
    float x = 4;
    // 01010
    real r1, r2;
    r1 = novo_real(x, Tfloat);
    r2 = novo_real(x, Tdouble);
    
    fIEEE *as_float;
    dIEEE *as_double;
    real sqrtR1 = sqrtNR(r1); // essa chamada da função deve retornar um valor real com type == Tfloat, pois r1.type == Tfloat 
    real sqrtR2 = sqrtNR(r2); // essa chamada da função deve retornar um valor real com type == Tdouble, pois r2.type == Tdouble
    
    float sqrt_xF =      real_to_float(sqrtR1);
    // float sqrt_xD_to_F = real_to_float(sqrtR2);
    double sqrt_xD =     real_to_double(sqrtR2);
    // double sqrt_xF_to_D =real_to_double(sqrtR1);

    
    printf("\nf sqrt(%f):%f\n",x,sqrt_xF);
    // printf("d to f sqrt(%lf):%f\n",x,sqrt_xD_to_F);
    printf("d sqrt(%lf):%lf\n",x,sqrt_xD);
    // printf("f to d sqrt(%lf):%lf\n",x,sqrt_xF_to_D);
    
    as_float = r1.data;
    as_double = r2.data;
    
    printf("sinal:%lx mantissa:%lx expoente:%lx\n", (long int) as_float->s, (long int) as_float->f, (long int) as_float->E - 127);
    printf("sinal:%llx mantissa:%llx expoente:%llx\n", (long long int) as_double->s,  (long long int)as_double->f,  (long long int)as_double->E - 1023);

    float f = real_to_float(r1);
    printf("float: %fz", f);

    double d = real_to_double(r2);
    printf("double: %lf\n", d); 

    return 0;
}