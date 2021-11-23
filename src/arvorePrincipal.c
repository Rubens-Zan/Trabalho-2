#include "stdio.h"
#include "stdlib.h"

#include "arvorePrincipal.h"
#include "arvoreSecundaria.h"
#include "biblioteca.h"
#include "estruturas.h"

/* -------------------------------------------------------------------------- */
tArvoreA *arvorePrincipalCriaNo(tArvoreB *arvoreB){
    tArvoreA *n = (tArvoreA *)malloc(sizeof(tArvoreA));
    n->chave = arvoreB; 
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    return n;
};
/* -------------------------------------------------------------------------- */
tArvoreA *arvorePrincipalInclui(tArvoreA *arvoreA,tArvoreB *arvoreB, int valor){
    if (arvoreA == NULL)
        return arvorePrincipalCriaNo(arvoreB); 
    int index = 0; 
    calculaChaveArvore(arvoreA->chave, &index); 
     
    if (valor < index){
        arvoreA->esq = arvorePrincipalInclui(arvoreA->esq, arvoreB, valor);
        arvoreA->esq->pai = arvoreA; 
    }
    else
    {
        arvoreA->dir = arvorePrincipalInclui(arvoreA->dir, arvoreB, valor);
        arvoreA->dir->pai = arvoreA;
    }
    return arvoreA;
}
/* -------------------------------------------------------------------------- */
void imprimeNosArvorePrincipal (tArvoreB *arvoreB){
    printf("("); 
    if (arvoreB != NULL){
        printf("%d",arvoreB->chave);
        if (arvoreB->dir != NULL || arvoreB->esq != NULL){
            imprimeNosArvorePrincipal(arvoreB->esq);
            imprimeNosArvorePrincipal(arvoreB->dir);
        }
    }
    printf(")");
}
/* -------------------------------------------------------------------------- */
void calculaChaveArvore(tArvoreB *no, int *chave){
    if (no != NULL){
        calculaChaveArvore(no->esq, chave);
        (*chave) += no->chave; 
        calculaChaveArvore(no->dir, chave);
    }
}
/* -------------------------------------------------------------------------- */
void arvoreResultante(tArvoreA *arvoreA){
    printf("[");
    if (arvoreA != NULL && arvoreA->chave != NULL){
        imprimeNosArvorePrincipal(arvoreA->chave);
        int chaveArvore = 0;
        calculaChaveArvore(arvoreA->chave, &chaveArvore);
        printf(": %d\n", chaveArvore); 

        if (arvoreA->dir != NULL || arvoreA->esq != NULL){
            arvoreResultante(arvoreA->esq);
            arvoreResultante(arvoreA->dir); 
        }
    }
    // else{
    //     printf("]\n"); 
    // }
    printf("]\n"); 
}
/* -------------------------------------------------------------------------- */
tArvoreA *buscaArvoreB(tArvoreA *arvoreA, int chave)
{
    if (arvoreA == NULL)
        return 0;
    else{
        int chaveArvore = 0;
        calculaChaveArvore(arvoreA->chave, &chaveArvore); 
       
        if ( chaveArvore == chave)
            return arvoreA;
        if (chave < chaveArvore)
            return buscaArvoreB(arvoreA->esq, chave);
        else
            return buscaArvoreB(arvoreA->dir, chave);
    }
};
/* -------------------------------------------------------------------------- */
tArvoreA *min(tArvoreA *arvoreB)
{
    if (arvoreB->esq == NULL)
        return arvoreB;
    else
        return min(arvoreB->esq);
};

/* -------------------------------------------------------------------------- */
tArvoreA *excluiNoArvoreA(tArvoreA *no, int chaveNo){
    if (no == NULL)
        return no;

    int chaveRaiz = 0;
    calculaChaveArvore(no->chave, &chaveRaiz); 

    if (chaveNo < chaveRaiz){
        no->esq = excluiNoArvoreA(no->esq, chaveNo); 
    }
    
    else if (chaveNo > chaveRaiz){
        no->dir = excluiNoArvoreA(no->dir, chaveNo);
    }

    else {
        // no com um filho ou sem filhos
        if (no->esq == NULL){
            printf("sem no esquerdo... ");
            tArvoreA *aux = no->esq;
            free(no);
            return aux;
        }
        else if (no->dir == NULL){
            printf("sem no direito... ");
            tArvoreA *aux = no->dir;
            free(no);
            return aux;
        }

        // no com dois filhos
        printf("dois filhos... ");
        int chaveAux = 0;
        tArvoreA *aux = min(no->dir);
        calculaChaveArvore(aux->chave, &chaveAux); 
        no->chave = aux->chave; 
        no->dir = excluiNoArvoreA(no->dir, chaveAux);
    } 
    return no; 
}