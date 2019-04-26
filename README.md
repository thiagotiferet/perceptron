# perceptron
Rede perceptron para reconhecimento de caracteres

Características da RNA:

  Entradas: 63 (matriz 9x7);
  
  Saídas: 7 (letras: A, B, C, D, E, J, K);
  
  Tipo de Treinamento: Perceptron;
  
  Função de transferência: Bipolar.
  
Observações:  
  As letras a serem reconhecidas são descritas por uma matriz de entrada no formato: 9 linhas x 7 colunas.
  A saída do reconhecedor de caracteres classificará o vetor de entrada em uma das sete letras.
  Representação bipolar para a entrada e a saída.
      "." = representa pixels OFF (-1)
      "#" = representa pixels ON (1).
  Os padrões de treinamento e teste são submetidos através de um arquivo de dados seguindo o modelo das imagagens 1 e 2
  Na imagem_2 os símbolos: “O” e “@” representam o ruído introduzido na informação.
    “O” = representa os pixels que eram ON e viraram OFF e
    “@” = representa os pixel que eram OFF e viraram ON. 
