/*
* 1ο ΕΠΑΛ ΓΕΡΑΣ, Μαθητική ομάδα "ΕνεργοΚλαδευτές": https://www.facebook.com/EnergyPruners
* 
* 1. Στοιχεία Κώδικα
*
*    Ονομα εργασίας         : Κατασκευή Μηχανής Εκκόλαψης Αυγών - Κλωσσομηχανή
*    Όνομα Αρχείων          : EggIncubator.info (διαθέσιμο στο https://github.com/1oEpalGeras)
*    Συντονιστές Έργου      : Φωτιάδης Κωνσταντίνος εκπ/κος ΠΕ83, Ανδρόνικος Δημήτριος εκπ/κος ΠΕ84 ΕΠΑΛ Γέρας 
*    Ομάδα Εργασίας         : Μαθητική Ομάδα "Ενεργοκλαδευτές" του ΕΠΑ.Λ. Γέρας
*    Προσομοίωση κατασκευής : https://www.tinkercad.com/things/bAd1tha6ust-klwssomhxanh/
*    Ημ/νια δημιουργίας     : 19/02/2019
*         Έκδοση Κώδικα     : This template is version Revision: 1.5
*         
*         Βιβλιοθήκες       : 1)DHT Sensor lib: https://learn.adafruit.com/dht
*                             2)LCD I2C  lib  : https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/
*                             3)RTC Lib       : https://github.com/adafruit/RTClib
* 
* - Με την κατασκευή αυτή το σχολείο μας συμμετέχει στον 1ο Πανελλήνιο Διαγωνισμό Εκπαιδευτικής Ρομποτικής & Physical Computing Ανοικτών Τεχνολογιών με την κατασκευή μιας 
*   Μηχανής Εκκόλαψης Αυγών (Κλωσσομηχανής) από την μαθητική ομάδα "Ενεργοκλαδυετές". 
* - Το έργο χρηματοδοτήθηκε στο πλαίσιο υλοποίησης της Πράξης «Υποστήριξη και Διαχείριση των Σχεδίων Δράσης του έργου "Μια Νέα Αρχή στα ΕΠΑΛ"» μέσω του Επιχειρησιακού Προγράμματος 
*   «ΑΝΑΠΤΥΞΗ ΑΝΘΡΩΠΙΝΟΥ ΔΥΝΑΜΙΚΟΥ, ΕΚΠΑΙΔΕΥΣΗ ΚΑΙ ΔΙΑ ΒΙΟΥ ΜΑΘΗΣΗ» με τη συγχρηματοδότηση της Ελλάδας και της Ευρωπαϊκής Ένωσης.
* 
* ΠΕΡΙΓΡΑΦΗ ΛΕΙΤΟΥΡΓΙΑΣ
* -------------------------------------------------------------
* Στόχος του αυτοματισμού είναι να ρυθμίζονται οι περιβαλλοντικές συνθήκες του θαλάμου που είναι απαραίτητες για την εκκόλαψη των αυγών. 
*
* Η μηχανή επιτελεί τις παρακάτω βασικές λειτουργίες: 
*
* - Ρυθμίζει την θερμοκρασία του θαλάμου, ώστε αυτή να παραμένει σταθερή γύρω από τους 38°C. 
* - Μετράει την υγρασία του χώρου.
* - Περιστρέφει τα αυγά  ανά τακτά χρονικά διαστήματα (π.χ. κάθε 4 ώρες).
* 
* - Η θέρμανση του χώρου πραγματοποιείται με την χρήση τεσσάρων λαμπτήρων πυράκτωσης. 
* - Για την μέτρηση της θερμοκρασίας και της υγρασίας χρησιμοποιείται o αισθητήρας DHT22. 
* - Όταν η θερμοκρασία στον θάλαμο εκκόλαψης πέσει κάτω από την επιθυμητή τιμή, ο μικροελεγκτής το αντιλαμβάνεται μέσω του αισθητήρα και δίνει εντολή για την έναυση του κυκλώματος των λαμπτήρων, 
*   έως ότου η θερμοκρασία φτάσει και πάλι στα επιθυμητά επίπεδα. 
* - Για την καλύτερη διάχυση της θερμοκρασίας στον θάλαμο εκκόλαψης λειτουργεί ένας ανεμιστήρας. 
* - Η περιστροφή των αυγών πραγματοποιείται με την βοήθεια ενός σερβοκινητήρα όπου ένας αρθρωτός βραχίονας μεταδίδει την κίνηση σε συρτάρι με 35 θήκες αυγών.
* - Κατά τις πρώτες και τις τελευταίες δύο ημέρες εκκόλαψης ο μηχανισμός περιστροφής των αυγών έχει προγραμματιστεί να μην λειτουργεί, αφού σε αυτή την περίοδο τα αυγά δεν πρέπει να περιστρέφονται.
* - Η χρονική λειτουργία του μηχανισμού βασίζεται σε άρθρωμα Ρολογιού Πραγματικού Χρόνου (RTC) PCF8523.
*
* - Η ενημέρωση του χρήστη πραγματοποιείται μέσω μιας σειριακής οθόνης LCD 4x20 που προβάλλει τις τιμές της θερμοκρασίας, της υγρασίας του θαλάμου, της ημερομηνίας έναρξης και λήξης της εκκόλαψης 
*  των αυγών καθώς και των ημερών που απομένουν για την ολοκλήρωση της.
* - Στον θάλαμο εκκόλαψης λειτουργεί και ένας αισθητήρας Ανίχνευσης Κίνησης (PIR) HC-SR501. 
* - Το άνοιγμα και το κλείσιμο της πόρτας ελέγχεται από μια μαγνητική επαφή. Όταν η πόρτα ανοίγει, η λειτουργία θέρμανσης του θαλάμου διακόπτεται. Για την επόπτευση του χώρου ανάβει μια λάμπα χαμηλής ισχύος LED. 
* - Όσο η πόρτα παραμένει ανοικτή, η οθόνη ενημερώνει τον χρήστη για την κατάσταση του θαλάμου με το ανάλογο μήνυμα.
* - Η λειτουργία της εκκόλαψης των αυγών ξεκινάει πάλι όταν η πόρτα κλείσει.
* - Η διαδικασία εκκόλαψης ολοκληρώνεται μετά την πάροδο 21 ημερών.
* 
* 3. Ιστορικό αλλαγών (latest version on top of the list)
*---------------------------------------------------------------------------------------------------
*    version: $Revision: 1.3 $
*    date modified: $Date: 
*    derived by: $Author: kfotiad $
*    Status: $State: Exp $ 
*    Version notes:
*    - $Log: 
*    - Revision 1.0  19-02-2019 14:41:02  kfotiad
*    - *** empty log message ***
*    -
*---------------------------------------------------------------------------------------------------
*/

// Βιβλιοθήκη οθόνης LCD, I2C 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Include RTC library:
#include "RTClib.h"

// Βιβλιοθήκη αισθητήρα θερμοκρασίας και υγρασίας DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
//#include "dht.h"

// Βιβλιοθήκη σερβοκινητήρα
#include <Servo.h> 

/* Uncomment for DEMO code version */
//#define DEMO 1

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

#ifdef DEMO
 #define TempMIN 29.00     // Minimum incubator temperature
 #define TempMAX 30.00     // Maximum incubator temperature
 #define TimeIntervalToTurnOverEggs 1 // Defines the time to turn over the eggs, in minutes or hours
#else
 #define TempMIN 37.00     // Minimum incubator temperature
 #define TempMAX 37.80     // Maximum incubator temperature
 #define TimeIntervalToTurnOverEggs 2 // Defines the time to turn over the eggs, in minutes or hours
#endif

#define IncubationDays 21 // Number of days necessery to incubate the eggs

#define EggsTurnOverDayMIN 2  // Defines the minimum time threshold NOT to turn over the eggs
#define EggsTurnOverDayMAX 19 // Defines the maximum time threshold NOT to turn over the eggs

/*-----( Declare Relay Constants )-----*/
#define RELAY_ON 0
#define RELAY_OFF 1


/* Ορισμός των Pins του arduino που χρησιμοποιούνται στην εφαρμογή */
const int DhtDataPin = 4;       // Pin σύνδεσης του αισθητήρα θερμοκρασίας και υγρασίας DHT22 
const int PilotLEDPin = 5;      // Pin σύνδεσης ρελε που ελέγχει το κύκλωμα (12Vdc) της ενδεικτικής λυχνίας λειτουργίας της κλωσσομηχανής: Power ON / PIR detection indicator
const int WarmingLampsPin = 6;  // Pin σύνδεσης ρελε που ελέγχει το κύκλωμα (230Vac) των λαμπτήρων θέρμανσης του θαλάμου εκκόλαψης των αυγών.
const int StandByLampPin = 7;   // Pin σύνδεσης ρελε που ελέγχει το κύκλωμα (230Vac) του λαμπτήρα LED για την επόπτευση του θαλάμου.
const int VentilatorPin = 8;    // Pin σύνδεσης ρελε που ελέγχει το κύκλωμα (230Vac) του ανεμιστήρα 
const int MagneticContactPin=9; // Pin σύνδεσης της μαγνητικής επαφής 
const int PIRPin=10;            // Pin σύνδεσης του αισθητήρα ανίχνευσης κίνησης (PIR)
const int ServoMotorPin = 11;   // Pin σύνδεσης του σερβοκινητήρα 
const int DhtPowerPin = 12;     // Pin για τον έλεγχο της τροφοδοσίας του αισθητήρα θερμοκρασίας DHT22: HIGH->(+5V), LOW->(0V)

/* Καθολικες μεταβλητές του σειριακού LCD (IC2 LCD Gloobal Parameters) */
#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // set the LCD address to 0x27

// Το σύμβολο "°" των βαθμών κελσίου για την τύπωση του στην LCD Οθόνη (Celcius symbol for LCD printing)
byte customChar[] = {
  0x1E,
  0x12,
  0x12,
  0x1E,
  0x00,
  0x00,
  0x00,
  0x00
};

// Ορισμός του αντικειμένου και των καθολικών παραμέτρων του Ρολογιού Πραγματικού χρόνου  (RTC Object)
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Ορισμός του αντικειμένου και των καθολικών παραμέτρων του ασιθητήρα Θερμοκρασίας και υγρασίας DHT22
DHT_Unified dht(DhtDataPin, DHTTYPE);
uint32_t delayMS;

// Ορισμός του αντικειμένου και των καθολικών παραμέτρων του σερβοκινητήρα (servo Object Creation)
Servo servo_motor; //  αντικείμενο σερβοκινητήρα - έλεγχος μέσω του PWM 

// Ορισμός συναρτήσεων (functions declaration)
void RTCSetup();
void SetupI2cLcdInterfaceForMsg();

void Servo180DegTurn(bool TurnLeftRight, int dTime);
//void ObtainDHTSensorMeasures_1();
void ObtainDHTSensorMeasures();

void DisplayRTCValues();
void DisplayDHTSensorMeasures();

/*Ορισμός καθολικών μεταβλητών (global variables definition)  */
bool WarmUpFlag; // προσδιορίζει την κατάσταση της προθέρμανσης του θαλάμου κατά την αρχική λειτουργία, 0 (false) -> δεν έχει γίνει προθέρμαση, 1 (true) -> έχει γίνει προθέρμαση
bool EnableServoMotorFlag;
bool MagneticContactState; // προσδιορίζει την κατάσταση της πόρτας, 0 (false) -> η πόρτα είναι ανοικτή, 1 (true) -> η πόρτα είναι κλειστή
bool Servo_TurnLeftRight;  // προσδιορίζει την κατεύθυνση περιστροφής του βραχίωνα του σερβοκινητήρα, 0 (false) -> αριστερόστροφη , 1 (true) -> δεξιόστροφη

int LastTimeToTurnOverEggs; // μεταβλητή για την αποθήκευση της τελευταίας κάθε φορά στιγμής που περιστρέφονται τα αυγά 
int IncubationDaysLeft; //μετα βλητή για την αποθήκευση των ημερών που απομένουν για την εκκόλαψη των αυγών
int PreviousDay; // μεταβλητή για την αποθήκευση της <προηγούμενης> ημέρας εκκόλαψης, η οποία ενημερώνεται κάθε φορά που η μέρα αλλάζει

float latestTempC; // μεταβλητή για την αποθήκευση της πιο πρόσφατης μέτρησης θερμοκρασίας

float DHTSensorMeasures[3]={0,0,0}; // DHTSensorMeasures[0] -> Humidity, DHTSensorMeasures[1] -> Temperature in deg. Celsius, DHTSensorMeasures[2] -> Temperature in deg. Fahrenheit

// int RTCDate[4]={0,0,0,0}; // RTCDate[0] -> day of the week, RTCDate[1] -> day, RTCDate[2] -> month, RTCDate[3 -> year
// int RTCTime[3]={0,0,0}; // RTCTime[0] -> hours, RTCTime[1] -> minutes, RTCTime[2] -> seconds

void setup() {

  DateTime now = rtc.now();
 
  digitalWrite(PilotLEDPin,RELAY_ON);
  pinMode(PilotLEDPin, OUTPUT);  // set pin to output mode

  digitalWrite(WarmingLampsPin,RELAY_OFF);
  pinMode(WarmingLampsPin, OUTPUT);  // set pin to output mode
 
  digitalWrite(VentilatorPin,RELAY_OFF);
  pinMode(VentilatorPin, OUTPUT);  // set pin to output mode

  digitalWrite(StandByLampPin,RELAY_OFF);
  pinMode(StandByLampPin, OUTPUT);

  digitalWrite(DhtPowerPin,HIGH); // Ενεργοποίηση της τροφοδοσίας του DHT22 -> ο αισθητήρας βρίσκεται σε λειτουργία
  pinMode(DhtPowerPin, OUTPUT);
  
  //digitalWrite(MagneticContactPin,LOW);
  pinMode(MagneticContactPin, INPUT);  // set pin to input mode
  
  //digitalWrite(PIRPin,LOW);
  pinMode(PIRPin, INPUT);  // set pin to input mode

  
  // Serial.begin(57600); 
  // setup I2C serial LCD interface
  SetupI2cLcdInterfaceForMsg();

  // Αρχικοποίηση του DHT αισθητήρα
  DHTSensor_setup();
  

 // Συνάρτηση για την λήψη των μετρήσεων θερμοκρασίας και υγρασίας του DHT αισθητήρα 
  ObtainDHTSensorMeasures();
 
  // Αρχικοποίηση του ρολογιού πραγματικού χρόνου (RTC)
  RTCSetup();

  // Συνάρτηση για την τύπωση του RTC χρόνου στην LCD οθόνη
  DisplayRTCValues();
  delay(5000);

  // Αρχικοποίηση του μετρητή ημερών που έχουν μείνει για την εκκόλαψη των αυγών
  IncubationDaysLeft = IncubationDays;

#ifdef DEMO
  PreviousDay = now.minute(); // Στην DEMO έκδοση του κώδικα, κάθε ημέρα εκκόλαψης αντιστιχίζεται σε ένα λεπτό πραγματικού χρόνου
#else
  PreviousDay = now.day();
#endif

  // Παραμετροποίηση του σερβοκινητήρα
  servo_motor.attach(ServoMotorPin,500,2500);

  digitalWrite(StandByLampPin,RELAY_ON);
  Servo180DegTurn(0,40);
  //delay(1000);
  //Servo180DegTurn(1,40); 
  
  digitalWrite(StandByLampPin,RELAY_OFF);
  //delay(8000);

  Servo_TurnLeftRight =1;
  
  WarmUpFlag = false;
  EnableServoMotorFlag = false;

  LastTimeToTurnOverEggs = 0;

}

void loop() {

  int CurrentDay;
  int CurrentTime;
  int PilotLedTimeDelay;
  int timeCoefficient;

   DateTime now = rtc.now();
   int TimeLapseToTurnOverEggs;

   // Pilot LED ON -> shows that the Incubator is ready to operate   
   digitalWrite(PilotLEDPin,RELAY_ON);
#ifdef DEMO
   CurrentDay = now.minute();
#else
   CurrentDay = now.day();
#endif
   
   if (PreviousDay != CurrentDay){
    
      IncubationDaysLeft-=1;
      PreviousDay = CurrentDay;
      if (IncubationDaysLeft<=0) IncubationDaysLeft = 0;
    
   } // end if -> calculation of the remaining egg incubation days
    
   if ((IncubationDaysLeft > EggsTurnOverDayMIN) && (IncubationDaysLeft <= EggsTurnOverDayMAX )) EnableServoMotorFlag = true;
   else EnableServoMotorFlag = false;   
    
   MagneticContactState = digitalRead(MagneticContactPin);
   
   if (MagneticContactState){
      digitalWrite(StandByLampPin,RELAY_ON);
      delay(500);
      digitalWrite(WarmingLampsPin,RELAY_OFF);
        
      delay(500);
      digitalWrite(VentilatorPin,RELAY_OFF);
      delay(500);
        
      lcd.setCursor(1, 2); // third row
      lcd.print("  Door Is Open    "); // two decimal places
      delay(3000);
        
      lcd.setCursor(1, 2); // third row
      if (now.hour()<10) {
         lcd.print("0");
         lcd.print(now.hour());
      }
      else lcd.print(now.hour());
        
      lcd.print(':');
      if (now.minute()<10) {
         lcd.print("0");
         lcd.print(now.minute());
      }
      else lcd.print(now.minute());
        
      lcd.print("   ");
        
      lcd.print(now.day(), DEC);
      lcd.print('/');
      lcd.print(now.month(), DEC);
      lcd.print('/');
      lcd.print(now.year(), DEC); 
        
      if (IncubationDaysLeft==0){
         lcd.setCursor(1, 3); // third row
         lcd.print(IncubationDaysLeft);
         lcd.print(" Inc. Days Left "); // two decimal places
         delay(2000);
         lcd.setCursor(1, 3); // first column, third row of LCD 4x20 Display 
         lcd.print("Restart by OFF/ON");
         delay(2000);
         //IncubationDaysLeft=1;
      }
      else{
         lcd.setCursor(1, 3); // third row
         lcd.print(IncubationDaysLeft);
         lcd.print(" Inc. Days Left "); // two decimal places
         delay(2000);
      }
   } // End of if(MagneticContactState) code section where the door is open
   
   else { // Code section where the door is closed
        
      digitalWrite(StandByLampPin,RELAY_OFF);
        
      //ObtainDHTSensorMeasures_1();
      ObtainDHTSensorMeasures();
      DisplayDHTSensorMeasures();
        
      latestTempC = DHTSensorMeasures[1];
        
      if (WarmUpFlag == false){ // Code section to prewarm the incubation chamber 
         if (latestTempC < TempMAX){ // Code section where the temperature of incubation chamber is less than TempMAX
            //Serial.println("I'm Here...1");
            //Serial.println("Temp (C): " + String(latestTempC, 1) + " deg C");
            
            digitalWrite(WarmingLampsPin,RELAY_ON);
            
            delay(500);
            digitalWrite(VentilatorPin,RELAY_ON);
            delay(500);
            
            lcd.setCursor(1, 2); // third row
            lcd.print("  Is Warming Up  "); // two decimal places

           // LastTimeVentilationIsOn = now.minute();
         } // End of code section where the temperature of incubation chamber is less than TempMAX
         
         else { // Code section when the temperature of incubation chamber is equal or more than TempMAX
            //Serial.println("I'm Here...2");
            digitalWrite(WarmingLampsPin,RELAY_OFF);
            
            delay(500);
            digitalWrite(VentilatorPin,RELAY_OFF);
            delay(500);

            lcd.setCursor(1, 2); // third row
            lcd.print("  Is Ready!     "); // two decimal places
            delay(2000);
            
            WarmUpFlag = true;
            
         } // End of code section when the temperature of incubation chamber is equal or more than TempMAX

      } // End of code section to prewarm the incubation chamber 
    
      else { // Code section for adjustment of incubation chamber temperature between TempMIN and TempMAX
        
        if (latestTempC < TempMIN){ // Code section where the temperature of incubation chamber is less than TempMIN
           //LastTimeVentilationIsOn = now.minute();
            
           digitalWrite(WarmingLampsPin,RELAY_ON);
          
           delay(500);
           digitalWrite(VentilatorPin,RELAY_ON);
           delay(500);

           lcd.setCursor(1, 2); // third row
           lcd.print("  Warming is ON     "); // two decimal places

        } // End of code section where the temperature of incubation chamber is less than TempMIN
        
        else if (latestTempC >= TempMAX){ // Code section where the temperature of incubation chamber is equal or more than TempMAX
           digitalWrite(WarmingLampsPin,RELAY_OFF);

           delay(500);
           digitalWrite(VentilatorPin,RELAY_OFF);
           delay(500);

           lcd.setCursor(1, 2); // third row
           lcd.print("  Warming is OFF    "); // two decimal places

        } // End of code section where the temperature of incubation chamber is equal or more than TempMAX
        
      } // End of code section for adjustment of incubation chamber temperature between TempMIN and TempMAX
     
      if (EnableServoMotorFlag){
        
#ifdef DEMO        
        CurrentTime = now.minute();
        timeCoefficient = 60;
#else
        CurrentTime = now.hour();
        timeCoefficient = 24;
#endif              
         TimeLapseToTurnOverEggs = CurrentTime-LastTimeToTurnOverEggs;
         if (TimeLapseToTurnOverEggs < 0) TimeLapseToTurnOverEggs+=timeCoefficient;
         if ( TimeLapseToTurnOverEggs >= TimeIntervalToTurnOverEggs ){
            Servo180DegTurn(Servo_TurnLeftRight,80);
            //Servo180DegTurn(1,80);
            Servo_TurnLeftRight = !Servo_TurnLeftRight;
            LastTimeToTurnOverEggs = CurrentTime;
          }
      }

      if (IncubationDaysLeft < EggsTurnOverDayMIN){

        PilotLedTimeDelay = 2000;
        if (digitalRead(PIRPin)){
           PilotLedTimeDelay = 500;
        }
        //Serial.print(MagneticContactState);
        delay(PilotLedTimeDelay);
        digitalWrite(PilotLEDPin,RELAY_OFF);
        delay(PilotLedTimeDelay);
        digitalWrite(PilotLEDPin,RELAY_ON);
      }
      
   } // End  of else() code section where the door is closed
   
} // End of loop()

void RTCSetup(){
    
    if (! rtc.begin()){
       // Serial.println("Couldn't find RTC");
        while (1);
    }
    if (! rtc.initialized()) {
       // Serial.println("RTC is NOT running!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2019, 3, 01, 21, 12, 0)); // Date and time is set manualy 01/03/2019, 21:12:00  
    }
    //DateTime now = rtc.now();
}// end of RTCSetup funtion

void DisplayRTCValues(){
  
  DateTime now = rtc.now();
 //  Serial.print(now.year(), DEC);
 //  Serial.print('/');
 //  Serial.print(now.month(), DEC);
 //  Serial.print('/');
 //  Serial.print(now.day(), DEC);
 //  Serial.print(" (");
 //  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 //  Serial.print(") ");
 //  Serial.print(now.hour(), DEC);
 //  Serial.print(':');
 //  Serial.print(now.minute(), DEC);
 //  Serial.print(':');
 //  Serial.print(now.second(), DEC);
 //  Serial.println();
  
  lcd.setCursor(0, 2); // third row
  lcd.print("    Start Time:    "); // two decimal places
  
  lcd.setCursor(1, 3); // third row
  
  if (now.hour()<10){
      lcd.print("0");
      lcd.print(now.hour());
  }
  else lcd.print(now.hour());\
  
  lcd.print(':');
  if (now.minute()<10){
      lcd.print("0");
      lcd.print(now.minute());
  }
  else lcd.print(now.minute());
  /* lcd.print(':');
     if (now.second()<10){
        lcd.print("0");
        lcd.print(now.second());
      }
      else lcd.print(now.second()); 
  */    
  
  lcd.print("   ");
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  
  delay(5000);
  
  // calculate a date which is 21 days, 00 hours and 00 seconds into the future
  DateTime future (now + TimeSpan(21,00,00,6));
  
  // Serial.print(" now + 21d + 00s: ");
  // Serial.print(future.day(), DEC);
  // Serial.print('/');
  // Serial.print(future.month(), DEC);
  // Serial.print('/');
  // Serial.print(future.year(), DEC);
  // Serial.print(' ');
  
  // Serial.print(future.hour(), DEC);
  // Serial.print(':');
  // Serial.print(future.minute(), DEC);
  // Serial.print(':');
  // Serial.print(future.second(), DEC);
  // Serial.println();
  
  lcd.setCursor(0, 2); // third row
  lcd.print("     End Time:     "); // two decimal places
  
  lcd.setCursor(1, 3); // third row
  if (future.hour()<10){
      lcd.print("0");
      lcd.print(future.hour());
  }
  else lcd.print(future.hour());
  
  lcd.print(':');
  if (future.minute()<10){
      lcd.print("0");
      lcd.print(future.minute());
  }
  else lcd.print(future.minute());
  
  lcd.print("   ");
  
  lcd.print(future.day(), DEC);
  lcd.print('/');
  lcd.print(future.month(), DEC);
  lcd.print('/');
  lcd.print(future.year(), DEC);  
}// end of DisplayRTCValues funtion

void DHTSensor_setup(){
  // Print temperature sensor details.
  sensor_t sensor;
  sensors_event_t event;
  
  dht.begin();

  sensor.min_delay = 2000;
  //dht.temperature().getSensor(&sensor);
  dht.temperature().getEvent(&event);

  //Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
 
  /*
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  */
  // Print humidity sensor details.

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
 // dht.humidity().getSensor(&sensor);
 /*
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  */
  
  DHTSensorMeasures[0]=event.relative_humidity;
  //DHTSensorMeasures[1]=event.temperature;
  DHTSensorMeasures[1]=1.41*event.temperature-7.58;
  delayMS = sensor.min_delay;
  
}

void ObtainDHTSensorMeasures(){

// Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
   // Serial.println(F("Error reading temp!"));
 
      lcd.setCursor(1, 2); // third row
      lcd.print("Error reading T!");
      DHTSensorMeasures[1]=100; // temperature dummy value stored, in order to ensure that the incubator heating will switched off when the sensor will not operate properly 

      // Reset the sensor power pin, in case the reading of the sensor is stuck
      digitalWrite(DhtPowerPin,LOW); // Απενεργοποίηση της τροφοδοσίας του DHT22 -> η λειτουργία του αισθητήρα διακόπτεται προσωρινά
      delay(1000);
      digitalWrite(DhtPowerPin,HIGH); // Ενεργοποίηση της τροφοδοσίας του DHT22 -> ο αισθητήρας βρίσκεται σε λειτουργία
      delay(2000);
  }
  else {
    //Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    //Serial.println(F("°C"));
    //DHTSensorMeasures[1]=event.temperature; // Test the sensor, compare it with an external temperature meter and if nesessary, perform correction the values   
    DHTSensorMeasures[1]=1.41*event.temperature-7.58; // In our case, we had to do linear correction y = a*x+b of the DHT sensor temperature measures 
    
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Serial.println(F("Error reading humidity!"));
    lcd.setCursor(1, 2); // third row
    lcd.print("Error reading Η!");
    DHTSensorMeasures[0]=100; // humidity dummy value stored when the sensor will not operate properly 
    
    // Reset the sensor power pin, in case the reading of the sensor is stuck
    digitalWrite(DhtPowerPin,LOW); // Απενεργοποίηση της τροφοδοσίας του DHT22 -> η λειτουργία του αισθητήρα διακόπτεται προσωρινά
    delay(1000);
    digitalWrite(DhtPowerPin,HIGH); // Ενεργοποίηση της τροφοδοσίας του DHT22 -> ο αισθητήρας βρίσκεται σε λειτουργία
    delay(2000);
  }
  else {
    //Serial.print(F("Humidity: "));
    //Serial.print(event.relative_humidity);
    //Serial.println(F("%"));
    DHTSensorMeasures[0]=event.relative_humidity;
  }
}

void DisplayDHTSensorMeasures(){
  
  lcd.setCursor(0, 3); // third row
  lcd.print("  H:"); // two decimal places
  lcd.print(DHTSensorMeasures[0],0);
  lcd.print("% ");
  lcd.print(" T:"); // two decimal places
  lcd.print(DHTSensorMeasures[1],1); // second parameter is to set decimal places, e.g. 2->two decimal
  lcd.write((byte) 0); 
  lcd.print("C  ");
}// end of DisplayDHTSensorMeasures funtion

void Servo180DegTurn(bool TurnLeftRight, int dTime){

 int pos = 0; // θέση σερβοκινητήρα
 int CurrentAngle;
 //CurrentAngle = servo_motor.read();
  
   if (TurnLeftRight == true){
     for (pos = 0; pos <= 180; pos+=1){
       // rotate from 0 up to 180 degrees with step 1 degree
       // θέση που ορίζεται από την μεταβλητή 'pos'
       servo_motor.write(pos);
       // Αναμονή 15 ms για την μετάβαση του σερβοκινητήρα
       // στην επθυμητή θέση
       delay(dTime); // Wait for dTime millisecond(s)
     }
   }
   else {
     for (pos = 180; pos >= 0; pos-=1){
       // rotate from 180 up to 0 degrees with step 1 degree
       // θέση που ορίζεται από την μεταβλητή 'pos'
       servo_motor.write(pos);
       // Αναμονή 15 ms για την μετάβαση του σερβοκινητήρα
       // στην επθυμητή θέση
       delay(dTime); // Wait for dTime millisecond(s)
     }
   }
} // end of Servo180DegTurn funtion

void SetupI2cLcdInterfaceForMsg(){

  // Switch on the backlight
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  pinMode ( BACKLIGHT_PIN, OUTPUT );

  lcd.begin(20,4);               // initialize the lcd 
  lcd.createChar((byte) 0, customChar);
  lcd.clear();
  lcd.home ();                   // go home
  //lcd.write((byte) 0);
  lcd.print("     EPAL GERAS ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("   Egg Incubator  ");
 }// end of SetupI2cLcdInterfaceForMsg funtion
