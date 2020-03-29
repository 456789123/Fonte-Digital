# Fonte Digital Arduino

Reaproveitando uma fonte velha ATX.
Elevei a tensão de saída de 12 Volts para 14 Volts e fiz um sistema de controle de tensão usando um sinal de PWM que sai do pino B9 do Arduino jogando em um filtro passa baixas.
Após sair do filtro passa baixas, a tensão é jogado em um amplificador operacional 741 que faz o papel do LM317 com um ganho de 2 vezes os sinal de entrada que é levado a base do transistor de potência TIP35.
Para elevar a tensão de 12 Volts para 14 Volts, eu tirei o transformador de saída de 12 Volts e peguei um fio de mesma espessua que o fio do enrolamento de 12 Volts e imendei dando mais voltas no transformado toroidal alcançando assim 14,6 Volts.
<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200319_172957_vHDR_Auto.jpg" width="450" height="600">
O transformador toroidal é o ultimo da direita.
Depois há um jumper que leva os 12 volts para o pino do C.I. de controle da fonte ATX que se ultrapassar os 13,5 Volts, ele para a fonte desligadoa automaticamente.
Eu retirei esse jumper e o substituir por um 7812 que manda para o C.I. de controle.

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200319_175018_vHDR_Auto.jpg" width="700" height="500">

Após a alteração da tensão de 12 Volts está concluida eu fiz um controle digital usando Arduino para monitoramento da tensão variável da fonte e claro, ajuste manual da fonte com botões para o controle de PWM que vai de 0 a 255 para o ajuste da tensão de saída.
Abaixo está o esquemário da fonte.

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/Esquema.png">

Estou usando um relé para a proteção contra curto na base do transistor TIP35 que quando a tensão estiver abaixo dos 0.3 Volts, a fonte acurará curto na saída, assim o usuário irá aperta qualquer um dos botões para ajuste de tensão que a fonte irá armar novamente.
A proteção é via software saido assim do pino B10 do Arduino.
O Amperímetro é o ACS712.


<img src="https://uploads.filipeflop.com/2017/07/001-3.png" width="400" height="300">


Tem que ficar atento a tensão que este sensor está mandando para o pino A3 do Arduino pois, esse valor de tenção de entrada será nosso OFFSETno código e terá um valor de correção para a leitura que eu chamo de FATOR_CORRECAO.
No meu caso estou usando um de 30 amperes que usará o valor de 0.66 para a correção de leitura. Caso vocês usem de amperagens diferentes, devem pesquisar sobre o valor de correção de do seu sensor.
Eu montei o circuito em uma placa ilhada como mostra abaixo.

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200319_172920_vHDR_Auto.jpg" width="400" height="600">


Assim após a montagem a placa ficou com esta aparência.

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200325_151813_vHDR_Auto.jpg" width="850" height="650">


As saídas de tensão são 3,3 Volts, 5 Volts, -12 Volts, e a tensão variável.
# O controle de tenão é somente para a saída de tensão variável as outras saídas são idependentes sendo monitorada apenas a corrente da fonte que está ao negativo de saída de todas as tensões.
A própria fonte ATX tem sua proteção contra curto em suas saídas e a placa de controle terá a proteção de curto somente na saída de tensão vaiável.
O código se encontra no <h2> crtl_fonte </h2>
Abaixo outras imagens que detalhei no decorrer do desenvolvimento do projeto.

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200321_023352_vHDR_Auto.jpg" width="850" height="650">


<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200321_023531_vHDR_Auto.jpg" width="850" height="650">

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200321_194927_vHDR_Auto.jpg" width="850" height="650">

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200323_211239_vHDR_Auto.jpg" width="850" height="650">

<img src="https://github.com/456789123/Fonte-Digital/blob/master/Imagens/P_20200325_143610_vHDR_Auto.jpg" width="850" height="650">


Mais detalhes esão no código.
