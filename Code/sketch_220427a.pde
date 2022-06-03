
import processing.serial.*;
Serial myPort;
String val;  //datos recibidos por el puerto serial

int s = 40;
int m = 1;

void setup(){
  
   size(600,300);
   background(0);
   noStroke();
   
   String[] sPorts = Serial.list();
   printArray(sPorts); 
   final int portIndex = 32; //modificar (4 antiguamente)
   myPort = new Serial(this, sPorts[portIndex], 9600);
   myPort.clear();
   
}

void draw(){
      background(0);
      textAlign(CENTER);
      textSize(90);
      delay(1000);
      
      
      //si hay mas de un minuto (mayor o igual)
      if(m>=1){
        //primera condicion
        if(s>0 && s<=9){
          text(m+":"+"0"+s,width/2,height/2);
           fill(255);
          myPort.write(s);
          println(s);
          s = s-1;
        }//segunda condicion
        else if(s>=10){
          /*
          Sección de calibrando: se pone el mensaje tanto tiempo como equivalga al calibrado
                                 del sensor PIR en el código arduino.
          */
          if(m==1 && s>25){
            fill(255,182,193);
             text("Loading...",width/2,height/2);
             fill(255,182,193);
             myPort.write(s);
             println(s);
             s = s-1;
          }else{
            text(m+":"+s,width/2,height/2);
            fill(255);
            //myPort.write('0');
            myPort.write(s);
            println(s);
            s = s-1;
          }
        }
        else{
           text(m+":"+"0"+s,width/2,height/2);
            fill(255);
          s=59;
          m-=1;
        }
      }
      
      //caso de que minuto =0
      else if (m==0){
        if(s>0 && s<=9){
          text(m+":"+"0"+s,width/2,height/2);
           fill(255);
          //myPort.write('0');
          myPort.write(s);
          println(s);
          s = s-1;
        }
        else if(s>=10){
          text(m+":"+s,width/2,height/2);
           fill(255);
          //myPort.write('0');
          myPort.write(s);
          println(s);
          s = s-1;
        }
        else{
          text(m+":"+"0"+"0",width/2,height/2);
           fill(255);
          myPort.write(0);
          println(s);
          exit();
        }
      }
      
      
     
        
}
