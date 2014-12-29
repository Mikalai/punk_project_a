#ifndef _H_MICROCONTROLLER
#define _H_MICROCONTROLLER

#include <array>
#include <bitset>

enum class Signal { Zero, One };

class Pin {
public:
	Signal input() const { return m_input; }
	Signal output() const { return m_output; }
	void setInpute(Signal value);
	void setOutput(Signal value);
private:
	Signal m_input{ 0 };
	Signal m_output{ 0 };
};

template<int Size> 
class MemorySlot {
public:
	using Slot = std::bitset < Size > ;

	const Slot& read() { return m_slot }
	void write(Slot& value);

	bool bit(int pos) { return m_slot.at(pos); }
	void reset(int pos);
	void set(int pos);

private:
	Slot m_slot;
};

template<int SlotsCount, int SlotSize> 
class MemoryBank {
public:
private:
	std::array<MemorySlot<SlotSize>, SlotsCount> m_slots;
};

template<int BanksCount, int SlotsCount, int SlotSize>
class Memory {
	void setBank(int value);
	int bank() const { return m_bank; }

	void setMapping(int from, int to, std::pair<int, int> range) {
		m_mapping[]
	}
public:
	std::array<std::pair<int, int>, BanksCount> m_mapping;
	int m_cur_bank{ 0 };
	std::array<MemoryBank<SlotsCount, SlotSize>, BanksCount> m_bank;
};

class Microcontroller {
public:
	static const int T0CKL = 1;
	static const int VDD = 2;
	static const int NC1 = 3;
	static const int VSS = 4;
	static const int NC2 = 5;
	static const int RA0 = 6;
	static const int RA1 = 7;
	static const int RA2 = 8;
	static const int RA3 = 9;
	static const int RB0 = 10;
	static const int RB1 = 11;
	static const int RB2 = 12;
	static const int RB3 = 13;
	static const int RB4 = 14;
	static const int RB5 = 15;
	static const int RB6 = 16;
	static const int RB7 = 17;
	static const int RC0 = 18;
	static const int RC1 = 19;
	static const int RC2 = 20;
	static const int RC3 = 21;
	static const int RC4 = 22;
	static const int RC5 = 23;
	static const int RC6 = 24;
	static const int RC7 = 25;
	static const int OSC2 = 26;
	static const int OSC1 = 27;
	static const int MCLR = 28;
	static const int PinsCount = 29;

private:
	std::array<Pin, PinsCount> m_pins;

	Memory<0x1FF, 9> m_program;
	Memory<
};

#endif	//	_H_MICROCONTROLLER