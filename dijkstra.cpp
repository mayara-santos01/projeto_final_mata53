#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <utility>
#include <climits>
#include <ctime>
using namespace std;

//Estrutura de dados que é utilizada para a criação do grafo inicial 
struct Vertice{
    //O rótulo do vértice
    string label;
    //Lista que contém as arestas, compostas pelo rótulo do vértice
    //E pela largura de banda do link entre os dois vértices
    vector<pair<string, int>> arestas;
};

//Estrutura de dados utilizada para gerenciamento dos nós
//Durante a execução do algortimo
struct Node{
    string label;
    int distancia_ate_raiz;
    string no_anterior;
    vector<pair<string, int>> arestas;
    int arestas_visitadas = 0;
};

//Os parâmetros da função são o grafo, o rótulo do vértice de origm e o rótulo do vértice de destino
vector<string> dijkstra_algorithm(vector<Vertice> grafo, string root, string destino){
    vector<Node> vetor_iteracao;
    vector<Node> vetor_resultado;
    vector<string> caminho;
    int contador = 0;
    
    //Construindo a lista inicial 
    for (int i=0; i<grafo.size(); i++){ //O(n)
        //Definimos a distância de todos os vértices até a raíz como infinito
        int distancia = INT_MAX;
        for (int j=0; j<grafo[i].arestas.size(); j++){ //O(m)
            if (grafo[i].arestas[j].first == root){
                //Se o vértice de origem for adjacente ao nó analisado, mudamos a distância inicial
                distancia = grafo[i].arestas[j].second;
                cout<<"Distancia ate a raiz "<<i<<" "<<grafo[i].label<<" "<<root<<" "<<distancia<<endl;
            }
        }
        //Se o nó for adjacente à raiz, criamos um vértice
        //para adicionarmos no grafo que será manipulado pelo algoritmo
        //com a distância obtida
        if (distancia < INT_MAX){
            Node no_atual;
            no_atual.label = grafo[i].label;
            no_atual.distancia_ate_raiz = distancia;
            no_atual.no_anterior = root;
            for (int k = 0; k < grafo[i].arestas.size(); k++){ // O(m)
                no_atual.arestas.push_back(make_pair(grafo[i].arestas[k].first, grafo[i].arestas[k].second));
            }
            vetor_iteracao.push_back(no_atual);
        }
        else if (grafo[i].label != root){           
            Node no_atual1;
            no_atual1.label = grafo[i].label;
            no_atual1.distancia_ate_raiz = INT_MAX;
            no_atual1.no_anterior = "None";
            for (int k = 0; k < grafo[i].arestas.size(); k++){
                no_atual1.arestas.push_back(make_pair(grafo[i].arestas[k].first, grafo[i].arestas[k].second));
            }
            vetor_iteracao.push_back(no_atual1);
            
       }
            
        // Custo do loop: O(m+n)
    }
    
    //for (Node no : vetor_iteracao){
    //    cout<<no.label<<" ";
    //}
    //cout<<endl;
    
    //Executando o algortimo de Dijkstra
    //for (int x=1; x < vetor_iteracao.size(); x++){
    while (!vetor_iteracao.empty()){
        // Criação de um vetor para inserir vértices do inner_core
        //que é incialziado como vazio durante o começo de cada iteração
        vector<pair<int, int>> vertices_innercore;
        int distancia = INT_MAX; 
        int menor_indice = -1;
        for (int i=0; i < vetor_iteracao.size(); i++){
            if (vetor_iteracao[i].distancia_ate_raiz < distancia){
                //Selecionando o vértice com menor distância até a raiz
                distancia = vetor_iteracao[i].distancia_ate_raiz;
                //Armazenando o índice do vértice de menor distância
                menor_indice = i;
            }
            //Verificando se o vértice faz parte do inner_core
            if (vetor_iteracao[i].label[0] == 'i' && vetor_iteracao[i].distancia_ate_raiz < INT_MAX){
                // Preenchendo o vetor que reúne vertices do iner_core
                // com as distancias e os indices
                vertices_innercore.push_back(make_pair(vetor_iteracao[i].distancia_ate_raiz, i));
            }
        }
        // A prioridade é selecionar vértices do inner_core por permitirem
        // Conexões mais rápidas
        if (!vertices_innercore.empty()){
            distancia = INT_MAX;
            for (int j = 0; j < vertices_innercore.size(); j++){
                if (vertices_innercore[j].first < distancia){
                    distancia = vertices_innercore[j].first;
                    menor_indice = vertices_innercore[j].second;
                }
            }
        }
        cout<<"pivo "<<vetor_iteracao[menor_indice].label<<endl;
        // vetor_iteracao[menor_indice] é o pivô da iteração
        for (int j=0; j < vetor_iteracao[menor_indice].arestas.size(); j++){ //O(m)
            string vizinho_atual = vetor_iteracao[menor_indice].arestas[j].first;
            cout<<"Analisando "<<vizinho_atual<<endl;
            // Procurar o vértice que tem o label do vizinho que estamos analisando
            for (int k=0; k < vetor_iteracao.size(); k++){ //O(n)
                if ((vetor_iteracao[k].label == vizinho_atual) && (vetor_iteracao[k].label != root)){
                    int distancia_atual = vetor_iteracao[k].distancia_ate_raiz;
                    // O segundo elemento da soma é o peso da aresta entre o pivô e seu adjacente analisado
                    int distancia_proposta = vetor_iteracao[menor_indice].distancia_ate_raiz + vetor_iteracao[menor_indice].arestas[j].second;
                    cout<<distancia_atual<<" "<<distancia_proposta<<endl;
                    cout<<"Comparando distancias "<<vetor_iteracao[menor_indice].distancia_ate_raiz<<" "<< vetor_iteracao[menor_indice].arestas[j].second<<endl;
                    if (distancia_atual > distancia_proposta){
                        vetor_iteracao[k].distancia_ate_raiz = distancia_proposta;
                        vetor_iteracao[k].no_anterior = vetor_iteracao[menor_indice].label;
                    }
                    
                }
            }
            
        }
        vetor_resultado.push_back(vetor_iteracao[menor_indice]);
        vetor_iteracao.erase(vetor_iteracao.begin() + menor_indice);
    }
    
    // Custo total do loop: O(m+n)
    
    
    
    /*for (int i=0; i<vetor_resultado.size(); i++){
        cout<<"*** Vertice "<<vetor_resultado[i].label<<" "<<vetor_resultado[i].distancia_ate_raiz<<" ***"<<endl;
        cout<<"Arestas"<<endl;
        for(int k = 0; k < vetor_resultado[i].arestas.size(); k++){
            cout<<vetor_resultado[i].arestas[k].first<<" "<<vetor_resultado[i].arestas[k].second<<endl;
        }
        cout<<endl;
    }*/
    int indice = 0;
    // Encontrar o indice do vetor que tem o vértice de destino
    for (int j=0; j<vetor_resultado.size(); j++){
        if (vetor_resultado[j].label == destino){
            indice = j;
            break;
            }
        } 
    string vertice_anterior;
    cout<<indice<<endl;
    caminho.push_back(vetor_resultado[indice].label);
    int x=0;
    while (true){
        //Se o nó anterior for a raiz, podemos encerrar o processamento
        if (vetor_resultado[indice].no_anterior == root){
            caminho.push_back(root);
            break;
        }
        for (int j=0; j<vetor_resultado.size(); j++){
            // Se estamos analisando o vertice anterior ao vertice do indice
            // a posicao dele passa a ser o novo indice
            if (vetor_resultado[j].label == vetor_resultado[indice].no_anterior){
                indice = j;
                // Armazenando o vértice no vetor de caminho
                vertice_anterior = vetor_resultado[indice].label;                
                cout<<"vertice analisado "<<vertice_anterior<<endl;

                caminho.push_back(vertice_anterior);
                cout<<vertice_anterior<<endl;
                break;
                }
            } 
            if (vertice_anterior == root){
                break;
            }
        x+=1;
    }
    
    return caminho;
    
}


int main(){
    // Marca o tempo de início
    clock_t start = clock();
    
    vector<Vertice> graph;
    
    Vertice ic1_1;
    ic1_1.label = "ic1_1";
    ic1_1.arestas = {{"ag2", 10}, {"ag3", 10}, {"ag4", 10}, {"ag8", 10}, {"ic1_2", 100}, {"ic1_4", 100}, {"ic2_1", 100}};
    graph.push_back(ic1_1);
    
    Vertice ic1_2;
    ic1_2.label = "ic1_2";
    ic1_2.arestas = {{"ag1", 10}, {"ag9", 10}, {"ag12", 10}, {"ic1_1", 100}, {"ic1_3", 100}, {"ic2_2", 100}};
    graph.push_back(ic1_2);
    
    Vertice ic1_3;
    ic1_3.label = "ic1_3";
    ic1_3.arestas = {{"ag15", 10}, {"ag22", 10}, {"ag23", 10}, {"ag24", 10}, {"ic1_4", 100}, {"ic1_2", 100}, {"ic2_3", 100}};
    graph.push_back(ic1_3);
    
    Vertice ic1_4;
    ic1_4.label = "ic1_4";
    ic1_4.arestas = {{"ag20", 10}, {"ag26", 10}, {"ag27", 10}, {"ag28", 10}, {"ic1_1", 100}, {"ic1_3", 100}, {"ic2_4", 100}};
    graph.push_back(ic1_4);
    
    Vertice ic2_1;
    ic2_1.label = "ic2_1";
    ic2_1.arestas = {{"ag5", 10}, {"ag6", 10}, {"ag10", 10}, {"ic1_1", 100}, {"ic2_2", 100}, {"ic2_4", 100}};
    graph.push_back(ic2_1);
    
    Vertice ic2_2;
    ic2_2.label = "ic2_2";
    ic2_2.arestas = {{"ag11", 10}, {"ag13", 10}, {"ag16", 10}, {"ic1_2", 100}, {"ic2_1", 100}, {"ic2_3", 100}};
    graph.push_back(ic2_2);
    
    Vertice ic2_3;
    ic2_3.label = "ic2_3";
    ic2_3.arestas = {{"ag14", 10}, {"ag19", 10}, {"ag25", 10}, {"ic1_3", 100}, {"ic2_2", 100}, {"ic2_4", 100}};
    graph.push_back(ic2_3);
    
    Vertice ic2_4;
    ic2_4.label = "ic2_4";
    ic2_4.arestas = {{"ag7", 10}, {"ag20", 10}, {"ag21", 10}, {"ic1_4", 100}, {"ic2_1", 100}, {"ic2_3", 100}};
    graph.push_back(ic2_4);
    
    Vertice ag1;
    ag1.label = "ag1";
    ag1.arestas = {{"ac1", 10}, {"ac4", 10}, {"ac13", 10}, {"ag2", 10}, {"ic1_2", 10}};
    graph.push_back(ag1);
    
    Vertice ag2;
    ag2.label = "ag2";
    ag2.arestas = {{"ac14", 10}, {"ac15", 10}, {"ag1", 10}, {"ic1_1", 10}};
    graph.push_back(ag2);
    
    Vertice ag3;
    ag3.label = "ag3";
    ag3.arestas = {{"ic1_1", 10}};
    graph.push_back(ag3);
    
    Vertice ag4;
    ag4.label = "ag4";
    ag4.arestas = {{"ac10", 10}, {"ac15", 10}, {"ag5", 10}, {"ic1_1", 10}};
    graph.push_back(ag4);
    
    Vertice ag5;
    ag5.label = "ag5";
    ag5.arestas = {{"ac12", 10}, {"ag4", 10}, {"ic2_1", 10}};
    graph.push_back(ag5);
    
    Vertice ag6;
    ag6.label = "ag6";
    ag6.arestas = {{"ac16", 10}, {"ag7", 10}, {"ic2_1", 10}};
    graph.push_back(ag6);
    
    Vertice ag7;
    ag7.label = "ag7";
    ag7.arestas = {{"ac3", 10}, {"ag6", 10}, {"ic2_4", 10}};
    graph.push_back(ag7);
    
    Vertice ag8;
    ag8.label = "ag8";
    ag8.arestas = {{"ac17", 10}, {"ag9", 10}, {"ic1_1", 10}};
    graph.push_back(ag8);
    
    Vertice ag9;
    ag9.label = "ag9";
    ag9.arestas = {{"ac18", 10}, {"ag8", 10}, {"ic1_2", 10}};
    graph.push_back(ag9);
    
    Vertice ag10;
    ag10.label = "ag10";
    ag10.arestas = {{"ac19", 10}, {"ag11", 10}, {"ic2_1", 10}};
    graph.push_back(ag10);
    
    Vertice ag11;
    ag11.label = "ag11";
    ag11.arestas = {{"ac20", 10}, {"ag10", 10}, {"ic2_2", 10}};
    graph.push_back(ag11);
    
    Vertice ag12;
    ag12.label = "ag12";
    ag12.arestas = {{"ac21", 10}, {"ag15", 10}, {"ic1_2", 10}};
    graph.push_back(ag12);
    
    Vertice ag13;
    ag13.label = "ag13";
    ag13.arestas = {{"ac23", 10}, {"ag14", 10}, {"ic2_2", 10}};
    graph.push_back(ag13);
    
    Vertice ag14;
    ag14.label = "ag14";
    ag14.arestas = {{"ac24", 10}, {"ag13", 10}, {"ic2_3", 10}};
    graph.push_back(ag14);
    
    Vertice ag15;
    ag15.label = "ag15";
    ag15.arestas = {{"ac22", 10}, {"ag12", 10}, {"ic1_3", 10}};
    graph.push_back(ag15);
    
    Vertice ag16;
    ag16.label = "ag16";
    ag16.arestas = {{"ag17", 10}, {"ic2_2", 10}};
    graph.push_back(ag16);
    
    Vertice ag17;
    ag17.label = "ag17";
    ag17.arestas = {{"ac25", 10}, {"ag16", 10}};
    graph.push_back(ag17);
    
    Vertice ag18;
    ag18.label = "ag18";
    ag18.arestas = {{"ag19", 10}, {"ic1_3", 10}};
    graph.push_back(ag18);
    
    Vertice ag19;
    ag19.label = "ag19";
    ag19.arestas = {{"ac43", 10}, {"ag18", 10}, {"ic2_3", 10}};
    graph.push_back(ag19);
    
    Vertice ag20;
    ag20.label = "ag20";
    ag20.arestas = {{"ac54", 10}, {"ag21", 10}, {"ic1_4", 10}};
    graph.push_back(ag20);
    
    Vertice ag21;
    ag21.label = "ag21";
    ag21.arestas = {{"ac57", 10}, {"ag20", 10}, {"ic2_4", 10}};
    graph.push_back(ag21);
    
    Vertice ag22;
    ag22.label = "ag22";
    ag22.arestas = {{"ac40", 10}, {"ag25", 10}, {"ic1_3", 10}};
    graph.push_back(ag22);
    
    Vertice ag23;
    ag23.label = "ag23";
    ag23.arestas = {{"ac26", 10}, {"ac33", 10}, {"ag26", 10}, {"ic1_3", 10}};
    graph.push_back(ag23);
    
    Vertice ag24;
    ag24.label = "ag24";
    ag24.arestas = {{"ac29", 10}, {"ag27", 10}, {"ic1_3", 10}};
    graph.push_back(ag24);
    
    Vertice ag25;
    ag25.label = "ag25";
    ag25.arestas = {{"ac44", 10}, {"ag22", 10}, {"ic2_3", 10}};
    graph.push_back(ag25);
    
    Vertice ag26;
    ag26.label = "ag26";
    ag26.arestas = {{"ac28", 10}, {"ag23", 10}, {"ic1_4", 10}};
    graph.push_back(ag26);
    
    Vertice ag27;
    ag27.label = "ag27";
    ag27.arestas = {{"ac32", 10}, {"ag24", 10}, {"ic1_4", 10}};
    graph.push_back(ag27);
    
    Vertice ag28;
    ag28.label = "ag28";
    ag28.arestas = {{"ac49", 10}, {"ag29", 10}, {"ic1_4", 10}};
    graph.push_back(ag28);
    
    Vertice ag29;
    ag29.label = "ag29";
    ag29.arestas = {{"ac48", 10}, {"ac53", 10}, {"ag28", 10}, {"ic2_4", 10}};
    graph.push_back(ag29);
    
    Vertice ac1;
    ac1.label = "ac1";
    ac1.arestas = {{"ac2", 10}, {"ag1", 10}};
    graph.push_back(ac1);
    
    Vertice ac2;
    ac2.label = "ac2";
    ac2.arestas = {{"ac1", 10}, {"ac3", 10}};
    graph.push_back(ac2);
    
    Vertice ac3;
    ac3.label = "ac3";
    ac3.arestas = {{"ac2", 10}, {"ag7", 10}};
    graph.push_back(ac3);
    
    Vertice ac4;
    ac4.label = "ac4";
    ac4.arestas = {{"ag1", 10}, {"ac5", 10}};
    graph.push_back(ac4);
    
    Vertice ac5;
    ac5.label = "ac5";
    ac5.arestas = {{"ac4", 10}, {"ac6", 10}};
    graph.push_back(ac5);
    
    Vertice ac6;
    ac6.label = "ac6";
    ac6.arestas = {{"ac5", 10}, {"ac16", 10}};
    graph.push_back(ac6);
    
    Vertice ac7;
    ac7.label = "ac7";
    ac7.arestas = {{"ac8", 10}, {"ac13", 10}};
    graph.push_back(ac7);
    
    Vertice ac8;
    ac8.label = "ac8";
    ac8.arestas = {{"ac7", 10}, {"ac9", 10}};
    graph.push_back(ac8);
    
    Vertice ac9;
    ac9.label = "ac9";
    ac9.arestas = {{"ac8", 10}, {"ac14", 10}};
    graph.push_back(ac9);
    
    Vertice ac10;
    ac10.label = "ac10";
    ac10.arestas = {{"ac11", 10}, {"ag4", 10}};
    graph.push_back(ac10);
    
    Vertice ac11;
    ac11.label = "ac11";
    ac11.arestas = {{"ac10", 10}, {"ac12", 10}};
    graph.push_back(ac11);
    
    Vertice ac12;
    ac12.label = "ac12";
    ac12.arestas = {{"ac11", 10}, {"ag5", 10}};
    graph.push_back(ac12);
    
    Vertice ac13;
    ac13.label = "ac13";
    ac13.arestas = {{"ac7", 10}, {"ag1", 10}};
    graph.push_back(ac13);
    
    Vertice ac14;
    ac14.label = "ac14";
    ac14.arestas = {{"ac9", 10}, {"ag2", 10}};
    graph.push_back(ac14);
    
    Vertice ac15;
    ac15.label = "ac15";
    ac15.arestas = {{"ag2", 10}, {"ag4", 10}};
    graph.push_back(ac15);
    
    Vertice ac16;
    ac16.label = "ac16";
    ac16.arestas = {{"ac6", 10}, {"ag4", 10}, {"ag6", 10}};
    graph.push_back(ac16);
    
    Vertice ac17;
    ac17.label = "ac17";
    ac17.arestas = {{"ac18", 10}, {"ag8", 10}};
    graph.push_back(ac17);
    
    Vertice ac18;
    ac18.label = "ac18";
    ac18.arestas = {{"ac17", 10}, {"ag9", 10}};
    graph.push_back(ac18);
    
    Vertice ac19;
    ac19.label = "ac19";
    ac19.arestas = {{"ac20", 10}, {"ag10", 10}};
    graph.push_back(ac19);
    
    Vertice ac20;
    ac20.label = "ac20";
    ac20.arestas = {{"ac19", 10}, {"ag11", 10}};
    graph.push_back(ac20);
    
    Vertice ac21;
    ac21.label = "ac21";
    ac21.arestas = {{"ac22", 10}, {"ag12", 10}};
    graph.push_back(ac21);
    
    Vertice ac22;
    ac22.label = "ac22";
    ac22.arestas = {{"ac21", 10}, {"ag15", 10}};
    graph.push_back(ac22);
    
    Vertice ac23;
    ac23.label = "ac23";
    ac23.arestas = {{"ac24", 10}, {"ag13", 10}};
    graph.push_back(ac23);
    
    Vertice ac24;
    ac24.label = "ac24";
    ac24.arestas = {{"ac23", 10}, {"ag14", 10}};
    graph.push_back(ac24);
    
    Vertice ac25;
    ac25.label = "ac25";
    ac25.arestas = {{"ag17", 10}};
    graph.push_back(ac25);
    
    Vertice ac26;
    ac26.label = "ac26";
    ac26.arestas = {{"ac27", 10}, {"ag23", 10}};
    graph.push_back(ac26);
    
    Vertice ac27;
    ac27.label = "ac27";
    ac27.arestas = {{"ac26", 10}, {"ac28", 10}};
    graph.push_back(ac27);
    
    Vertice ac28;
    ac28.label = "ac28";
    ac28.arestas = {{"ac27", 10}, {"ag26", 10}};
    graph.push_back(ac28);
    
    Vertice ac29;
    ac29.label = "ac29";
    ac29.arestas = {{"ac30", 10}, {"ag24", 10}};
    graph.push_back(ac29);
    
    Vertice ac30;
    ac30.label = "ac30";
    ac30.arestas = {{"ac29", 10}, {"ac31", 10}};
    graph.push_back(ac30);
    
    Vertice ac31;
    ac31.label = "ac31";
    ac31.arestas = {{"ac30", 10}, {"ac32", 10}};
    graph.push_back(ac31);
    
    Vertice ac32;
    ac32.label = "ac32";
    ac32.arestas = {{"ac31", 10}, {"ag27", 10}};
    graph.push_back(ac32);
    
    Vertice ac33;
    ac33.label = "ac33";
    ac33.arestas = {{"ac34", 10}, {"ag23", 10}};
    graph.push_back(ac33);
    
    Vertice ac34;
    ac34.label = "ac34";
    ac34.arestas = {{"ac33", 10}, {"ac35", 10}};
    graph.push_back(ac34);
    
    Vertice ac35;
    ac35.label = "ac35";
    ac35.arestas = {{"ac34", 10}, {"ac36", 10}};
    graph.push_back(ac35);
    
    Vertice ac36;
    ac36.label = "ac36";
    ac36.arestas = {{"ac35", 10}, {"ac37", 10}};
    graph.push_back(ac36);
    
    Vertice ac37;
    ac37.label = "ac37";
    ac37.arestas = {{"ac36", 10}, {"ac38", 10}};
    graph.push_back(ac37);
    
    Vertice ac38;
    ac38.label = "ac38";
    ac38.arestas = {{"ac37", 10}, {"ac39", 10}};
    graph.push_back(ac38);
    
    Vertice ac39;
    ac39.label = "ac39";
    ac39.arestas = {{"ac38", 10}, {"ag25", 10}};
    graph.push_back(ac39);
    
    Vertice ac40;
    ac40.label = "ac40";
    ac40.arestas = {{"ac41", 10}, {"ag22", 10}};
    graph.push_back(ac40);
    
    Vertice ac41;
    ac41.label = "ac41";
    ac41.arestas = {{"ac40", 10}, {"ac42", 10}};
    graph.push_back(ac41);
    
    Vertice ac42;
    ac42.label = "ac42";
    ac42.arestas = {{"ac41", 10}, {"ac43", 10}};
    graph.push_back(ac42);
    
    Vertice ac43;
    ac43.label = "ac43";
    ac43.arestas = {{"ac42", 10}, {"ag19", 10}};
    graph.push_back(ac43);
    
    Vertice ac44;
    ac44.label = "ac44";
    ac44.arestas = {{"ac45", 10}, {"ag25", 10}};
    graph.push_back(ac44);
    
    Vertice ac45;
    ac45.label = "ac45";
    ac45.arestas = {{"ac44", 10}, {"ac46", 10}};
    graph.push_back(ac45);
    
    Vertice ac46;
    ac46.label = "ac46";
    ac46.arestas = {{"ac45", 10}, {"ac47", 10}};
    graph.push_back(ac46);
    
    Vertice ac47;
    ac47.label = "ac47";
    ac47.arestas = {{"ac46", 10}, {"ac48", 10}};
    graph.push_back(ac47);
    
    Vertice ac48;
    ac48.label = "ac48";
    ac48.arestas = {{"ac47", 10}, {"ag29", 10}};
    graph.push_back(ac48);
    
    Vertice ac49;
    ac49.label = "ac49";
    ac49.arestas = {{"ac50", 10}, {"ag28", 10}};
    graph.push_back(ac49);
    
    Vertice ac50;
    ac50.label = "ac50";
    ac50.arestas = {{"ac49", 10}, {"ac51", 10}};
    graph.push_back(ac50);
    
    Vertice ac51;
    ac51.label = "ac51";
    ac51.arestas = {{"ac50", 10}, {"ac52", 10}};
    graph.push_back(ac51);
    
    Vertice ac52;
    ac52.label = "ac52";
    ac52.arestas = {{"ac51", 10}, {"ac53", 10}};
    graph.push_back(ac52);
    
    Vertice ac53;
    ac53.label = "ac53";
    ac53.arestas = {{"ac52", 10}, {"ag29", 10}};
    graph.push_back(ac53);
    
    Vertice ac54;
    ac54.label = "ac54";
    ac54.arestas = {{"ac55", 10}, {"ag20", 10}};
    graph.push_back(ac54);
    
    Vertice ac55;
    ac55.label = "ac55";
    ac55.arestas = {{"ac54", 10}, {"ac56", 10}};
    graph.push_back(ac55);
    
    Vertice ac56;
    ac56.label = "ac56";
    ac56.arestas = {{"ac55", 10}, {"ac57", 10}};
    graph.push_back(ac56);
    
    Vertice ac57;
    ac57.label = "ac57";
    ac57.arestas = {{"ac56", 10}, {"ag21", 10}};
    graph.push_back(ac57);
    
    vector<string> resultado = dijkstra_algorithm(graph, "ic1_1", "ac57");
    
    cout<<"*** Caminho entre os vértices ici1_1 e ac57 ***"<<endl;
    for (string elem : resultado){
        cout<<elem<<" ";
    }

    // Marca o tempo de término
    clock_t end = clock();

    // Calcula a duração
    double duration = double(end - start) / CLOCKS_PER_SEC;

    // Exibe o tempo de execução em segundos
    cout<<"Tempo de execução: "<<duration<<" segundos"<<endl;


    return 0;
}
