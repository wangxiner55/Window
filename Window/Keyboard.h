#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class U_Windows;

public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() :type(Type::Invalid), code(0u){}
		Event(Type type, unsigned char code)noexcept :code(code), type(type){}
		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		bool IsValid() const noexcept
		{
			return type == Type::Invalid;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}


	};

public:
	Keyboard() = default;  //invoke default constructor
	Keyboard(const Keyboard&) = delete;  // copy constructor 
	Keyboard& operator =(const Keyboard&) = delete;    // copy assignment operator ¿½±´¸³ÖµÔËËã·û
	//key event
	bool KeyIsPressed(unsigned char Keycode) const noexcept;
	Event Readkey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;
	// char event
	char ReadChar()noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar()noexcept;
	void Flush() noexcept;
	//autorepeat control
	void EnableAutorepeat()noexcept;
	void DisableAutorepeat() noexcept;
	bool AutoreapectIsEnable() noexcept;
private:
	void OnKeyPressed(unsigned char Keycode) noexcept;
	void OnKeyReleased(unsigned char Keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;



};


