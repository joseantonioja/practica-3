#include "Estado.h"
typedef struct datos{
	Estado inicial;
	Estado final;
}* AFN;

Estado inicial(AFN);
Estado final(AFN);
AFN unSimbolo(char);
AFN concatenacionAFN(AFN, AFN);
AFN unionAFN(AFN, AFN);
AFN cerraduraP(AFN);
AFN cerraduraE(AFN);
void imprimeAFN(AFN);

Estado inicial(AFN a){
	return a->inicial;
}

Estado final(AFN a){
	return a->final;
}
AFN unSimbolo(char c){
	Estado f = cons(2,' ',NULL, ' ',NULL);
	Estado i = cons(1,c,f, ' ', NULL);
	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = i;
	temp->final = f;
	return temp;
}

AFN concatenacionAFN(AFN a, AFN b){
	int desplazamiento = getId(a->final) - 1;
	renumera(inicial(b), desplazamiento);
	
	reinicia(a->inicial);
	reinicia(b->inicial);

	a->final->ts = b->inicial->ts;
	a->final->ti = b->final->ti;
	a->final->s = b->inicial->s;
	a->final->i = b->final->i;

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = a->inicial;
	temp->final = b->final;
	return temp;
}

AFN unionAFN(AFN a, AFN b){
	renumera(a->inicial,1);
	renumera(b->inicial, getId(a->final));

	reinicia(a->inicial);
	reinicia(b->inicial);

	Estado inicial = cons(1, 'E', a->inicial, 'E', b->inicial);
	Estado final = cons(getId(b->final) + 1, ' ', NULL, ' ', NULL);

	a->final->ts = 'E';
	b->final->ti = 'E';
	a->final->s = final;
	b->final->i = final;

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;
	return temp;
}

AFN cerraduraP(AFN a){
	renumera(a->inicial, 1);

	reinicia(a->inicial);

	a->final->ts = 'E';
	a->final->ti = 'E';
	a->final->s = a->inicial;
	Estado final = cons(getId(a->final) + 1, ' ', NULL, ' ', NULL);
	a->final->i = final;
	Estado inicial = cons(1, 'E', a->inicial, ' ', NULL);

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;

	return temp;
}

AFN cerraduraE(AFN a){
	renumera(a->inicial, 1);
	reinicia(a->inicial);

	a->final->ts = 'E';
	a->final->ti = 'E';
	a->final->s = a->inicial;
	Estado final = cons(getId(a->final) + 1, ' ', NULL, ' ', NULL);
	a->final->i = final;
	Estado inicial = cons(1, 'E', a->inicial, 'E', final);

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;

	return temp;
}
void imprimeAFN(AFN afn){
	int i;
	printf("Estados: ");
	for(i = 1; i<=getId(afn->final); i++)
		printf("%d,",i);
	printf("\n");
	printf("Estado inicial: %d\n", getId(afn->inicial));
	printf("Estado final: %d\n", getId(afn->final));
	printf("Transiciones: \n");
	imprimeTransiciones(afn->inicial);
	reinicia(afn->inicial);
}
