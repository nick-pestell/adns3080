import processing.serial.*;

final int rate = 9600;
final int frameX = 30;
final int frameY = 30;
final int frameLen = frameX * frameY;
final float sz = 20;


Serial port; // declare serial port
byte[] FrameBuffer = new byte[900];

void setup()
{
  size( 600, 600 ); 

  initSerial();
  background(245);
  frameRate(12);
  noStroke();
  noSmooth();
  //port.write('1');

}

void serialEvent(Serial port){
    FrameBuffer = port.readBytes();
    //println("new frame!");
    //for (int i = 0; i<900; i++){
    //  println(FrameBuffer[i]);
    //}
    updateFrame(FrameBuffer);
  
}

void draw()
{  
}

void updateFrame(byte[] data){
  background(245);
  int k = 0;
  for(int i = 0; i<frameX; i++){
    for(int j = 0; j<frameY; j++){
    fill(data[k]);
    print(data[k]);
    print("      pixel number:");
    println(k);
    rect(sz*i, sz*j, sz, sz);
    k ++;
    }
  }
  print ("new frame!");
  //port.write('1');
}


void initSerial()
{
  String portName = Serial.list()[0];
  port = new Serial(this, portName, rate);
  println("Using " + portName + " as serial device.");
  port.buffer(900);
}