#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 40
struct Node{
int kimlik;//kimlik numarasi
char Ad[MAX];//Ad  char dizisi
char Soy[MAX];//Soyad char dizisi
int arkadas[MAX];//arkadaslarinin dizisi
 struct Node *sol;
struct Node *sag;
};





int size(struct Node *tree);
int  contain (struct Node *tree ,int no);
struct Node * inserNewUser( struct Node *tree , int kimlikNo,int arkadas[34],char name[MAX],char soy[MAX]);
int PrintinOrder (struct Node * tree);
struct Node * delete(struct Node * tree, int no);
struct Node* min(struct Node * tree);
struct Node* max(struct Node * tree);
struct Node* delete(struct Node* root, int no);
int printGreater (struct Node * tree,int kimlik);






int main()
{
char arkadas[MAX];//arkadas dızısı okumak ıcın
struct  Node * tree= NULL;//agacın kendısı
FILE *fp;//fıle poınter fıle acmak ve dolasmak ıcın
char soy[MAX];//soy ısmı fıledan almak ıcın
char birsatir[100];//fıle ı satır satır okumak icın
int kimlikNo=0;//Kimlik numarasi okumak icin
char *c='d';//okunmus satiri yazmak icin
char soyad[34];//soy isim almak icin
char name[34];//isim almak icin
int i=0;//Donguler killanilmak icin
fp = fopen("input1.txt","r+");
c = fgets(birsatir,80,fp);
sscanf(birsatir,"%d" ",%s" " %s"  ",%s",&kimlikNo,name,soyad);
//sscanf de bir yanlis oldu. Kimlik no-la adlari aldim ama digerlerini alamadim
    while(soyad[i]!=','){//soyad ad alma kismi
        soy[i]=soyad[i];
        i++;
    }
    while (c != NULL){//file dan agaca add etme kismi

          tree=inserNewUser(tree,kimlikNo,arkadas,name,soy);
          for (i=0;i<MAX;i++){
                soy[i]=NULL;
          }

          c = fgets(birsatir,80,fp);
          sscanf(birsatir,"%d" ",%s" " %s" ,&kimlikNo,name,soyad);
          i=0;
          while(soyad[i]!=','&&soyad[i]!=NULL){
            soy[i]=soyad[i];
            i++;
          }

          //arkadaslari file dan almak istedim ama yapamadim
 /*      while(soyad[k]!=NULL){

            printf("Ds");

                if(soyad[k]>'47'&&soyad[k]<'58'){
                    if((soyad[k+1]>'47')&&(soyad[k+1]<'58')){
                        int v=soyad[k]-'0';
                        int b=soyad[k+1]-'0';
                    t=b+v*10;
                    printf("%d\n",t);
                    k=k+2;
                    }
                else{

                t=soyad[k]-'0';
                printf("%d\n",t);
                k++;
                }


          }
           k++;

   }*/


    }

    printf("agacda %d sayida eleman bulunmaktadir \n",size(tree));
    PrintinOrder(tree);
    fclose(fp);//file kismi bitti
    return 0;
}
//size fonksiyonu agaci dolasarak node gordugu yerde c i bir artirarak eleman sayisini buluyor
int size(struct Node *tree){
    static int c=0;
    if(tree==NULL){
        return c;
    }
    size(tree->sol);
    size(tree->sag);
    c++;

}
// agaci gezerek eger istenilen kisiye ulasmissa ekrana ad siyadi yazdiriyo
int contain (struct Node *tree ,int no){
  if(tree==NULL){
         return 1;
  }
   contain(tree->sol,no);
   if(tree->kimlik==no){
        printf("Bu deger agacta bulunmaktadir\n");
        printf("Aradiginiz kisi %s %s",tree->Ad,tree->Soy);
    }
  contain(tree->sag,no);
}




//yeni elemen eklenmek istenildiginde yeni bir node olusturuluyor. Fonksiyondan gelen bilgiler bu node -a aktariliyor ve bu node agaca ekleniyor.
struct Node * inserNewUser( struct Node *tree , int kimlikNo,int arkadas[34],char name[MAX],char soy[MAX]){
    if(tree==NULL){
        struct Node *yeni =  (struct Node *)malloc(sizeof(struct Node));
        yeni->kimlik=kimlikNo;
        yeni->sag=NULL;
        yeni->sol=NULL;
        strcpy(yeni->Ad,name);
        strcpy(yeni->Soy,soy);
        return yeni;
    }
  if((tree->kimlik)<kimlikNo){
            tree->sag = inserNewUser(tree->sag,kimlikNo,arkadas,name,soy);
            return tree;
  }
       tree->sol=inserNewUser(tree->sol,kimlikNo,arkadas,name,soy);
             return tree;
}

//Agacta recursive olarak geziyor ve tum elemanlarin isimlerini ekrana yazdiriyor parametre olarak agaci aliyor
int PrintinOrder (struct Node * tree){
    if(tree==NULL){
        return 1;
    }
        PrintinOrder(tree->sol);

        printf("%d   ",tree->kimlik);
         printf("%s  ",tree->Ad);
        printf("%s   ",tree->Soy);

         printf("\n");

        PrintinOrder(tree->sag);
}
//parametre olarak agaci aliyor
struct Node * min(struct Node*tree){
 while(tree->sol!=NULL){
    tree =tree->sol;
}
    return tree;
}

struct Node* max(struct Node * tree){
     while(tree->sag!=NULL){
        tree =tree->sag;
     }
   return tree;
}


////parametre olarak agaci ve kimlik numarasini aliyor. Agaci donduruyor

struct Node * delete(struct Node * tree, int no){
   struct Node * tmp;
    if(tree==NULL){//Agacin bos oldugu durum
        return NULL;
    }
    if((tree->kimlik)==no){
            if((tree->sol==NULL)&&(tree->sag==NULL)){//Aranan elemanin sag ve solunun bos olmasi durumu
                return NULL;
            }
            if(tree->sag!=NULL){//saginda eleman olma durumu . Bu durumda saginin en kucuk elemani silinen elemanin yerine geliyo
                    tmp=min(tree->sag);
                    tree->kimlik=tmp->kimlik;
                    int i=0;

                    for(i=0;i<MAX;i++){
                        int b=tree->arkadas[i];
                        tmp->arkadas[i]=b;
                    }
                    strcpy(tree->Ad,tmp->Ad);
                    tree->sag=delete(tree->sag,min(tree->sag)->kimlik);

                    return tree;
            }
        tmp=max(tree->sol);
        tree->sag=tmp->sag;
        int i=0;

        for(i=0;i<MAX;i++){
                int b=tree->arkadas[i];
                tmp->arkadas[i]=b;
        }
        strcpy(tree->Ad,tmp->Ad);
        strcpy(tree->Soy,tmp->Soy);
        tree->sol=delete(tree->sol,max(tree->sol)->kimlik);
        tree=tmp;
        return tree;
    }
    if(tree->kimlik<no){
            tree->sag=delete(tree->sag,no);
            return tree;
    }
    tree->sol=delete(tree->sol,no);
    return tree;

}

//Eger girilen kimlik Nosundan buyukse ekrana yazdir .
//parametre olarak agaci ve kimlik numarasini aliyor.

int printGreater (struct Node * tree,int kimlik){
    if(tree==NULL){
        return 1;
    }
        printGreater(tree->sol,kimlik);
        if(tree->kimlik>kimlik){
            printf("%d   ",tree->kimlik);
            printf("%s  ",tree->Ad);
            printf("%s   ",tree->Soy);
            printf("\n");

        }

        printGreater(tree->sag,kimlik);
}
//Friends ve Subtree fonksiyonlarini yazmadim .
