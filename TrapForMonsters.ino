// -------------------------------------------------
// Trap for Monsters
// Ulrix Creation © 2016
// Version: 1.4.13
// 2016-10-13
// -------------------------------------------------

#define Trig 8
#define Echo 7

unsigned int impulseTime=0; 
unsigned int distance_sm1=0; 
unsigned int distance_sm2=0; 
unsigned int distance_sz=0; // distance of save zone

void soundOfDanger()
{
    tone(9,1000);
    delay(500);
    tone(9,800);
    delay(500);
    tone(9,1000);
    delay(500);
    tone(9,800);
    delay(500);
    noTone( 9);
    delay(500);
}

void soundOfStart()
{
    tone(9,700);
    delay(500);
    tone(9,800);
    delay(500);
    tone(9,900);
    delay(500);
    tone(9,1000);
    delay(500);
    noTone( 9);
    delay(500);
}
 
int readSonicData()
{
    // Код дальномера. Тупая задежка, как принято в Arduino. Никаких таймеров.
    digitalWrite( Trig, HIGH);// Подаем импульс на вход trig дальномера
    delayMicroseconds( 10);   // равный 10 микросекундам 
    digitalWrite( Trig, LOW); // Отключаем 
    impulseTime = pulseIn( Echo, HIGH); // Замеряем длину импульса 
    return impulseTime/58; // Пересчитываем в сантиметры 
}


void setup() 
{
    pinMode( 9, OUTPUT); // пьезо-пищалка инициируем как выход
    pinMode( Trig, OUTPUT); // инициируем как выход 
    pinMode( Echo, INPUT); // инициируем как вход 
    Serial.begin( 9600);
    distance_sm1 = distance_sm1 = 0;
	while( distance_sm1 != distance_sm1)
    {
		distance_sm1 = readSonicData();
		delay( 4000);
		distance_sm2 = readSonicData();
        if( distance_sm1 == distance_sm2 ) distance_sz = distance_sm2;
    }
    soundOfStart();
    delay( 2500);
}

void loop() 
{
    distance_sm1 = readSonicData();
    
    if( ( distance_sm1 < distance_sz - 6) || ( distance_sm1 > distance_sz + 6))
    {
        soundOfDanger();  
        Serial.println( "DANGER : MONSTER DETECTED");
		delay( 1000);
		distance_sz = distance_sm1;
    }
    else
    {
        Serial.println( "INFORMATION : UNDETECTED MOITION");
        delay( 1000);
    }
}
