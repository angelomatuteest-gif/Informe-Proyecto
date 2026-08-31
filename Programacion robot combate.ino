bien/******************************************************
 * ROBOT ESP32
 * VERSION 4
 * Control DumboRC + Seguridad + Luces
 ******************************************************/


//---------------- Pines ----------------


// Canales receptor
const byte CH1 = 34;
const byte CH2 = 35;
const byte CH3 = 32;
const byte CH4 = 33;


// Motores
const byte MI_A = 16;
const byte MI_B = 17;

const byte MD_A = 18;
const byte MD_B = 19;


// Luces
const byte LUZ = 21;
const byte BALIZA = 22;


// LEDs estado
const byte LED_ROJO = 25;
const byte LED_VERDE = 26;


//--------------- Parámetros ----------------

const int CENTRO_CH1 = 1510;
const int CENTRO_CH2 = 1519;

const int DEAD = 80;


// Tiempo para parpadeo emergencia
unsigned long tiempoLED = 0;
bool estadoLED = false;


//======================================================

void setup()
{

    Serial.begin(115200);


    pinMode(CH1, INPUT);
    pinMode(CH2, INPUT);
    pinMode(CH3, INPUT);
    pinMode(CH4, INPUT);


    pinMode(MI_A, OUTPUT);
    pinMode(MI_B, OUTPUT);

    pinMode(MD_A, OUTPUT);
    pinMode(MD_B, OUTPUT);


    pinMode(LUZ, OUTPUT);
    pinMode(BALIZA, OUTPUT);

    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);


    apagarTodo();

    Serial.println("Robot iniciado");

}


//======================================================

void loop()
{

    int ch1 = pulseIn(CH1,HIGH,30000);
    int ch2 = pulseIn(CH2,HIGH,30000);
    int ch3 = pulseIn(CH3,HIGH,30000);
    int ch4 = pulseIn(CH4,HIGH,30000);



    Serial.print("CH1:");
    Serial.print(ch1);

    Serial.print(" CH2:");
    Serial.print(ch2);

    Serial.print(" CH3:");
    Serial.print(ch3);

    Serial.print(" CH4:");
    Serial.println(ch4);



    //---------------- Seguridad ----------------

    if(ch1==0 || ch2==0)
    {

        emergencia();

        return;

    }



    //---------------- Transmisor conectado ----------------


    digitalWrite(LED_VERDE,HIGH);



    //---------------- Control CH3 Luz ----------------


    if(ch3 > 1500)
    {
        digitalWrite(LUZ,HIGH);
        digitalWrite(LED_ROJO,HIGH);
    }

    else
    {
        digitalWrite(LUZ,LOW);
        digitalWrite(LED_ROJO,LOW);
    }



    //---------------- Control CH4 Baliza ----------------


    if(ch4 > 1500)
    {
        digitalWrite(BALIZA,HIGH);
    }

    else
    {
        digitalWrite(BALIZA,LOW);
    }





    //---------------- Movimiento ----------------


    if(ch2 < (CENTRO_CH2-DEAD))
    {
        adelante();
    }


    else if(ch2 > (CENTRO_CH2+DEAD))
    {
        atras();
    }


    else if(ch1 > (CENTRO_CH1+DEAD))
    {
        izquierda();
    }


    else if(ch1 < (CENTRO_CH1-DEAD))
    {
        derecha();
    }


    else
    {
        detener();
    }


    delay(20);

}



//======================================================
// SEGURIDAD
//======================================================


void emergencia()
{

    detener();


    digitalWrite(LUZ,LOW);
    digitalWrite(BALIZA,LOW);

    digitalWrite(LED_VERDE,LOW);



    // Parpadeo rojo

    if(millis()-tiempoLED > 300)
    {

        tiempoLED = millis();

        estadoLED=!estadoLED;

        digitalWrite(LED_ROJO,estadoLED);

    }

}



//======================================================
// MOTORES
//======================================================


void adelante()
{

    digitalWrite(MI_A,HIGH);
    digitalWrite(MI_B,HIGH);


    digitalWrite(MD_A,LOW);
    digitalWrite(MD_B,LOW);

}



void atras()
{

    digitalWrite(MI_A,LOW);
    digitalWrite(MI_B,LOW);


    digitalWrite(MD_A,HIGH);
    digitalWrite(MD_B,HIGH);

}



void izquierda()
{

    digitalWrite(MI_A,LOW);
    digitalWrite(MI_B,LOW);


    digitalWrite(MD_A,LOW);
    digitalWrite(MD_B,LOW);

}



void derecha()
{

    digitalWrite(MI_A,HIGH);
    digitalWrite(MI_B,HIGH);


    digitalWrite(MD_A,HIGH);
    digitalWrite(MD_B,HIGH);

}



void detener()
{

    digitalWrite(MI_A,LOW);
    digitalWrite(MI_B,HIGH);


    digitalWrite(MD_A,LOW);
    digitalWrite(MD_B,HIGH);

}



//======================================================
// APAGADO GENERAL
//======================================================

void apagarTodo()
{

    detener();


    digitalWrite(LUZ,LOW);
    digitalWrite(BALIZA,LOW);


    digitalWrite(LED_ROJO,LOW);
    digitalWrite(LED_VERDE,LOW);

}
