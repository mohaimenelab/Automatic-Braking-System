int flag_1 = 0;
int flag_2 = 0;
int flag_3 = 0;
int flag_4 = 0;
int flag_5 = 0;
int flag_6 = 0;
int flag_7 = 0;
int flag_8 = 0;

int oldValue = 0;

void setup()
{
  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);    

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(9, 0);

  Serial.begin(9600);
}

void loop() 
{
  int x = analogRead(A0);
  int y = digitalRead(A1);    // Manual Overwright - 1 
  int z = digitalRead(A2);    // Manual Overwright - 2
  
  Serial.print("Value = ");
  Serial.print(x);  
  Serial.print("   "); 
  Serial.print("oldValue = ");
  Serial.println(oldValue); 

  //------------------------------------------------------------1st Stage-----------------------------------------------------------------------------
   if(x > 50 && x <= 340 && flag_1 == 0 && flag_5 == 0)
   {
    analogWrite(9, 255);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); 
    delay(350);
    flag_1 = 1;
    if(flag_1 == 1)
    {
     analogWrite(9, 0);
     digitalWrite(12, LOW);
     digitalWrite(13, LOW);
     oldValue = x;
     Serial.println(oldValue);
    }     
   }
   else if(x < oldValue && flag_1 == 1)         // 1st Stage release
   {
      analogWrite(9, 255);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH); 
      delay(125);
      flag_5 = 1;
      if(flag_5 == 1)
      {
       analogWrite(9, 0);
       digitalWrite(12, LOW);
       digitalWrite(13, LOW);
       oldValue = x;
       Serial.println(oldValue); 
      }
      //flag_1 = 0;
      //flag_5 = 0; 
    }  
   //----------------------------------------------------------------------------2nd Stage------------------------------------------------------------------ 
   else if(x > 340 && x <= 680 && flag_2 == 0 && flag_6 == 0)
   { 
    analogWrite(9, 255);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); 
    delay(350);
    flag_2 = 1;
    if(flag_2 == 1)
    {
     analogWrite(9, 0);
     digitalWrite(12, LOW);
     digitalWrite(13, LOW);
     oldValue = x;
     Serial.println(oldValue); 
   
    } 
   }
  else if(x < oldValue && flag_2 == 1)          // 2nd Stage release
   {
      analogWrite(9, 255);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH); 
      delay(125);
      flag_6 = 1;
      if(flag_6 == 1)
      {
       analogWrite(9, 0);
       digitalWrite(12, LOW);
       digitalWrite(13, LOW);
       oldValue = x;
       Serial.println(oldValue);   
      }
      //flag_2 = 0;
      //flag_6 = 0; 
    }  
    //------------------------------------------------------------------------------3rd Stage----------------------------------------------------------------------------
   else if(x > 680 && x <= 1023 && flag_3 == 0 && flag_7 == 0)
   {
    analogWrite(9, 255);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); 
    delay(350);
    flag_3 = 1;
    if(flag_3 == 1)
    {
     analogWrite(9, 0);
     digitalWrite(12, LOW);
     digitalWrite(13, LOW);
     oldValue = x;
     Serial.println(oldValue);
  
    } 
   }
   else if(x < oldValue && flag_3 == 1)         // 3rd Stage release
   {
      analogWrite(9, 255);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH); 
      delay(125);
      flag_7 = 1;
      if(flag_7 == 1)
      {
       analogWrite(9, 0);
       digitalWrite(12, LOW);
       digitalWrite(13, LOW);
       oldValue = x;
       Serial.println(oldValue);   
      }
    }
    else if(x < 50)
    {
       flag_1 = 0;
       flag_2 = 0;
       flag_3 = 0;
       flag_4 = 0;
       flag_5 = 0;
       flag_6 = 0;
       flag_7 = 0;
       flag_8 = 0;

       if(y != 0 && z != 1)
       {
         analogWrite(9, 80);
         digitalWrite(12, LOW);
         digitalWrite(13, HIGH); 
       }

       if(y != 1 && z != 0)
       {
         analogWrite(9, 80);
         digitalWrite(13, LOW);
         digitalWrite(12, HIGH); 
       }

       if(y != 1 && z != 1)
       {
         analogWrite(9, 0);
         digitalWrite(13, LOW);
         digitalWrite(12, LOW); 
       }
    }
       
}


