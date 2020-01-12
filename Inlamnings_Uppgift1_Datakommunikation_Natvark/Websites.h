#include <RH_ASK.h>
RH_ASK driver(2000, 13, 16, 12);
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

void test(){
    #ifdef RH_HAVE_SERIAL
    Serial.begin(115200);    // Debugging only
    #endif
    if (!driver.init())
    #ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
    #else
      ;
    #endif
}

void login() {
  webserver.send(200, "text/html", "<!DOCTYPE html><html><head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'> <title>Login - Webserver</title> <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css'> <link rel='stylesheet' href='https://www.epndata.com/iot18/demo/css/style.css'></head><body class='text-center'> <form action='/validatelogin' method='post' class='form-signin'> <h1 class='h3 mb-3 font-weight-normal'>Please sign in</h1> <label for='inputEmail' class='sr-only'>Email address</label> <input type='email' name='inputEmail' id='inputEmail' class='form-control' placeholder='Email address' required autofocus> <label for='inputPassword' class='sr-only'>Password</label> <input type='password' name='inputPassword' id='inputPassword' class='form-control' placeholder='Password' required> <button class='btn btn-lg btn-primary btn-block' type='submit'>Sign in</button> <button formaction='/weather' class='btn btn-lg btn-primary btn-block' type='sensor'>Weather Sensor</button> <p class='mt-5 mb-3 text-muted'>&copy; 2019 IoT18 InlämningsUppgift1.</p></form></body></html>");
}

void validateLogin() {
  if(webserver.args() > 0) {
    for(uint8_t i = 0; i < webserver.args(); i++) {
      
      if(webserver.argName(i) == "inputEmail") {
        if(webserver.arg(i) == user_email) {
          Serial.println("E-postadressen stämmer");
          emailCheck = true;
        }
      }
      
      if(webserver.argName(i) == "inputPassword") {
        if(webserver.arg(i) == user_password) {
          Serial.println("Lösenordet stämmer");
          passwordCheck = true;
        }
      }
    }
  }
  
  if(emailCheck && passwordCheck) {
    webserver.sendHeader("Location", "/text");
    webserver.send(303);
  } else {
    webserver.sendHeader("Location", "/");
    webserver.send(303);   
  } 
}

void textpage() {
  webserver.send(200, "text/html", "<!DOCTYPE html> <h1>Enter your text to send it to Arduino IDE</h1> <label for='inputEmail'>Enter your text here --&gt;</label> <input required='' type='text' autofocus='' placeholder='Enter your text here'/> <label> <label> <button type='submit'>Send</button> </label> </label> <p>&copy; 2019</p></form>");
}




String receiver(){
   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
   uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;

      // Message with a good checksum received, dump it.
      driver.printBuffer("Got:", buf, buflen);
    }
    String rcv;
    for (int i = 0; i<buflen; i++){
      rcv += (char)buf[i];
    }
    Serial.println(rcv);
    delay(1000);
    return rcv;
}
void weatherpage(){
  String temperature = receiver();
  String humidity = receiver();;
  //webserver.send(200, "text/html" "<!DOCTYPE html><html><head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'> <title>Login - Webserver</title> <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css'> <link rel='stylesheet' href='https://www.epndata.com/iot18/demo/css/style.css'></head><body class='text-center'> <form action='/weatherpage' method='postpage' class='weatherpage'> </form></body></html>") + temperature;

      
      String weatherpage = String("<!doctype html><html> <head> <title>Temperature</title> </head><body> Temperatur: ") + temperature+" Humidity: " + humidity;
      webserver.send(200, "text/html", weatherpage);
}
