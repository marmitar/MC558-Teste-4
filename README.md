# MC558 2021s1 - Teste 4

- [Enunciado](enunciado.pdf).
- ~~Entrega~~.

## Item 1 - *(50 pontos)*

Seja MM o problema da multiplicar duas matrizes quadradas:
uma instância `I[MM] = (A,B,n)` de MM consiste de duas matrizes quadradas `A` e `B` de ordem `n` e a saı́da é a matriz `C = A × B`.

Seja MQ o problema de calcular o quadrado de uma matriz quadrada:
uma instância `I[MQ] = (P,n)` de MQ consiste de uma matriz quadrada `P` de ordem `n` e a saı́da é a matriz `Q = P × P`.

Suponha que MM tenha cota inferior Ω(n^2.5). Mostre que MQ tem cota inferior Ω(n2.5). Descreva claramente as funções τI e τS. **Justifique.**

### Observações

Espero uma resposta nos moldes dos exemplos vistos nos slides. Não me pergunte o quanto ou como a resposta deve ser justificada. Veja os exemplos.

## Item 2 - *(50 pontos)*

Um fabricante de plásticos planeja criar um novo produto a partir de misturas de 4 compostos quı́micos que chamaremos simplesmente de 1, 2, 3 e 4. Estes compostos são feitos de três elementos A, B e C (e outros elementos irrelevantes). A composição e o custo por quilo destes compostos estão indicados na tabela abaixo:

| Composto Quı́mico | 1  | 2  | 3  | 4  |
|:----------------:|:--:|:--:|:--:|:--:|
| Porcentagem de A | 30 | 20 | 40 | 20 |
| Porcentagem de B | 20 | 60 | 30 | 40 |
| Porcentagem de C | 40 | 15 | 25 | 30 |
| Custo por Kg     | 20 | 30 | 20 | 15 |

O novo produto deve ser constituı́do de exatamente 20% do elemento A, pelo menos 30% do elemento B e pelo menos 20% do elemento C. Devido a efeitos colaterais dos compostos 1 e 2, eles não podem exceder 30% e 40% da composição do novo produto, respectivamente. Nesta questão você deve projetar um programa linear para encontrar o modo mais barato de fazer a mistura para um quilo do produto.

- Descreva as variáveis do seu programa linear e obrigatoriamente descreva sucintamente o que cada uma representa. A falta da descrição acarretará em desconto
30 pontos.

- Descreva a função objetivo do seu programa linear e se o problema é de minimização ou maximização.

- **Não use notação matricial para descrever as restrições!** Faça como nos slides: escreva explicitamente os coeficientes e lado direito de cada restrição. O não cumprimento desta regra resultará em um desconto de 30 pontos.


## Instruções:

1. As respostas devem ser digitadas usando qualquer editor/formatador (sugiro LATEX, se você souber usar). As submissões devem ser feitas em formato pdf no Google Classroom; você pode anexar figuras, mas gere um único arquivo. Soluções que não respeitem estas condições receberão **nota ZERO**.

2. Todas as respostas devem ter justificativas (corretude e/ou complexidade), a menos que a questão diga explicitamente que não são necessárias.

3. Você pode usar qualquer resultado ou algoritmo visto em aula. Conforme o caso, enuncie o resultado ou escreva qual é a complexidade do algoritmo, caso seja necessário na análise de complexidade.

4. Em qualquer questão que exija um pseudo-código complicado, explique sua ideia antes de escrevê-lo (no máximo uma página, mas isto provavelmente é muito dependendo da questão). Outra forma é você explicar em alto nı́vel o que faz cada trecho de código.
Sua explicação deve ser boa o suficiente para me convencer que o algoritmo funciona (inclua provas de resultados auxiliares, se necessário). Note que explicar bem não é o mesmo que explicar muito. Soluções que tenham pseudo-códigos complicados, mas sem nenhuma tentativa razoável de explicação não serão consideradas.

5. Os pseudo-códigos devem ter estilo semelhante aos apresentados em aula ou que estão no livro do CLRS. Pseudo-códigos com trechos de linguagem de programação como C ou Python não serão aceitos. Você pode implementar um programa para resolver a questão, se quiser, mas não aceitarei como resposta um copy-and-paste do código sob nenhuma hipótese.

6.  Em um pseudo-código você pode devolver diretamente um conjunto (e.g., escreva "devolva Q"). Você pode usar instruções em português também, e.g., "devolva os vértices da árvore T" ou "ordene a sequência X" ou "execute DFS sobre o grafo G". Há muitas situações em que é razoável usar uma instrução deste tipo. Tenha em mente que uma instrução deste tipo consome uma certa quantidade de tempo que você deve analisar e deve ser razoavelmente óbvio (para mim) que ela pode ser executada no tempo descrito.

7. Em qualquer questão que exija uma descrição de um algoritmo em alto nı́vel (sem pseudo-código), descreva-o de maneira clara e precisa em português. A descrição dos seus passos deve ter detalhes suficicientes para eu poder concluir que o algoritmo tem a complexidade exigida.

8. Se você usar alguma notação que não está nos slides ou no CLRS, você deve explicar precisamente o que representa. Não tenho como saber toda notação usada em outras fontes. É esperado também que ninguém invente uma notação para algo que já tem uma notação definida e que foi bastante usada nas aulas.
