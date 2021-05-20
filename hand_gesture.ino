
const int inputPin1=12;
const int outputPin1=9;
const int inputPin2=5;
const int outputPin2=7;

//distance
long time_dur;                               
int dis1,dis2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;

void distance_cal(void);

void distance_cal(void)                   
{ 
  digitalWrite(inputPin1,LOW);
  delayMicroseconds(2);
  digitalWrite(inputPin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(inputPin1,LOW);

  time_dur=pulseIn(outputPin1,HIGH,5000);
  r=3.4*time_dur/2;
  dis1=r/100.00;
  
  digitalWrite(inputPin2,LOW);
  delayMicroseconds(2);
  digitalWrite(inputPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(inputPin2,LOW);

  time_dur=pulseIn(outputPin2,HIGH,5000);
  r=3.4*time_dur/2;     
  dis2=r/100.00;
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(inputPin1,OUTPUT);
  pinMode(outputPin1,INPUT);
  pinMode(inputPin2,OUTPUT);
  pinMode(outputPin2,INPUT);
  delay(1000);
    
}

void loop()
{
  distance_cal();
  
  if(dis2<=30 && dis2>=10)
  { 
    temp=millis();
    while(millis()<=(temp+300))
    distance_cal();
    if(dis2<=30 && dis2>=10)
    {
     temp=dis2;  
     while(dis2<=30 || dis2==0)
     {
       distance_cal();
       if((temp+6)<dis2)
       {
       Serial.println("down");
       }
       else if((temp-6)>dis2)
       {
        Serial.println("up");
       }
     }
    }
    else
    {
      Serial.println("next");
    }
  }

  else if(dis1<=30 && dis1>=10)
  { 
  
    temp=millis();                           
  
    while(millis()<=(temp+300))             
    {
       distance_cal();
       if(dis2<=30 && dis2>=10)
       {
         Serial.println("change");
         l=1;
         break;
       }
    }
    
    if(l==0)
    {
    Serial.println("previous");
    while(dis1<=30 && dis1>=10)
    distance_cal();                      
    }
    l=0;
   }
   
}
