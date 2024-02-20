// Lic:
// Units/Headers/SlyvBank.hpp
// Slyvina - Banks (header)
// version: 23.11.07
// Copyright (C) 2022, 2023 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#pragma once
#include "Slyvina.hpp"
#include "SlyvEndian.hpp"

namespace Slyvina {
	namespace Units {
		SlyvClass(_Bank, Bank);
		typedef std::unique_ptr<_Bank> UBank;

		typedef void(* BankPanic)(std::string error);

		class _Bank {
		private:
			char* _buffer;
			std::shared_ptr<std::vector<char>> _xbuffer;
			bool _Expandable{ false };
			size_t _sz;
			size_t _pos{ 0 };
			Endian _endian;
			static BankPanic _DefPanic;
		public:
			BankPanic Panic{ nullptr };
			_Bank(size_t size, Endian SetEndian = Endian::Little); // NEVER create this class regularly! Always use CreateBank() in stead. Otherwise destructors can mess the entire thing up.
			_Bank(char* buf, size_t size, Endian SetEndian = Endian::Little);

			_Bank(Endian SetEndian = Endian::Little);

			~_Bank();

			static void DefineDefaultBankPanic(BankPanic p);

			void PokeChar(size_t position, char value);
			void PokeByte(size_t position, byte value);
			void PokeInt16(size_t position, int16 value);
			void PokeInt32(size_t position, int32 value); inline void PokeInt(size_t position, int32 value) { PokeInt32(position, value); }
			void PokeInt64(size_t position, int64 value);
			void PokeUInt16(size_t position, uint16 value);
			void PokeUInt32(size_t position, uint32 value);
			void PokeUInt64(size_t position, uint64 value);

			inline void Poke(size_t position, char value) { PokeChar(position, value); }
			inline void Poke(size_t position, byte value) { PokeByte(position, value); }
			inline void Poke(size_t position, int16 value) { PokeInt16(position, value); }
			inline void Poke(size_t position, int32 value) { PokeInt32(position, value); }
			inline void Poke(size_t position, int64 value) { PokeInt64(position, value); }

			inline void Poke(size_t position, uint16 value) { PokeUInt16(position, value); }
			inline void Poke(size_t position, uint32 value) { PokeUInt32(position, value); }
			inline void Poke(size_t position, uint64 value) { PokeUInt64(position, value); }

			char PeekChar(size_t position);
			byte PeekByte(size_t position);
			int16 PeekInt16(size_t position);
			int32 PeekInt32(size_t position); inline int32 PeekInt(size_t position) { return PeekInt32(position); }
			int64 PeekInt64(size_t position);
			uint16 PeekUInt16(size_t position);
			uint32 PeekUInt32(size_t position);
			uint64 PeekUInt64(size_t position);

			inline size_t Size() { if (_Expandable) return _xbuffer->size(); else return _sz; }
			inline size_t Position() { return _pos; }
			inline void Position(size_t p) { _pos = std::min(p, _sz); }
			inline bool AtEnd() { return _pos >= _sz; }

			inline char ReadChar() { return PeekChar(_pos++); }
			inline byte ReadByte() { return PeekChar(_pos++); }
			inline byte ReadByte(byte& b) { b = ReadByte(); return b; }
			inline int16 ReadInt16() { auto r = PeekInt16(_pos); _pos += sizeof(int16); return r; }
			inline int32 ReadInt32() { auto r = PeekInt32(_pos); _pos += sizeof(int32); return r; }
			inline int64 ReadInt64() { auto r = PeekInt64(_pos); _pos += sizeof(int64); return r; }
			inline uint16 ReadUInt16() { auto r = PeekUInt16(_pos); _pos += sizeof(uint16); return r; }
			inline uint32 ReadUInt32() { auto r = PeekUInt32(_pos); _pos += sizeof(uint32); return r; }
			inline uint64 ReadUInt64() { auto r = PeekUInt64(_pos); _pos += sizeof(uint64); return r; }
			inline int32 ReadInt() { return ReadInt32(); }
			inline bool ReadBoolean() { return ReadByte() > 0; }
			inline bool ReadBool() { return ReadByte() > 0; }

			/// <summary>
			/// Reads characters and puts them in a char array. Please note, there is NO protection whatsoever against overwriting memory that should not be overwritten, so handle with care!
			/// </summary>
			/// <param name="c"></param>
			/// <param name="size"></param>
			void GetChars(char* c, size_t size);

			void chcpy(char* buf, size_t pos, size_t sz);
			void chcpy(char* buf, size_t sz);

			/// <summary>
			/// Reads a string from the bank. Please note, this routine does NOT take null-termination into account!
			/// </summary>
			/// <param name="sz">The length of the string. When set to 0 it reads an uint32 value to get the size</param>
			/// <returns></returns>
			std::string ReadString(size_t sz = 0);

			/// <summary>
			/// Reads a string with null terminator.
			/// </summary>
			/// <param name="sz">When 0 it just keeps reading until the null terminator is found, otherwise it will read number of bytes regardless of the terminator</param>
			/// <returns></returns>
			std::string ReadNullString(size_t sz = 0);

			/// <summary>
			/// Reads a string with null terminator.
			/// </summary>
			/// <param name="str">String buffer</param>
			/// <param name="bufsize">Size of the string buffer</param>
			/// <param name="blocksize">Block size. If not set size of the string will be used</param>
			void ReadNullString(char* str, size_t bufsize, size_t blocksize = 0);

			inline bool Expandable() { return _Expandable; }

			inline void WriteChar(char c) { PokeChar(_pos++, c); }
			inline void WriteByte(byte b) { PokeByte(_pos++, b); }
			inline void WriteInt16(int16 i) { PokeInt16(_pos, i); _pos += sizeof(int16); }
			inline void WriteInt32(int32 i) { PokeInt32(_pos, i); _pos += sizeof(int32); }
			inline void WriteInt64(int64 i) { PokeInt64(_pos, i); _pos += sizeof(int64); }
			inline void WriteUInt32(uint32 i) { PokeUInt32(_pos, i); _pos += sizeof(uint32); }
			inline void WriteUInt64(uint64 i) { PokeUInt64(_pos, i); _pos += sizeof(uint64); }
			inline void WriteInt(int32 i) { WriteInt32(i); }

			inline void WriteString(std::string value, bool raw=false) {
				if (!raw) WriteInt32((int)value.size());
				for (int i = 0; i < value.size(); ++i) WriteChar(value[i]);
			}

			/// <summary>
			/// Writes a C style string with null terminator at the end.
			/// </summary>
			/// <param name="bufsize">If set it will make the block always as long as bufsize regardless of the length of the string</param>
			void WriteNullString(std::string str, size_t bufsize = 0);

			inline void WriteChars(const char* cb, size_t s) { for (size_t i = 0; i < s; i++) WriteChar(cb[i]); }
			inline void WriteBytes(const byte* cb, size_t s) { for (size_t i = 0; i < s; i++) WriteByte(cb[i]); }
			inline void WriteChars(std::vector<char> cb) { for (auto c : cb) WriteChar(c); }
			inline void WriteChars(std::vector<char>* cb) { for (auto c : *cb) WriteChar(c); }

			inline void Write(char c) { WriteChar(c); }
			inline void Write(byte b) { WriteByte(b); }
			inline void Write(int16 i) {WriteInt16(i); }
			inline void Write(int32 i) { WriteInt32(i); }
			inline void Write(int64 i) { WriteInt64(i); }
			inline void Write(uint32 i) { WriteUInt32(i); }
			inline void Write(uint64 i) { WriteUInt64(i); }
			inline void Write(std::string str,bool raw=false) { WriteString(str,raw); }
			inline void Write(std::vector<char> &vc) { for (char c : vc) WriteChar(c); }
			inline void Write(std::vector<byte> &vc) { for (char c : vc) WriteByte(c); }
			inline void Write(const char* cb, size_t s) { WriteChars(cb, s); }
			inline void Write(const byte* cb, size_t s) { WriteBytes(cb, s); }
			
			void WriteStringMap(StringMap sm);
			inline void Write(StringMap sm) { WriteStringMap(sm); }

			/// <summary>
			/// Copy the contents of a buffer into a regular char buffer
			/// </summary>
			/// <param name="ch"></param>
			void ToChar(char* ch);

			/// <summary>
			/// Copy the contents of a buffer into a regular char buffer! WARNING! This variant actually allocates memory in order to get the job done, but you will have to release it yourself.
			/// </summary>
			char* ToChar(); 

			/// <summary>
			/// Tries to convert the buffer into a string
			/// </summary>
			/// <returns></returns>
			std::string ToString();


			/// <summary>
			/// Will return the buffer pointer used in non-expandable banks. Please note, Banks are shared-pointers and will automatically release the buffer from the memory if there are no more references to this bank
			/// </summary>
			/// <returns></returns>
			inline char* Direct() { if (_Expandable) return nullptr; return _buffer; }

			/// <summary>
			/// Will return the buffer pointer used in expandable banks. The buffer used in expandable banks hold a shared pointer, so when the bank is disposed this buffer could live on if there are still references to it.
			/// </summary>
			/// <returns></returns>
			inline std::shared_ptr<std::vector<char>> DirectX() { if (_Expandable) return _xbuffer; return nullptr; }
		};


	Bank CreateBank(size_t size, Endian E = Endian::Little);
	Bank CreateBank(char* buf, size_t size, Endian E = Endian::Little);
	Bank CreateBank(std::vector<char>, Endian E = Endian::Little);

	/// <summary>
	/// Takes over a buffer and turns it into a bank. Please note! This routine actually copies the pointer to that buffer! Don't use this unless you know what you are doing. Also note that the memory allocated to this pointer will as a result be disposed automatically once this Bank is being disposed. If you do not want all that, this may not be the best way to go!
	/// </summary>
	/// <param name="buf"></param>
	/// <param name="size"></param>
	/// <param name="E"></param>
	/// <returns></returns>
	Bank TurnToBank(char* buf, size_t size, Endian E = Endian::Little);

	Bank CreateXBank(Endian E = Endian::Little);

	UBank CreateUBank(size_t size, Endian E = Endian::Little);
	UBank CreateUXBank();
	
	
	
	}

}