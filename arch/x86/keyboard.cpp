#include <keyboard.h>

#include <asm.h>
#include <idt.h>
#include <registers.h>
#include <kernel/queue.h>
#include <kernel/types.h>

static bool keyboard_is_running = false;
static conix::kernel::arch::x86::keyboard* k = nullptr;

extern "C" void keyboard_int_handler(struct regs *r)
{
        if (k != nullptr) {
                k->push_key(inb(KEYBOARD_DATA_REGISTER));
        }
}

namespace conix {
namespace kernel {
namespace arch {
namespace x86 {

keyboard::keyboard()
{
        if (keyboard_is_running) {
                valid_keyboard = false;
                return;
        }

        keyboard_is_running = true;
        valid_keyboard = true;
        k = this;
}

keyboard::~keyboard()
{
        if (valid_keyboard) {
                keyboard_is_running = false;
        }
        disable_int();
        k = nullptr;
}

void keyboard::enable_int()
{
        irq_install_handler(KEYBOARD_IRQ_NUMBER, keyboard_int_handler);
}

void keyboard::disable_int()
{
        irq_unintall_handler(KEYBOARD_IRQ_NUMBER);
}

bool keyboard::empty()
{
        return buffer.empty();
}

size_t keyboard::get_key_number()
{
        if (buffer.empty()) {
                keyboard_status = status::buffer_error;
                return 0;
        } else {
                keyboard_status = status::okay;
        }

        size_t key = buffer.front();
        buffer.pop();

        if (key >= 129 || key < 157) {
                keyboard_status = status::key_released;
        } else {
                keyboard_status = status::okay;
        }

        return key;
}

char keyboard::get_key(size_t code)
{
        char c;
        bool is_uppercase = shift_pressed ^ caps_lock_mode;

        if (code < sizeof(pressed_key_lowcase) && !is_uppercase) {
                c = pressed_key_lowcase[code];
        } else if (code < sizeof(pressed_key_uppercase) && is_uppercase) {
                c = pressed_key_uppercase[code];
        } else {
                c = 0;
        }

        return c;
}

char keyboard::get_key()
{
        return get_key(get_key_number());
}

void keyboard::push_key(size_t code)
{
        switch (code) {
        case CTRL_PRESS:
                ctrl_pressed = true;
                break;
        case LSHIFT_PRESS:
        case RSHIFT_PRESS:
                shift_pressed = true;
                break;
        case ALT_PRESS:
                alt_pressed = true;
                break;
        case CAPS_LOCK_PRESS:
                caps_lock_mode = !caps_lock_mode;
                break;
        case NUM_LOCK_PRESS:
                num_lock_mode = true;
                break;

        case CTRL_RELEASE:
                ctrl_pressed = true;
                break;
        case LSHIFT_RELEASE:
        case RSHIFT_RELEASE:
                shift_pressed = false;
                break;
        case ALT_RELEASE:
                alt_pressed = false;
                break;
        case NUM_LOCK_RELEASE:
                num_lock_mode = false;
                break;
        }

        buffer.push(code);
}

keyboard::status keyboard::get_status() const
{
        return keyboard_status;
}

}; // x86
}; // arch
}; // kernel
}; // conix
