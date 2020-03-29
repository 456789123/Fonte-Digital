# Fonte Digital Arduino

Reaproveitando uma fonte velha ATX.
Elevei a tensão de saída de 12 Volts para 14 Volts e fiz um sistema de controle de tensão usando um sinal de PWM que sai do pino B9 do Arduino jogando em um filtro passa baixas.
Após sair do filtro passa baixas, a tensão é jogado em um amplificador operacional 741 que faz o papel do LM317 com um ganho de 2 vezes os sinal de entrada que é levado a base do transistor de potência TIP35.
Para elevar a tensão de 12 Volts para 14 Volts, eu tirei o transformador de saída de 12 Volts e peguei um fio de mesma espessua que o fio do enrolamento de 12 Volts e imendei dando mais voltas no transformado toroidal alcançando assim 14,6 Volts.
<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200319_172957_vHDR_Auto.jpg" width="450" height="600">
O transformador toroidal é o ultimo da direita.
Depois há um jumper que leva os 12 volts para o pino do C.I. de controle da fonte ATX que se ultrapassar os 13,5 Volts, ele para a fonte desligadoa automaticamente.
Eu retirei esse jumper e o substituir por um 7812 que manda para o C.I. de controle.
<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200319_175018_vHDR_Auto.jpg" width="450" height="600">

O Amperímetro é o ACS712.
Está funcionando perfeitamente e ainda coloquei uma proteção contra curto somente na saída de tensão variável usando um relé. As outras saídas já tem esse controle que vem da própria fonte ATX.
Virou a fonte da minha bancada.
