#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SOLUTION 1000

//long counter = 0 ; //program�n cal�smas�n� etkilemeyen sadece algoritmalar�n kac ad�mda cal�st�g�n� sayan basit bir counter.
typedef struct queen{ // her bir vezirin koordinatlar� icin struct yap�s�
	int i, j;
}QUEEN;

typedef struct wholeboard{ // t�m oyun tahtas� icin struct yap�s�
	QUEEN*queens;
}WHOLEBOARD;
/*
@brief ald�g� queens dizisi ile vezirlerin o anki konumlar�yla bir ��z�m �retilip �retilmedigini d�nen fonksiyon
@param queens : vezirler dizisi
@param numberOfQueens : vezirler say�s�
@return : ��z�m olu�up olu�mad�g�n� d�ner.
*/
int solved(QUEEN*queens,int numberOfQueens){  
	int i =0,j,k ;
	int flag = 1;
	while(flag && i < numberOfQueens){
		
	for(j= 0 ; j < numberOfQueens; j ++){
		if(i!=j&&queens[i].i == queens[j].i){ // sat�r kontorl�
			flag = 0;
		}
		if(i!=j&&queens[i].j == queens[j].j){ // sutun kontrol�
			flag = 0;
		}
		for(k = 0 ; k < numberOfQueens; k++){// diagonal kontrol�
			if(i!=j&&((queens[i].i)+k == queens[j].i)&&((queens[i].j)+k == queens[j].j)){
				flag = 0;
			}
			if(i!=j&&((queens[i].i)+k == queens[j].i)&&((queens[i].j)-k == queens[j].j)){
				flag = 0;
			}
		}
	}
		
		i++;
	}
	if(flag){
		return 1;
	}else{
		return 0;		
	}
	
	
}
/*
@brief ald�g� queens dizisi ile oyun tahtas�n� cizer
@param queens : vezirler dizisi
@param numberOfQueens : vezirler say�s�
*/
void printBoard(QUEEN*queens,int numberOfQueens){
	
	int ** board = (int ** ) calloc(numberOfQueens+30,sizeof(int*));
	int  j,k;
	for(k = 0 ; k< numberOfQueens; k++){
		board[k] = (int* ) calloc (numberOfQueens+30,sizeof(int));
		
	}
	for(k =0; k < numberOfQueens; k++){
		//printf("%d,%d ",queens[k].i,queens[k].j);
		board[queens[k].i][queens[k].j] = k+1;
		
	}
	
	for(k = 0; k< numberOfQueens; k++){
		for(j= 0 ; j <numberOfQueens; j++){
			printf("%2d ",board[k][j]);
		}
		printf("\n");
	}
		printf("\n");
}
/*
@brief ald�g� queens dizisi solutions diziisnde o anki ��z�m�n daha �nceden eklenip eklenmedi�ini kontrol eder.
@param queens : vezirler dizisi
@param numberOfQueens : vezirler say�s�
@param solutions : ��z�mler dizisi
@param numberOfSolutions : ��z�mler say�s�
@return : ��z�m�n daha �nce  olu�up olu�mad�g�n� d�ner.
*/
int exist(QUEEN*queens,int numberOfQueens,WHOLEBOARD*solutions,int numberOfSolutions){
	int i,j ; 
	for (i = 0 ;i <numberOfSolutions ;i ++){
		j= 0 ;
		while(solutions[i].queens[j].i == queens[j].i && solutions[i].queens[j].j == queens[j].j){
			j++;
		}
		if (j == numberOfQueens){
			return 1;
		}
	}
	return 0;
}
/*
@brief ald�g� vezir say�s�na g�re recursive bi �ekilde n-queen problemini brute_force algoritmas�yla ��zen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerle�tirildi�ini tutan degisken
@param numberOfQueens : vezirler say�s�
@param whereAmI : o an hangi koordinat�n kontrol edildigini tutan degi�ken
@param solutions : ��z�mler dizisi
@param numberOfSolutions : ��z�mler say�s�
*/
void brute_force(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i;
		while( whereAmI < numberOfQueens*numberOfQueens ){ // oyun tahtas� icinde kalmam�z� saglayan dongu.
			currentQueens[whichQueen].i = whereAmI / numberOfQueens; // whereAmI linear bi �ekilde art�yor her seferinde bunu sat�r say�s�na b�lerek hangi sat�rda oldugumuzu buluyoruz.
			currentQueens[whichQueen].j = whereAmI % numberOfQueens; // ayn� i�lem mod alarak hangi sutunda oldugumuzu buluyoruz.
			//counter ++; // algoritma karmas�kl�g�n� gormek icin //counter.
			
			if(whichQueen == numberOfQueens) // eger son vezir de yerlestirildiyse return
			return ;
			whereAmI++;
			
			
			//printf("where %d \n",queens[whichQueen].i);
			//if(whichQueen == numberOfQueens)
			//printf("%d:  whereAmI \n",whereAmI);
			//printBoard(currentQueens,numberOfQueens);			
			if(whichQueen != numberOfQueens){
					brute_force(currentQueens,whichQueen+1,numberOfQueens,whereAmI,solutions,numberOfSolutions);
			}
			if(whichQueen == numberOfQueens-1){ // son eleman yerlestirilip return edildiyse buraya gir. ��z�m olup olmad�g�n� kontrol et.
				if(solved(currentQueens,numberOfQueens)&&!exist(currentQueens,numberOfQueens,solutions,*numberOfSolutions)){
				for(i =0 ;i < numberOfQueens ; i++){
					//printf(" %d,%d",currentQueens[i].i,currentQueens[i].j);
					solutions[*numberOfSolutions].queens[i] = currentQueens[i];
				}
				*numberOfSolutions = *numberOfSolutions+1;
				printf("%d. solution is found !\n",*numberOfSolutions);
			}
			}
			
		}			
}
/*
@brief ald�g� vezir say�s�na g�re recursive bi �ekilde n-queen problemini optimized_1 algoritmas�yla ��zen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerle�tirildi�ini tutan degisken
@param numberOfQueens : vezirler say�s�
@param whereAmI : o an hangi koordinat�n kontrol edildigini tutan degi�ken
@param solutions : ��z�mler dizisi
@param numberOfSolutions : ��z�mler say�s�
*/

void optimized_1(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i ;
		while( whereAmI < numberOfQueens*(whichQueen+1)){// bu ko�ul ile her vezirin kendi sat�r�ndan ileri gitmemesini sagl�yorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi sat�r�ndan baslamas�n� sagl�yorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			//counter ++ ;
			currentQueens[whichQueen].i = whereAmI / numberOfQueens;// whereAmI linear bi �ekilde art�yor her seferinde bunu sat�r say�s�na b�lerek hangi sat�rda oldugumuzu buluyoruz.
			currentQueens[whichQueen].j = whereAmI % numberOfQueens;// ayn� i�lem mod alarak hangi sutunda oldugumuzu buluyoruz.
			if(whichQueen == numberOfQueens)
			return ;
			whereAmI++;
			//printf("where %d \n",queens[whichQueen].i);
			//if(whichQueen == numberOfQueens)
			//printf("%d:  whereAmI \n",whereAmI);
			//printBoard(queens,numberOfQueens);
			
			if(whichQueen != numberOfQueens){	
					optimized_1(currentQueens,whichQueen+1,numberOfQueens,whereAmI,solutions,numberOfSolutions);
			}
			//son eleman� yerle�tirdiysek burada ��z�m bulunup bulunmad�g� kontrol ediliyor. bulunduysa solutions dizisine ekleniyor.
			if(solved(currentQueens,numberOfQueens)&&!exist(currentQueens,numberOfQueens,solutions,*numberOfSolutions)){
				for(i =0 ;i < numberOfQueens ; i++){
					//printf(" %d,%d",currentQueens[i].i,currentQueens[i].j);
					solutions[*numberOfSolutions].queens[i] = currentQueens[i];
				}
				printf("%d. solution is found !\n",*numberOfSolutions+1);
				*numberOfSolutions = *numberOfSolutions+1;
			}
		}			
}
/*
@brief ald�g� koordinatlara bakarak o sutunda ba�ka vezir olup olmad�g�n� kontrol eden fonksiyon
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerle�tirildi�ini tutan degisken
@param numberOfQueens : vezirler say�s�
@param whereAmIColumn : o an hangi sutunun kontrol edildigini tutan degi�ken
@return : valid bir sutun ise 1 de�il ise 0 d�ner.
*/
int checkColumn(QUEEN*currentQueens, int whichQueen, int numberOfQueens,int whereAmIColumn){
	int i = 0,flag = 1;
	while(i < numberOfQueens && flag){
		if(currentQueens[i].i != currentQueens[whichQueen].i&&currentQueens[i].j == whereAmIColumn && i != whichQueen){
			flag = 0;
		}
		i++;
	}
	if(flag){
		return 1;
	}
	return 0;
}
/*
@brief ald�g� vezir say�s�na g�re recursive bi �ekilde n-queen problemini optimized_2 algoritmas�yla ��zen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerle�tirildi�ini tutan degisken
@param numberOfQueens : vezirler say�s�
@param whereAmI : o an hangi koordinat�n kontrol edildigini tutan degi�ken
@param solutions : ��z�mler dizisi
@param numberOfSolutions : ��z�mler say�s�
*/
void optimized_2(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i ;
		while( whereAmI < numberOfQueens*(whichQueen+1)){ // bu ko�ul ile her vezirin kendi sat�r�ndan ileri gitmemesini sagl�yorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi sat�r�ndan baslamas�n� sagl�yorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			
			
			if(checkColumn(currentQueens,whichQueen,numberOfQueens,whereAmI % numberOfQueens) ){ //bu kontrol ile her veziri yerlestirirken ayn� sutunda baska vezir olmamas�n� sagl�yorum.
				currentQueens[whichQueen].i = whereAmI / numberOfQueens;
				currentQueens[whichQueen].j = whereAmI % numberOfQueens;
				if(whichQueen == numberOfQueens)
					return ;
				whereAmI++;
				//counter ++ ;
				//printf("where %d \n",queens[whichQueen].i);
				//if(whichQueen == numberOfQueens)
				//printf("%d:  whereAmI \n",whereAmI);
				//printBoard(currentQueens,numberOfQueens);
				
				if(whichQueen != numberOfQueens){	
					optimized_2(currentQueens,whichQueen+1,numberOfQueens,whereAmI,solutions,numberOfSolutions);
				}
				//cozum bulunup bulunmad�g� kontorl edillr bulunduysa solutions dizisine ��z�m eklenir.
				if(solved(currentQueens,numberOfQueens)&&!exist(currentQueens,numberOfQueens,solutions,*numberOfSolutions)){
					for(i =0 ;i < numberOfQueens ; i++){
						//printf(" %d,%d",currentQueens[i].i,currentQueens[i].j);
						solutions[*numberOfSolutions].queens[i] = currentQueens[i];
					}
					printf("%d. solution is found !\n",*numberOfSolutions+1);
					*numberOfSolutions = *numberOfSolutions+1;
				}
			}else{
				whereAmI++;
			}
			
		}
		//e�er ilgili veziri yerle�tiremediysem vezirin koordinatlar�n� s�f�rl�yorum.
		currentQueens[whichQueen].i = 0;
		currentQueens[whichQueen].j = 0;			
}
/*
@brief ald�g� koordinatlara bakarak ilgili diagonallerde ba�ka vezir olup olmad�g�n� kontrol eden fonksiyon
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerle�tirildi�ini tutan degisken
@param numberOfQueens : vezirler say�s�
@param whereAmI : o an hangi koordinat�n kontrol edildigini tutan degi�ken
@return : valid bir koordinat ise 1 de�il ise 0 d�ner.
*/
int checkDiagonal(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI){
		int i = 0,flag = 1;
	while(i < whichQueen && flag){
		
			if((whereAmI / numberOfQueens) != currentQueens[i].i && (whereAmI % numberOfQueens) != currentQueens[i].j ){	
				if(abs((whereAmI / numberOfQueens) - currentQueens[i].i) == abs((whereAmI % numberOfQueens) - currentQueens[i].j) ){
				flag = 0;
				}
			
			}
		
		
		i++;
		
	}
	if(flag){
		return 1;
	}
	return 0;
}
void backTracking(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i ;
		while( whereAmI < numberOfQueens*(whichQueen+1)){ // bu ko�ul ile her vezirin kendi sat�r�ndan ileri gitmemesini sagl�yorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi sat�r�ndan baslamas�n� sagl�yorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			if(checkColumn(currentQueens,whichQueen,numberOfQueens,whereAmI % numberOfQueens) && checkDiagonal(currentQueens,whichQueen,numberOfQueens,whereAmI)){ 
			//bu kontrol ile her veziri yerlestirirken ayn� sutunda ve diagonallerde baska vezir olmamas�n� sagl�yorum.
				currentQueens[whichQueen].i = whereAmI / numberOfQueens;
				currentQueens[whichQueen].j = whereAmI % numberOfQueens;
				if(whichQueen == numberOfQueens)
					return ;
				whereAmI++;
				//counter ++ ;
				//printf("where %d \n",queens[whichQueen].i);
				//if(whichQueen == numberOfQueens)
				//printf("%d:  whereAmI \n",whereAmI);
				//printBoard(currentQueens,numberOfQueens);
				
				if(whichQueen != numberOfQueens){	
					backTracking(currentQueens,whichQueen+1,numberOfQueens,whereAmI,solutions,numberOfSolutions);
				}
				//cozum bulunup bulunmad�g� kontorl edillr bulunduysa solutions dizisine ��z�m eklenir.
				if(solved(currentQueens,numberOfQueens)&&!exist(currentQueens,numberOfQueens,solutions,*numberOfSolutions)){
					for(i =0 ;i < numberOfQueens ; i++){
						//printf(" %d,%d",currentQueens[i].i,currentQueens[i].j);
						solutions[*numberOfSolutions].queens[i] = currentQueens[i];
					}
					printf("%d. solution is found !\n",*numberOfSolutions+1);
					*numberOfSolutions = *numberOfSolutions+1;
				}
			}else{
				whereAmI++;
			}
			
		}
		//e�er ilgili veziri yerle�tiremediysem vezirin koordinatlar�n� s�f�rl�yorum.
		currentQueens[whichQueen].i = 0;
		currentQueens[whichQueen].j = 0;			
}
void menu(){
	int numberOfQueens,mod,i;
	int numberOfSolutions = 0;
	int flag  =1 ;
	
	clock_t start[5], end[5];
    double cpu_time_used[5];

    
	
	printf("-N-Queen Problemi Cozum Programi-\n");
	printf("N degerini giriniz.\n-->");
	scanf("%d",&numberOfQueens);
	do{
		if(numberOfQueens<1){
			printf("Lutfen 0'dan buyuk deger giriniz.\n-->");
			scanf("%d",&numberOfQueens);
		}
	}while(numberOfQueens<1);
		
	QUEEN*queens = (QUEEN*)calloc(numberOfQueens,sizeof(QUEEN));
	WHOLEBOARD*solutions = (WHOLEBOARD*)calloc(MAX_SOLUTION,sizeof(WHOLEBOARD));
	for(i = 0 ; i < MAX_SOLUTION ; i++){
		solutions[i].queens =  (QUEEN*)calloc(numberOfQueens,sizeof(QUEEN));
	}
	do{
		
	
	printf("Mod seciniz:\n1) Brute Force \n2) Optimized_1 \n3)Optimized_2 \n4) Backtracking\n5)Hepsini arka arkaya calistir.\n--> ");
	scanf("%d",&mod);
		switch(mod){
			case 1: 
				printf("Brute Force algoritmasi calistiriliyor.\n");
				start[0] = clock();
				brute_force(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[0] = clock();
				cpu_time_used[0] = ((double)(end[0] - start[0])) / CLOCKS_PER_SEC;
				printf("N = %d -- Brute Force algoritmasi icin calisma suresi : %f\n",numberOfQueens,cpu_time_used[0]);
				flag = 0;
				break;
			case 2: 
				printf("Optimized_1 algoritmasi calistiriliyor.\n");
				start[1] = clock();
				optimized_1(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[1] = clock();
				cpu_time_used[1] = ((double)(end[1] - start[1])) / CLOCKS_PER_SEC;
				printf("N = %d -- Optimized_1 algoritmasi icin calisma suresi : %f\n",numberOfQueens,cpu_time_used[1]);
				flag = 0;
				break;
			case 3: 
				printf("Optimized_2 algoritmasi calistiriliyor.\n");
				start[2] = clock();
				optimized_2(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[2] = clock();
				cpu_time_used[2] = ((double)(end[2] - start[2])) / CLOCKS_PER_SEC;
				printf("N = %d -- Optimized_2 algoritmasi icin calisma suresi : %f\n",numberOfQueens,cpu_time_used[2]);
				flag = 0;
				break;
			case 4: 
				printf("Backtracking algoritmasi calistiriliyor.\n");
				start[3] = clock();
				backTracking(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[3] = clock();
				cpu_time_used[3] = ((double)(end[3] - start[3])) / CLOCKS_PER_SEC;
				printf("N = %d -- Backtracking algoritmasi icin calisma suresi : %f\n",numberOfQueens,cpu_time_used[3]);
				flag = 0;
				break;
			case 5: 
				flag = 0;
				printf("Brute Force algoritmasi calistiriliyor.\n");
				start[0] = clock();
				brute_force(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[0] = clock();
				cpu_time_used[0] = ((double)(end[0] - start[0])) / CLOCKS_PER_SEC;
				numberOfSolutions = 0;
				printf("Optimized_1 algoritmasi calistiriliyor.\n");
				start[1] = clock();
				optimized_1(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[1] = clock();
				cpu_time_used[1] = ((double)(end[1] - start[1])) / CLOCKS_PER_SEC;
				numberOfSolutions = 0;
				printf("Optimized_2 algoritmasi calistiriliyor.\n");
				start[2] = clock();
				optimized_2(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[2] = clock();
				cpu_time_used[2] = ((double)(end[2] - start[2])) / CLOCKS_PER_SEC;
				numberOfSolutions = 0;
				printf("Backtracking algoritmasi calistiriliyor.\n");
				start[3] = clock();
				backTracking(queens,0,numberOfQueens,0,solutions,&numberOfSolutions);
				end[3] = clock();
				cpu_time_used[3] = ((double)(end[3] - start[3])) / CLOCKS_PER_SEC;
				printf("\nSirasiyla bruteForce, optimized_1, optimized_2 ve backtracking algoritmalari icin calisma sureleri:\n");
				for (i = 0 ; i< 4 ; i++){
					printf("--> %f\n",cpu_time_used[i]);
				}
				break;
			default:
				printf("Gecersiz sayi girdiniz. Lutfen tekrar giris yapiniz.\n");
		
		}
 	}while(flag);
 	printf("Tum cozumleri yazdirmak icin enter'a basin\n");
 	getchar(); // clear the buffer
 	getchar();
 	for(i = 0 ;i < numberOfSolutions ; i++){
		printBoard(solutions[i].queens,numberOfQueens);
		printf("\n");
	}
}

int main(){
	
	menu();

	return 0;
}
