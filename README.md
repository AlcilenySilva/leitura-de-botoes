
📡 Leitura dos status dos botões da placa BitDogLab
Este projeto tem como objetivo monitorar o status de botões físicos conectados à placa BitDog Lab, enviando atualizações periódicas para um servidor web via Wi-Fi. Além disso, a temperatura interna da placa também é monitorada e enviada junto com os dados do botão.

🔧 Funcionalidades
 Atualizações periódicas (a cada 1 segundo) via protocolo TCP

 Monitoramento de botão físico (identifica cliques como entrada ou saída)

🌡 Leitura da temperatura interna

 Contagem de pessoas presentes, com base nas entradas/saídas

🌐 Interface web em tempo real com:

Última ação registrada (entrada ou saída)

Temperatura atual

Total de pessoas

🧰 Tecnologias Utilizadas
 Placa BitDog Lab programada em C

 Comunicação TCP com pilha de rede leve lwIP

🛠️ Backend com Node.js, usando:

Express para criar o servidor TypeScript 

🖥️  HTML simples com autoatualização

🚀 Como Executar
🖥️ Servidor
Instale as dependências:

bash
Copiar
Editar
npm install
Inicie o servidor:

bash
Copiar
Editar
npm run start
 Placa BitDog Lab
Compile e carregue o firmware com o código C na placa.

Verifique se o IP e a porta do servidor estão corretos no código da placa.

🌍 Acesse no navegador
Vá até http://<IP_DA_MAQUINA>:3000
