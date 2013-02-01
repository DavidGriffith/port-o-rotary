//*******************************************************
//					GPIO Definitions
//*******************************************************
#define HOOK		0		//Port C.0
#define BT_EN		1		//Port C.1
#define RING_PWR	2		//Port C.2
#define RING1		3		//Port C.3
#define RING2		4		//Port C.4
#define PSTAT		5		//Port C.5
#define BATT		7

#define BT_TX		0		//Port D.0
#define BT_RX		1		//Port D.1
#define	BT_RES		2		//Port D.2
#define EROTARY		3		//Port D.3
#define ROTARY		4		//Port D.4
#define BT_UNPAIR   5       //Port D.5
#define DT1			6		//Port D.6
#define DT2			7		//Port D.7

#define	CS			2		//Port B.2
#define MOSI		3		//Port B.3
#define MISO		4		//Port B.4
#define SCK			5		//Port B.5

//*******************************************************
//						Macros
//*******************************************************
#define	LED_ON()	cbi(PORTC, PSTAT);
#define	LED_OFF()	sbi(PORTC, PSTAT);

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))
//*******************************************************
//					General Definitions
//*******************************************************
#define MYUBRR 16	//Used to set the AVR Baud Rate

#define MAX_MESSAGE_LENGTH	150	//Buffer length for UART messages
#define	OK		1
#define	ERROR	0

#define	OFF_HOOK	1
#define	ON_HOOK		0
#define	ROTARY_DIALING	1
#define	ROTARY_FINISHED	0
#define STEP_SHIFT 7
#define SINE_SAMPLES 511U
#define TICKS_PER_CYCLE 256U
// see http://www.atmel.com/Images/doc1982.pdf
#define STEP_350 (350UL * SINE_SAMPLES * (TICKS_PER_CYCLE << STEP_SHIFT) / F_CPU)
#define STEP_440 (440UL * SINE_SAMPLES * (TICKS_PER_CYCLE << STEP_SHIFT) / F_CPU)

//=======================================================
//					Function Definitions
//=======================================================
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
void ioinit(void);
void delay_ms(uint16_t x);
void config_bluetooth(void);
void incoming_call(void);
void place_call(void);		
void ring_it(void);			
void short_ring_it(void);	
char string_compare(const char *search_string, const char *find_string);	
void dial_tone(void);	
char get_rotary_number(void);
void dial_number(void);	

const unsigned char sine_table[] PROGMEM = {128,
    129,
    131,
    132,
    134,
    135,
    137,
    138,
    140,
    142,
    143,
    145,
    146,
    148,
    149,
    151,
    152,
    154,
    155,
    157,
    159,
    160,
    162,
    163,
    165,
    166,
    168,
    169,
    171,
    172,
    173,
    175,
    176,
    178,
    179,
    181,
    182,
    184,
    185,
    186,
    188,
    189,
    190,
    192,
    193,
    195,
    196,
    197,
    198,
    200,
    201,
    202,
    204,
    205,
    206,
    207,
    209,
    210,
    211,
    212,
    213,
    214,
    216,
    217,
    218,
    219,
    220,
    221,
    222,
    223,
    224,
    225,
    226,
    227,
    228,
    229,
    230,
    231,
    232,
    233,
    234,
    235,
    235,
    236,
    237,
    238,
    239,
    239,
    240,
    241,
    242,
    242,
    243,
    244,
    244,
    245,
    245,
    246,
    247,
    247,
    248,
    248,
    249,
    249,
    250,
    250,
    250,
    251,
    251,
    252,
    252,
    252,
    253,
    253,
    253,
    253,
    254,
    254,
    254,
    254,
    254,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    254,
    254,
    254,
    254,
    254,
    254,
    253,
    253,
    253,
    252,
    252,
    252,
    251,
    251,
    251,
    250,
    250,
    249,
    249,
    248,
    248,
    247,
    247,
    246,
    246,
    245,
    244,
    244,
    243,
    243,
    242,
    241,
    240,
    240,
    239,
    238,
    237,
    237,
    236,
    235,
    234,
    233,
    232,
    231,
    231,
    230,
    229,
    228,
    227,
    226,
    225,
    224,
    223,
    222,
    221,
    219,
    218,
    217,
    216,
    215,
    214,
    213,
    212,
    210,
    209,
    208,
    207,
    205,
    204,
    203,
    202,
    200,
    199,
    198,
    196,
    195,
    194,
    192,
    191,
    190,
    188,
    187,
    186,
    184,
    183,
    181,
    180,
    179,
    177,
    176,
    174,
    173,
    171,
    170,
    168,
    167,
    165,
    164,
    162,
    161,
    159,
    158,
    156,
    155,
    153,
    152,
    150,
    149,
    147,
    145,
    144,
    142,
    141,
    139,
    138,
    136,
    135,
    133,
    131,
    130,
    128,
    127,
    125,
    124,
    122,
    120,
    119,
    117,
    116,
    114,
    113,
    111,
    110,
    108,
    106,
    105,
    103,
    102,
    100,
    99,
    97,
    96,
    94,
    93,
    91,
    90,
    88,
    87,
    85,
    84,
    82,
    81,
    79,
    78,
    76,
    75,
    74,
    72,
    71,
    69,
    68,
    67,
    65,
    64,
    63,
    61,
    60,
    59,
    57,
    56,
    55,
    53,
    52,
    51,
    50,
    48,
    47,
    46,
    45,
    43,
    42,
    41,
    40,
    39,
    38,
    37,
    36,
    34,
    33,
    32,
    31,
    30,
    29,
    28,
    27,
    26,
    25,
    24,
    24,
    23,
    22,
    21,
    20,
    19,
    18,
    18,
    17,
    16,
    15,
    15,
    14,
    13,
    12,
    12,
    11,
    11,
    10,
    9,
    9,
    8,
    8,
    7,
    7,
    6,
    6,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    4,
    4,
    5,
    5,
    5,
    6,
    6,
    7,
    7,
    8,
    8,
    9,
    10,
    10,
    11,
    11,
    12,
    13,
    13,
    14,
    15,
    16,
    16,
    17,
    18,
    19,
    20,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    41,
    42,
    43,
    44,
    45,
    46,
    48,
    49,
    50,
    51,
    53,
    54,
    55,
    57,
    58,
    59,
    60,
    62,
    63,
    65,
    66,
    67,
    69,
    70,
    71,
    73,
    74,
    76,
    77,
    79,
    80,
    82,
    83,
    84,
    86,
    87,
    89,
    90,
    92,
    93,
    95,
    96,
    98,
    100,
    101,
    103,
    104,
    106,
    107,
    109,
    110,
    112,
    113,
    115,
    117,
    118,
    120,
    121,
    123,
    124,
    126};