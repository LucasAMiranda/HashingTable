# HashingTable com Listas duplamente encadeadas.
 
          
a) Quando deveria ser implementado tratamento de colisão?

O tratamento de colisão deve ser implementado sempre que dois ou mais elementos tiverem a mesma chave após o cálculo do índice. No código, quando ocorre uma colisão, ou seja, quando uma chave já está ocupada, um novo elemento é inserido no início da lista encadeada correspondente àquela chave.

b) Como poderia ser esta implementação?

A implementação do tratamento de colisão é realizada por meio das listas encadeadas duplas. Caso ocorra uma colisão, um novo elemento é inserido no início da lista encadeada correspondente à chave calculada. Dessa forma, vários elementos podem estar associados à mesma chave, formando uma estrutura de lista para lidar com as colisões.

c) Qual sua avaliação da tabela hash gerada em relação à hipótese do hashing uniforme?

A avaliação da tabela hash gerada em relação à hipótese do hashing uniforme depende da distribuição dos dados utilizados para a inserção. Se os dados estiverem uniformemente distribuídos e não houver muitas colisões, a tabela hash terá um desempenho satisfatório. No entanto, se houver uma concentração de elementos em determinadas chaves devido a colisões frequentes, a tabela pode não apresentar um bom desempenho.

d) Qual sua análise em relação ao histograma de frequência de cada uma das chaves da tabela hash?

O histograma de frequência de cada uma das chaves da tabela hash mostra a distribuição dos nomes em cada chave. Cada barra do histograma representa uma chave, e a altura da barra indica a quantidade de elementos presentes naquela chave. O histograma permite visualizar a distribuição dos nomes nas diferentes chaves e identificar se existem chaves com maior concentração de nomes do que outras. Essa análise é útil para avaliar se a distribuição dos nomes é uniforme ou se há uma distribuição desequilibrada com colisões frequentes em determinadas chaves.

8) Importante questão a ser respondida é: a hipótese do hashing uniforme foi alcançada?

   A hipótese do hashing uniforme é alcançada quando a distribuição dos nomes nas chaves é uniforme, ou seja, não há concentração excessiva de nomes em determinadas chaves. Para avaliar se a hipótese do hashing uniforme foi alcançada, é necessário analisar o histograma de frequência das chaves. Se as barras do histograma estiverem aproximadamente na mesma altura, indica que a distribuição dos nomes é uniforme e a hipótese do hashing uniforme foi alcançada. No entanto, se algumas barras estiverem significativamente mais altas do que outras, indica uma distribuição desigual e a hipótese do hashing uniforme não foi alcançada.

9) A distribuição dos nomes em cada uma das chaves utilizando um histograma e explicar o que o histograma está apresentando
O código já possui a função exibirHistograma() que gera o histograma de frequência das chaves. O histograma é uma representação gráfica da distribuição dos nomes em cada uma das chaves. Cada barra do histograma corresponde a uma chave, e a altura da barra representa a quantidade de elementos presentes naquela chave.



