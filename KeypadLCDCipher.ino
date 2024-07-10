#include <Keypad.h>
#include <LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//4x4 Matrix key pad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap
char keys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to Arduino pins.
byte rowPins[ROWS] = {9, 8, 7, 6};

// Connect keypad COL0, COL1, COL2 and COL3 to Arduino pins.
byte colPins[COLS] = {5, 10, 3, 2};

// Create the Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("CIPHER");
}

String inputString = "";

void loop()
{
  char key = kpd.getKey();
  // check if a key is pressed
  if (key != NO_KEY)
  {
    // check if the key is '#', which means the user is done entering the string
    if (key == '#')
    {
      // clear the LCD display
      lcd.clear();

      // print the entered string on the first row of the LCD
      lcd.setCursor(0, 0);
      lcd.print("Entered String:");
      lcd.setCursor(0, 1);
      lcd.print(inputString);
      
      int n = inputString.length();
      int i = 0;
      for(i = 0; i<n-16;i++)
      {
        if(i == 0)
        {
          delay(200);
        }
        delay(1000);
        
        lcd.scrollDisplayLeft();        
      }
      delay(2000);
      
      options();
    }
    else if (key == '*')
    {
      //resetting the process
      setup();
      inputString = "";
      loop();
    }
    
    else
    {
      // add the pressed key to the input string
      inputString += key;
      
      if(inputString.length()>10)
      {
        //lcd.clear();
        lcd.scrollDisplayLeft();
        lcd.setCursor((inputString.length()-10), 0);
        
        lcd.print("CIPHER");
      }
	
      // print the pressed key on the second row of the LCD
      lcd.setCursor(0, 1);
      lcd.print("Input:");
      lcd.setCursor(6, 1);
      lcd.print(inputString);
    }
  }
  	
}



void options()
{mainoptions:
	lcd.clear();
	lcd.print("1.Encode/Decode");
  	lcd.setCursor(0,1);
  	lcd.print("2.(En/De)crypt");
  		mainoptionso:
  	char key = kpd.getKey();
  	if (key == '1')
    {
        
      	key = ' ';
      	lcd.clear();
      	
		lcd.print("1.HEX->DEC");
  		lcd.setCursor(0,1);
  		lcd.print("2.DEC->HEX");
      	options1:
      	char key = kpd.getKey();
    	if (key == '1')
        {	
          	key = ' ';
          	lcd.clear();       	
        	encode(inputString);
        }
      	else if (key == '*')
        {
          	goto mainoptions;
        }
      	else if (key == '2')
        {
          	
        	decode(inputString);
        }
      	else
        {
          	goto options1;
        }
    }
  	else if (key == '2')
    {
      	
      	lcd.clear();
      	
		lcd.print("1.Encrypt");
  		lcd.setCursor(0,1);
  		lcd.print("2.Decrypt");
      	options2:
      	char key = kpd.getKey();
    	if (key == '1')
        {
          	lcd.clear();
          	lcd.print("Encrypting");
          	delay(1000);
        	encrypt(inputString);
        }
      	else if (key == '2')
        {
          	lcd.clear();
          	lcd.print("Decrypting");
          	delay(1000);
        	decrypt(inputString);
        }
      	else if (key == '*')
        {
          	goto mainoptions;
        }
      	else
        {
          	goto options2;
        }
    }
  	else if (key == '*')
        {
          	loop();
        }
 	else
    {
    	goto mainoptionso;
    }
  	
}

void encode(String text)
{
  int hexLength = text.length();  
  int decimal = 0;
    for (int i = 0; i < hexLength; i++) {
        int hexDigit;
        char c = text[i];
        if (c >= '0' && c <= '9') 
        {
            hexDigit = c - '0';
        } else if (c >= 'a' && c <= 'f') 
        {
            hexDigit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') 
        {
            hexDigit = c - 'A' + 10;
        } else 
        {
            // Invalid hex character
        }
        decimal = decimal * 16 + hexDigit;
    }
    lcd.clear();
 	lcd.print("Output String:");
  	lcd.setCursor(0,1);
  	lcd.print(decimal);
 	
 	int n = text.length();
      int i = 0;
      for(i = 0; i<n-16;i++)
      {
        if(i == 0)
        {
          delay(200);
        }
        delay(1000);
        
        lcd.scrollDisplayLeft();
      }
      delay(2000);
 
	
  	delay(4000);
    }

void decrypt(String text)
{	
  	int s = 9;
  		lcd.clear();
		lcd.print("Enter Shift");
  		lcd.setCursor(0,1);
 		lcd.print("Amount: ");
      	options2x:
      	char key = kpd.getKey();
    	if (indexof(key) < 10)
        {
          	s = 14-indexof(key);
    	}
 		else
    	{
    	goto options2x;
    	}
    String result = "";
  	String raw = "0123456789ABCD";
 
    // traverse text
    for (int i = 0; i < text.length(); i++) 
    {
        // apply transformation to each character
        result += raw[(indexof(text[text.length()-i-1])+s)%14];
    }
 
    // Return the resulting string
  	lcd.clear();
 	lcd.print("Output String:");
  	lcd.setCursor(0,1);
  	lcd.print(result);
 	
 	int n = inputString.length();
      int i = 0;
      for(i = 0; i<n-16;i++)
      {
        if(i == 0)
        {
          delay(200);
        }
        delay(1000);
        
        lcd.scrollDisplayLeft();
      }
      delay(2000);
 
	
  	delay(4000);
    
}
void encrypt(String text)
{	int s = 5;
      	lcd.clear();
		lcd.print("Enter Shift");
  		lcd.setCursor(0,1);
 		lcd.print("Amount: ");
      	options2x:
      	char key = kpd.getKey();
    	if (indexof(key) < 10)
        {
          	s = indexof(key);
    	}
 		else
    	{
    	goto options2x;
    	}
  	
    String result = "";
  	String raw = "0123456789ABCD";
 
    // traverse text
    for (int i = 0; i < text.length(); i++) 
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        result += raw[(indexof(text[text.length()-i-1])+s)%14];
    }
 
    // Return the resulting string
  	lcd.clear();
 	lcd.print("Output String:");
  	lcd.setCursor(0,1);
  	lcd.print(result);
 	
 	int n = inputString.length();
      int i = 0;
      for(i = 0; i<n-16;i++)
      {
        if(i == 0)
        {
          delay(200);
        }
        delay(1000);
        
        lcd.scrollDisplayLeft();
      }
      delay(2000);
 
	
  	delay(4000);
    }


int decode(String text)
{
      int decimal = stoi(text);
  	if (decimal == -1)
    {
      	lcd.clear();
 			lcd.print("* to restart");
      	return 0;
    }
    String hex = "";
    while (decimal > 0) {
        int hexDigit = decimal % 16;
        if (hexDigit < 10) {
            hex = char(hexDigit + '0') + hex;
        } else {
            hex = char(hexDigit - 10 + 'A') + hex;
        }
        decimal /= 16;
    }
    lcd.clear();
 	lcd.print("Output String:");
  	lcd.setCursor(0,1);
  	lcd.print(hex);
 	
 	int n = text.length();
      int i = 0;
      for(i = 0; i<n-16;i++)
      {
        if(i == 0)
        {
          delay(200);
        }
        delay(1000);
        
        lcd.scrollDisplayLeft();
      }
      delay(2000);
 
	
  	delay(4000);
  	return 0;
    }


                       
int indexof(char x)
{
  	String raw = "0123456789ABCD";
   	for (int i =0;i<14;i++)
    {
      	if(x == raw[i])
        {
          	return i;
        }
    }
}

int stoi(String str) {
    int num = 0;
    bool isNegative = false;
    int i = 0;
    if (str[0] == '-') {
        isNegative = true;
        i = 1;
    }
    for (; i < str.length(); i++) {
        if (isdigit(str[i])) {
            num = num * 10 + (str[i] - '0');
        } else 
        {
			lcd.clear();
 			lcd.print("Error in Input");
  			delay(1000);
          	return -1;
        }
    }
    return isNegative ? -num : num;
}
