Monitoramento de Entrada com Microcontrolador e Servidor Web
Este projeto tem como objetivo monitorar o status de um botão físico da placa BitDogLab, enviando atualizações em intervalos de 1 segundo para um servidor web via conexão TCP. Como desafio adicional, também foi integrada a leitura de temperatura ambiente, enviada junto com os dados do botão.

Funcionalidades
Envio periódico (a cada 1 segundo) do estado do botão.

Identificação de entrada e saída com base nos cliques.

Leitura de temperatura com sensor digital.

Interface web que exibe em tempo real:

Última ação registrada (entrada ou saída)

Temperatura atual

Total de pessoas

Tecnologias utilizadas
Microcontrolador programado em C, utilizando uma pilha de rede leve (lwIP)

Comunicação com servidor via protocolo TCP, enviando dados em formato JSON

Backend desenvolvido com Node.js e Express

Visualização dos dados em tempo real por meio de uma página web simples

Como executar
Servidor

Instale as dependências com:
npm install

Inicie o servidor com:
node server.js

Dispositivo de envio

Compile e carregue o firmware no microcontrolador.

Verifique se o IP e a porta do servidor estão configurados corretamente no código.

Acesse a visualização no navegador

Visite http://<IP do servidor>:3000 para acompanhar os dados em tempo real.
Créditos 
A configuração básica inicial wifi/servidor foi baseado foi baseado no código de
@alexsousadev disponível em: https://github.com/alexsousadev/wifi-init.git
