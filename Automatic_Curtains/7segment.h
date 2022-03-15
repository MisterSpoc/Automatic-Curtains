int a = 11;
int b = 12;
int c = 13;
int d = 4;
int e = 5;
int f = 10;
int g = 9;
int dp = A2;
int pin[] = {dp, g, f, e, d, c, b, a};

const uint8_t SevenSegmentASCII[96] = {
  0b00000000, /* (space) */
  0b10000110, /* ! */
  0b00100010, /* " */
  0b01111110, /* # */
  0b01101101, /* $ */
  0b11010010, /* % */
  0b01000110, /* & */
  0b00100000, /* ' */
  0b00101001, /* ( */
  0b00001011, /* ) */
  0b00100001, /* * */
  0b01110000, /* + */
  0b00010000, /* , */
  0b01000000, /* - */
  0b10000000, /* . */
  0b01010010, /* / */
  0b00111111, /* 0 */
  0b00000110, /* 1 */
  0b01011011, /* 2 */
  0b01001111, /* 3 */
  0b01100110, /* 4 */
  0b01101101, /* 5 */
  0b01111101, /* 6 */
  0b00000111, /* 7 */
  0b01111111, /* 8 */
  0b01101111, /* 9 */
  0b00001001, /* : */
  0b00001101, /* ; */
  0b01100001, /* < */
  0b01001000, /* = */
  0b01000011, /* > */
  0b11010011, /* ? */
  0b01011111, /* @ */
  0b01110111, /* A */
  0b01111100, /* B */
  0b00111001, /* C */
  0b01011110, /* D */
  0b01111001, /* E */
  0b01110001, /* F */
  0b00111101, /* G */
  0b01110110, /* H */
  0b00110000, /* I */
  0b00011110, /* J */
  0b01110101, /* K */
  0b00111000, /* L */
  0b00010101, /* M */
  0b00110111, /* N */
  0b00111111, /* O */
  0b01110011, /* P */
  0b01101011, /* Q */
  0b00110011, /* R */
  0b01101101, /* S */
  0b01111000, /* T */
  0b00111110, /* U */
  0b00111110, /* V */
  0b00101010, /* W */
  0b01110110, /* X */
  0b01101110, /* Y */
  0b01011011, /* Z */
  0b00111001, /* [ */
  0b01100100, /* \ */
  0b00001111, /* ] */
  0b00100011, /* ^ */
  0b00001000, /* _ */
  0b00000010, /* ` */
  0b01011111, /* a */
  0b01111100, /* b */
  0b01011000, /* c */
  0b01011110, /* d */
  0b01111011, /* e */
  0b01110001, /* f */
  0b01101111, /* g */
  0b01110100, /* h */
  0b00010000, /* i */
  0b00001100, /* j */
  0b01110101, /* k */
  0b00110000, /* l */
  0b00010100, /* m */
  0b01010100, /* n */
  0b01011100, /* o */
  0b01110011, /* p */
  0b01100111, /* q */
  0b01010000, /* r */
  0b01101101, /* s */
  0b01111000, /* t */
  0b00011100, /* u */
  0b00011100, /* v */
  0b00010100, /* w */
  0b01110110, /* x */
  0b01101110, /* y */
  0b01011011, /* z */
  0b01000110, /* { */
  0b00110000, /* | */
  0b01110000, /* } */
  0b00000001, /* ~ */
  0b00000000, /* (del) */
};

// sets up pins as outputs
void setupDisplay() {
	for (int i = 0; i < 8; i++) {
    pinMode(pin[i], OUTPUT);
	}
}

// lights up segments in order, ensuring proper pin connection
// order: dp, g, f, e, d, c, b, a
void testLoop() {
	for (int i = 0; i < 8; i++) {
		digitalWrite(pin[i], 1);
		delay(1000);
		digitalWrite(pin[i], 0);
	}
}

// prints character to 7 segment
// takes in ASCII int value of char (can just pass through char, auto converts)
// passing through a space turns display off
void printChar(int c) {
  int character = SevenSegmentASCII[c - 32];
  for (int i = 7; i >= 0; i--) {
    digitalWrite(pin[i], character%2);
    character /= 2;
  }
}

// prints a word
void printWord(char w[]) {
  int len = strlen(w);

  for (int i = 0; i < len; i++) {
    printChar(w[i]);
    delay(1000);
  }
}

// blinks char c num times
void blinkChar(char c, int num) {
  for (int i = 0; i < num; i++) {
    printChar(c);
    delay(500);
    printChar(' ');
    delay(250);
  }
}

// tests numbers 1-9 on display
void testNums() {
  char nums[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

  for (int i = 0; i < 10; i++) {
    printChar(nums[i]);
    delay(1000);
  }
}
