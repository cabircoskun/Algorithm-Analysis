#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SOLUTION 1000

//long counter = 0 ; //programýn calýsmasýný etkilemeyen sadece algoritmalarýn kac adýmda calýstýgýný sayan basit bir counter.
typedef struct queen{ // her bir vezirin koordinatlarý icin struct yapýsý
	int i, j;
}QUEEN;

typedef struct wholeboard{ // tüm oyun tahtasý icin struct yapýsý
	QUEEN*queens;
}WHOLEBOARD;
/*
@brief aldýgý queens dizisi ile vezirlerin o anki konumlarýyla bir çözüm üretilip üretilmedigini dönen fonksiyon
@param queens : vezirler dizisi
@param numberOfQueens : vezirler sayýsý
@return : çözüm oluþup oluþmadýgýný döner.
*/
int solved(QUEEN*queens,int numberOfQueens){  
	int i =0,j,k ;
	int flag = 1;
	while(flag && i < numberOfQueens){
		
	for(j= 0 ; j < numberOfQueens; j ++){
		if(i!=j&&queens[i].i == queens[j].i){ // satýr kontorlü
			flag = 0;
		}
		if(i!=j&&queens[i].j == queens[j].j){ // sutun kontrolü
			flag = 0;
		}
		for(k = 0 ; k < numberOfQueens; k++){// diagonal kontrolü
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
@brief aldýgý queens dizisi ile oyun tahtasýný cizer
@param queens : vezirler dizisi
@param numberOfQueens : vezirler sayýsý
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
@brief aldýgý queens dizisi solutions diziisnde o anki çözümün daha önceden eklenip eklenmediðini kontrol eder.
@param queens : vezirler dizisi
@param numberOfQueens : vezirler sayýsý
@param solutions : çözümler dizisi
@param numberOfSolutions : çözümler sayýsý
@return : çözümün daha önce  oluþup oluþmadýgýný döner.
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
@brief aldýgý vezir sayýsýna göre recursive bi þekilde n-queen problemini brute_force algoritmasýyla çözen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerleþtirildiðini tutan degisken
@param numberOfQueens : vezirler sayýsý
@param whereAmI : o an hangi koordinatýn kontrol edildigini tutan degiþken
@param solutions : çözümler dizisi
@param numberOfSolutions : çözümler sayýsý
*/
void brute_force(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i;
		while( whereAmI < numberOfQueens*numberOfQueens ){ // oyun tahtasý icinde kalmamýzý saglayan dongu.
			currentQueens[whichQueen].i = whereAmI / numberOfQueens; // whereAmI linear bi þekilde artýyor her seferinde bunu satýr sayýsýna bölerek hangi satýrda oldugumuzu buluyoruz.
			currentQueens[whichQueen].j = whereAmI % numberOfQueens; // ayný iþlem mod alarak hangi sutunda oldugumuzu buluyoruz.
			//counter ++; // algoritma karmasýklýgýný gormek icin //counter.
			
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
			if(whichQueen == numberOfQueens-1){ // son eleman yerlestirilip return edildiyse buraya gir. çözüm olup olmadýgýný kontrol et.
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
@brief aldýgý vezir sayýsýna göre recursive bi þekilde n-queen problemini optimized_1 algoritmasýyla çözen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerleþtirildiðini tutan degisken
@param numberOfQueens : vezirler sayýsý
@param whereAmI : o an hangi koordinatýn kontrol edildigini tutan degiþken
@param solutions : çözümler dizisi
@param numberOfSolutions : çözümler sayýsý
*/

void optimized_1(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i ;
		while( whereAmI < numberOfQueens*(whichQueen+1)){// bu koþul ile her vezirin kendi satýrýndan ileri gitmemesini saglýyorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi satýrýndan baslamasýný saglýyorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			//counter ++ ;
			currentQueens[whichQueen].i = whereAmI / numberOfQueens;// whereAmI linear bi þekilde artýyor her seferinde bunu satýr sayýsýna bölerek hangi satýrda oldugumuzu buluyoruz.
			currentQueens[whichQueen].j = whereAmI % numberOfQueens;// ayný iþlem mod alarak hangi sutunda oldugumuzu buluyoruz.
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
			//son elemaný yerleþtirdiysek burada çözüm bulunup bulunmadýgý kontrol ediliyor. bulunduysa solutions dizisine ekleniyor.
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
@brief aldýgý koordinatlara bakarak o sutunda baþka vezir olup olmadýgýný kontrol eden fonksiyon
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerleþtirildiðini tutan degisken
@param numberOfQueens : vezirler sayýsý
@param whereAmIColumn : o an hangi sutunun kontrol edildigini tutan degiþken
@return : valid bir sutun ise 1 deðil ise 0 döner.
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
@brief aldýgý vezir sayýsýna göre recursive bi þekilde n-queen problemini optimized_2 algoritmasýyla çözen fonksiyon. 
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerleþtirildiðini tutan degisken
@param numberOfQueens : vezirler sayýsý
@param whereAmI : o an hangi koordinatýn kontrol edildigini tutan degiþken
@param solutions : çözümler dizisi
@param numberOfSolutions : çözümler sayýsý
*/
void optimized_2(QUEEN*currentQueens,int whichQueen,int numberOfQueens,int whereAmI,WHOLEBOARD*solutions,int*numberOfSolutions){
		int i ;
		while( whereAmI < numberOfQueens*(whichQueen+1)){ // bu koþul ile her vezirin kendi satýrýndan ileri gitmemesini saglýyorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi satýrýndan baslamasýný saglýyorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			
			
			if(checkColumn(currentQueens,whichQueen,numberOfQueens,whereAmI % numberOfQueens) ){ //bu kontrol ile her veziri yerlestirirken ayný sutunda baska vezir olmamasýný saglýyorum.
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
				//cozum bulunup bulunmadýgý kontorl edillr bulunduysa solutions dizisine çözüm eklenir.
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
		//eðer ilgili veziri yerleþtiremediysem vezirin koordinatlarýný sýfýrlýyorum.
		currentQueens[whichQueen].i = 0;
		currentQueens[whichQueen].j = 0;			
}
/*
@brief aldýgý koordinatlara bakarak ilgili diagonallerde baþka vezir olup olmadýgýný kontrol eden fonksiyon
@param currentQueens : vezirler dizisi
@param whichQueen : o an hangi vezirin yerleþtirildiðini tutan degisken
@param numberOfQueens : vezirler sayýsý
@param whereAmI : o an hangi koordinatýn kontrol edildigini tutan degiþken
@return : valid bir koordinat ise 1 deðil ise 0 döner.
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
		while( whereAmI < numberOfQueens*(whichQueen+1)){ // bu koþul ile her vezirin kendi satýrýndan ileri gitmemesini saglýyorum
			if(whereAmI < whichQueen * numberOfQueens){ // bu if blogunda her vezirin kendi satýrýndan baslamasýný saglýyorum.
				whereAmI = whichQueen * numberOfQueens;
			}
			if(checkColumn(currentQueens,whichQueen,numberOfQueens,whereAmI % numberOfQueens) && checkDiagonal(currentQueens,whichQueen,numberOfQueens,whereAmI)){ 
			//bu kontrol ile her veziri yerlestirirken ayný sutunda ve diagonallerde baska vezir olmamasýný saglýyorum.
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
				//cozum bulunup bulunmadýgý kontorl edillr bulunduysa solutions dizisine çözüm eklenir.
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
		//eðer ilgili veziri yerleþtiremediysem vezirin koordinatlarýný sýfýrlýyorum.
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
