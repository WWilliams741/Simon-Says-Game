// Initialize the hardware to software configuration:
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;

const int ledPin1 =  9;
const int ledPin2 =  10;
const int ledPin3 =  11;
const int ledPin4 =  12;

void setup() {
  // initialize the pushbutton pins as input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

  // Initialize the LED pins as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // Instantiate a random number generator (Note that this has a seed based on other factors from Pin 0):
  randomSeed(analogRead(0));
}

void loop() {
  // Setting game length (in number of turns) and array to store Simon's previous commands:
  int gameTime = 15;
  int gameArray[gameTime];

  // Storing button states, default zero/LOW:
  int button1 = 0;
  int button2 = 0;
  int button3 = 0;
  int button4 = 0;

  // Randomly assigns values to the game array:
  for (int setValues = 0; setValues < gameTime; setValues++) {
    gameArray[setValues] = random(1, 5);
  }
  
  // Loop until first two buttons are pressed together then both released - Start the game:
  while (button1 == LOW || button2 == LOW) {
    button1 = digitalRead(buttonPin1);
    button2 = digitalRead(buttonPin2);
  }
  while (button1 == HIGH || button2 == HIGH) {
    button1 = digitalRead(buttonPin1);
    button2 = digitalRead(buttonPin2);
  }

  // Loop over the game array:
  for (int mainLoop = 0; mainLoop < gameTime; mainLoop++) {

    // Loop over the current game array state and display the next "order" that Simon will give:
    for (int displayLoop = 0; displayLoop < mainLoop + 1; displayLoop++) {

      // Light up the correct LED based on the number in the game array:
      delay(150);
      if (gameArray[displayLoop] == 1) {
        digitalWrite(ledPin1, HIGH);
        delay(300);
        digitalWrite(ledPin1, LOW);
        delay(150);
      }
      else if (gameArray[displayLoop] == 2) {
        digitalWrite(ledPin2, HIGH);
        delay(300);
        digitalWrite(ledPin2, LOW);
        delay(150);
      }
      else if (gameArray[displayLoop] == 3) {
        digitalWrite(ledPin3, HIGH);
        delay(300);
        digitalWrite(ledPin3, LOW);
        delay(150);
      }
      else {
        digitalWrite(ledPin4, HIGH);
        delay(300);
        digitalWrite(ledPin4, LOW);
        delay(150);
      }
    }

    // For each "order" Simon gives you have to repeat it, this is where that happens:
    for (int inputLoop = 0; inputLoop < mainLoop + 1; inputLoop++) {

      // Accept the first input the user gives, wait otherwise:
      while (button1 == LOW && button2 == LOW && button3 == LOW && button4 == LOW) {
        button1 = digitalRead(buttonPin1);
        button2 = digitalRead(buttonPin2);
        button3 = digitalRead(buttonPin3);
        button4 = digitalRead(buttonPin4);
        delay(100);
      }

      // check which button was pressed then if that was the correct "order":
      if (button1 == HIGH && gameArray[inputLoop] == 1) {
        digitalWrite(ledPin1, HIGH);
        while (button1 == HIGH) {
          button1 = digitalRead(buttonPin1);
        }
        delay(150);
        digitalWrite(ledPin1, LOW);
      }
      else if (button2 == HIGH && gameArray[inputLoop] == 2) {
        digitalWrite(ledPin2, HIGH);
        while (button2 == HIGH) {
          button2  = digitalRead(buttonPin2);
        }
        delay(150);
        digitalWrite(ledPin2, LOW);
      }
      else if (button3 == HIGH && gameArray[inputLoop] == 3) {
        digitalWrite(ledPin3, HIGH);
        while (button3 == HIGH) {
          button3 = digitalRead(buttonPin3);
        }
        delay(150);
        digitalWrite(ledPin3, LOW);
      }
      else if (button4 == HIGH && gameArray[inputLoop] == 4) {
        digitalWrite(ledPin4, HIGH);
        while (button4 == HIGH) {
          button4 = digitalRead(buttonPin4);
        }
        delay(150);
        digitalWrite(ledPin4, LOW);
      }
      // If they got the "order" wrong, the game is over:
      else {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        delay(750);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        delay(500);
        return;
      }

      // If all the "orders" were correct, and there are none left, the user has won the game:
      if (inputLoop == gameTime - 1) {
        delay(150);
        for (int victoryLoop = 0; victoryLoop < 3; victoryLoop++) {
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          digitalWrite(ledPin4, HIGH);
          delay(500);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          digitalWrite(ledPin4, LOW);
          delay(500);
        }
        return;
      }
    }
  }
}
