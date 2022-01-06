void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
void handleLED();
void aba2();
void Root();

void handleRoot() {
  server.send(200, "text/html", "<center><h2>Ordens</h2><center><div></div><center><form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form></center><div></div><center><h3>Umidade nos Vasos</h3></center><div></div><center><form action=\"/h1\" method=\"POST\">  <input type=\"submit\" value=\"Suculenta\"></form><center>");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void handleLED() {                          // If a POST request is made to URI /LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void Root() {
  
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}


extern const int pino_sinal_analogico, h1;
float umi, umi2, top = (1023-371);



void aba2() {
  digitalWrite(h1, 1);
  delay(800);
  umi = analogRead(pino_sinal_analogico);
  digitalWrite(h1, 0);
  umi2 = 100*(top-(umi-371))/top;
  server.send(200, "text/html", "<div><h1> </h1></div><div><h5> </h5></div><center><h2>Umidade no vaso: " +String(umi2)+ "%</h2></center> <p> </p> <p></p> <p> </p> <center> <form action=\"/Root\" method=\"POST\"><input type=\"submit\" value =\"Tela inicial\"></form></center>  <div></div><center><h3>Umidade nos Vasos</h3></center><div></div><center><form action=\"/h1\" method=\"POST\">  <input type=\"submit\" value=\"Suculenta\"></form></center>");
//   </p>leitura do sensor :" +String(umi)+"<p>
}
