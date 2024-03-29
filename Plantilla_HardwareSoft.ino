//****************************
//1. Librerias

  //****************************
//2.  Definicion de Pinout
  //      Las Etiquetas para los pinout son los que comienzan con GPIO
  //      Es decir, si queremos activar la salida 1, tenemos que buscar la referencia GPIO 1, Pero solomante Escribir 1 sin "GPIO"
  //      NO tomar como referencia las etiquetas D1.

  //    - 2.1 Definicion de etiquetas para las Entradas.

  #define PB_ENTER 0

  //    - 2.2 Definicion de etiquetas para las Salidas.
  #define LED_azul 2               // Led Por defecto embebido con la Placa GPIO 2 "D4"

  // #define xxxxx 3
  // #define xxxxx 4
  // #define xxxxx 5

  //      - 2.3 Modulo de xxx

  //****************************
  //    - 2.4. Constantes
  #define RF95_FREQ 915.0


  //****************************
//3. Variables Globales.
  //   -3.1 Variables para las Interrupciones
    String        inputString;           // Buffer recepcion Serial.
    String        funtion_Mode;          // Tipo de funcion para ejecutar.
    String        funtion_Number;        // Numero de funcion a EJECUTAR.
    String        funtion_Parmeter1;     // Parametro 1 de la Funcion.
    String        funtion_Parmeter2;     // Parametro 2 de la Funcion.
    String        funtion_Parmeter3;     // Parametro 3 de la Funcion.
    String        funtion_Parmeter4;      // Parametro para las Funciones remotas.
    String        function_Remote;
    String        function_Enable;
    volatile int  x1=0;
    volatile int  x2=0;
    volatile int  x3=0;
    volatile int  x4=0;
  //    -3.2 Variables Globales para Las Funciones.
    bool    inicio= false;
    bool    codified_funtion = true;
    bool    flag_ISR_stringComplete = false;
    bool    flag_F_codified_funtion = false;


//4. Instancias de Clases de Librerias Incluidas.
//5. Funciones ISR.
  //-5.1 Serial Function.
    void serialEvent (){
      while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming_function character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == '\n') {
          flag_ISR_stringComplete = true;
          flag_F_codified_funtion=false;
        }
      }
    }
void setup() { 
//1.  Configuracion de Puertos.
  //****************************
  //    1.1 Configuracion de Salidas:
  pinMode(LED_azul, OUTPUT);

  //    1.2 Configuracion de Entradas
  //****************************
  //****************************
//2.  Condiciones Iniciales.
  //    2.1 Estado de Salidas.
  digitalWrite(LED_azul, HIGH);
  //****************************
  //    2.2 Valores y Espacios de Variables
  inputString.reserve(200);         // reserve 200 bytes for the inputString:
  inicio = true;
  //****************************
// 3. Configuracion de Perifericos:
  //    - 3.1 Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 //****************************
  //    - 3.2 Interrupciones Habilitadas.
  //interrupts ();

  //****************************
// 4. Sitema Minimo Configurado.
  Serial.println("Sistema Minimo Configurado");

  //****************************
// 5. Configuracion de DEVICE externos
  //    5.1 Configuracion xxx
  //****************************
  //    5.1.2 INIT. RF95
}

void loop() {
//1. Mensaje de Bienvenida Para Comprobar el Sistema minimo de Funcionamiento.
  while (inicio){
    welcome();
    led_Monitor(2);
  }
//2. Decodificar Funcion
  if(flag_ISR_stringComplete){
    decodificar_solicitud();
  }
//3. Ejecutar Funcion
  if(codified_funtion){
    ejecutar_solicitud();
    // 3.1 Desactivar Banderas.
    codified_funtion=false;
  }
  funcion_predeterminada();
}
//    Funciones de Logic interna del Micro.
void welcome(){
  // Deshabilitamos Banderas
    inicio=false;
    Serial.println("Comenzamos el Programa");
    Serial.println("Esperamos recibir un Dato");
}
void led_Monitor(int repeticiones){
  // Deshabilitamos Banderas
  int repetir=repeticiones;
  for (int encender=0; encender<=repetir; ++encender){
    digitalWrite(LED_azul, LOW);   // Led ON.
    delay(500);                    // pausa 1 seg.
    digitalWrite(LED_azul, HIGH);    // Led OFF.
    delay(500);                    // pausa 1 seg.
  }
}
void decodificar_solicitud(){
  // Deshabilitamos Banderas
  flag_ISR_stringComplete=false;
  codified_funtion=true;
  Serial.println(inputString);         // Pureba de Comunicacion Serial.
  funtion_Mode=inputString.substring(0,1);
  funtion_Number=inputString.substring(1,2);
  funtion_Parmeter1=inputString.substring(2,3);
  funtion_Parmeter2=inputString.substring(3,4);
  inputString="";
  Serial.println("funcion: " + funtion_Mode);
  Serial.println("Numero: " + funtion_Number);
  Serial.println("Parametro1: " + funtion_Parmeter1);
  Serial.println("Parametro2: " + funtion_Parmeter2+ "\n");
  //Serial.println("Numero de funcion: ")

}
//    Funciones de dispositivo externos.

// Funciones Seleccionadas para Ejecutar.
void f1_Destellos (int repeticiones, int tiempo){
  int veces=repeticiones;
  int retardo=tiempo*100;
  Serial.println("Ejecutando F1.. \n");
  for(int repetir=0; repetir<veces; ++repetir){
    delay(retardo);                  // pausa 1 seg.
    digitalWrite(LED_azul, LOW);     // Led ON.
    delay(retardo);                  // pausa 1 seg.
    digitalWrite(LED_azul, HIGH);    // Led OFF.
  }
}
void f2_serial_Enviar(){
  // Deshabilitamos Banderas
  Serial.println("hola");         // Pureba de Comunicacion Serial.
}
// Ultima Funcxion
void ejecutar_solicitud(){
  // Deshabilitamos Banderas
  if (funtion_Number=="1"){
    int x1=funtion_Parmeter1.toInt();
    int x2=funtion_Parmeter2.toInt();
    Serial.println("funion Nº1");
    f1_Destellos(x1,x2);
  }
  if (funtion_Number=="2"){
    Serial.println("funion Nº2");
  }
  if (funtion_Number=="3"){
    Serial.println("funion Nº3");
  }
  else{
    Serial.println("Ninguna Funcion");
  }
}
void funcion_predeterminada(){

  Serial.println("SEC,NOK,1,A");
  delay(1000);
  Serial.println("SEC,NOK,2,A");
  delay(1000);
  Serial.println("SEC,NOK,1,B");
  delay(1000);
  Serial.println("SEC,NOK,2,B");
  delay(1000);
  Serial.println("SEC,NOK,2,A");
  delay(1000);
  Serial.println("SEC,NOK,3,A");
  delay(1000);
  Serial.println("SEC,NOK,2,B");
  delay(1000);
  Serial.println("SEC,NOK,4,A");
  delay(1000);
  Serial.println("SEC,NOK,2,B");
  delay(1000);
  Serial.println("SEC,NOK,3,A");


  Serial.println("SEC,OK,1,A");
  delay(1000);
  Serial.println("SEC,OK,2,A");
  delay(1000);
  Serial.println("SEC,OK,1,B");
  delay(1000);
  Serial.println("SEC,OK,2,B");
  delay(1000);
  Serial.println("SEC,OK,2,A");
  delay(1000);
  Serial.println("SEC,OK,3,A");
  delay(1000);
  Serial.println("SEC,OK,2,A");
  delay(1000);
  Serial.println("SEC,OK,4,A");
  delay(1000);
  Serial.println("SEC,OK,2,A");
  delay(1000);
  Serial.println("SEC,OK,3,A");

}