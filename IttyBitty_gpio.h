/**********************************************************************************
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_bytes.h"
#include "IttyBitty_registers.h"


#define TRISTATE_INPUT INPUT

#define L LOW		// I/O low state; 0x0
#define H HIGH		// I/O high state; 0x1

#define HIGH_Z 0x0	// (Tri-state) input high impedance / disconnected state
#define DISCONNECTED HIGH_Z


namespace IttyBitty
{
	typedef SIZE PIN_NUMBER;

	struct _PortRegisters;
	typedef struct _PortRegisters _portregisters_t, PortReg, PORTREG, * PPORTREG, & RPORTREG, ** PPPORTREG, && RRPORTREG;
	typedef const struct _PortRegisters CPORTREG, * PCPORTREG, & RCPORTREG, ** PPCPORTREG;

	struct _Port;
	typedef struct _Port _port_t, Port, PORT, * PPORT, & RPORT, ** PPPORT, && RRPORT;
	typedef const struct _Port CPORT, * PCPORT, & RCPORT, ** PPCPORT;
	
	struct GPIO;
	typedef GPIO _gpio_t, * PGPIO, & RGPIO, ** PPGPIO, && RRGPIO;
	typedef const GPIO CGPIO, * PCGPIO, & RCGPIO, ** PPCGPIO;


	ENUM PinModeBasic : BYTE
	{
		Input	= INPUT,
		Output	= OUTPUT,
		PullUp	= INPUT_PULLUP
	};

	ENUM PinMode : BYTE
	{
		// Input mode states
		TriStateInput	= 0x0,	// 00b; PinModeBasic::Input OR HIGH_Z << PinModeBasic::Input
		BinaryInput		= 0x2,	// 10b; PinModeBasic::Input OR INPUT_PULLUP << PinModeBasic::Input

		// Output mode states
		CurrentSink		= 0x1,	// 01b; PinModeBasic::Output OR LOW << PinModeBasic::Output
		CurrentSource	= 0x3,	// 11b; PinModeBasic::Output OR HIGH << PinModeBasic::Output
	};


	STRUCT _PortRegisters
	{
	private:

		_PortRegisters()  : DirectionReg(ByteField::NULL_OBJECT()), OutputReg(ByteField::NULL_OBJECT()), InputReg(ByteField::NULL_OBJECT()) { }


	public:

		_PortRegisters(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg) 
			: DirectionReg(directionReg), OutputReg(outputReg), InputReg(inputReg) { }

		_PortRegisters(RVBYTE directionRegAddr, RVBYTE outputRegAddr, RVBYTE inputRegAddr) 
		{
			this->DirectionReg	= ByteField((RBYTE)directionRegAddr);
			this->OutputReg 	= ByteField((RBYTE)outputRegAddr);
			this->InputReg		= ByteField((RBYTE)inputRegAddr);
		}

		_PortRegisters(RCPORTREG other)  : DirectionReg(other.DirectionReg), OutputReg(other.OutputReg), InputReg(other.InputReg) { }

		VIRTUAL ~_PortRegisters() { }

		STATIC RPORTREG NULL_OBJECT()
		{
			STATIC PORTREG NULL_PORTREG = _PortRegisters();
			return NULL_PORTREG;
		}

		VIRTUAL RPORTREG operator=(RCPORTREG other) 
		{
			this->DirectionReg	= ByteField(other.DirectionReg);
			this->OutputReg 	= ByteField(other.OutputReg);
			this->InputReg		= ByteField(other.InputReg);

			return *this;
		}


		RREG8 DirectionReg	= ByteField::NULL_OBJECT();
		RREG8 OutputReg 	= ByteField::NULL_OBJECT();
		RREG8 InputReg		= ByteField::NULL_OBJECT();
	};


	STRUCT _Port
	{
	public:	

		_Port() : Registers(PortReg::NULL_OBJECT()) { }
		
		_Port(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg) 
		{
			 this->Registers = PortReg(directionReg, outputReg, inputReg);
		}

		_Port(RVBYTE directionRegAddr, RVBYTE outputRegAddr, RVBYTE inputRegAddr) 
		{
			 this->Registers = PortReg(directionRegAddr, outputRegAddr, inputRegAddr);
		}

		_Port(RCPORT other)
		{
			this->Registers = other.Registers;
		}

		VIRTUAL ~_Port() { }

		STATIC RPORT NULL_OBJECT()
		{
			STATIC PORT NULL_PORT = _Port();
			return NULL_PORT;
		}

		VIRTUAL RPORT operator=(RCPORT other) 
		{
			this->Registers = other.Registers;

			return *this;
		}

		VIRTUAL BIT operator[](PIN_NUMBER p) const
		{
			return this->ReadPin(p);
		}

		VIRTUAL BITREF operator[](PIN_NUMBER p)
		{
			return this->PinState(p);
		}

		VIRTUAL PinMode GetPinMode(PIN_NUMBER p) const
		{
			return (PinMode)((BIT)Registers.DirectionReg[p] OR (BIT)Registers.OutputReg[p] SHL 1);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, PinMode mode = PinMode::CurrentSink)
		{
			Registers.DirectionReg[p]	= MASK((BYTE)mode, OUTPUT);
			Registers.OutputReg[p]		= MASK((BYTE)mode, INPUT_PULLUP);
		}

		VIRTUAL VOID SetPinModeBasic(PIN_NUMBER p, PinModeBasic basicMode = PinModeBasic::Output)
		{
			this->SetPinMode(p, (PinMode)basicMode);
		}

		VIRTUAL BIT ReadPin(PIN_NUMBER p) const
		{
			return Registers.InputReg[p];
		}

		VIRTUAL BITREF PinState(PIN_NUMBER p) const
		{
			return Registers.OutputReg[p];
		}

		VIRTUAL VOID SetPin(PIN_NUMBER p) const
		{
			Registers.OutputReg[p] = 1;
		}

		VIRTUAL VOID ResetPin(PIN_NUMBER p) const
		{
			Registers.OutputReg[p] = 0;
		}
		

	protected:

		RPORTREG Registers = PortReg::NULL_OBJECT();
	};
	
	EXTERN RPORT NULL_PORT;

	
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	struct _Pin;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using _pin_t = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using Pin = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using PIN = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using PPIN = struct _Pin<pin_number, port> *;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using RPIN = struct _Pin<pin_number, port> &;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using PPPIN = struct _Pin<pin_number, port> **;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using RRPIN = struct _Pin<pin_number, port> &&;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using CPIN = const struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using PCPIN = const struct _Pin<pin_number, port> *;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using RCPIN = const struct _Pin<pin_number, port> &;
	template<PIN_NUMBER pin_number = 0x0, RPORT port = NULL_PORT>
	using PPCPIN = const struct _Pin<pin_number, port> **;


	template<PIN_NUMBER pin_number, RPORT port>
	STRUCT _Pin
	{
	public:

		_Pin() { }

		VIRTUAL ~_Pin() { }

		STATIC PinMode Mode()
		{
			return port.GetPinMode(pin_number);
		}

		STATIC VOID Mode(PinMode mode)
		{
			port.SetPinMode(pin_number, mode);
		}

		STATIC VOID BasicMode(PinModeBasic basicMode)
		{
			port.SetPinModeBasic(pin_number, basicMode);
		}

		STATIC BIT Read()
		{
			return port.ReadPin(pin_number);
		}

		STATIC VOID Set()
		{
			return port.SetPin(pin_number);
		}

		STATIC VOID Reset()
		{
			return port.ResetPin(pin_number);
		}

		STATIC VOID Clear()
		{
			return port.ResetPin(pin_number);
		}
	};
	
	
#define DECLARE_PORT(port_letter) RPORT Port##port_letter = Port::NULL_OBJECT(); 
#define INITIALIZE_PORT(port_letter) this->Port##port_letter = Port((RVBYTE)DDR##port_letter, (RVBYTE)PORT##port_letter, (RVBYTE)PIN##port_letter);


	STRUCT GPIO FINAL
	{
	private:

		GPIO()
		{
		#ifdef PORTA
			INITIALIZE_PORT(A)
		#endif

		#ifdef PORTB
			INITIALIZE_PORT(B)
		#endif

		#ifdef PORTC
			INITIALIZE_PORT(C)
		#endif

		#ifdef PORTD
			INITIALIZE_PORT(D)
		#endif

		#ifdef PORTE
			INITIALIZE_PORT(E)
		#endif

		#ifdef PORTF
			INITIALIZE_PORT(F)
		#endif

		#ifdef PORTG
			INITIALIZE_PORT(G)
		#endif

		#ifdef PORTH
			INITIALIZE_PORT(H)
		#endif
		}


	public:

		~GPIO()
		{
			delete[] _Ports;
		}
		
		STATIC RGPIO Instance()
		{
			STATIC GPIO INSTANCE = GPIO();
			return INSTANCE;
		}
		

	#ifdef PORTA
		DECLARE_PORT(A)
	#endif

	#ifdef PORTB
		DECLARE_PORT(B)
	#endif

	#ifdef PORTC
		DECLARE_PORT(C)
	#endif

	#ifdef PORTD
		DECLARE_PORT(D)
	#endif

	#ifdef PORTE
		DECLARE_PORT(E)
	#endif

	#ifdef PORTF
		DECLARE_PORT(F)
	#endif

	#ifdef PORTG
		DECLARE_PORT(G)
	#endif

	#ifdef PORTH
		DECLARE_PORT(H)
	#endif

	private:

		PPCPORT _Ports;
	};
}


extern IttyBitty::RGPIO IO;


#define DECLARE_PINS(port_letter) extern IttyBitty::PIN<0, IO.Port##port_letter> Pin##port_letter##1;
#define INITIALIZE_PINS(port_letter) Pin##port_letter##1 = IttyBitty::Pin<0, IO.Port##port_letter>();


//#ifdef PORTA
//	DECLARE_PINS(A)
//#endif
//
//#ifdef PORTB
//	DECLARE_PINS(B)
//#endif
//
//#ifdef PORTC
//	DECLARE_PINS(C)
//#endif
//
//#ifdef PORTD
//	DECLARE_PINS(D)
//#endif
//
//#ifdef PORTE
//	DECLARE_PINS(E)
//#endif
//
//#ifdef PORTF
//	DECLARE_PINS(F)
//#endif
//
//#ifdef PORTG
//	DECLARE_PINS(G)
//#endif
//
//#ifdef PORTH
//	DECLARE_PINS(H)
//#endif


#endif
