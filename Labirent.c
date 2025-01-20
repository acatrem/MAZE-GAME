#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>	

void labirentOlusturma(char **,int,int);
void labirentYazdir(char **,int,int);
int dfsKesinYol(char **,int,int,int,int,time_t,int);
void oyunBilgisi();
void labirentHareket(char **,char,int,int,int *,int *);
void ekranTemizle();



int main(){
	int i,sizeX,sizeY,hamleSayaci=0;
	char move;
	srand(time(NULL));
	
	
	oyunBilgisi();
	
	
	do{
		printf("\n\nOyun kaca kaclik olsun (En az 5x5 olacak sekilde giriniz):");
		scanf("%d%d",&sizeX,&sizeY);
		
		if(sizeX<5 || sizeY<5){
			printf("\nHatali giris! Lutfen en az 5x5 boyutunda bir deger girin.\n");
		}
	}while(sizeX<5 || sizeY<5);
	
	
	int newX=0,newY=sizeY-2; //fonksiyonda kullanabilmek icin start pointi bu degerlere atandi
	
	char **matrix=NULL;
	matrix=(char **)malloc(sizeX*sizeof(char *));
	for(i=0;i<sizeX;i++){
		matrix[i]=(char *)malloc(sizeY*sizeof(char));
	}
	
	
	labirentOlusturma(matrix,sizeX,sizeY);
	
	
	while(1){
		ekranTemizle();
		labirentYazdir(matrix,sizeX,sizeY);
	
		printf("Gitmek istediginiz yon tusuna basin(W/A/S/D)\n");
		move=getch();
		
		
		labirentHareket(matrix,move,sizeX,sizeY,&newX,&newY);
		hamleSayaci++;
		
		if(newX==sizeX-1 && newY==1){
			printf("\n\nTEBRIKLER,BITIS NOKTASINA ULASTINIZ! \n");
			printf("TOPLAM HAMLE SAYISI: %d \n\n",hamleSayaci);
			break;
		}
	
	}
	
	
	for(i=0;i<sizeX;i++){
		free(matrix[i]);
		
	}
	free(matrix);
	return 0;
}



void labirentOlusturma(char **matrix,int sizeX,int sizeY){
	int i,j;
    time_t startTime=time(NULL);
    int timeLimit=5;
	
	for(i=0;i<sizeX;i++){
		for(j=0;j<sizeY;j++){
			matrix[i][j]=' ';
		}
	}
	
	
	for(i=0;i<sizeX;i++){
		matrix[i][0]='*';
		matrix[i][sizeY-1]='*';
	}
	for(j=0;j<sizeY;j++){
		matrix[0][j]='*';
		matrix[sizeX-1][j]='*';
	}
	
	
	matrix[0][sizeY-2]='S';
	matrix[sizeX-1][1]='E';
	
	
	dfsKesinYol(matrix,1,sizeY-2,sizeX,sizeY,startTime,timeLimit);
	
	for(i=1;i<sizeX-1;i++){
		for(j=1;j<sizeY-1;j++){
			if(matrix[i][j]=='+'){
				matrix[i][j]=' ';
			}
		}
	}
	

	for(i=1;i<sizeX-1;i++){
		for(j=1;j<sizeY-1;j++){
			if(matrix[i][j]==' ' && (i!=1 || j!=sizeY-2) && (i!=sizeX-2 || j!=1)){ // S ve E noktasýný kapanýp sýkýsmasý onlendi
				if(rand()%4==0 || rand()%7==0){
					matrix[i][j]='*';
				}
				
			}
		}
	}
	
	
	if(dfsKesinYol(matrix,1,sizeY-2,sizeX,sizeY,startTime,timeLimit)==0){
		printf("Labirent yeniden olusturuluyor ...\n");
		labirentOlusturma(matrix,sizeX,sizeY);
	}
	for(i=1;i<sizeX-1;i++){
		for(j=1;j<sizeY-1;j++){
			if(matrix[i][j]=='+'){
				matrix[i][j]=' ';
			}	
		}
	}
	
}
void labirentYazdir(char **matrix,int sizeX,int sizeY){
	
	int i,j;
	for(i=0;i<sizeX;i++){
		for(j=0;j<sizeY;j++){
			printf("%c ",matrix[i][j]);
		}
		printf("\n");
	}
}
int dfsKesinYol(char **matrix,int x,int y,int sizeX,int sizeY,time_t startTime,int timeLimit){
	int i,newX,newY;
	if(difftime(time(NULL),startTime)>timeLimit){
        return 0;
    }
	
	if(matrix[x][y]=='E'){
		return 1;
	}
	
	if(matrix[x][y]==' ' || matrix[x][y]=='S'){
		matrix[x][y]='+';
	}
	
	int rdluYonler[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	
	for(i=0;i<4;i++){
		newX=x+rdluYonler[i][0];
		newY=y+rdluYonler[i][1];
	
	
		if(newX>=0 && newX<sizeX && newY>=0 && newY<sizeY &&
			(matrix[newX][newY]==' ' || matrix[newX][newY]=='E')){
				if(dfsKesinYol(matrix,newX,newY,sizeX,sizeY,startTime,timeLimit)){
					return 1;
			}
		}
	}
		
	
	if(matrix[x][y]!='S' && matrix[x][y]=='+'){
		matrix[x][y]=' ';
	}
	return 0;
	
}
void oyunBilgisi(){
	printf("===================================================\n");
	printf("            LABIRENT'E     HOSGELDINIZ!            \n");
	printf("===================================================\n");
	printf("Oyunun amaci:\n");
	printf("-  'S' noktasindan baslayarak 'E' noktasina ulasmak.\n");
	printf(" !!! Duvarlara ('*') carpmadan hareket edin !!! \n");
	printf("Kontroller:\n");
	printf(" - W/w : Yukari\n");
	printf(" - A/a : Sol\n");
	printf(" - S/s : Asagi\n");
	printf(" - D/d : Sag\n");
	printf("===================================================\n\n");
}
void labirentHareket(char **matrix,char move,int sizeX,int sizeY,int *newX,int *newY){
	
	int oldX=*newX;
	int oldY=*newY;
	
	switch(move){
		case 'W':
		case 'w':
			(*newX)--;
			break;
			
		case 'S':
		case 's':
			(*newX)++;
			break;
			
		case 'A':
		case 'a':
			(*newY)--;
			break;
			
		case 'D':
		case 'd':
			(*newY)++;
			break;
		
		default:
			printf("GECERSIZ HAMLE !!!.\n");
			printf("(Devam etmek icin bir tusa basiniz...)\n");
			getch();
	}
	
	if(*newX==0 && *newY==sizeY-2){
		printf("Baslangic noktasina geri donemezsiniz!\n");
		printf("(Devam etmek icin bir tusa basiniz...)\n");
		getch();
		*newX=oldX;
		*newY=oldY;
	}
	
	if(*newX>=0 && *newX<sizeX && *newY>=0 && *newY<sizeY && matrix[*newX][*newY]!='*' && matrix[*newX][*newY]!='S'){
		if(matrix[oldX][oldY]!='S' && matrix[oldX][oldY]!='E'){
			matrix[oldX][oldY]=' ';
		}
		matrix[*newX][*newY]='P';
	}else{
		printf("DUVARA CARPTINIZ! \n");
		printf("(Devam etmek icin bir tusa basiniz...)\n");
		getch();
		*newX=oldX;
		*newY=oldY;
	}
	
	
}
void ekranTemizle(){
	system("cls");
}
