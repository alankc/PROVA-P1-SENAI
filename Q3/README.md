# Respostas

## Implemente um código em linguagem C, C++, ou Python, capaz de realizar a decodificação da mensagem e imprimir a mesma em terminal de execução do software.

A pasta `lib` contém o arquivo `Q3.py`. Este arquivo contém a implementação de uma classe para criptografar e descriptografar mensagens.

Para rodar o código, você precisa ter instalado:

```bash
pip install pycryptodome
```

O exemplo de descriptografia da mensagem `a57fd9725fb53c53d5bd0b56185da50f70ab9baea5a43523b76c03e3eb989a20` com a chave `thisisasecretkey` está dentro do próprio arquivo `Q3.py`.

Para rodar:

```bash
python3 lib/Q3.py
```

o retorno será:
```bash
decrypted msg: ==>Sistemas Embarcados<==
```

## Implemente testes unitários para validar o funcionamento do código desenvolvido. 

Para os testes, utilizei o `unittest`, que é um módulo padrão e não precisa de instalação.

Os testes unitários estão implementados no arquivo `teste.py`. Para testá-los, basta executar:

```bash
python3 test.py
```