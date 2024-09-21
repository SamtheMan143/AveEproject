#define runningLightsLeft 2 //Facing oncoming "car"
#define runningLightsRight 3
#define brightsLeft 4
#define brightsRight 5
#define test 6
#define button 7
const int PR = A0; //PhotoReceptor
#define buttonIndicator 9 //Yellow LED
#define daylight 200
#define threshold 350
int average; //Ambient lighting
int difference; //Adds ambience from brights to average




void runningLights(bool);
void brights(bool);
void turnOnRunningLights();
void turnOnBrights();
void turnOffRunningLights();
void turnOffBrights();
void standard();
void tester();
int averageLighting();




void setup()
{
  pinMode(runningLightsLeft, OUTPUT);
  pinMode(brightsLeft, OUTPUT);
  pinMode(runningLightsRight, OUTPUT);
  pinMode(brightsRight, OUTPUT);

  pinMode(test, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  //pinMode(PR, INPUT);
  pinMode(buttonIndicator, OUTPUT);
  Serial.begin(9600);

  average = averageLighting();
  //average = 240;
  difference = 100;
}






void loop()
{
  Serial.println(analogRead(PR));
  //check for button trigger
  static bool lightsOn = 0;
  static bool brightsOn = 0;
  if (digitalRead(button) == HIGH) //button is currently being pushed and
                                  //connects pin to power
  {
    if (lightsOn)
    {
      lightsOn = 0;
      brightsOn = 0;
    }
    else
    {
      lightsOn = 1;
      brightsOn = 1;
      difference = averageLighting() - average;
    }
    
    while (digitalRead(button) == HIGH); //Loops uselessly until button is released
  }

  if (brightsOn)
  {
    int read = analogRead(A0);
    if (read > (average + 120))
      brightsOn = 0;

    Serial.println(read);
  }

  runningLights(lightsOn);
  brights(brightsOn);
}

int averageLighting()
{
  int total = 0;

  for (int i = 0; i < 100; i++)
  {
    total += analogRead(PR);
  }

  return total / 100;
}

void runningLights(bool on)
{
  if (on)
    turnOnRunningLights();
  else
    turnOffRunningLights();
}

void brights(bool on)
{
  if (on)
    turnOnBrights();
  else
    turnOffBrights();
}

void turnOnRunningLights()
{
  digitalWrite(runningLightsLeft, HIGH);
  digitalWrite(runningLightsRight, HIGH);
}

void turnOnBrights()
{
  digitalWrite(brightsLeft, HIGH);
  digitalWrite(brightsRight, HIGH);
}

void turnOffRunningLights()
{
  digitalWrite(runningLightsLeft, LOW);
  digitalWrite(runningLightsRight, LOW);
}

void turnOffBrights()
{
  digitalWrite(brightsLeft, LOW);
  digitalWrite(brightsRight, LOW);
}