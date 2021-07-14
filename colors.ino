void Red()
{
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);  
}

void Blue()
{
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, HIGH);
}

void Green()
{
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);
}

void Yellow()
{
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);
}

void Cyan()
{
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, HIGH);
}

void Purple()
{
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
}

void White()
{
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
}
