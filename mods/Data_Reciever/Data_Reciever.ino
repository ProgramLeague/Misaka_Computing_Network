unsigned char Re_buf[11],counter=0;
unsigned char sign=0;
float a[3],w[3],angle[3],T;
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  if(sign)
  {  
     sign=0;
     if(Re_buf[0]==0x55)
     {  
        switch(Re_buf [1])
        {
        case 0x51:
                a[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*16;
                a[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*16;
                a[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*16;
                T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                break;
        case 0x52:
                w[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*2000;
                w[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*2000;
                w[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*2000;
                T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                break;
        case 0x53:
                angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
                angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
                angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
                T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                Serial.print("a:");
                Serial.print(a[0]);Serial.print(" ");
                Serial.print(a[1]);Serial.print(" ");
                Serial.print(a[2]);Serial.print(" ");
                Serial.print("w:");
                Serial.print(w[0]);Serial.print(" ");
                Serial.print(w[1]);Serial.print(" ");
                Serial.print(a[2]);Serial.print(" ");
                Serial.print("angle:");
                Serial.print(angle[0]);Serial.print(" ");
                Serial.print(angle[1]);Serial.print(" ");
                Serial.print(angle[2]);Serial.print(" ");
                Serial.print("T:");
                Serial.println(T);
                break;
        } 
    }
  } 
}
 
void serialEvent() {
  while (Serial.available()) {
    Re_buf[counter]=(unsigned char)Serial.read();
    if(counter==0&&Re_buf[0]!=0x55) return;             
    counter++;       
    if(counter==11)
    {    
       counter=0;
       sign=1;
    }
  }
}

