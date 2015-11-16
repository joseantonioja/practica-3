#include<stdio.h>
#include<stdlib.h>
#include "AFN.h"

int main(){
	AFN top = unSimbolo('a');
	AFN temp = unSimbolo('b');
	top = concatenacionAFN(top,temp);
	top = cerraduraE(top);
	top = unionAFN(top,unSimbolo('c'));
	imprimeAFN(top); //top es (ab)*|c

	AFN sig = unSimbolo('d');
	sig = unionAFN(sig, unSimbolo('e'));
	sig = cerraduraP(sig);
	imprimeAFN(sig);//sig es (d|e)+

	top = concatenacionAFN(top, sig);
	imprimeAFN(top);//top ahora es {(ab)*|c}(d|e)+
	return 0;
}
