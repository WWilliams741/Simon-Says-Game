// Initialize the hardware to software configuration:
enum BUTTONPINS : uint_least8_t
{
    BUTTONPIN1 = 2,
    BUTTONPIN2 = 3,
    BUTTONPIN3 = 4,
    BUTTONPIN4 = 5
};

enum LEDPINS : uint_least8_t
{
    LEDPIN1 = 9,
    LEDPIN2 = 10,
    LEDPIN3 = 11,
    LEDPIN4 = 12
};

void setup()
{
    // initialize the pushbutton pins as input:
    pinMode(BUTTONPIN1, INPUT);
    pinMode(BUTTONPIN2, INPUT);
    pinMode(BUTTONPIN3, INPUT);
    pinMode(BUTTONPIN4, INPUT);

    // Initialize the LED pins as output:
    pinMode(LEDPIN1, OUTPUT);
    pinMode(LEDPIN2, OUTPUT);
    pinMode(LEDPIN3, OUTPUT);
    pinMode(LEDPIN4, OUTPUT);

    // Instantiate a random number generator (Note that this has a seed based on other factors from Pin 0):
    randomSeed(analogRead(0));
}

void loop()
{
    // Setting game length (in number of turns) and array to store Simon's commands:
    const uint_least8_t GAMETIME = 15; // 254 is max that you can make this without changing data types, or the compiler changing them for you.
    uint_least8_t gameArray[GAMETIME]; // in future make this a bitfield

    // Stores how many times we will do the "victory screech!" (victory loop) along with random number enum:
    const uint_least8_t VICTORYSCREECH = 3;
    enum RANDNUMS : uint_least8_t
    {
        RAND1,
        RAND2,
        RAND3,
        RAND4
    };

    // Stores delay values, I don't like hardcoding:
    enum DELAYS : uint_least16_t
    {
        DELAY150 = 150,
        DELAY300 = 300,
        DELAY500 = 500,
        DELAY750 = 750
    };

    // Storing button states, default LOW:
    uint_least8_t button1 = LOW;
    uint_least8_t button2 = LOW;
    uint_least8_t button3 = LOW;
    uint_least8_t button4 = LOW;

    // Randomly assigns values to the game array:
    for (uint_least8_t setValues = 0; setValues < GAMETIME; ++setValues)
    {
        gameArray[setValues] = random(RAND1, RAND4 + 1);
    }

    // Loop until first two buttons are pressed together then both released - Start the game:
    while (button1 == LOW || button2 == LOW)
    {
        button1 = digitalRead(BUTTONPIN1);
        button2 = digitalRead(BUTTONPIN2);
    }
    while (button1 == HIGH || button2 == HIGH)
    {
        button1 = digitalRead(BUTTONPIN1);
        button2 = digitalRead(BUTTONPIN2);
    }

    // Loop over the game array:
    for (uint_least8_t mainLoop = 0; mainLoop < GAMETIME; ++mainLoop)
    {
        // Loop over the current game array state and display the next "order" that Simon will give:
        for (uint_least8_t displayLoop = 0; displayLoop < (mainLoop + 1); ++displayLoop)
        {
            // Light up the correct LED based on the number in the game array:
            delay(DELAY300);
            if (gameArray[displayLoop] == RAND1)
            {
                digitalWrite(LEDPIN1, HIGH);
                delay(DELAY300);
                digitalWrite(LEDPIN1, LOW);
            }
            else if (gameArray[displayLoop] == RAND2)
            {
                digitalWrite(LEDPIN2, HIGH);
                delay(DELAY300);
                digitalWrite(LEDPIN2, LOW);
            }
            else if (gameArray[displayLoop] == RAND3)
            {
                digitalWrite(LEDPIN3, HIGH);
                delay(DELAY300);
                digitalWrite(LEDPIN3, LOW);
            }
            else
            {
                digitalWrite(LEDPIN4, HIGH);
                delay(DELAY300);
                digitalWrite(LEDPIN4, LOW);
            }
        }

        // For each "order" Simon gives, you have to repeat it, this is where that happens:
        for (uint_least8_t inputLoop = 0; inputLoop < (mainLoop + 1); ++inputLoop)
        {
            // Accept the first input the user gives, wait otherwise:
            while (button1 == LOW && button2 == LOW && button3 == LOW && button4 == LOW)
            {
                button1 = digitalRead(BUTTONPIN1);
                button2 = digitalRead(BUTTONPIN2);
                button3 = digitalRead(BUTTONPIN3);
                button4 = digitalRead(BUTTONPIN4);
                delay(DELAY150);
            }

            // check which button was pressed, then if that was the correct "order" light up that led:
            if (button1 == HIGH && gameArray[inputLoop] == RAND1)
            {
                digitalWrite(LEDPIN1, HIGH);
                while (button1 == HIGH)
                {
                    button1 = digitalRead(BUTTONPIN1);
                }
                delay(DELAY150);
                digitalWrite(LEDPIN1, LOW);
            }
            else if (button2 == HIGH && gameArray[inputLoop] == RAND2)
            {
                digitalWrite(LEDPIN2, HIGH);
                while (button2 == HIGH)
                {
                    button2 = digitalRead(BUTTONPIN2);
                }
                delay(DELAY150);
                digitalWrite(LEDPIN2, LOW);
            }
            else if (button3 == HIGH && gameArray[inputLoop] == RAND3)
            {
                digitalWrite(LEDPIN3, HIGH);
                while (button3 == HIGH)
                {
                    button3 = digitalRead(BUTTONPIN3);
                }
                delay(DELAY150);
                digitalWrite(LEDPIN3, LOW);
            }
            else if (button4 == HIGH && gameArray[inputLoop] == RAND4)
            {
                digitalWrite(LEDPIN4, HIGH);
                while (button4 == HIGH)
                {
                    button4 = digitalRead(BUTTONPIN4);
                }
                delay(DELAY150);
                digitalWrite(LEDPIN4, LOW);
            }
            // If they got the "order" wrong, the game is over:
            else
            {
                digitalWrite(LEDPIN1, HIGH);
                digitalWrite(LEDPIN2, HIGH);
                digitalWrite(LEDPIN3, HIGH);
                digitalWrite(LEDPIN4, HIGH);
                delay(DELAY750);
                digitalWrite(LEDPIN1, LOW);
                digitalWrite(LEDPIN2, LOW);
                digitalWrite(LEDPIN3, LOW);
                digitalWrite(LEDPIN4, LOW);
                return;
            }

            // If all the "orders" were correct, and there are none left, the user has won the game:
            if (inputLoop == (GAMETIME - 1))
            {
                delay(DELAY150);
                for (uint_least8_t victoryLoop = 0; victoryLoop < VICTORYSCREECH; ++victoryLoop)
                {
                    digitalWrite(LEDPIN1, HIGH);
                    digitalWrite(LEDPIN2, HIGH);
                    digitalWrite(LEDPIN3, HIGH);
                    digitalWrite(LEDPIN4, HIGH);
                    delay(DELAY500);
                    digitalWrite(LEDPIN1, LOW);
                    digitalWrite(LEDPIN2, LOW);
                    digitalWrite(LEDPIN3, LOW);
                    digitalWrite(LEDPIN4, LOW);
                    delay(DELAY500);
                }
                return;
            }
        }
    }
}
