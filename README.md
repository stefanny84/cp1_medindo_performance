# cp1_medindo_performance
# Comparação de Algoritmos de Ordenação em C

Este projeto implementa e compara três algoritmos de ordenação em diferentes cenários de entrada, medindo **tempo de execução** e **número de comparações** realizadas.

---

## Algoritmos Implementados

1. **Bubble Sort**  
   - Compara pares adjacentes e os troca se necessário.  

2. **Insertion Sort**  
   - Insere cada elemento na posição correta dentro da parte já ordenada.  
     - Melhor caso (vetor ordenado): **O(n)**  

3. **qsort (C Standard Library)**  
   - Implementação otimizada de **Quicksort** (pode usar estratégias híbridas).  
   - Muito mais eficiente para grandes valores de **n**.  

---

## Cenários de Teste

O programa gera vetores de tamanho `N` (configurável) em quatro cenários:

- **Aleatório**: valores pseudoaleatórios entre 0 e 1000.  
- **Crescente**: vetor já ordenado em ordem crescente.  
- **Reverso**: vetor em ordem decrescente.  
- **Quase ordenado (10%)**: vetor crescente com ~10% dos elementos embaralhados.  

