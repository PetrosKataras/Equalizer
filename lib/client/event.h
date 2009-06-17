
/* Copyright (c) 2006-2009, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 
 
   Various event-related definitions.
*/

#ifndef EQ_EVENT_H
#define EQ_EVENT_H

#include <eq/client/renderContext.h> // used as member

#include <eq/base/base.h>
#include <eq/base/log.h>

namespace eq
{
    /** 
     * Yet another key code table to report keys in a window system
     * independent way. Ordinary keys (letters, numbers, etc) are reported
     * using the corresponding ascii code. The naming is oriented on the X11
     * keysym naming.
     */
    enum KeyCode
    {
        KC_ESCAPE = 256,
        KC_BACKSPACE,
        KC_RETURN,
        KC_TAB,
        KC_HOME,
        KC_LEFT,
        KC_UP,
        KC_RIGHT,
        KC_DOWN,
        KC_PAGE_UP,
        KC_PAGE_DOWN,
        KC_END,
        KC_F1,
        KC_F2,
        KC_F3,
        KC_F4,
        KC_F5,
        KC_F6,
        KC_F7,
        KC_F8,
        KC_F9,
        KC_F10,
        KC_F11,
        KC_F12,
        KC_F13,
        KC_F14,
        KC_F15,
        KC_F16,
        KC_F17,
        KC_F18,
        KC_F19,
        KC_F20,
        KC_F21,
        KC_F22,
        KC_F23,
        KC_F24,
        KC_SHIFT_L,
        KC_SHIFT_R,
        KC_CONTROL_L,
        KC_CONTROL_R,
        KC_ALT_L,
        KC_ALT_R,
        KC_VOID = 0xFFFFFF /* == XK_VoidSymbol */
    };

    /**
     * Mouse pointer button definition. The enums are defined as masks, so that
     * the state of all buttons can be OR'd using the same enum.
     */

    enum PointerButton
    {
        PTR_BUTTON_NONE = EQ_BIT_NONE,
        PTR_BUTTON1     = EQ_BIT1,
        PTR_BUTTON2     = EQ_BIT2,
        PTR_BUTTON3     = EQ_BIT3,
        PTR_BUTTON4     = EQ_BIT4,
        PTR_BUTTON5     = EQ_BIT5
    };

    struct ResizeEvent
    {
        int32_t x; //<! relative to parent
        int32_t y;
        int32_t w;
        int32_t h;
        float dw;  //<! view only: relative to baseline
        float dh;
    };
    struct PointerEvent
    {
        int32_t x;             //<! relative to entity (window)
        int32_t y;
        int32_t dx;
        int32_t dy;
        uint32_t buttons;      //<! current state of all buttons
        uint32_t button;       //<! fired button
    };
    struct KeyEvent
    {
        uint32_t key; // KC_? for special keys, ascii code otherwise
        // TODO modifier state
    };

    struct Statistic
    {
        enum Type // Also update string table in event.cpp
        {
            NONE = 0,
            CHANNEL_CLEAR,
            CHANNEL_DRAW,
            CHANNEL_DRAW_FINISH,
            CHANNEL_ASSEMBLE,
            CHANNEL_READBACK,
            CHANNEL_TRANSMIT,
            CHANNEL_TRANSMIT_NODE,
            CHANNEL_WAIT_FRAME,
            CHANNEL_COMPRESS,
            WINDOW_FINISH,
            WINDOW_SWAP_BARRIER,
            WINDOW_SWAP,
            WINDOW_THROTTLE_FRAMERATE,
            PIPE_IDLE,
            NODE_TRANSMIT,
            NODE_COMPRESS,
            CONFIG_START_FRAME,
            CONFIG_FINISH_FRAME,
            CONFIG_WAIT_FINISH_FRAME,
            TYPE_ALL          // must be last
        };

        Type     type;
        uint32_t frameNumber;
        uint32_t task;
        union
        {
            int64_t  startTime;
            int64_t  idleTime;
        };
        union
        {
            int64_t  endTime;
            int64_t  totalTime;
        };
        float ratio; // compression ratio
        char resourceName[32];
    };

    struct MagellanEvent
    {
        uint32_t button;       //<! fired button
        uint32_t buttons;      //<! current state of all buttons
        int16_t xAxis;
        int16_t yAxis;
        int16_t zAxis;
        int16_t xRotation;
        int16_t yRotation;
        int16_t zRotation;
    };

#   define EQ_USER_EVENT_SIZE 64
    struct UserEvent
    {
        char data[ EQ_USER_EVENT_SIZE ];
    };

    struct Event
    {
        EQ_EXPORT Event();

        enum Type // Also update string table in event.cpp
        {
            EXPOSE = 0,
            WINDOW_RESIZE,
#ifdef EQ_USE_DEPRECATED
            RESIZE = WINDOW_RESIZE,
#endif
            WINDOW_CLOSE,
            WINDOW_HIDE,
            WINDOW_SHOW,
            WINDOW_SCREENSAVER,
            POINTER_MOTION,
            POINTER_BUTTON_PRESS,
            POINTER_BUTTON_RELEASE,
            KEY_PRESS,
            KEY_RELEASE,
            CHANNEL_RESIZE,
            STATISTIC,
            VIEW_RESIZE,
            EXIT,
            MAGELLAN_AXIS,
            UNKNOWN,
            FILL1,  // some buffer for binary-compatible patches
            FILL2,
            FILL3,
            FILL4,
            FILL5,
            USER,
            ALL // must be last
        };

        uint32_t type;
        uint32_t originator;

        union // event data
        {
            ResizeEvent   resize;
            ResizeEvent   show;
            ResizeEvent   hide;
            
            PointerEvent  pointer;
            PointerEvent  pointerMotion;
            PointerEvent  pointerButtonPress;
            PointerEvent  pointerButtonRelease;

            KeyEvent      key;
            KeyEvent      keyPress;
            KeyEvent      keyRelease;

            Statistic     statistic;
            MagellanEvent magellan;

            UserEvent     user;
        };
     
        RenderContext context; //<! The last rendering context at (x,y)
    };

    EQ_EXPORT std::ostream& operator << ( std::ostream&, const Event& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const Event::Type& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const ResizeEvent& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const PointerEvent& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const KeyEvent& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const Statistic& );
    EQ_EXPORT std::ostream& operator << ( std::ostream&, const MagellanEvent& );
}

#endif // EQ_EVENT_H

