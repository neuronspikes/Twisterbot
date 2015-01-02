//Standard PWM DC control
int MA1 = 7;     //M1  Control
int MA2 = 5;     //M1  Control
int MB1 = 8;    //M2  Control
int MB2 = 6;    //M2  Control

float speedRight=0.0;
float speedLeft=0.0;

float speedStep = 0.1;

void increaseLeft()
{
  speedLeft += speedStep;
  if(speedLeft > 1.0) speedLeft = 1.0;
}

void increaseRight()
{
  speedRight += speedStep;
  if(speedRight > 1.0) speedRight = 1.0;
}

void decreaseLeft()
{
  speedLeft -= speedStep;
  if(speedLeft < -1.0) speedLeft = -1.0;
}

void decreaseRight()
{
  speedRight -= speedStep;
  if(speedRight < -1.0) speedRight = -1.0;
}

void stopAll ()             //STOP
{
 speedRight=0.0;
 speedLeft=0.0;
}


void setMotors()
{
   
  // LEFT
  if(speedLeft >= 0)
  {
    digitalWrite(MA1,LOW);    
    analogWrite(MA2,speedLeft*255);
  }
  else
    {
    digitalWrite(MA1,HIGH);    
    analogWrite(MA2,speedLeft*255);
  }
  
  // RIGHT
  if(speedRight >= 0)
  {
    digitalWrite(MB1,LOW);    
    analogWrite(MB2,speedRight*255);
  }
  else
    {
    digitalWrite(MB1,HIGH);    
    analogWrite(MB2,speedRight*255);
  }
}

void setup(void) 
{ 
  pinMode(MA1, OUTPUT);  
  pinMode(MA2, OUTPUT);  
  pinMode(MB1, OUTPUT);  
  pinMode(MB2, OUTPUT);  
  Serial.begin(9600);      //Set Baud Rate
  Serial.println("Run keyboard control");
} 

void loop(void) 
{
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
        
      case '8':
        increaseLeft();
        increaseRight();
        Serial.println("Forward");  
        break;
      case '2':
        decreaseLeft();
        decreaseRight();
        Serial.println("Backward");   
        break;
      case '4':
        decreaseLeft();
        increaseRight();
        Serial.println("Left");
        break;       
      case '6':
        increaseLeft();
        decreaseRight();
        Serial.println("Right");
        break;
        
        
      case '7':
        increaseLeft();
        Serial.println("More left");  
        break;
      case '1':
        decreaseLeft();
        Serial.println("Less left");   
        break;
        
        
      case '9':
        increaseRight();
        Serial.println("More right");
        break;       
      case '3':
        decreaseRight();
        Serial.println("Less right");
        break;
  
      case '5':
        stopAll ();
        Serial.println("StopAll");
        break;
      }
    }
    else {
      stopAll (); 
      Serial.println("Stoped because error -----------------");
    }
    
    Serial.print("Speed left=");
    Serial.print(speedLeft);
    Serial.print(" right=");
    Serial.println(speedRight);
    setMotors();
  }
}

