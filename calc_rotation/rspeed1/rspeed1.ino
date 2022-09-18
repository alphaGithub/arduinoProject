//measure speed or rotating object with blade 
#define PIN_READ 0            //pin from which we read analog data from photo register
#define THRESOLD 700
#define NUM_OF_BLADES 3
#define TOTAL_BLADE 30

int count=0;                 //to store number of encouter with blade
int count_enable=true;       //turn off and on counting during blade encounter
int time1=0,time2=0;         //time to measure difference 
void setup() {
  Serial.begin(9600);               //setting baud rate for serial monitor
}

void loop() {
  int read_data = analogRead(PIN_READ);  //reading data from pin 
  //Serial.println(read_data);
  if(count_enable && read_data>=THRESOLD){
    count++;
    count_enable = false;
    if(count==1){
      time1=millis();      
    }
  }else if(!count_enable && read_data<THRESOLD){
    count_enable = true;
  }

  
  if(count >= TOTAL_BLADE){
    time2 = millis();
    float diff_time = (float)time2-time1;
    float num_rotation=0;               
    diff_time = diff_time/TOTAL_BLADE;         //time taken in single count
    diff_time = diff_time*NUM_OF_BLADES;       //time taken in one rotation (in millisecond)
    diff_time = diff_time/1000.0;                //time millisecond to second
    num_rotation = 1.0/diff_time;                //number of rotation in 1 second  
    num_rotation = 60*num_rotation;            //number of rotation in 1 minuter(rpm);
    Serial.print("RPM -> ");
    Serial.println(num_rotation);
    count =0;
  }
}
  