/* SLiM - Simple Login Manager
   Copyright (C) 1997, 1998 Per Liden
   Copyright (C) 2004-06 Simone Rota <sip@varlock.com>
   Copyright (C) 2004-06 Johannes Winkelmann <jw@tks6.net>
   Copyright (C) 2013 Nobuhiro Iwamatsu <iwamatsu@nigauri.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
*/

#ifndef _PANEL_H_
#define _PANEL_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xft/Xft.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <string>

#include "switchuser.h"
#include "log.h"
#include "image.h"
#include "coord.h"
struct Rectangle {
    int x;
    int y;
    unsigned int width;
    unsigned int height;

    Rectangle() : x(0), y(0), width(0), height(0) {};
    Rectangle(int x, int y, unsigned int width, unsigned int height) :
              x(x), y(y), width(width), height(height) {};
    bool is_empty() const {
            return width == 0 || height == 0;
    }
};

class Panel {
public:
    enum ActionType {
        Login,
        Lock,
        Console,
        Reboot,
        Halt,
        Exit,
        Suspend
    };
    enum FieldType {
        Get_Name,
        Get_Passwd
    };
    enum PanelType {
        Mode_DM,
        Mode_Lock
    };

    Panel(Display* dpy, int scr, Window root, Cfg* config,
          const std::string& themed, const std::string& themeName,
          PanelType panel_mode);
    ~Panel();
    void OpenPanel();
    void ClosePanel();
    void ClearPanel();
    void WrongPassword(int timeout);
    void Message(const std::string& text);
    void Error(const std::string& text);
    void EventHandler(const FieldType& curfield);
    std::string getSession();
    ActionType getAction(void) const;

    void Reset(void);
    void ResetName(void);
    void ResetPasswd(void);
    void SetName(const std::string& name);
    const std::string& GetName(void) const;
    const std::string& GetPasswd(void) const;
private:
    Panel();
    void Cursor(int visible);
    unsigned long GetColor(const char* colorname);
    void OnExpose(void);
    bool OnKeyPress(XEvent& event);
    void ShowText();
    void SwitchSession();
    void ShowSession();

    void SlimDrawString8(XftDraw *d, XftColor *color, XftFont *font,
                            int x, int y, const std::string& str,
                            XftColor* shadowColor,
                            int xOffset, int yOffset);

    Rectangle GetPrimaryViewport();
    void ApplyBackground(Rectangle = Rectangle());

    // Private data
    PanelType mode; // work mode
    Cfg *cfg;

    Window Win;
    Window Root;
    Display* Dpy;
    int Scr;
    int X, Y;
    GC TextGC;
    GC WinGC;
    XftFont* font;
    XftColor inputshadowcolor;
    XftColor inputcolor;
    XftColor msgcolor;
    XftColor msgshadowcolor;
    XftFont* msgfont;
    XftColor introcolor;
    XftFont* introfont;
    XftFont* welcomefont;
    XftColor welcomecolor;
    XftFont* sessionfont;
    XftColor sessioncolor;
    XftColor sessionshadowcolor;
    XftColor welcomeshadowcolor;
    XftFont* enterfont;
    XftColor entercolor;
    XftColor entershadowcolor;
    ActionType action;
    FieldType field;
    
    // Username/Password
    std::string NameBuffer;
    std::string PasswdBuffer;
    std::string HiddenPasswdBuffer;

    // screen stuff
    Rectangle viewport;

    // Configuration
    Coord input_name;
    Coord input_pass;
    Coord inputShadowOffset;
    Coord welcome;
    Coord welcome_shadow_offset;
    Coord session_shadow_offset;
    Coord intro;
    Coord username;
    Coord username_shadow_offset;
    Coord password;
    std::string welcome_message;
    std::string intro_message;

    // Pixmap data
    Pixmap PanelPixmap;

    Image* image;

    // Session handling
    std::string session_name;
    std::string session_exec;

};

#endif


