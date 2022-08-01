#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char Keycode) const noexcept
{
    return keystates[Keycode];
}

Keyboard::Event Keyboard::Readkey() noexcept
{
    if (keybuffer.size() > 0u)
    {
        Keyboard::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    else
    {
        return Keyboard::Event();
    }
}

bool Keyboard::KeyIsEmpty() const noexcept
{
    return keybuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
    keybuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
    if (charbuffer.size() > 0)
    {
        unsigned char charcode = charbuffer.front();
        charbuffer.pop();
        return charcode;
    }
    else
    return 0;
}

bool Keyboard::CharIsEmpty() const noexcept
{
    return charbuffer.empty();
}

void Keyboard::FlushChar() noexcept
{
    charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
    charbuffer = std::queue<char>();
    keybuffer = std::queue<Event>();
}

void Keyboard::EnableAutorepeat() noexcept
{
    autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
    autorepeatEnabled = false;
}

bool Keyboard::AutoreapectIsEnable() noexcept
{
    return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char Keycode) noexcept
{
    keystates[Keycode] = true;
    keybuffer.push(Keyboard::Event( Keyboard::Event::Type::Press, Keycode));
    TrimBuffer(keybuffer);


}

void Keyboard::OnKeyReleased(unsigned char Keycode) noexcept
{
    keystates[Keycode] = false;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, Keycode));
    TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
    charbuffer.push(character);
    TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
    keystates.reset();
}




template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
    while (buffer.size() > bufferSize)
    {
        buffer.pop();
    }
}