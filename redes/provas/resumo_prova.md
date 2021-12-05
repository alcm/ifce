### aula-01

- ex campos de uma request: método (GET, POST, etc), versão do protocolo (http), recurso requisitado e user-agent (que pode ser o browser utilizado)
- ex campos de uma response: status code, versão do protocolo (http) e timestamp

**arquiteturas de rede**

- cliente e servidor;
- p2p: não há servidor central, comumente usado para compartilhamento de arquivos, cada membro da rede atua como cliente e servidor
- sistema hibrido;

**protocolos**

- orientados a conexão: confiável, confirmação e retransmissão, usado amplamente
- não orientado a conexão: não há retransmissão, maior performance, menos confiável

**atrasos**

- atraso de fila;
- atraso de propagação;
- atraso de processamento;
- atraso de transmissão;
- atraso nodal total: soma dos anteriores;

**perda de pacotes**

- ocasionado quando a fila de pacotes do roteador (buffer) está cheia
- buffer de entrada é limitado

### aula-02

**camadas**

- reduzir o nível de complexidade;
- cada camada possue uma finalidade e um set de protocolos;
- o consjunto de camadas define a pilha TCP/IP;

![modelo_tcp.png](path "modelo_tcp.png")

**serviços**

- utilizam os protocolos na sua implementação;
- listen, connect, receive, send e disconnect;

**endereçamento**

- endereço IP (identifica o host origem/destino) e porta (identifica as aplicações atuantes na comunicação);

**requisitos de aplicações**

- perda de dados, largura de banda e sensibilidade ao atraso;

### aula-03

- http: protocolo para transferência de hypertexto
- cliente e servidor
- protocolo da camada de aplicação
- url: composto por protocolo, documento e caminho do recurso
- http 1.0 e http 1.1 (adiciona headers para melhorar a compressão e usa conexão persistente por padrão)

**conexões**

- não-persistidas: uma nova conexão a cada recurso requisitado (menos eficiente)
- persistidas: o cliente e servidor mantém a conexão aberta por um período de tempo

**métodos**

- query-string: para passar parâmetros na request GET (campo1=valor1&campo2=valor2), não indicado para dados sensíveis
- no post os dados são contidos no corpo da mensagem
- requisições post n são colocadas no histórico e no cache
- método head é um get sem body
- método trace é para testes ou diagnóstico

**cookies**

- para guardar dados do usuário, já q os servidores são stateless
- mantido na máquina do usuário e gerenciado pelo navegador
- guardado do lado do cliente

### aula-04

- https: http + ssl (camada adicional de segurança)
- mensagens http trafegam pela rede em plain text
- aplicações: bancos, comercio eletronico
- camada SSL se situa entre camada de transporte e de aplicação
- ssl provê criptografia e autenticação

**criptografia**

- algoritmo de chave publica garante confidencialidade e autenticidade
- para garantir autenticidade: uso de assinatura digital (hash da mensagem e código do remetente criptografados com chave publica)
- certificados: autenticidade, integreidade e confidencialidade
- informações do certificado: titular, autoridade certificadora, validade e método de criptografia da assinatura

> confidencialidade: só os elementos envolvidos na conexão podem visualizar o conteúdo da mensagem,
> integridade: a corretude da mensagem e autenticidade: garantia do remetente

**ssl**

- versões 2.0 e 3.0

![sessao_ssl.png](path "opt title")

### aula-05

**http 1.x**

- precisa de várias conexões simultaneas para mitigar latência
- sem compressão de cabeçalho

**http 2**

- diminuição da latência em relação a versão 1
- uso de compressão
- formato binário nas mensagens
- http 1.x
