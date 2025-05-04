//import express from 'express';
//const app = express();
//const port = 3000;

//app.use(express.json());

//app.post('/receber', (req, res) => {
  //  console.log('Dados recebidos:', req.body);
    //res.send('Dados recebidos com sucesso!');
//});

//app.listen(port, () => {
  //  console.log(`Servidor escutando na porta ${port}`);
//});//
 import express from 'express';
import cors from 'cors';
import bodyParser from 'body-parser';
const app = express();
const PORT = 3000;

app.use(cors());
app.use(bodyParser.json());

let statusAtual = 'Ninguem entrou ou saiu';
let totalAtual = 0;
let temperaturaAtual = 0;

app.post('/receber', (req, res) => {
    const { status, total, temperatura } = req.body;

    // Atualiza as variáveis globais
    statusAtual = status;
    totalAtual = total;
    temperaturaAtual = temperatura;

    console.log(`Status: ${status}, Total: ${total}, Temp: ${temperatura}°C`);
    res.status(200).send('Dados recebidos com sucesso!');
});

// Página que mostra os dados em tempo real
app.get('/', (req, res) => {
    res.send(`
        <html>
            <head>
                <meta http-equiv="refresh" content="5" />
            </head>
            <body>
                <h1>Contador de pessoas</h1>
                <p>${statusAtual}</p>
                <p>Temperatura: ${temperaturaAtual}°C</p>
                <p>Total de pessoas: ${totalAtual}</p>
            </body>
        </html>
    `);
});

app.listen(PORT, () => {
    console.log(`Servidor rodando em http://192.168.0.77:${PORT}`);
});
