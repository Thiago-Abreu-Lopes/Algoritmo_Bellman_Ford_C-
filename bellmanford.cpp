#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#define Vertex int
#define INFINITO 36

using namespace std;
/*******************************************************ESTRUTURA*******************************************************/

struct digraph{
	int V;                          //N�mero de Vertices
	int A;                          //N�mero de Arestas
	vector<vector<int> > adj;       //Matriz de Adjac�ncia
};

/**************************************************FUN��ES AUXILIARES**************************************************/

//Fun��o inicializadora de Digrafos
struct digraph Digraphinit(Vertex v){
	struct digraph g;
	vector<vector<int> >  matrix(v, vector<int>(v,INFINITO));     //A matriz de adjanc�ncia � preenchida com INFINITO para permitir o uso de peso 0
	g.V = v;
	g.A = 0;
	g.adj = matrix;
	return g;
};

//Fun��o de inser��o de Aresta no Digrafo
void DigraphinsertA(struct digraph &g,Vertex v, Vertex w, int peso){
	if(v!=w && g.adj[v][w]==INFINITO){
		g.A++;
		g.adj[v][w]=peso;
	};
};

//Fun��o de remo��o de Aresta no Digrafo (percebi q n�o serve pra nada, mas deixa a�)
void DigraphremoveA(struct digraph &g,int v, int w){
	if(g.adj[v][w]!=INFINITO){
		g.adj[v][w]=0;
		g.A--;
	}
};

//Fun��o de impress�o pra lista de adjacencia
void ImprimeDigraph(struct digraph &g){
	for(int i=0;i<g.adj.size();i++){
        for(int j=0;j<g.adj[i].size();j++)
            if(g.adj[i][j]==INFINITO){                  //substitui os valores INFINITO por "-"
            	cout<<"-"<<"\t";
			}else{
				cout<<g.adj[i][j]<<"\t";
			}
        cout<<endl;
    } 
    cout<<endl;
    printf("\n\n");
}
/***************************************************BELLMAN FORD**********************************************/

vector<int> cst(INFINITO);

/*
	O Algoritmo de Bellman Ford � uma fun��o que permite descobrir o caminho m�nimo de grafos, 
	diferencia-se do Algoritmo de Dijkstra por ter a capacidade de descobrir caminho m�nimo
	de -> DIGRAFOS <- com pesos de arestas negativos (e por ser mais f�cil de pronunciar :D).
	
*/
//Fun��o Bellman Ford (agora vai)
void bellman_ford2(struct digraph &g, Vertex s){
	Vertex v, w;
	int k, d;
	cst.resize(g.V);                 //Reajusta o vetor de custo
	for(v=0;v<g.V;v++){
		cst[v]=INFINITO;             //Atribui a lista de custo valores Infinitos
	}
	cst[s]=0;                        //Menos no valor correspondente a fonte(Vertice de onde parte o calculo do custo)
	bool change;                     //Boleano para verificar se houve mudan�as nos valores de custo 
	for(k=1;k<g.V;k++){
		change = false;             
		for(v=0;v<g.V;v++){
			for(w=0;w<g.A;w++){
				d=cst[v]+g.adj[v][w];  //Parte referente ao relaxamento
				if(cst[w]>d){          //Verifica se a soma do peso da aresta e do vertice anterior e menor que o valor atual de custo
					cst[w]=d;          //Se for atribui a ao custo em quest�o esse valor
					change = true;     //Sinaliza q houve mudan�a
				}
			}	
		}
		if(!change) break;             //Quebra o la�o para evitar loop
	}
	
	for(v=0;v<g.V;v++){                //Parte resposns�vel de verrificar se h� ciclo negativo
		for(w=0;w<g.A;w++){
			if(cst[v]+g.adj[v][w]<cst[w]){
				cout<<"Possui ciclo negativo!!"<<endl;
			}
		}
	}

}

/********************************************************APLICA��O*********************************************/

int main(){
	struct digraph g,f,h; //Digrafos para teste
    
	//inicializa��o dos digrafos
	g=Digraphinit(5);    
	h=Digraphinit(4);
    f=Digraphinit(3);
	
	//inser��o das arestas nos digrafos
	DigraphinsertA(f,0,1,-3);
	DigraphinsertA(f,1,2,2);
	DigraphinsertA(f,2,0,2);
	DigraphinsertA(f,0,2,5);
	
	DigraphinsertA(h,0,1,3);
	DigraphinsertA(h,0,2,1);
	DigraphinsertA(h,1,3,-4);
	DigraphinsertA(h,3,2,4);
	DigraphinsertA(h,3,0,5);
	DigraphinsertA(h,2,1,2);
	
	//DIGRAFO UTILIZADO NO SLIDE DA AULA 17(ultimo exemplo)
	DigraphinsertA(g,0,1,3);
	DigraphinsertA(g,0,3,6);
	DigraphinsertA(g,1,2,0);
	DigraphinsertA(g,1,4,-2);
	DigraphinsertA(g,3,1,-1);
	DigraphinsertA(g,3,4,-7);
	DigraphinsertA(g,4,2,3);
	
	//impress�o dos digrafos
	cout<<"DIGRAFO 1"<<endl;
    ImprimeDigraph(f);
    cout<<"DIGRAFO 2"<<endl;
    ImprimeDigraph(h);
    cout<<"DIGRAFO 3"<<endl;
    ImprimeDigraph(g);
    cout<<"Partindo de 0:"<<endl;
    printf("\n\n");
	
	//teste da fun��o Bellman Ford
	cout<<"Caminho minimo do DIGRAFO 1: {\t";
	bellman_ford2(f,0);
	for(int u=0;u<cst.size();u++){
		cout << cst[u] << "\t";
	}
	cout<<"}"<<endl;
	
	cout<<"Caminho minimo do DIGRAFO 2: {\t";
	bellman_ford2(h,0);
	for(int u=0;u<cst.size();u++){
		cout << cst[u] << "\t";
	}
	cout<<"}"<<endl;
	
	cout<<"Caminho minimo do DIGRAFO 3: {\t";
	bellman_ford2(g,0);
	for(int u=0;u<cst.size();u++){
		cout << cst[u] << "\t";
	}
	cout<<"}"<<endl;
	
	// :)
	
	return 1;
}
