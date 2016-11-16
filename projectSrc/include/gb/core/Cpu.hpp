#ifndef _CPU_HPP
# define _CPU_HPP

#include "Timer.hpp"
#include "Memory.hpp"
#include "Rom.hpp"
#include "register.hpp"
#include "opcode.hpp"
#include "htype.hpp"

#define NB_OPCODE 255
#define NOP_OPCODE 0

#define LENGTH_ADDR 0x01

template <typename T1, typename T2, typename T3>
inline bool testAdd(T1 op1, T2 op2, T3 mask)
{
	if ((op1 + op2) & mask)
		return true;
	return false;
}

template <typename T1, typename T2, typename T3>
inline bool testSub(T1 op1, T2 op2, T3 mask)
{
	if ((op1 - op2) & mask)
		return true;
	return false;
}

class Machine;

class Cpu_z80
{
	friend Machine;
	bool _tmp;
	/*
	** ################################################################
	** CREATE Singleton
	** ################################################################
	*/
	private:
		Cpu_z80(Memory *memory);
		virtual ~Cpu_z80(void);
		static Cpu_z80					_instance;

	/*
	** ################################################################
	** METHOD opcode
	** ################################################################
	*/

	public:
		uint8_t							nbCycleNextOpCode(void);
		uint8_t							executeNextOpcode(void);
		void							setStepState(bool state);
		bool							getStepState(void);
		void							setHoldIME(bool state);
		bool							getIME(void);
		bool							getHoldIME(void);
		uint32_t						getClockSpeed(void);

	private:
		t_opcode						_getOpcode(uint8_t opcode);
		uint8_t							_getCycleOpcode(void);
		uint16_t						_getDataOpcode(void);
		uint8_t							_getLengthDataOpcode(void);
		void							_setDataOpcode(void);
		void							_setOpcodeMap(void);
		void							_setIME(bool state);
		void							_setCbOpcodeMap(void);

	/*
	** ################################################################
	** METHOD
	** ################################################################
	*/

	public:
		std::array<uint32_t, 4>			getArrayFrequency();
		void							init(htype hardware = GB);

	/*
	** ################################################################
	** METHOD Opcode
	** ################################################################
	*/

		void							XOR(uint8_t val);
		void							AND(uint8_t val);
		void							OR(uint8_t val);
		void							CP(uint8_t val);
		void							LD_x_y(uint16_t *dst, uint16_t src);
		void							LD_x_y(uint8_t *dst, uint8_t src);
		void							inc(uint8_t *val);
		void							dec(uint8_t *val);
		void							add(uint8_t val);
		void							adc(uint8_t val);
		void							sub(uint8_t val);
		void							sbc(uint8_t val);
		void							RST(uint16_t addr);

		void							NOP();			//0x00
		void							LD_BC_n();		//0x01
		void							LD_BC_A();		//0x02
		void							INC_BC();		//0x03
		void							INC_B();		//0x04
		void							DEC_B();		//0x05
		void							LD_B_n();		//0x06
		void							RLCA();			//0x07
		void							LD_n_SP();		//0x08   
		void							ADD_HL_BC();	//0x09
		void							LD_A_BC();		//0x0a
		void							DEC_BC();		//0x0b
		void							INC_C();		//0x0c
		void							DEC_C();		//0x0d
		void							LD_C_n();		//0x0e 
		void							RRCA();			//0x0f
		void							STOP();			//0x10     Not done yet
		void							LD_DE_n();		//0x11
		void							LD_DE_A();		//0x12
		void							INC_DE();		//0x13
		void							INC_D();		//0x14
		void							DEC_D();		//0x15
		void							LD_D_n();		//0x16
		void							RLA();			//0x17
		void							JR_n();			//0x18 
		void							ADD_HL_DE();	//0x19
		void							LD_A_DE();		//0x1a
		void							DEC_DE();		//0x1b
		void							INC_E();		//0x1c
		void							DEC_E();		//0x1d
		void							LD_E_n();		//0x1e
		void							RRA();			//0x1f
		void							JR_NZ_n();		//0x20
		void							LD_HL_nn();		//0x21
		void							LD_HLI_A();		//0x22
		void							INC_HL();		//0x23
		void							INC_H();		//0x24
		void							DEC_H();		//0x25
		void							LD_H_n();		//0x26
		void							DAA();			//0x27
		void							JR_Z_n();		//0x28
		void							ADD_HL_HL();	//0x29
		void							LD_A_HLI();		//0x2a
		void							DEC_HL();		//0x2b
		void							INC_L();		//0x2c
		void							DEC_L();		//0x2d
		void							LD_L_n();		//0x2e
		void							CPL();			//0x2f
		void							JR_NC_n();		//0x30 
		void							LD_SP_n();		//0x31 
		void							LD_HLD_A();		//0x32
		void							INC_SP();		//0x33 
		void							INC_HLF();		//0x34
		void							DEC_HLF();		//0x35
		void							LD_HL_n();		//0x36
		void							SCF();			//0x37
		void							JR_C_n();		//0x38
		void							ADD_HL_SP();	//0x39
		void							LD_A_HLD();		//0x3a
		void							DEC_SP();		//0x3b 
		void							INC_A();		//0x3c
		void							DEC_A();		//0x3d
		void							LD_A_n();		//0x3e
		void							CCF();			//0x3f
		void							LD_B_B();		//0x40
		void							LD_B_C();		//0x41
		void							LD_B_D();		//0x42
		void							LD_B_E();		//0x43
		void							LD_B_H();		//0x44
		void							LD_B_L();		//0x45
		void							LD_B_HL();		//0x46
		void							LD_B_A();		//0x47
		void							LD_C_B();		//0x48
		void							LD_C_C();		//0x49
		void							LD_C_D();		//0x4a
		void							LD_C_E();		//0x4b
		void							LD_C_H();		//0x4c
		void							LD_C_L();		//0x4d
		void							LD_C_HL();		//0x4e
		void							LD_C_A();		//0x4f
		void							LD_D_B();		//0x50
		void							LD_D_C();		//0x51
		void							LD_D_D();		//0x52
		void							LD_D_E();		//0x53
		void							LD_D_H();		//0x54
		void							LD_D_L();		//0x55
		void							LD_D_HL();		//0x56
		void							LD_D_A();		//0x57
		void							LD_E_B();		//0x58
		void							LD_E_C();		//0x59
		void							LD_E_D();		//0x5a
		void							LD_E_E();		//0x5b
		void							LD_E_H();		//0x5c
		void							LD_E_L();		//0x5d
		void							LD_E_HL();		//0x5e
		void							LD_E_A();		//0x5f
		void							LD_H_B();		//0x60
		void							LD_H_C();		//0x61
		void							LD_H_D();		//0x62
		void							LD_H_E();		//0x63
		void							LD_H_H();		//0x64
		void							LD_H_L();		//0x65
		void							LD_H_HL();		//0x66
		void							LD_H_A();		//0x67
		void							LD_L_B();		//0x68
		void							LD_L_C();		//0x69
		void							LD_L_D();		//0x6a
		void							LD_L_E();		//0x6b
		void							LD_L_H();		//0x6c
		void							LD_L_L();		//0x6d
		void							LD_L_HL();		//0x6e
		void							LD_L_A();		//0x6f
		void							LD_HL_B();		//0x70
		void							LD_HL_C();		//0x71
		void							LD_HL_D();		//0x72
		void							LD_HL_E();		//0x73
		void							LD_HL_H();		//0x74
		void							LD_HL_L();		//0x75
		void							HALT();			//0x76 Not done yet
 		void							LD_HL_A();		//0x77
		void							LD_A_B();		//0x78
		void							LD_A_C();		//0x79
		void							LD_A_D();		//0x7a
		void							LD_A_E();		//0x7b
		void							LD_A_H();		//0x7c
		void							LD_A_L();		//0x7d
		void							LD_A_HL();		//0x7e
		void							LD_A_A();		//0x7f
		void							ADD_A_B();		//0x80
		void							ADD_A_C();		//0x81
		void							ADD_A_D();		//0x82
		void							ADD_A_E();		//0x83
		void							ADD_A_H();		//0x84
		void							ADD_A_L();		//0x85
		void							ADD_A_HL();		//0x86
		void							ADD_A_A();		//0x87
		void							ADC_A_B();		//0x88
		void							ADC_A_C();		//0x89
		void							ADC_A_D();		//0x8a
		void							ADC_A_E();		//0x8b
		void							ADC_A_H();		//0x8c
		void							ADC_A_L();		//0x8d
		void							ADC_A_HL();		//0x8e
		void							ADC_A_A();		//0x8f
		void							SUB_B();		//0x90
		void							SUB_C();		//0x91
		void							SUB_D();		//0x92
		void							SUB_E();		//0x93
		void							SUB_H();		//0x94
		void							SUB_L();		//0x95
		void							SUB_HL();		//0x96
		void							SUB_A();		//0x97
		void							SBC_A_B();		//0x98
		void							SBC_A_C();		//0x99
		void							SBC_A_D();		//0x9a
		void							SBC_A_E();		//0x9b
		void							SBC_A_H();		//0x9c
		void							SBC_A_L();		//0x9d
		void							SBC_A_HL();		//0x9e
		void							SBC_A_A();		//0x9f
		void							AND_B();		//0xa0
		void							AND_C();		//0xa1
		void							AND_D();		//0xa2
		void							AND_E();		//0xa3
		void							AND_H();		//0xa4
		void							AND_L();		//0xa5
		void							AND_HL();		//0xa6
		void							AND_A();		//0xa7
		void							XOR_B();		//0xa8
		void							XOR_C();		//0xa9
		void							XOR_D();		//0xaa
		void							XOR_E();		//0xab
		void							XOR_H();		//0xac
		void							XOR_L();		//0xad
		void							XOR_HL();		//0xae
		void							XOR_A();		//0xaf
		void							OR_B();			//0xb0
		void							OR_C();			//0xb1
		void							OR_D();			//0xb2
		void							OR_E();			//0xb3
		void							OR_H();			//0xb4
		void							OR_L();			//0xb5
		void							OR_HL();		//0xb6
		void							OR_A();			//0xb7
		void							CP_B();			//0xb8
		void							CP_C();			//0xb9
		void							CP_D();			//0xba
		void							CP_E();			//0xbb
		void							CP_H();			//0xbc
		void							CP_L();			//0xbd
		void							CP_HL();		//0xbe
		void							CP_A();			//0xbf
		void							RET_NZ();		//0xc0  
		void							POP_BC();		//0xc1    
		void							JP_NZ_n();		//0xc2
		void							JP_n();			//0xc3
		void							CALL_NZ_n();	//0xc4    
		void							PUSH_BC();		//0xc5
		void							ADD_A_n();		//0xc6    
		void							RST_00H();		//0xc7    
		void							RET_Z();		//0xc8   
		void							RET();			//0xc9  
		void							JP_Z_n();		//0xca   
		void							PREFIX_CB();	//0xcb     Not done yet
		void							CALL_Z_n();		//0xcc     
		void							CALL_n();		//0xcd     
		void							ADC_A_n();		//0xce
		void							RST_08H();		//0xcf   
		void							RET_NC();		//0xd0    
		void							POP_DE();		//0xd1    
		void							JP_NC_n();		//0xd2    
		void							CALL_NC_n();	//0xd4  
		void							PUSH_DE();		//0xd5
		void							SUB_n();		//0xd6     
		void							RST_10H();		//0xd7 
		void							RET_C();		//0xd8     
		void							RETI();			//0xd9     
		void							JP_C_n();		//0xda 
		void							CALL_C_n();		//0xdc     
		void							SBC_A_n();		//0xde
		void							RST_18H();		//0xdf   
		void							LDH_n_A();		//0xe0
		void							POP_HL();		//0xe1     
		void							LD_CC_A();		//0xe2  
		void							PUSH_HL();		//0xe5
		void							AND_n();		//0xe6  
		void							RST_20H();		//0xe7    
		void							ADD_SP_n();		//0xe8 
		void							JP_HL();		//0xe9
		void							LD_n_A();		//0xea
		void							XOR_n();		//0xee 
		void							RST_28H();		//0xef
		void							LDH_A_n();		//0xf0
		void							POP_AF();		//0xf1
		void							LD_A_CC();		//0xf2    
		void							DI();			//0xf3     Not done yet
		void							PUSH_AF();		//0xf5
		void							OR_n();			//0xf6  
		void							RST_30H();		//0xf7     
		void							LD_HL_SP_n();	//0xf8  
		void							LD_SP_HL();		//0xf9 
		void							LD_A_b();		//0xfa
		void							EI();			//0xfb     Not done yet
		void							CP_n();			//0xfe 
		void							RST_38H();		//0xff  		

	/*
	** ################################################################
	** METHOD CB opcode
	** ################################################################
	*/
		void							rotate_left(uint8_t *reg);
		void							RLC_B();		//0x00
	
	private:
		void							_resetPtrAddr(void);
		void							_loadPtr(uint16_t pc);
		void							_nextPtr(void);
						
	/*
	** ################################################################
	** METHOD setBits
	** ################################################################
	*/
						
	private:
		void							_setLowBit(uint16_t addr, uint8_t bit);
		void 							_setHightBit(uint16_t addr, uint8_t bit);

	/*
	** ################################################################
	** METHOD CPU
	** ################################################################
	*/
	public:
		void							execInterrupt(void);
		bool							isInterrupt(void);
		bool							_getInterrupt(uint8_t interrupt);
		bool							getHalt(void);
		bool							getStop(void);

	private:
		void								_resetInterrupt(void);
		void								_setStop(bool state);
		void								_setHalt(bool state);


	/*
	** ################################################################
	** ATTRIBUTE
	** ################################################################
	*/
	private:
		unsigned int					_ptrAddr;
		Memory							*_memory;
		std::array<uint32_t, 4>			_arrayFrequency {{static_cast<uint32_t>(4096), static_cast<uint32_t>(16385), static_cast<uint32_t>(65536), static_cast<uint32_t>(262144) }};
		t_opcode						_opcodeInProgress;
		bool							_stepState;
		bool							_halt = false;
		bool							_stop = false;
		bool							_IME = true;
		bool							_holdIME = true;

	public:
		unsigned int					_addrLength;
		t_register						_cpuRegister;
		
};

#endif
