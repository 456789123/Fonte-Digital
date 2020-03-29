#include <LiquidCrystal.h>

#define RS  (2)
#define EN  (3)
#define D_0 (4)
#define D_1 (5)
#define D_2 (6)
#define D_3 (7)

#define COLUNAS (16)
#define LINHAS  (2)

#define LINHA_1 (0)
#define LINHA_2 (1)

#define SEC_3 (3000)

#define BOTAO_1 (A0)
#define BOTAO_2 (A1)

#define DELAY_TIMER (1)
#define DELAY_READ  (3)

#define MAXIMO_VALOR (255)
#define MEDIO_VALOR  (255)
#define MINIMO_VALOR (0)

#define CTRL_PWM    (9)
#define VOLTAGE_PIN (A2)
#define AMPER_PIN   (A3)

#define FATOR_CORRECAO (0.66) // Fator de correção do sensor de 30 Amperes
#define OFFSET    (2490.2344) // Valor de tensão que está no pino A3 do Arduino

#define AMOSTRAS (50)

#define RELE  (10)
#define CURTO (0.3)

#define MILVINTEQUATRO (1024.0)
#define MILVINTETRES   (1023)
#define CINCOMIL       (5000)
#define ZERO           (0)
#define UM             (1)
#define TRESTRES       (3.3)
#define DEZ            (10)

/* rs, e, d0, d1, d2, d3*/
LiquidCrystal lcd(RS, EN, D_0, D_1, D_2, D_3);

static void bonce( const int butao );
static float leitura_voltagem( );
static float leitura_amperagem( );
static boolean arma_fonte( );

static void bonce( const int botao ) {
  while( digitalRead( botao ) == LOW ){delay(DELAY_TIMER);}
}

static float leitura_voltagem( ) {

  long   leitura  = 0;
  float media    = 0.0;
  float voltagem = 0.0;

  for( int i = 0; i < AMOSTRAS; i++ ) {
    leitura += analogRead(VOLTAGE_PIN);
    delay(DELAY_READ);
  }

  media = leitura / AMOSTRAS;
  voltagem = ((float) media * TRESTRES) / MILVINTETRES; // Multiplicando po 3.3 Volts para maior precisão na leitura de voltagem
  return voltagem * DEZ;
  
}

/*

Nesta parte deve-se ter muita atenão para não ter leituras erradas
no amperimetro. O OFFSET deve ter o mesmo valor de repouso do amperimetro
que no meu caso está lendo uma tensão de 2,49 Volts e o meu OFFSET está
em 2490.2344
Se este valor no seu circuito estiver com a mínima diferença, não terá uma
boa leitura.
*/

static float leitura_amperagem( ) {
  
  long  leitura   = 0;
  float media     = 0.0;
  float voltagem  = 0.0;
  float amperagem = 0.0;
  float amp = 0.0;

  for( int i = 0; i < AMOSTRAS; i++ ) {
    leitura += analogRead(AMPER_PIN);
    delay(DELAY_READ);
  }

  media = leitura / AMOSTRAS;
  voltagem = ((float) media / MILVINTEQUATRO) * CINCOMIL;
  
  amperagem = (float) ((voltagem - OFFSET) * FATOR_CORRECAO) * (-UM);

  if( amperagem > ZERO ) amp = amperagem;
  else amperagem = amp;

  return amperagem / DEZ;

}

static boolean arma_fonte( ) {

  if( digitalRead(BOTAO_1) == LOW ) {
    bonce(BOTAO_1);
    digitalWrite(RELE, LOW);
    lcd.clear();
    return false;
  } else if( digitalRead(BOTAO_2) == LOW ) {
    bonce(BOTAO_2);
    digitalWrite(RELE, LOW);
    lcd.clear();
    return false;
  } else return true;
}

void setup() {
  lcd.begin(COLUNAS, LINHAS);

  pinMode(BOTAO_1, INPUT);
  pinMode(BOTAO_2, INPUT);

  pinMode(CTRL_PWM, OUTPUT);
  pinMode(RELE, OUTPUT);


  lcd.clear();
  lcd.setCursor(0, LINHA_1);
  lcd.print("FONTE INTELIGENT");
  lcd.setCursor(3, LINHA_2);
  lcd.print("CHRISTIANO");

  delay(SEC_3);

  lcd.clear();
}

void loop() {

  static float current = 0.0;
  static float volts = 0.0;
  static int controle_volts = MEDIO_VALOR;
  static boolean aciona_rele = false;
  
  analogWrite( CTRL_PWM, controle_volts );

  volts = leitura_voltagem( );
  current = leitura_amperagem( );

  lcd.setCursor(0, LINHA_1);
  lcd.print(volts);
  lcd.print(" V ");

  lcd.setCursor(0, LINHA_2);
  lcd.print(current);
  lcd.print(" A ");

  lcd.setCursor(8, LINHA_1);
  lcd.print(volts * current);
  lcd.print(" W   ");

  if( volts < CURTO || aciona_rele ) {
    digitalWrite(RELE, HIGH);

    lcd.clear();
    lcd.setCursor(0, LINHA_1);
    lcd.print("   ESTOU EM     ");
    lcd.setCursor(0, LINHA_2);
    lcd.print("    CURTO       ");

    if( digitalRead(BOTAO_1) == LOW || digitalRead(BOTAO_2) == LOW ) {
      aciona_rele = arma_fonte( );
    } else aciona_rele = true;
    
  } else if( digitalRead(BOTAO_1) == LOW ) {
    bonce(BOTAO_1);
    controle_volts ++;
    if( controle_volts > MAXIMO_VALOR ) controle_volts = MAXIMO_VALOR;

  } else if( digitalRead(BOTAO_2) == LOW ) {
    bonce(BOTAO_2);
    controle_volts --;
    if( controle_volts < MINIMO_VALOR ) controle_volts = MINIMO_VALOR;
  } 

}
