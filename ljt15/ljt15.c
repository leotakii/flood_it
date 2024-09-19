#include <stdio.h>
#define failure FALSE
#define success TRUE

int main()
{
    
}

int g(Node n, Graph graph) {
    //distancia do nodo inicial ao nodo atual
}

int h(Node n, Graph graph) {
    int components[colors];
    int area[colors];
    int frontierComponents[colors];
    int frontierArea[colors];

     return getFartherComponent(graph,i); //Heurística menos ruim que as abaixo.

    for (int i = 0; i < colors; ++i) {

        getComponentsAndAreaByColor(graph,i,&components[i],&area[i]);
        getFrontierComponentsAndAreaByColor(graph,i,&frontierComponents[i],&frontierArea[i]);
    }
    //contar componentes na vizinhanca 
    //decidir em uma razão entre numero de componentes vizinhos, tamanho deles e presença de cada um no mapa. 
    //Escolher nodo que mais reduz a presença de certa cor no mapa(??) 
}

bool SMA_star(Graph graph,List path *) {
    OrderedQueue nodeQueue;
    queueInsert(&nodeQueue,&graph.root); //insere na fila o no raiz
    Node * currentNode;
    Node * successor
    for(;;) {
        if ( isEmpty(&nodeQueue) ){ //se não houver mais nenhum filho
            return failure;
        }
        currentNode = first(&nodeQueue); //pega o primeiro da fila de prioridades
        if (isGoal(&graph, currentNode) ) { //se é solucao
            return success;
        }
        successor = &nextSuccessor(currentNode); //prox filho nao explorado
        
        if (!isGoal(&graph, successor) && depth(successor) == max_depth) { //se enfileirar o sucessor ocupar mais que o máximo de memória
            f(successor) = infinite;
        }
        
        else {
            f(successor) = max( f(currentNode), g(successor) + h(successor))
        }
        //g = cost from origin
        
        /*if no more successors then
        update f-cost of node and those of its ancestors if needed
        */
        if (currentNode.successors ⊆ queue ) //se todos os filhos do no atual estão na fila de prioridade
            queue.remove(currentNode);  //remove no atual

        if (memory is full) { //se ocupou toda a memoria
            badNode := shallowest node with highest f-cost; //encontra o nó mais raso com o maior custo f
            for (parent in badNode.parents) {
                parent.successors.remove(badNode); //remove todos os filhos dele
                if needed then queue.insert(parent);  //insere ele na fila de volta
            }
    
        }

        queue.insert(successor); //insere sucessor na fila.
    }   
    
    
}
/*
function SMA-star(problem): path
  queue: set of nodes, ordered by f-cost;
begin
  queue.insert(problem.root-node);

  while True do begin
    if queue.empty() then return failure; //there is no solution that fits in the given memory
    node := queue.begin(); // min-f-cost-node
    if problem.is-goal(node) then return success;
    
    s := next-successor(node)
    if !problem.is-goal(s) && depth(s) == max_depth then
        f(s) := inf; 
        // there is no memory left to go past s, so the entire path is useless
    else
        f(s) := max(f(node), g(s) + h(s));
        // f-value of the successor is the maximum of
        //      f-value of the parent and 
        //      heuristic of the successor + path length to the successor
    endif
    if no more successors then
       update f-cost of node and those of its ancestors if needed
    
    if node.successors ⊆ queue then queue.remove(node); 
    // all children have already been added to the queue via a shorter way
    if (memory is full) {
        badNode := shallowest node with highest f-cost;
        for (parent in badNode.parents) {
            parent.successors.remove(badNode);
            if needed then queue.insert(parent); 
        }
    
    }
      

    queue.insert(s);
  endwhile
end
*/