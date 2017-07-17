#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define clear; system("cls");
#define flush; fflush(stdin);
#define MAX 100

	/*
		Dannylo Carlos
		RA - 2216111572
	*/
	
	FILE *fa, *novo;
	
	struct x { 
		char nome[20], fone[20];
		int ok;
	};
	
	//var's
	struct x agenda[MAX];
	int cont, m;
	
	//prototipos
	char menu(void);		
	int learq(void);		
	void consulta(void);	//DONE
	void remover(void);		//DONE
	void alterar(void);		//DONE
	void cadastro(void);	//DONE

main(){
	for(;;){
		cont = learq();
		switch(menu()){
			case '1': 
				clear;
				consulta();
				break;
			case '2':
				clear;
				alterar();
				break;
			case '3':
				clear;
				remover();
				break;
			case '4':
				clear;
				cadastro();
				break;
			case '0':
				puts("\tAte breve... ^^");
				getch();
				exit(1);
				break;
			default:
				puts("\tOpção invalida tente novamente...");
				getch();
				clear;
		}	
	}
	getch();
}

void cadastro(){
	char nome[20], fone[20];
	fa = fopen ("agenda.dat", "a+");
	for(;;){
		puts("\nDigite o nome do(a) amigo(a), ou '.' para finalizar: ");
		flush;
		scanf("%s", nome);
		strupr(nome);
		if(strcmp(nome,".") == 0){
			break;
		}
		flush;
		printf("\nDigite o telefone de %s: ", nome);
		scanf("%s", fone);
		fprintf(fa,"%s %s\n", nome, fone);
	}// for forever
	fclose(fa);
	puts("\nFim da agenda");
	getch();
	clear;	
}

void alterar(){
	char nome[20], nome2[20], fone2[20];
	int i;
	printf("Buscar contato (Alterar): ");
	flush;
	scanf("%s", nome);
	strupr(nome);
	for(i=0;i<cont;i++){
		if(strcmp(nome,agenda[i].nome)==0 && agenda[i].ok == 1){
			printf("\tNome: %s | N: %s\n", agenda[i].nome, agenda[i].fone);
			printf("\tNovo nome: ");
			scanf("%s", nome2);
			strupr(nome2);
			printf("\tNovo numero: ");
			scanf("%s", fone2);
			strcpy(agenda[i].nome,nome2);
			strcpy(agenda[i].fone,fone2);
		}
	}
	fa = fopen("agenda.dat", "a+");
	novo = fopen("novaagenda.dat", "w");
	for(i=0;i<cont;i++){
		if(agenda[i].ok == 1){
			fprintf(novo,"%s %s\n", agenda[i].nome, agenda[i].fone);
		}		
	}
	fclose(fa);
	fclose(novo);
	remove("agenda.dat");
	rename("novaagenda.dat", "agenda.dat");
	getch();
	clear;
}

void remover(){
	char nome[20];
	int i;
	printf("Buscar contato (Remover): ");
	flush;
	scanf("%s", nome);
	strupr(nome);
	for(i=0;i<cont;i++){
		if(strcmp(nome,agenda[i].nome)==0 && agenda[i].ok == 1){
			printf("%s foi removido(a).", agenda[i].nome);
			agenda[i].ok = 0;
		}
	}
	fa = fopen("agenda.dat", "a+");
	novo = fopen("novaagenda.dat", "w");
	for(i=0;i<cont;i++){
		if(agenda[i].ok == 1){
			fprintf(novo,"%s %s\n", agenda[i].nome, agenda[i].fone);
		}		
	}
	fclose(fa);
	fclose(novo);
	remove("agenda.dat");
	rename("novaagenda.dat", "agenda.dat");
	getch();
	clear;
}

char menu(){ // menu
	puts("\t-----Menu-----");
	puts("\t1 - Consultar");
	puts("\t2 - Alterar");
	puts("\t3 - Remover");
	puts("\t4 - Cadastro");	
	puts("\t0 - Sair");
	printf("\tOpção: ");
	scanf("%s", &m);
	return m;
}

int learq(){ // ler aquivo
	int contamigos = 0;
	fa = fopen("agenda.dat", "r");
	if(fa == NULL){
		puts("\nErro na abertura de agenda.dat");
		puts("Programa sera finalizado. ");
		getch();
		exit(1);
	}// if verificação de erro
	while(fscanf(fa,"%s %s\n", agenda[contamigos].nome,agenda[contamigos].fone) != EOF){
		agenda[contamigos].ok = 1;
		printf("\nNome = %s | Fone = %s", agenda[contamigos].nome,agenda[contamigos].fone);
		contamigos++;	
	}
	puts("\n");
	fclose(fa);
	return contamigos;		
}

void consulta(void){
	char nome2[100];
	int i, ok2 = 0;
	printf("Digite o nome da pessoa: ");
	flush;
	scanf("%s", nome2);
	strupr(nome2);
	for(i = 0; i<cont; i++){
		if((strcmp(nome2, agenda[i].nome) == 0) && agenda[i].ok == 1){
			ok2 = 1;
			printf("Nome: %s | Fone: %s", agenda[i].nome, agenda[i].fone);
		} // if
	}// for
	if(ok2 == 0){
		printf("\n%s Não esta na agenda.", nome2);
	}
	getch();
	clear;
}
