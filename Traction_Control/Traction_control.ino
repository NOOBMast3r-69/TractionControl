

// code initialisation and settings
#define NUMBER_OF_SLITS 10 // change it to actual number of slits in setup
#define FRONT_SENS_PIN  PB3  //DIN1
#define REAR_SENS_PIN   PB4  //DIN2
#define RPM_UPDATE_FREQUENCY 10 //Hz 
#define TRACTION_DIFF_THRESHOLD 2 




#if !defined(STM32_CORE_VERSION) || (STM32_CORE_VERSION  < 0x01090000)
#error "Due to API change, this sketch is compatible with STM32_CORE_VERSION  >= 0x01090000"
#endif

volatile unsigned int slit_counter_front = 0;
volatile unsigned int slit_counter_rear  = 0;
volatile unsigned int front_RPM = 0;
volatile unsigned int Rear_RPM = 0;

unsigned long debug_millis=0;
bool traction=true;


void front_detect_ISR(){
  slit_counter_front++;
}
void rear_detect_ISR(){
  slit_counter_rear++;
}
void Timer_Callback(void)
{ 
  front_RPM = (RPM_UPDATE_FREQUENCY*slit_counter_front*60)/NUMBER_OF_SLITS;
  Rear_RPM = (RPM_UPDATE_FREQUENCY*slit_counter_rear*60)/NUMBER_OF_SLITS;
  slit_counter_rear=0;
  slit_counter_front=0;
}


void setup()
{
#if defined(TIM1)
  TIM_TypeDef *Instance = TIM1;
#else
  TIM_TypeDef *Instance = TIM2;
#endif

  // Instantiate HardwareTimer object. Thanks to 'new' instanciation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);
  Serial.begin(9600);
  // configure pin in output mode
  pinMode(FRONT_SENS_PIN, INPUT);
  pinMode(REAR_SENS_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FRONT_SENS_PIN),front_detect_ISR,RISING);
  attachInterrupt(digitalPinToInterrupt(REAR_SENS_PIN),rear_detect_ISR,RISING);
  
  MyTim->setOverflow(RPM_UPDATE_FREQUENCY, HERTZ_FORMAT); // 
  MyTim->attachInterrupt(Timer_Callback);
  MyTim->resume();
}


void loop()
{
  debug();
  check_Traction();

}

void debug(){
  if(millis()-debug_millis>1500){
  Serial.println("Front Wheel RPM = "+String(front_RPM)+" , Rear Wheel RPM = "+String(Rear_RPM));
  debug_millis=millis();
  }
  if(!traction){
    Serial.println("Just losty traction RPM Difference>2, Reduce vch speed");
  }
  
}
