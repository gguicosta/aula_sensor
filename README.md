# aula_sensor

Esse é um projeto simples, desenvolvido com o objetivo de ser aplicado em uma sala de aula para ensino interdiscilpinar
de física e programação de arduíno (placa microcontroladora).

O vídeo que explica a montagem do projeto, desenvolvimento do código de forma resumida: https://youtu.be/ogk3MB9ewrg

O higrômetro funciona com uma sonda ligada a um regulador de tensão, essa sonda funciona como um resistor, que ao 
transferir descarga elétrica para o vaso de planta mede a resistividade da terra, uma vez que a mesma é alterada pela 
presença da umidade já que a água é um bom condutor de eletricidade. O módulo do sensor já faz as transformações de
forma que a placa microcontroladora recebe o sinal de forma analógica (0 a 1023) ou digital (0 ou 1), este segundo 
precisa de uma informação que será usada como acionadora. A informação é calibrada com a saída analógica e apartir do
valor determinado como "molhado", retorna pela saída digital "molhado" ou "seco".

A placa microcontroladora lê esse valor, interpretando de forma que transforme em uma porcentagem de umidade no vaso
e passando essa informação ao sistema. Por sua vez, o sistema conta com uma página responsíva que pode ser acessada 
através da rede wi-fi na qual a placa estiver conectada, permitindo que o usuário veja se precisa ou não molhar suas plantas.
