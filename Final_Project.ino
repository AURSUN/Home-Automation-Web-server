
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
const int led = 4;
 const int led1 =5;
 const int led2=6;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 1, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(led, OUTPUT);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) 
        {
          readString += c;          
        }
    if(c=='\n')    
    {
   client.println("<html>");
   client.println("<head>");
   client.println("<title>Home Automation</title>");
   client.println("</head>");  //   style CSS
   client.println("<style>");
     client.println("header{margin-top:-10px;background-color: #ff0000;");
   client.println("padding-top:20px;padding-bottom:20px;box-shadow: 5px 5px 5px gray; color:white;}");
    client.println(".button {");
     client.println("background-color: #4CAF50;");
     client.println("border: none;");
     client.println(" color: white;");
    client.println("padding: 16px 32px;");
    client.println( "text-align: center;");
    client.println("text-decoration: none;");
    client.println("display: inline-block;");
    client.println("font-size: 16px;");
    client.println("margin: 4px 2px;");
    client.println("-webkit-transition-duration: 0.4s;");
    client.println("transition-duration: 0.4s;");
    client.println("cursor: pointer;}");
    client.println(".button3 { background-color: white;") ;
    client.println("border-radius:20%;");
    client.println("color: black; border: 2px solid #ff0000;");
    client.println("margin-left:200px; margin-top:100px;}");
    client.println(".button3:hover { background-color: #f44336;");
    client.println(" color: white;}");
   client.println("</style>");  
    client.println("<body>");
client.println("<header>");    //  Main content and control
client.println("<h2><center>Home Automation System</center><h2>");
client.println("</header>");
client.println("<a href='/l1_on'><button class='button button3'>Light 1 On</button></a>");
client.println("<a href='/l2_on'><button  class='button button3'>Light 2 On</button></a>");
client.println("<a href='/l3_on'><button  class='button button3'>Light 3 On</button></a>");
client.println("<a href='/l1_off'><button class='button button3'>Light 1 Off</button></a>");
client.println("<a href='/l2_off'><button class='button button3'>Light 2 Off</button></a>");
client.println("<a href='/l3_off'><button  class='button button3'>Light 3 Off</button></a>");
   client.println("</body>");
    client.println("</html>");
    client.stop();
           if (readString.indexOf("l1_on") >0){
               digitalWrite(led, HIGH);
           }
          else if (readString.indexOf("l1_off") >0){
               digitalWrite(led, LOW);
           }
           if (readString.indexOf("l2_on") >0){
          digitalWrite(led1,HIGH);
           }
         else  if (readString.indexOf("l2_off") >0){
             digitalWrite(led1,LOW);
           }
            if (readString.indexOf("l3_on") >0){
          digitalWrite(led2,HIGH);
           }
          else if (readString.indexOf("l3_off") >0){
             digitalWrite(led2,LOW);
           }
            //clearing string for next read
            readString="";  
      }
         }
    }
       
    }
}


