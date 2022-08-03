#pragma once
#include <queue>

class Mouse
{
	friend class WS_Windows;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			RPress,
			LRelease,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid,
			Enter,
			Leave
		};
	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x;
		int y;
	public:
		Event() noexcept : type(type), leftIsPressed(false), rightIsPressed(false), x(0), y(0){}
		Event(Type type, const Mouse& parent) noexcept : type(type), leftIsPressed(parent.leftIsPressed), rightIsPressed(parent.rightIsPressed), x(parent.x), y(parent.y){}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return { x,y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}

	};

public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator = (const Mouse&) = delete;
	std::pair<int, int>GetPos()const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	bool IsInWindow() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	Mouse::Event read() noexcept;
	bool IsEmpty() const noexcept;
	void Flush() noexcept;



private:
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;

private:
	static constexpr unsigned int buffersize = 16u;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	int x;
	int y;
	std::queue<Event> buffer;
};