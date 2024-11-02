# Respostas


## Crie uma imagem Docker para a utilização dos pacotes ROS2 versão Humble. A imagem deve incluir as dependências necessárias para construir pacotes ROS, suas bibliotecas de comunicação, pacotes de mensagens, e ferramentas de linha de comando. O arquivo Dockerfile deve ser entregue juntamente com instruções claras para construir a imagem Docker e executar containers a partir dela.

A imagem docker pode ser criada a partir dos arquivos [Dokerfile](Dokerfile) e [compose.yaml](compose.yaml)

Obs.: Sistema testado em Linux Ubuntu 22.04

Para buildar a imagem execute (nesta pasta):
```bash
docker compose build
```

Em seguida, para subir o container execute:
```bash
docker compose up <MODE> -d
```

Caso você tiver uma GPU nvidia configurada para o docker,  substitua `<MODE>` por `gpu`. Caso não tiver, substitua por `cpu`.


Você precisará de dois terminais para testar os pacotes, para executar o bash dentro dos containers em dois terminais faça o seguinte comando nos dois terminais fora do container:

```bash
docker compose exec <MODE> bash
```

Após o comando você verá algo do tipo
```bash
isi_user@seu_host:~/ws_ros$
```

Execute o seguinte comando para buildar todos os pacotes:
```bash
colcon build
```

Depois de buildar, não se esqueça se fazer o source nos dois terminais:
```bash
source install/setup.bash
```
Se você não fizer isso, não conseguirá rodar os pacotes e as interfaces customizadas não serão encontradas pelo ROS.


## Pacote "1" deve publicar mensagens a cada 1 (um) segundo com informações sobre a quantidade total de memória, o uso de memória RAM em Gigabyte e o percentual do uso.

Este pacote está implementado na pasta [pkg_1](pkg_1)

Para executar o nó:
```bash
ros2 run pkg_1 RAMInformer
```

você pode escolher qual dado do sistema o nó utilizará para considerar a memória livre usando:
```bash
ros2 run pkg_1 RAMInformer --ros-args -p use_mem_free_as:=<MEM_MODE>
```
Substitua `<MEM_MODE>` por `MemFree` ou `MemAvailable`.

- `MemFree`: Representa a quantidade de memória física livre no sistema, ou seja, que não está sendo usada ativamente para nada.
- `MemAvailable`: Inclui `MemFree` e a memória usada para cache de disco e buffers, que pode ser rapidamente liberada pelo kernel se outros processos precisarem de mais memória.

A opção `MemAvailable` é o padrão que o Kubuntu utiliza em seu widget de memória.

Para ler os dados sendo publicados utilize:
```bash
ros2 topic echo /ram_informer
```
Você receberá prints como este:
```bash
mem_total: 31.08568572998047 # Total em GB
mem_used: 5.3719940185546875 # Total utilizado em GB
percentage_in_use: 17.299999237060547 # Percentual utilizado em %

```

## Pacote "2" deve simular a leitura de um sensor com uma taxa de amostragem de 1 Hz. Os dados do sensor devem passar por um filtro de média móvel considerando os últimos 5 valores adquiridos pelo sensor. Esse pacote deve prover duas interfaces de serviço, a primeira deve retornar os últimos 64 resultados gerados pelo filtro, e a segunda deve zerar os dados gerados pelo filtro.

Este pacote está implementado na pasta [pkg_2](pkg_2)

## Pacote "3" deve encontrar, via requisição de ação, os décimo número primo, gerando respostas intermediárias pela interface de ação e também o resultado final.

Este pacote está implementado na pasta [pkg_3](pkg_3)

