// VS23S010D-L header file for
// P42 Video Display Shield for Arduino
// Wolfgang Friedrich
// Last change: 2018/Feb/11
// https://hackaday.io/project/21097-ntscpal-video-display-shield
// https://github.com/wolfgangfriedrich/P42Display

#ifndef VS23S040D_h
#define VS23S040D_h

// *** Select Video Resolution here ***
#define NTSC320x200
//#define NTSC426x200
//#define PAL300x240
//#define PAL500x240

// *** Select Platform here ***
#define ArduinoShield
//#define FeatherWing		// use FeatherWing for Breadboard

// *** Uncomment this line to get extra debug information on the serial interface ***
//#define SERIAL_DEBUG

#ifdef NTSC320x200
	#include "ntsc320x200.h"
#endif
#ifdef NTSC426x200
	#include "ntsc426x200.h"
#endif
#ifdef PAL300x240
	#include "pal300x240.h"
#endif
#ifdef PAL500x240
	#include "pal500x240.h"
#endif

#define u_int32 unsigned long
#define u_int16 unsigned int

#ifdef ArduinoShield
  // Arduino Uno
const int slaveSelectPin	= 10;
const int MemSelectPin		=  9;
const int nHOLDPin			=  8;
const int nWPPin			=  7;
#endif

#ifdef FeatherWing
  // Feather
const int slaveSelectPin	= 11;
const int MemSelectPin		= 10;
const int nHOLDPin			=  9;
const int nWPPin			=  6;
#endif


// Command definitions incl read / write designation


// SRAM Read Commands
const int ReadSRAM						= 0x03;
const int DORead						= 0x3B;		// Dual Output Read
const int DORead_DualAddress			= 0xBB;
const int QORead						= 0x6B;		// Quad Output Write
const int QORead_QuadAddress			= 0xEB;
// SRAM Write Commands
const int WriteSRAM						= 0x02;
const int DIWrite						= 0xA2;		// Dual Input Read
const int DIWrite_DualAddress			= 0x22;
const int QIWrite						= 0x32;		// Quad Input Read
const int QIWrite_QuadAddress			= 0xB2;
// Miscellaneous Commands
const int ReadStatus					= 0x05;
const int WriteStatus					= 0x01;
const int ReadDeviceID					= 0x9F;
const int ReadGPIOControl				= 0x84;
const int WriteGPIOControl				= 0x82;
const int ReadGPIOState					= 0x86;
const int ReadMultiICAccessControl		= 0xB7;
const int WriteMultiICAccessControl		= 0xB8;
// Video Display Controller Commands
const int WritePictureStart				= 0x28;
const int WritePictureEnd				= 0x29;
const int WriteLineLength				= 0x2A;
const int WriteVideoDisplayControl1		= 0x2B;
const int WritePictureIndexStartAddress	= 0x2C;
const int WriteVideoDisplayControl2		= 0x2D;
const int WriteVTable					= 0x2E;
const int WriteUTable					= 0x2F;
const int WriteProgram					= 0x30;
const int ReadCurrentLinePLL			= 0x53;
const int WriteBlockMoveControl1		= 0x34;
const int WriteBlockMoveControl2		= 0x35;
const int StartBlockMove				= 0x36;


// GPIO Control Register
const byte PIO4Dir	= 0x10;
const byte PIO4High	= 0x01;
const byte PIO4Low	= 0xFE;
const byte PIO5Dir	= 0x20;
const byte PIO5High	= 0x02;
const byte PIO5Low	= 0xFD;
const byte PIO6Dir	= 0x40;
const byte PIO6High	= 0x04;
const byte PIO6Low	= 0xFC;
const byte PIO7Dir	= 0x80;
const byte PIO7High	= 0x08;
const byte PIO7Low	= 0xF7;

// WriteVideoDisplayControl1 Register
const word PLLEnable = 0x1000;
const word SelPLLCLK = 0x2000;
// WriteVideoDisplayControl1 Register
const word LineCount		= ( (TOTAL_LINES-1) << 0);
const word Program_Length	= ((PLLCLKS_PER_PIXEL-1)<<10);
const word NTSC				= 0x0000;
const word PAL				= 0x4000;
const word Enable_Video		= 0x8000;
// WriteBlockMoveControl1 Register
const word BMVC_PYF			= 0x0010;
const word BMVC_DACC		= 0x0008;
const word BMVC_DIR			= 0x0001;

// four Video Display Controller instances can be selected
const byte CH0	= 0x00;
const byte CH1	= 0x01;
const byte CH2	= 0x02;
const byte CH3	= 0x03;

const u_int32 ch_block = 0x20000;

class P42Display
{
	public:
		P42Display();
		uint8_t SPIReadRegister (uint8_t address, boolean debug);
		uint16_t SPIReadRegister16 (uint8_t address, boolean debug);
		void SPIWriteRegister (uint8_t address, uint8_t value, boolean debug);
		void SPIWriteRegister16 (uint8_t address, uint16_t value, boolean debug );
		void SPIWriteRegister32 (uint8_t address, uint32_t value, boolean debug );
		void SPIWriteRegister40 (uint8_t address, uint16_t source, uint16_t target, uint8_t control, boolean debug );
		uint16_t Config( uint8_t channel );
//		uint8_t SPITransferUint8_T (uint32_t address, uint8_t value, boolean debug);
//		uint16_t SPITransferWord (uint32_t address, uint8_t value, boolean debug);
		uint8_t SPIReadByte (uint8_t channel, uint32_t address);
		uint16_t SPIReadWord (uint8_t channel, uint32_t address, boolean debug);
		void SPIWriteByte (uint8_t channel, uint32_t address, uint8_t value, boolean debug );
		void SPIWriteWord (uint8_t channel, uint32_t address, uint16_t value, boolean debug );
		// Graphics commands
		void FilledRectangle (uint8_t channel, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
		void ClearScreen (uint8_t channel,  uint8_t colour );
		void SetRGBPixel (uint8_t channel, uint16_t x, uint16_t y, uint32_t colour);	// colour is 0x00rrggbb
		void SetYUVPixel (uint8_t channel, uint16_t x, uint16_t y, uint8_t colour);   			// colour is single word
		void PrintChar (uint8_t channel, char Letter, uint16_t x, uint16_t y, uint8_t colour);	// YUV colour
		void PrintString (uint8_t channel, char* Text, uint16_t x, uint16_t y, uint8_t colour);	// YUV colour
		// block move

		// Data copy
		uint8_t UARTDataToFlash ( uint32_t length, uint32_t mem_location);   // receive number of bytes on UART and write to Flash memory address
		void DisplayBMPFromFlash (uint8_t channel, uint32_t mem_location, uint16_t x, uint16_t y );	//
	private:
		void _protoline(uint8_t channel, uint16_t line, uint16_t offset, uint16_t limit, uint16_t data);
		void _printdebug (uint8_t address, uint32_t value);

};

#ifndef ATTRIBUTE_UNUSED
#if GCC_VERSION >= 3004
#  define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#else
#define ATTRIBUTE_UNUSED
#endif
#endif /* ATTRIBUTE_UNUSED */


#endif
