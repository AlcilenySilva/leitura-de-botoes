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

import express, { Request, Response } from 'express';
import bodyParser from 'body-parser';

const app = express();
const PORT = 3000;


app.use(bodyParser.json()); 
app.use(bodyParser.text({ type: '*/*' })); 

let ultimoDado: string = 'Nenhum dado recebido ainda';

app.post('/receber', (req: Request, res: Response) => {
  let body;

  if (typeof req.body === 'string') {
    try {
      body = JSON.parse(req.body);
    } catch (err) {
      console.error("Erro ao fazer parse do JSON cru:", err);
      return res.status(400).send("JSON inválido (texto)");
    }
  } else {
    body = req.body;
  }

  const dado = body?.dado || 'valor não definido';
  console.log("Dado recebido:", dado);
  ultimoDado = dado;

  res.send("JSON recebido com sucesso!");
});

app.get('/', (req: Request, res: Response) => {
  res.send(`<h1>Último dado recebido:</h1><p>${ultimoDado}</p>`);
});

app.listen(PORT, '0.0.0.0', () => {
  console.log(`Servidor rodando em http://0.0.0.0:${PORT}`);
});

