#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <errno.h>



//Codigo do heap utilizado nesse trabalho:

/*
    File:   minHeap.c
    Desc:   Program showing various operations on a binary min heap
    Author: Robin Thomas <robinthomas2591@gmail.com>
*/
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2
#define HEAPSIZE 200

typedef struct node {
    int data ;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;


/*
    Function to initialize the min heap with size = 0
*/
minHeap initMinHeap(int size) {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}
//---------------------------------------------------------------------------------------------
/*
    Function to swap data within two nodes of the min heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a min heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data < hp->elem[i].data) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data < hp->elem[smallest].data) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}



/* 
    Build a Min Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMinHeap() function to build the heap in O(n) time
*/
void buildMinHeap(minHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.data = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}


/*
    Function to insert a node into the min heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(minHeap *hp, int data) {
    if(hp->size) {
        hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
    } else {
        hp->elem = malloc(sizeof(node)) ;
    }

    node nd ;
    nd.data = data ;

    int i = (hp->size)++ ;
    while(i && nd.data < hp->elem[PARENT(i)].data) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
}


/*
    Function to delete a node from the min heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated
*/
void deleteNode(minHeap *hp) {
    if(hp->size) {
     //   printf("Deleting node %d\n\n", hp->elem[0].data) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
     //   printf("\nMin Heap is empty!\n") ;
        free(hp->elem) ;
    }
}


/*
    Function to get maximum node from a min heap
    The maximum node shall always be one of the leaf nodes. So we shall recursively
    move through both left and right child, until we find their maximum nodes, and
    compare which is larger. It shall be done recursively until we get the maximum
    node
*/
int getMaxNode(minHeap *hp, int i) {
    if(LCHILD(i) >= hp->size) {
        return hp->elem[i].data ;
    }

    int l = getMaxNode(hp, LCHILD(i)) ;
    int r = getMaxNode(hp, RCHILD(i)) ;

    if(l >= r) {
        return l ;
    } else {
        return r ;
    }
}


/*
    Function to clear the memory allocated for the min heap
*/
void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;
}


/*
    Function to display all the nodes in the min heap by doing a inorder traversal
*/
void inorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}


/*
    Function to display all the nodes in the min heap by doing a preorder traversal
*/
void preorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        preorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        preorderTraversal(hp, RCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
}


/*
    Function to display all the nodes in the min heap by doing a post order traversal
*/
void postorderTraversal(minHeap *hp, int i) {
    printf("%d ", hp->elem[i].data) ;
    if(LCHILD(i) < hp->size) {
        postorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        postorderTraversal(hp, RCHILD(i)) ;
    }
}


/*
    Function to display all the nodes in the min heap by doing a level order traversal
*/
void levelorderTraversal(minHeap *hp) {
    int i ;
    for(i = 0; i < hp->size; i++) {
        printf("%d ", hp->elem[i].data) ;
    }
}



//----------------------------------------------------------------------------------------
#define MAXPONTOS  500
#define MAXVIZINHOS 5000
#define MAXCOMPONENT 10000
typedef struct {
  char nlinhas;
  char ncolunas;
  char ncores;
  char **mapa;
} tmapa;


typedef struct {
  char coordX, coordY;
} tcoord;

typedef struct tcomponente{
  struct tcomponente **vizinhos; //CHECAR O PONTEIRO
  char cor;
  char estado; //indica se o componente sofreu merges
  unsigned int tamanho;  //contador de pontos
  int distancia;
  tcoord * pontos; //pontos do componente
  
  unsigned int numVizinhos; //limita o vetor vizinhos
  unsigned int id;
} tcomponente;



typedef struct tnodo{
  struct tnodo **next; //lista de ponteiros para nodos
  tcomponente *componentes;
  unsigned int numComponentes;
  char status; //para a busca em profundidade
  int heuristic;
} tnodo;

void aloca_pontos(tcoord **pontos, unsigned int currentMax){
  *pontos = (tcoord * ) malloc (currentMax * sizeof(tcoord));
}

void aloca_vizinhos (tnodo * nodo, int currentMax) {
  nodo->componentes[nodo->numComponentes].vizinhos = (tcomponente **) malloc (currentMax * sizeof(tcomponente *));

}
void aloca_componentes(tcomponente **componentes, unsigned int currentMax) {
  *componentes = (tcomponente *) malloc(currentMax * sizeof(tcomponente));
 
 
}

void getDistancia(tnodo * nodo) {
  int max =1;
  int min =424242;
  tcomponente * maisDistante;
  int dist;
  int i,j;                                     ////////////////////////////////////////////////////
   for(i = 1; i < nodo->numComponentes; i++) { //TODO Alterar AS DISTANCIAS AO LONGO DOS TABULEIROS
                                               //////////////////////////////////////////////////////
        if (nodo->componentes[i].distancia != 0){  //nao esta ligado ao raiz

            
            for(j = 0; j < nodo->componentes[i].numVizinhos; ++j) {
              dist=nodo->componentes[i].vizinhos[j]->distancia;
                if (dist > -1) {
                   
                  

                  if(dist < min){
                    min = dist; //menor valor vizinho
                    
                    nodo->componentes[i].distancia = min + 1;
                  }
                   
                  if(nodo->componentes[i].vizinhos[j]->distancia > max && nodo->componentes[i].vizinhos[j]->distancia > -1) {

                   max = nodo->componentes[i].vizinhos[j]->distancia;
                   maisDistante = nodo->componentes[i].vizinhos[j]; 
                  // printf("tempmax = %d\n",max);
                } 
                }


               
            }
       //     printf("%d ",nodo->componentes[i].distancia);
            min =424242;
        }
    }

  //  printf("\nmax = %d\n",maisDistante->distancia);

}

void mostra_mapa(tmapa *m) {
  char i, j;

  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
  printf("%02d ", m->mapa[i][j]);
      else
  printf("%d ", m->mapa[i][j]);
    printf("\n");
  }
}



int mostraVizinhos (tnodo * nodo) {
  int i;
  int j;
  int componentesRestantes =0;
  for (i = 0; i < nodo->numComponentes; ++i){

        if (nodo->componentes[i].estado != 0) {
          if (nodo->componentes[i].id != 0) ++componentesRestantes;
     //     printf("Vizinhanca[%d]:\n",i);
          for (j = 0; j < nodo->componentes[i].numVizinhos; ++j) {
 //            printf("%d ",nodo->componentes[i].vizinhos[j]->id);
             
          }
   //       printf("\n");
       
        }
    }




  return componentesRestantes;
}

void mostra_mapa_cor(tmapa *m) {
  char i, j;
  char* cor_ansi[] = { "\x1b[0m",
           "\x1b[31m", "\x1b[32m", "\x1b[33m",
           "\x1b[34m", "\x1b[35m", "\x1b[36m",
           "\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
           "\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
           "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

  if(m->ncores > 15) {
    mostra_mapa(m);
    return;
  }
//  printf("=====================================\n"); //REMOVER DPS
  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
  printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
      else
        if(m->mapa[i][j]>9){
            printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
        }

        else {
          printf("%s%d%s  ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
        }

    printf("\n");
    
  }
 // printf("=====================================\n"); //REMOVER DPS
}

void copia_mapa(tmapa *m, tmapa *n){

  //TODO desalocar o temporario
  // printf("!\n");
  n->nlinhas = m->nlinhas;
  n->ncolunas = m->ncolunas;
  n->ncores = m->ncores;
  char i, j;
  n->mapa = (char**) malloc(n->nlinhas * sizeof(char*));
  
  for(i = 0; i < n->nlinhas; i++){
    n->mapa[i] = (char*) malloc(n->ncolunas * sizeof(char)); 

    for(j = 0; j < n->ncolunas; j++){
      n->mapa[i][j] = m->mapa[i][j];
    }

  }   
   

}

void copia_nodo(tnodo * pai, tnodo * filho){

}


int saoVizinhosCadastrados(tcomponente * amostra, tcomponente * pivo) {
  unsigned int i,j;
  
  for (i = 0; i < amostra->numVizinhos; ++i){

   // printf("%d == %d ?\n",amostra->vizinhos[i]->id,pivo->id);
    if (amostra->vizinhos[i]->id == pivo->id) { //é vizinho já cadastrado
      return 1;
    }
  }
  return 0; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int mergeRoot (tnodo* nodo, char nextColor) { //////////CHECAR ESTA FUNC!!!!!!!!!!!!!!!!!!!!!! 
  int i,j,k;  ///////////////////////////////////////////////////////////////////////////////////////////////
  int flag1, flag2, flagChanges;
  flag1 = 0;
  flag2 = 0;
  flagChanges = 0;

  minHeap heap;
  heap = initMinHeap(HEAPSIZE);
  
  tcomponente* raiz = &nodo->componentes[0];
  tcomponente** vizinhoIndireto; 
  tcomponente** vizinhoDireto;
  tcomponente** segundoPonteiroDireto;    // Raiz -> vizinhoDireto -> vizinhoIndireto
                                         //                ^              |
                                         //                |----segundo---

  int offsetVizinhos = raiz->numVizinhos;
  
  for (i = 0; i< raiz->numVizinhos; ++i) { //percorre todos os vizinhos do nodo raíz
    
    if(raiz->vizinhos[i]->cor == nextColor && raiz->vizinhos[i]->id != 0 ) { //se o vizinho direto tem a cor = nextColor
 //     printf("%d\n",nextColor );
      flagChanges = 1;
      insertNode(&heap,i); //indica vaga na lista
      
      vizinhoDireto = &raiz->vizinhos[i];  //vizinho direto identificado

      (*vizinhoDireto)->id = 0;
      (*vizinhoDireto)->estado = 0;

      (*vizinhoDireto)->distancia -= 1; ///////////////REVER DISTANCIA

     // printf("@@@merging %d@@@\n",(*vizinhoDireto)->id);

      for(j = 0; j < (*vizinhoDireto)->numVizinhos; ++j ) { //pega os vizinhos dos novos componentes a serem absorvidos       

        vizinhoIndireto = &((*vizinhoDireto)->vizinhos[j]); //vizinhos dos componentes absorvidos
      //  if  ( (*vizinhoIndireto)->id == 0 ) continue;      
        
        
        if(!saoVizinhosCadastrados(raiz,(*vizinhoIndireto)) && (*vizinhoIndireto)->id != 0 ) {
          flag1 = 1;
        }

          for (k = 0; k < (*vizinhoIndireto)->numVizinhos; ++k ) { //vizinhos dos vizinhos
            segundoPonteiroDireto = &((*vizinhoIndireto)->vizinhos[k]);

            if(!saoVizinhosCadastrados(raiz,(*segundoPonteiroDireto)) && (*segundoPonteiroDireto)->id != 0 ) {
              
                (*segundoPonteiroDireto)->distancia-=1; ///////////////REVER DISTANCIA
                raiz->vizinhos[offsetVizinhos] = *segundoPonteiroDireto;
                ++offsetVizinhos;


             
              
            }

          }
    

      }

    }

    if (flag1) {
      (*vizinhoIndireto)->distancia-=1; ///////////////REVER DISTANCIA
      if( heap.size>0 ) {
        raiz->vizinhos[heap.elem->data] = *vizinhoIndireto; //realoca valor em posicao vazia do vetor
        deleteNode(&heap); //reduz heap
      }
      else {
        raiz->vizinhos[offsetVizinhos] = (*vizinhoIndireto);
        +offsetVizinhos;
      }

      flag1= 0 ;
    }
  
  }

  if(flagChanges){
    raiz->numVizinhos = offsetVizinhos;
    nodo->componentes[0].cor = nextColor;

  }
  return flagChanges;

  //printf("Heap:%d\n",heap.size);
}



void search_component(char x, char y, tnodo *nodo) {
//  printf("\n{%d,%d}\n",x,y);
  int i;
  tcomponente * vizinho;
  int current = nodo->numComponentes;

  for (i = 0; i < current; ++i) {
    
    if (nodo->componentes[i].cor != nodo->componentes[current].cor )  { //se as cores forem diferentes

      int a;
   //   printf("componente %d :",i);
      for (a = 0; a < nodo->componentes[i].tamanho ;++a){
      //    printf("|%d,%d|\n",nodo->componentes[i].pontos[a].coordX,nodo->componentes[i].pontos[a].coordY); 
          if(x == nodo->componentes[i].pontos[a].coordX && y == nodo->componentes[i].pontos[a].coordY && !saoVizinhosCadastrados(&nodo->componentes[i],&nodo->componentes[current]) ) { //se o vizinho existe
              //adiciona vizinhos
      //      printf("[%d,%d]\n",x,y);

            nodo->componentes[i].vizinhos[nodo->componentes[i].numVizinhos] = &nodo->componentes[current];
            nodo->componentes[current].vizinhos[nodo->componentes[current].numVizinhos] = &nodo->componentes[i];
            nodo->componentes[i].numVizinhos+=1;
            nodo->componentes[current].numVizinhos+=1;

         //   printf("%d <-> %d\n",current,i);

            return;

          }

      } 
      //   printf("\n");
    }    
       
   
  }


}




void componentes (tnodo *nodo, tmapa *temp, char l, char c, char cor) { //consome a matriz de char inicial para gerar um grafo
  

   if(cor == 0) return; //já visitado
 

   else {

       temp->mapa[l][c] = 0;

   //    printf ("(%d,%d) ",l,c );
       char tamanho = nodo->componentes[nodo->numComponentes].tamanho;
       
       nodo->componentes[nodo->numComponentes].pontos[tamanho].coordX = l;
       nodo->componentes[nodo->numComponentes].pontos[tamanho].coordY = c;        
       nodo->componentes[nodo->numComponentes].tamanho +=1;

       if(l < temp->nlinhas - 1) {
         if(temp->mapa[l+1][c] == cor ) {

          componentes(nodo, temp, l+1, c, cor);
         }

         else if (temp->mapa[l+1][c] == 0) { //já foi inserido como componente
           search_component(l+1,c,nodo); 
         } 

       }
       
       if(c < temp->ncolunas - 1) {
         if( temp->mapa[l][c+1] == cor ) {

          componentes(nodo, temp, l, c+1, cor);
         }

         else if (temp->mapa[l][c+1] == 0) { //já foi inserido como componente
           search_component(l,c+1,nodo);  
         } 

       }     

       if(l > 0) {
         if( temp->mapa[l-1][c] == cor) {

          componentes(nodo, temp, l-1, c, cor);
         }

         else if (temp->mapa[l-1][c] == 0) { //já foi inserido como componente
           search_component(l-1,c,nodo);  
         } 

       } 

       if(c > 0) {
         if( temp->mapa[l][c-1] == cor) {

          componentes(nodo, temp, l, c-1, cor);
         }

         else if (temp->mapa[l][c-1] == 0) { //já foi inserido como componente
           search_component(l,c-1,nodo);  
         } 

       } 


   }

}

void get_componentes (tnodo *nodo, tmapa *m) {
  char l ;
  char c ;
  char cor;
  tmapa temp;
//    printf("!");
  copia_mapa(m,&temp);

  nodo->numComponentes = 0;
  nodo->componentes = NULL;
  aloca_componentes(&(nodo->componentes),MAXCOMPONENT);
  for(l = 0; l < m->nlinhas; l++){
    for(c = 0; c < m->ncolunas; c++){
       cor = temp.mapa[l][c];  
       if(cor != 0) {
          
          nodo->componentes[nodo->numComponentes].cor = cor; //cor do novo componente
          nodo->componentes[nodo->numComponentes].tamanho = 0; //tamanho do novo componente
          nodo->componentes[nodo->numComponentes].id = nodo->numComponentes; //cor do novo componente
          nodo->componentes[nodo->numComponentes].estado = 1; //não sofreu merges
          aloca_pontos(&(nodo->componentes[nodo->numComponentes].pontos),MAXPONTOS);
          aloca_vizinhos(nodo,MAXVIZINHOS); 
          
          /////////////////////////////////////////////TODO MALLOC NOS COMPONENTES E GERAR VIZINHOS////////////////////////////////////////////////////
          //printf("/////////////////componente_id = %d /////////////////////\n",nodo->numComponentes);
          componentes(nodo, &temp, l, c,cor);
         // printf("\n");
         
         // mostra_mapa_cor(&temp);

       //   printf("|cor = %d ",cor);
     //     printf("area = %d |\n",nodo->componentes[nodo->numComponentes].tamanho+1);
          
          nodo->numComponentes+=1;
       }

    }
  }

  for (l = 0; l <nodo->numComponentes; ++l) {
    free((nodo->componentes[nodo->numComponentes].pontos));
    nodo->componentes[l].distancia = -1; //distancia invalida inicial
  }
  
  nodo->componentes[0].distancia =0; //nó raiz tem distancia 0;
  getDistancia(nodo);

 

}


void gera_mapa(tmapa *m, int semente) {
  char i, j;

  if(semente < 0)
    srand(time(NULL));  
  else
    srand(semente);  
  m->mapa = (char**) malloc(m->nlinhas * sizeof(char*));
    for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (char*) malloc(m->ncolunas * sizeof(char));
    for(j = 0; j < m->ncolunas; j++)
      m->mapa[i][j] = 1 + rand() % m->ncores;
  }
}

void carrega_mapa(tmapa *m) {
  char i, j;

  scanf("%d",(int *) &(m->nlinhas));
  scanf("%d",(int *) &(m->ncolunas));
  scanf("%d",(int *) &(m->ncores));
  m->mapa = (char**) malloc(m->nlinhas * sizeof(char*));
  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (char*) malloc(m->ncolunas * sizeof(char));
    for(j = 0; j < m->ncolunas; j++)
      scanf("%d",(int *) &(m->mapa[i][j]));
  }
}





void pinta(tmapa *m, char l, char c, char fundo, char cor) {
  m->mapa[l][c] = cor;
  if(l < m->nlinhas - 1 && m->mapa[l+1][c] == fundo)
    pinta(m, l+1, c, fundo, cor);
  if(c < m->ncolunas - 1 && m->mapa[l][c+1] == fundo)
    pinta(m, l, c+1, fundo, cor);
  if(l > 0 && m->mapa[l-1][c] == fundo)
    pinta(m, l-1, c, fundo, cor);
  if(c > 0 && m->mapa[l][c-1] == fundo)
    pinta(m, l, c-1, fundo, cor);
}

void pinta_mapa(tmapa *m, char cor) {
  if(cor == m->mapa[0][0])
    return;
  pinta(m, 0, 0, m->mapa[0][0], cor);
}

void printSolution(char * vector, int size){
  int i;
  printf("%d\n",size);
  for (i = 0; i < size; ++i) {
    printf("%d ",vector[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  char cor;
  tnodo * campo = (tnodo *) malloc (sizeof(campo));
  int semente;
  tmapa * m = (tmapa *) malloc (sizeof(tmapa));

  if(argc < 4 || argc > 5) {
    printf("uso: %s <numero_de_linhas> <numero_de_colunas> <numero_de_cores> [<semente_aleatoria>]\n", argv[0]);
    exit(1);
  }

  m->nlinhas = atoi(argv[1]);
  m->ncolunas = atoi(argv[2]);
  m->ncores = atoi(argv[3]);



 // grafo.vizinhos =(tcomponenteCor *) malloc(grafo.m.ncores*sizeof(tcomponenteCor)); //aloca vetor de componentes vizinhos

  if(argc == 5)
    semente = atoi(argv[4]);
  else
    semente = -1;
  gera_mapa(m, semente);
  mostra_mapa(m);

  get_componentes((campo),m);
  
 // mostraVizinhos(campo);
//  mostra_mapa_cor(m);



errno = 0;
struct rusage* memory = malloc(sizeof(struct rusage));
getrusage(RUSAGE_SELF, memory);
if(errno == EFAULT)
    printf("Error: EFAULT\n");
else if(errno == EINVAL)
    printf("Error: EINVAL\n");
  

  //scanf("%d",(int *) &cor);//resposta do SMA-Star
  mergeRoot(campo,cor);
  
  int i;
  int moveCounter=0;
  char * moveArray =(char*) malloc(10000);
  int finish =1;
//     printf("componentes restantes: %d\n",finish=mostraVizinhos((campo)));
  //  printf("componentes ligados no raiz: %d\n",campo->componentes[0].numVizinhos);
  cor = 1;
  while(finish > 0) {
   
    //mostra_mapa_cor(m); // para mostrar sem cores use mostra_mapa(&m);
  //  scanf("%d",(int *) &cor);


    for (i = 1; i<=m->ncores && finish>0;++i) {
     moveArray[moveCounter] = i;//////////////////////VER ISSSOOOO
     moveCounter+=mergeRoot(campo,i);
     finish=mostraVizinhos(campo);
 //    printf("componentes restantes: %d\n",finish);
   // printf("componentes ligados no raiz: %d\n",campo->componentes[0].numVizinhos);
      //getDistancia(campo); //calcula distancias atuais
    }
    


  }

     // printf("Memory allocated: %ld\n", memory->ru_maxrss); 
      printSolution(moveArray, moveCounter);

  return 0;
}
