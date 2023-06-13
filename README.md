# HashingTable com Listas duplamente encadeadas.
 
          
 O tratamento de colisão deve ser implementado sempre que ocorrer uma  colisão, ou seja, quando dois ou mais elementos tiverem a mesma chave após o cálculo do índice.
 
 O tratamento de colisão é feito utilizando uma lista encadeada dupla. Se houver colisão, o novo elemento é inserido no início da lista encadeada correspondente ao índice calculado.
 
 A tabela hash gerada em relação à hipótese do hashing uniforme depende dos dados utilizados para inserção. Se os dados estiverem uniformemente distribuídos e não houver muitas colisões, a tabela hash terá um desempenho satisfatório. Caso contrário, pode ser necessário ajustar o tamanho da tabela ou utilizar outras técnicas de tratamento de colisão.
 
O histograma de frequência de cada uma das chaves da tabela hash pode ser obtido percorrendo a lista encadeada correspondente a cada índice da tabela. Para cada chave, é possível contar a quantidade de ocorrências e gerar o histograma. Essa análise pode ajudar a identificar colisões frequentes e auxiliar no ajuste da tabela hash.

Verifiquei a distribuição dos nomes na tabela hash: calculando a frequência de colisões (quando duas ou mais chaves são mapeadas para a mesma posição na tabela) e analisei se essa distribuição é uniforme ou se existem posições com maior concentração de colisões.

Avaliei o desempenho da função de hash: executei o algoritmo com diferentes conjuntos de dados e analisar se a função de hash produz uma distribuição equilibrada em termos de colisões e tempo de execução.



