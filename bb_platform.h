// platform abstraction layer written by Brajan Bartoszewicz
//
//
// NOTES:
//  - use #define BB_PLATFORM_IMPLEMENTATION before including this file to include implementation
//  - Win32:
//     - libs required: opengl32.lib (if using opengl)
// TODO:
//  - threads
//    - thread pool too
//  - mouse wheel

#ifndef BB_PLATFORM_H_

#if defined(_WIN32)
#define BB_PLATFORM_WIN32
#endif

#ifdef BB_PLATFORM_WIN32
#include "bb_platform_win32.h"
#endif

#ifndef BB_TOOL_H_
#error "Include bb_tool library!"
#endif

#define bb_NumKeys 256
#define bb_NumButtons 128

struct bb_platform_state {
  bb_window Window;

  struct {
    bool Keys[bb_NumKeys];
    bool KeysDown[bb_NumKeys];
    bool KeysUp[bb_NumKeys];

    bool Buttons[bb_NumButtons];
    bool ButtonsDown[bb_NumButtons];
    bool ButtonsUp[bb_NumButtons];

    int MouseX;
    int MouseY;

    int MouseMoveX;
    int MouseMoveY;
  } InputState;
};

// ----------------------------------------------------------------------------
// -----------------------------IMPLEMENTATION---------------------------------
// ----------------------------------------------------------------------------
#ifdef BB_PLATFORM_IMPLEMENTATION

// NOTE(Brajan): you can define these functions to work with them in your game
// BB_PLATFORM_INIT - calls after creating window and opengl context
// BB_PLATFORM_LOOP
// BB_PLATFORM_CONFIG - calls on changing resolution etc
// BB_PLATFORM_SHUTDOWN - calls just before exiting an app

#include "gl3w.h"

#ifdef BB_PLATFORM_INIT
void BB_PLATFORM_INIT (bb_platform_state *PlatformState);
#endif

#ifdef BB_PLATFORM_LOOP
void BB_PLATFORM_LOOP (float DeltaTime);
#endif

#ifdef BB_PLATFORM_CONFIG
void BB_PLATFORM_CONFIG ();
#endif

#ifdef BB_PLATFORM_SHUTDOWN
void BB_PLATFORM_SHUTDOWN ();
#endif

static bb_platform_state bb_PlatformState;

#ifdef BB_PLATFORM_WIN32
int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR     LpCmdLine,
        int       CmdShow) {
#else
int
main(int ArgumentsNumber, char **Arguments) {
#endif
  bb_opengl_context OpenGLContext;
  
  bool IsRunning = true;
  
  bb_OpenWindow(&bb_PlatformState.Window, "Voxel Engine", 0, 0, 1024, 576, bb_FlagDefault | bb_FlagResizable);
  bb_CreateOpenGLContext(&bb_PlatformState.Window, &OpenGLContext);

  // gl3w
  gl3wInit();

  // game init
#ifdef BB_PLATFORM_INIT
  BB_PLATFORM_INIT(&bb_PlatformState);
#endif

  int LastMousePositionX = 0;
  int LastMousePositionY = 0;

  unsigned int EndTime = 0;
  float DeltaTime = 0.0f;

  while (IsRunning) {
    bb_UpdateWindow(&bb_PlatformState.Window);

    // reset keys & buttons
    for (int Index = 0; Index < bb_NumKeys; ++Index) {
      bb_PlatformState.InputState.KeysUp[Index] = false;
      bb_PlatformState.InputState.KeysDown[Index] = false;
    }

    for (int Index = 0; Index < bb_NumButtons; ++Index) {
      bb_PlatformState.InputState.ButtonsUp[Index] = false;
      bb_PlatformState.InputState.ButtonsDown[Index] = false;
    }
    bb_PlatformState.InputState.MouseMoveX = 0;
    bb_PlatformState.InputState.MouseMoveY = 0;

    // handle events
    bb_event Event;
    if (bb_PullEvent(&Event)) {
      if (Event.Type == bb_EventQuit) {
        IsRunning = false;
      } else if (Event.Type == bb_EventKeyDown) {
        bb_PlatformState.InputState.Keys[Event.Key] = true;
        bb_PlatformState.InputState.KeysUp[Event.Key] = true;
      } else if (Event.Type == bb_EventKeyUp) {
        bb_PlatformState.InputState.Keys[Event.Key] = false;
        bb_PlatformState.InputState.KeysDown[Event.Key] = true;
      } else if (Event.Type == bb_EventButtonDown) {
        bb_PlatformState.InputState.Buttons[Event.Button] = true;
        bb_PlatformState.InputState.ButtonsDown[Event.Button] = true;
      } else if (Event.Type == bb_EventButtonUp) {
        bb_PlatformState.InputState.Buttons[Event.Button] = false;
        bb_PlatformState.InputState.ButtonsUp[Event.Button] = true;
      } else if (Event.Type == bb_EventMouseMove) {
        bb_PlatformState.InputState.MouseX = Event.Mouse.X;
        bb_PlatformState.InputState.MouseY = Event.Mouse.Y;

        bb_PlatformState.InputState.MouseMoveX = LastMousePositionX - Event.Mouse.X;
        bb_PlatformState.InputState.MouseMoveY = LastMousePositionY - Event.Mouse.Y;

        LastMousePositionX = Event.Mouse.X;
        LastMousePositionY = Event.Mouse.Y;
      } else if (Event.Type == bb_EventResized) {
#ifdef BB_PLATFORM_CONFIG
        BB_PLATFORM_CONFIG();
#endif
      }
    }

    unsigned int StartTime = bb_GetTicks();
    DeltaTime = (float)(StartTime - EndTime) / 1000.0f;
    EndTime = StartTime;

    // game update and render
#ifdef BB_PLATFORM_LOOP
    BB_PLATFORM_LOOP(DeltaTime);
#endif

    bb_OpenGLSwapBuffers(&OpenGLContext);
  }

#ifdef BB_PLATFORM_SHUTDOWN
  BB_PLATFORM_SHUTDOWN();
#endif

  bb_DestroyOpenGLContext(&OpenGLContext);
  bb_CloseWindow(&bb_PlatformState.Window);
  return 0;
}

#endif

#define BB_PLATFORM_H_
#endif