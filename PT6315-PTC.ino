/****************************************************/
/* This is only one example of code structure       */
/* OFFCOURSE this code can be optimized, but        */
/* the idea is let it so simple to be easy catch    */
/* where we can do changes and look to the results  */
/****************************************************/

/* Port controls  (Platform dependent) */
//#define CS_LOW()  PORTB &= ~1     /* CS=low */
//#define CS_HIGH() PORTB |= 1      /* CS=high */

//#define LCD_Port PORTB
#define VFD_in 5// If 0 write LCD, if 1 read of LCD
#define VFD_clk 6 // if 0 is a command, if 1 is a data0
#define VFD_stb 7 // Must be pulsed to LCD fetch data of bus

#define numberGrids 0b00000111// On the PT6315 means 11 Grids and 17 segments
bool flag = false;
//......................ggfbhija.....pdmlkec  // p is the dot!
uint8_t letter[80] = {0b11110001, 0b00000011, 0b00000000, //A //00
                      0b01010101, 0b00101001, 0b00000000, //B //03
                      0b00100001, 0b00100010, 0b00000000, //C //06
                      0b00010101, 0b00101001, 0b00000000, //D //09
                      0b11100001, 0b00100010, 0b00000000, //E //0C
                      0b11100001, 0b00000010, 0b00000000, //F //0F
                      0b01100001, 0b00100011, 0b00000000, //G //12
                      0b11110000, 0b00000011, 0b00000000, //H //15
                      0b00000101, 0b00101000, 0b00000000, //I //18
                      0b00010000, 0b00100011, 0b00000000, //J //1B
                      0b10100010, 0b00000110, 0b00000000, //K //1E
                      0b00100000, 0b00100010, 0b00000000, //L //21
                      0b00111010, 0b00000011, 0b00000000, //M //24
                      0b00111000, 0b00000111, 0b00000000, //N //27
                      0b00110001, 0b00100011, 0b00000000, //O //2A
                      0b11110001, 0b00000010, 0b00000000, //P //2D
                      0b00110001, 0b00100111, 0b00000000, //Q //30
                      0b11110001, 0b00000110, 0b00000000, //R //33
                      0b11100001, 0b00100001, 0b00000000, //S //36
                      0b00000101, 0b00001000, 0b00000000, //T //39
                      0b00110000, 0b00100011, 0b00000000, //U //3C
                      0b00100010, 0b00010010, 0b00000000, //V //3F
                      0b00001010, 0b00010100, 0b00000000, //X //42
                      0b00000011, 0b00110000, 0b00000000, //Z //45
                      0b00110000, 0b00010111, 0b00000000, //W //48
                      0b00000000, 0b00000000, 0b00000000};//  //4B

uint8_t number[33] = {0b00110001, 0b00100011, 0b00000000, //0
                      0b00010000, 0b00000001, 0b00000000, //1
                      0b11010001, 0b00100010, 0b00000000, //2
                      0b11010001, 0b00100001, 0b00000000, //3
                      0b11110000, 0b00000001, 0b00000000, //4
                      0b11100001, 0b00100001, 0b00000000, //5
                      0b11100001, 0b00100011, 0b00000000, //6
                      0b00010001, 0b00000001, 0b00000000, //7
                      0b11110001, 0b00100011, 0b00000000, //8
                      0b11110001, 0b00100001, 0b00000000, //9
                      0b00000000, 0b00000000, 0b00000000};
//
void msgHiFolks(void){
      PIND &= ~(1 << VFD_stb);
       delay(2);
      sendCmd(0b01000000); // cmd 2  Write to display, start fix and display ON
      PIND = (1 << VFD_stb);
       delay(2);
      send_data(0b11000000); //cmd 3 Memory 0x00 to 0x1D, Each grid use 3 bytes here define the 1º, 2º, 3º until max address
  //Grid0 "empty"
      send_data(letter[0x4B]); // 
      send_data(letter[0x4B +1]); // 
      send_data(letter[0x4B +2]); // 
  //Grid1 "empty"
      send_data(letter[0x4B]); // 
      send_data(letter[0x4B +1]); // 
      send_data(letter[0x4B +2]); // 
  //Grid2 "empty"
      send_data(letter[0x15]); // 
      send_data(letter[0x15 +1]); // 
      send_data(letter[0x15 +2]); // 
  //Grid3  "F" 
      send_data(letter[0x18]); // 
      send_data(letter[0x18 +1]); // 
      send_data(letter[0x18 +2]); // 
  //Grid4 "u"
      send_data(letter[0x4B]); // 
      send_data(letter[0x4B +1]); // 
      send_data(letter[0x4B +2]); // 
  //Grid5 "n"
      send_data(letter[0x0F]); // 
      send_data(letter[0x0F +1]); // 
      send_data(letter[0x0F +2]); // 
  //Grid6 "n"
      send_data(letter[0x2A]); // 
      send_data(letter[0x2A +1]); // 
      send_data(letter[0x2A +2]); // 
  //Grid7 "n"
      send_data(letter[0x21]); // 
      send_data(letter[0x21 +1]); // 
      send_data(letter[0x21 +2]); // 
  //Grid8
      send_data(letter[0x1E]); // 
      send_data(letter[0x1E +1]); // I need apply here a space, other way the compiler give me a error!!!
      send_data(letter[0x1E +2]); // I need apply here a space, other way the compiler give me a error!!!
  //Grid9   
      send_data(letter[0x36]); // 
      send_data(letter[0x36 +1]); // 
      send_data(letter[0x36 +2]); // 
  //Grid7 "empty"
      send_data(letter[0x4B]); // 
      send_data(letter[0x4B +1]); // 
      send_data(letter[0x4B +2]); // 
    
      PIND = (1 << VFD_stb);
       delay(2);
  //
      PIND &= ~(1 << VFD_stb);
       delay(2);
      // ATT: this is at PT6515-S (DIP 28pins)
      sendCmd((0b10001000) | 7); //cmd 4 Dimming adjust, 7 is maximum of bright
      PIND = (1 << VFD_stb);
       delay(2);
      delay(600);
      clearCmd();
      delay(600);
}
void wrData(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t grid){
   PIND = (1 << VFD_stb);
    delay(2);
    sendCmd(0b01000000); // cmd 2  Write to display, start fix and display ON
    PIND &= ~(1 << VFD_stb);
    delay(2);
    send_data((0b11000000) | grid); //cmd 3 Memory 0x00 to 0x1D, Each grid use 3 bytes here define the 1º, 2º, 3º until max address
        
    send_data(ch1); // data
    send_data(ch2); // data
    send_data(ch3); // data
        
    PIND = (1 << VFD_stb);
    delay(2);

  //sendCmd(0b00000101); // cmd1 Here I define the 7 grids and 9 Segments ATT: this is at PT6515-S (DIP 28pins)
    sendCmd((0b10001000) | 7); //cmd 4
     delay(2);
}
void send_data(byte a) {
  unsigned char data = 0x00; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  data = a; // This pass the byte received to local variable!
  //This funtion don't send the strobe signal, to be used in burst data send
  PIND = (0 << VFD_clk);
  for (mask = 0b00000001; mask > 0; mask <<= 1) { //iterate through bit mask
    if (data & mask) { // if bitwise AND resolves to true
      PORTD = (1 << VFD_in);
    }
    else { //if bitwise and resolves to false
      PORTD = (0 << VFD_in); // send 0
    }
     delay(2); //delay
    PIND = (1 << VFD_clk);
     delay(2); //delay
    PIND &= ~(0 << VFD_clk);
     delay(2); //delay
  }
}
void sendCmd(uint8_t a) {
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask

  data = a;
  PIND &= ~(1 << VFD_stb);
   delay(2);
  for (mask = 0b00000001; mask > 0; mask <<= 1) { //iterate through bit mask
    PIND = (0 << VFD_clk);
    if (data & mask) { // if bitwise AND resolves to true
      PORTD = (1 << VFD_in);
    }
    else { //if bitwise and resolves to false
      PORTD = (0 << VFD_in); // send 0
    }
     delay(2);
    PIND = (1 << VFD_clk);
     delay(2);
    PIND &= ~(0 << VFD_clk);
     delay(2);
  }
  PIND = (1 << VFD_stb);
   delay(2);
}
void pt6315_init(void) {
  delay(200); //power_up delay
  // Configure VFD display (grids)
  sendCmd(numberGrids);//  (0b01000000)    cmd2 7 grids and 9 segments.
  delay(2); // 4/16 4 grids & 16 segments
  // Write to memory display, increment address, normal operation
  sendCmd(0b01000000);// cmd2 write to display, incremente address, Mode normal
  delay(2);
  // Address 00H - 15H ( total of 11*2Bytes=176 Bits)
  sendCmd(0b11000000);//(BIN(01100110)); //(BIN(01100110)));
  delay(2);
  // set DIMM/PWM to value
  sendCmd((0b10001000) | 7);//0 min - 7 max  )(0b01010000)
  delay(2);
}
void clearCmd(void) {
  /*
    Here I clean all registers
    Could be done only on the number of grid
    to be more fast. The 12 * 3 bytes = 36 registers
  */
  sendCmd(0b01000000); // cmd 2
  PIND &= ~(1 << VFD_stb);
   delay(2);
  send_data(0b11000000); //cmd 3

  for (unsigned int i = 0; i < 29; i++) {  //0x1D is 29
    send_data(0b00000000); // data
  }
  PIND = (1 << VFD_stb);
   delay(2);
}
void setup() {
  // put your setup code here, to run once:
  pinMode( VFD_stb, OUTPUT);// Must be pulsed to LCD fetch data of bus
  pinMode( VFD_in, OUTPUT);//  If 0 write LCD, if 1 read of LCD
  pinMode( VFD_clk, OUTPUT);// if 0 is a command, if 1 is a data0
  pinMode( 13, OUTPUT); //Pin of pinMode(LED_BUILTIN, OUTPUT);
  pinMode( 3, OUTPUT);
  Serial.begin(115200);
   cli();
  //sei();
}
void allOn(){
  uint8_t g = 0x00;
  uint8_t i = 0x00;
    for ( g = 0x00; g < 0x21; g=g+3){
            wrData(0b11111111, 0b11111111, 0b11111111, g); //Here I make all segments of a Grid On.
            //wrData(0b00000000, 0b00000000, 0b00000000, 0x03); //Here I make all segments of a Grid On.    
    }
}
void allOff(){
   uint8_t g = 0x00;
   uint8_t i = 0x00;
    for ( g = 0x00; g < 33; g=g+3){
            wrData(0b00000000, 0b00000000, 0b00000000, g); //Here I make all segments of a Grid Off.
    }
}
void allOnBurst(void) {
  /*
    Here I clean all registers
    Could be done only on the number of grid
    to be more fast. The 12 * 3 bytes = 36 registers
  */
  sendCmd(0b01000000); // cmd 2
  PIND &= ~(1 << VFD_stb);
 delayMicroseconds(5);
  send_data(0b11000000); //cmd 3

  for (unsigned int i = 0x00; i < 0x21; i++) {  //0x21 I address of last group of 3 bytes on table map memory digit.
    send_data(0b11111111); // data
  }

  PIND = (1 << VFD_stb);
  delayMicroseconds(5);
}
void allOffBurst(void) {
  /*
    Here I clean all registers
    Could be done only on the number of grid
    to be more fast. The 12 * 3 bytes = 36 registers
  */
  sendCmd(0b01000000); // cmd 2
  PIND &= ~(1 << VFD_stb);
  delayMicroseconds(5);
  send_data(0b11000000); //cmd 3

  for (unsigned int i = 0x00; i < 0x21; i++) {  //0x21 I address of last group of 3 bytes on table map memory digit.
    send_data(0b00000000); // data
  }

  PIND = (1 << VFD_stb);
  delayMicroseconds(5);
}
void showLetter(){
  uint8_t g = 0x00;
  uint8_t i = 0x00;
  for ( g = 0x06; g < 33; g=g+3){
          for( i = 0x00; i < 78; i=i+3){
            wrData(letter[i], letter[i+1], letter[i+2], g);
            delayMicroseconds(5);
            wrData(0x00, 0x00, 0x00, g);
            delayMicroseconds(5);
          }
      }
}
void showNumber(){
  uint8_t g = 0x00;
  uint8_t i = 0x00;
  for ( g = 0x06; g < 33; g=g+3){
          for( i = 0x00; i < 30; i=i+3){
            wrData(number[i], number[i+1], number[i+2], g);
            delayMicroseconds(5);
            wrData(0x00, 0x00, 0x00, g);
            delayMicroseconds(5);
          }
      }
}
void measureCurrentGrid2(){
  digitalWrite(3, HIGH);
  while(1){
            if (flag == true){
              digitalWrite(3, HIGH);
              flag=false;
              delay(2000);
            }
            else{
              digitalWrite(3, LOW);
              flag=true;
              delay(2000);
            }
        allOn();
      }
}
void loop() {
  delayMicroseconds(200);
  pt6315_init();
  allOff();
  msgHiFolks();
  delay(1200);
      for (uint8_t s = 0x00; s < 1; s++){
        allOn();
        delay(5);
        allOff();
        delay(5);
      }
          for (uint8_t s = 0x00; s < 1; s++){
            allOnBurst();
            delay(5);
            allOffBurst();
            delay(5);
          }
              while(1){
                showNumber(); 
                msgHiFolks();
                delay(1200);
                showLetter();   
              }
}
