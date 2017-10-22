#ifndef BB_PLATFORM_WIN32_H_

#include <Windows.h>
#include <windowsx.h>
#include <process.h>

// keys & buttons
enum {
  bb_ButtonLeft       = 0x01,
  bb_ButtonRight      = 0x02,
  bb_ButtonMiddle     = 0x04,
  bb_KeyBackspace     = 0x08,
  bb_KeyTab           = 0x09,
  bb_KeyClear         = 0x0C,
  bb_KeyReturn        = 0x0D,
  bb_KeyShift         = 0x10,
  bb_KeyControl       = 0x11,
  bb_KeyAlt           = 0x12,
  bb_KeyPause         = 0x13,
  bb_KeyCapslock      = 0x14,
  bb_KeyEscape        = 0x1B,
  bb_KeySpace         = 0x20,
  bb_KeyPageup        = 0x21,
  bb_KeyPagedown      = 0x22,
  bb_KeyEnd           = 0x23,
  bb_KeyHome          = 0x24,
  bb_KeyLeft          = 0x25,
  bb_KeyUp            = 0x26,
  bb_KeyRight         = 0x27,
  bb_KeyDown          = 0x28,
  bb_KeySelect        = 0x29,
  bb_KeyPrint         = 0x2A,
  bb_KeyExecute       = 0x2B,
  bb_KeyPrintScreen   = 0x2C, // print screen
  bb_KeyInsert        = 0x2D,
  bb_KeyDelete        = 0x2E,
  bb_KeyHelp          = 0x2F,
  bb_Key0             = 0x30,
  bb_Key1             = 0x31,
  bb_Key2             = 0x32,
  bb_Key3             = 0x33,
  bb_Key4             = 0x34,
  bb_Key5             = 0x35,
  bb_Key6             = 0x36,
  bb_Key7             = 0x37,
  bb_Key8             = 0x38,
  bb_Key9             = 0x39,
  bb_KeyA             = 0x41,
  bb_KeyB             = 0x42,
  bb_KeyC             = 0x43,
  bb_KeyD             = 0x44,
  bb_KeyE             = 0x45,
  bb_KeyF             = 0x46,
  bb_KeyG             = 0x47,
  bb_KeyH             = 0x48,
  bb_KeyI             = 0x49,
  bb_KeyJ             = 0x4A,
  bb_KeyK             = 0x4B,
  bb_KeyL             = 0x4C,
  bb_KeyM             = 0x4D,
  bb_KeyN             = 0x4E,
  bb_KeyO             = 0x4F,
  bb_KeyP             = 0x50,
  bb_KeyQ             = 0x51,
  bb_KeyR             = 0x52,
  bb_KeyS             = 0x53,
  bb_KeyT             = 0x54,
  bb_KeyU             = 0x55,
  bb_KeyV             = 0x56,
  bb_KeyW             = 0x57,
  bb_KeyX             = 0x58,
  bb_KeyY             = 0x59,
  bb_KeyZ             = 0x5A,
  bb_KeyNumpad0       = 0x60,
  bb_KeyNumpad1       = 0x61,
  bb_KeyNumpad2       = 0x62,
  bb_KeyNumpad3       = 0x63,
  bb_KeyNumpad4       = 0x64,
  bb_KeyNumpad5       = 0x65,
  bb_KeyNumpad6       = 0x66,
  bb_KeyNumpad7       = 0x67,
  bb_KeyNumpad8       = 0x68,
  bb_KeyNumpad9       = 0x69,
  bb_KeyMultiply      = 0x6A,
  bb_KeyAdd           = 0x6B,
  bb_KeySeparator     = 0x6C,
  bb_KeySubtract      = 0x6D,
  bb_KeyDecimal       = 0x6E,
  bb_KeyDivide        = 0x6F,
  bb_KeyF1            = 0x70,
  bb_KeyF2            = 0x71,
  bb_KeyF3            = 0x72,
  bb_KeyF4            = 0x73,
  bb_KeyF5            = 0x74,
  bb_KeyF6            = 0x75,
  bb_KeyF7            = 0x76,
  bb_KeyF8            = 0x77,
  bb_KeyF9            = 0x78,
  bb_KeyF10           = 0x79,
  bb_KeyF11           = 0x7A,
  bb_KeyF12           = 0x7B,
  bb_KeyF13           = 0x7C,
  bb_KeyF14           = 0x7D,
  bb_KeyF15           = 0x7E,
  bb_KeyF16           = 0x7F,
  bb_KeyF17           = 0x80,
  bb_KeyF18           = 0x81,
  bb_KeyF19           = 0x82,
  bb_KeyF20           = 0x83,
  bb_KeyF21           = 0x84,
  bb_KeyF22           = 0x85,
  bb_KeyF23           = 0x86,
  bb_KeyF24           = 0x87,
  bb_KeyNumlock       = 0x90,
  bb_KeyScroll        = 0x91,
  bb_KeyLeftShift     = 0xA0,
  bb_KeyRightShift    = 0xA1,
  bb_KeyLeftControl   = 0xA2,
  bb_KeyRightControl  = 0xA3,
  bb_KeyLeftAlt       = 0xA4,
  bb_KeyRightAlt      = 0xA5
};

// events
enum {
  bb_EventUnknown = 0,
  bb_EventQuit,
  bb_EventKeyDown,
  bb_EventKeyUp,
  bb_EventButtonDown,
  bb_EventButtonUp,
  bb_EventMouseMove,
  bb_EventSetFocus,
  bb_EventLostFocus,
  bb_EventResized,
  bb_EventMinimized,
  bb_EventMaximized,
  bb_EventMouseWheel,
  bb_EventChar
};

// window flags
enum {
  bb_FlagNone       = 0,
  bb_FlagTitlebar   = 1 << 0,
  bb_FlagResizable  = 1 << 1,
  bb_FlagClose      = 1 << 2,
  bb_FlagFullscreen = 1 << 3,
  bb_FlagDefault    = bb_FlagTitlebar | bb_FlagClose
};

struct bb_event {
  int Type;
  union {
    struct { int X, Y; } Mouse;
    struct { int Width, Height; } Window;
    struct { int X, Y; } Wheel;
    struct { char Character; };
    int Key;
    int Button;
  };
};

struct bb_window {
  HWND Win32Handle; 
  HDC DeviceContext;
};

struct bb_opengl_context {
  HDC DeviceContext;
  HGLRC OpenGLContext;
  HWND WindowHandle;
};

struct bb_thread {
  HANDLE ThreadHandle;
  unsigned int ThreadId;

  void(*Function)(void *);
  void *Data;
};

struct bb_mutex {
  HANDLE MutexHandle;
};

struct bb_thread_pool {
  bb_thread *Workers;
  int NumWorkers;

  // NOTE(Brajan): do not set these variables manually
  void *Tasks;
  int NumTasks;
  int TasksCapacity;

  bb_mutex Mutex;
  volatile bool StopFlag;
};

// window functions
int bb_OpenWindow(bb_window *Window, const char *Title, int PositionX, int PositionY, int Width, int Height, int Flags);
int bb_CloseWindow(bb_window *Window);
void bb_UpdateWindow(bb_window *Window);
void bb_SetWindowCursorPosition(bb_window *Window, int X, int Y);
void bb_SetWindowTitle(bb_window *Window, const char *Title);
void bb_GetWindowSize(bb_window *Window, int *Width, int *Height);
void bb_ShowCursor(bool Show);
bool bb_GetAsyncKeyState(int Key);
void bb_GetScreenMousePosition(int *X, int *Y);
void bb_GetClientMousePosition(bb_window *Window, int *X, int *Y);

// events
bool bb_PullEvent(bb_event *Event);

// time
unsigned int bb_GetTicks();

// opengl context
int bb_CreateOpenGLContext(bb_window *Window, bb_opengl_context *Context);
int bb_DestroyOpenGLContext(bb_opengl_context *Context);
void bb_OpenGLSwapBuffers(bb_opengl_context *Context);

// memory
void *bb_AllocateMemory(int Size);
void bb_FreeMemory(void *Memory);

// threads
int bb_CreateThread(bb_thread *Thread, void (*Function)(void *), void *Data);
void bb_DestroyThread(bb_thread *Thread);

// mutex
int bb_CreateMutex(bb_mutex *Mutex);
void bb_DestroyMutex(bb_mutex *Mutex);
void bb_Lock(bb_mutex *Mutex);
void bb_Unlock(bb_mutex *Mutex);
bool bb_TryLock(bb_mutex *Mutex);

// thread pool
int bb_CreateThreadPool(bb_thread_pool *ThreadPool, int NumWorkers, int MaxTasks);
void bb_DestroyThreadPool(bb_thread_pool *ThreadPool);
void bb_StopThreadPool(bb_thread_pool *ThreadPool);
int bb_PushTaskToThreadPool(bb_thread_pool *ThreadPool, void(*Function)(void *), void *Data);

// system
void bb_Sleep(int Ms);
void bb_SetTextClipboard(const char *Data, unsigned int Length);
char *bb_GetTextClipboard();

// ----------------------------------------------------------------------------
// -----------------------------IMPLEMENTATION---------------------------------
// ----------------------------------------------------------------------------
#ifdef BB_PLATFORM_IMPLEMENTATION

// events queue
#define __bb_MaxEventsQueue 0xFF
struct __bb_events_queue{
  int Front;
  int Rear;
  int EventCount;
  bb_event Array[__bb_MaxEventsQueue];
};
static __bb_events_queue __bb_EventsQueue = {
  0, -1, 0, { }
};

static bool __bb_IsResizing = false;
static int __bb_LastWindowWidth = 0;
static int __bb_LastWindowHeight = 0;

static void
__bb_InsertEvent(bb_event Event) {
  if (__bb_EventsQueue.EventCount < __bb_MaxEventsQueue) {
    if (__bb_EventsQueue.Rear == __bb_MaxEventsQueue - 1) {
      __bb_EventsQueue.Rear = -1;
    }
    __bb_EventsQueue.Array[++__bb_EventsQueue.Rear] = Event;
    ++__bb_EventsQueue.EventCount;
  }
}

// win32
static LRESULT CALLBACK __bb_Win32HandleEvents(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam) {
  LRESULT Result = 0;

  bb_event Event;
  ZeroMemory(&Event, sizeof(bb_event));
  
  switch (Message) {
    case WM_QUIT:
    case WM_DESTROY: {
      Event.Type = bb_EventQuit;
      __bb_InsertEvent(Event);
    } break;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP: {
      unsigned int VKCode = (unsigned int)WParam;
      bool WasDown = ((LParam & (1 << 30)) != 0);
      bool IsDown = ((LParam & (1 << 31)) == 0);

      if (WasDown != IsDown) {
        if (IsDown) {
          Event.Type = bb_EventKeyDown;
        } else {
          Event.Type = bb_EventKeyUp;
        }

        Event.Key = VKCode;

        __bb_InsertEvent(Event);
      }
      break;
    }

    case WM_LBUTTONDOWN: {
      Event.Type = bb_EventButtonDown;
      Event.Button = bb_ButtonLeft;
      __bb_InsertEvent(Event);
    } break;

    case WM_LBUTTONUP: {
      Event.Type = bb_EventButtonUp;
      Event.Button = bb_ButtonLeft;
      __bb_InsertEvent(Event);
    } break;

    case WM_RBUTTONDOWN: {
      Event.Type = bb_EventButtonDown;
      Event.Button = bb_ButtonRight;
      __bb_InsertEvent(Event);
    } break;

    case WM_RBUTTONUP: {
      Event.Type = bb_EventButtonUp;
      Event.Button = bb_ButtonRight;
      __bb_InsertEvent(Event);
    } break;

    case WM_MBUTTONDOWN: {
      Event.Type = bb_EventButtonDown;
      Event.Button = bb_ButtonMiddle;
      __bb_InsertEvent(Event);
    } break;

    case WM_MBUTTONUP: {
      Event.Type = bb_EventButtonUp;
      Event.Button = bb_ButtonMiddle;
      __bb_InsertEvent(Event);
    } break;

    case WM_MOUSEMOVE: {
      Event.Type = bb_EventMouseMove;
      Event.Mouse.X = GET_X_LPARAM(LParam); 
      Event.Mouse.Y = GET_Y_LPARAM(LParam);
      __bb_InsertEvent(Event);
    } break;

    case WM_MOUSEWHEEL: {
      Event.Type = bb_EventMouseWheel;
      Event.Wheel.X = GET_X_LPARAM(LParam); 
      Event.Wheel.Y = GET_Y_LPARAM(LParam);
      __bb_InsertEvent(Event);
    } break;

    case WM_CHAR: {
      Event.Type = bb_EventChar;
      Event.Character = (char)WParam;
      __bb_InsertEvent(Event);
    } break;

    case WM_SETFOCUS: {
      Event.Type = bb_EventSetFocus;
      __bb_InsertEvent(Event);
      break;
    }

    case WM_KILLFOCUS: {
      Event.Type = bb_EventLostFocus;
      __bb_InsertEvent(Event);
      break;
    }

    case WM_SIZE: {
      RECT Rect;
      GetClientRect(Handle, &Rect);
      int Width = (int)(Rect.right - Rect.left);
      int Height = (int)(Rect.bottom - Rect.top);

      if (WParam != SIZE_MINIMIZED && !__bb_IsResizing && 
          (Width != __bb_LastWindowWidth || 
          Height != __bb_LastWindowHeight)) {
        Event.Type = bb_EventResized;
        Event.Window.Width = Width;
        Event.Window.Height = Height;

        __bb_LastWindowWidth = Width;
        __bb_LastWindowHeight = Height;

        __bb_InsertEvent(Event);
      }
      break;
    }

    case WM_ENTERSIZEMOVE: {
      __bb_IsResizing = true;
      break;
    }

    case WM_EXITSIZEMOVE: {
      __bb_IsResizing = false;

      RECT Rect;
      GetClientRect(Handle, &Rect);
      int Width = (int)(Rect.right - Rect.left);
      int Height = (int)(Rect.bottom - Rect.top);

      if (Width != __bb_LastWindowWidth || 
          Height != __bb_LastWindowHeight) {
        Event.Type = bb_EventResized;
        Event.Window.Width = Width;
        Event.Window.Height = Height;

        __bb_LastWindowWidth = Width;
        __bb_LastWindowHeight = Height;

        __bb_InsertEvent(Event);
      }
      break;
    }

    default: {
      Result = DefWindowProcW(Handle, Message, WParam, LParam);
      break;
    }
  }
  return Result;
}

// window
int
bb_OpenWindow(bb_window *Window, const char *Title, int PositionX, int PositionY, int Width, int Height, int Flags) {
  WNDCLASSW WindowClass;
  WindowClass.style = CS_HREDRAW | CS_VREDRAW;
  WindowClass.cbClsExtra = 0;
  WindowClass.cbWndExtra = 0;
  WindowClass.lpszClassName = L"bb_window";
  WindowClass.hInstance = GetModuleHandleW(NULL);
  WindowClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  WindowClass.lpszMenuName = NULL;
  WindowClass.lpfnWndProc = &__bb_Win32HandleEvents;
  WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  WindowClass.hIcon = NULL;
  RegisterClassW(&WindowClass);

  DWORD Win32Style = WS_VISIBLE;
  if (Flags & bb_FlagTitlebar)
    Win32Style |= WS_CAPTION | WS_MINIMIZEBOX;

  if (Flags & bb_FlagResizable)
    Win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;

  if (Flags & bb_FlagClose)
    Win32Style |= WS_SYSMENU;

  Window->Win32Handle = 
      CreateWindowA("bb_window", Title,
                    Win32Style,
                    PositionX, PositionY, Width, Height,
                    NULL, NULL, GetModuleHandle(NULL), NULL);

  ShowWindow(Window->Win32Handle, SW_SHOW);
  UpdateWindow(Window->Win32Handle);
  return 0;
}

int
bb_CloseWindow(bb_window *Window) {
  ReleaseDC(Window->Win32Handle, Window->DeviceContext);
  DestroyWindow(Window->Win32Handle);
  return 0;
}

void
bb_UpdateWindow(bb_window *Window) {
  MSG Message;
  while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
    /*bb_event Event = { 0 };

    switch (Message.message) {
      case WM_SYSKEYDOWN:
      case WM_KEYDOWN:
      case WM_SYSKEYUP:
      case WM_KEYUP: {
        
        unsigned int VKCode = (unsigned int)Message.wParam;
        bool WasDown = ((Message.lParam & (1 << 30)) != 0);
        bool IsDown = ((Message.lParam & (1 << 31)) == 0);

        if (WasDown != IsDown) {
          if (IsDown) {
            Event.Type = bb_EventKeyDown;
          } else {
            Event.Type = bb_EventKeyUp;
          }

          Event.Key = VKCode;

          __bb_InsertEvent(Event);
        }
        break;
      }

      case WM_LBUTTONDOWN: {
        Event.Type = bb_EventButtonDown;
        Event.Button = bb_ButtonLeft;
        __bb_InsertEvent(Event);
      } break;

      case WM_LBUTTONUP: {
        Event.Type = bb_EventButtonUp;
        Event.Button = bb_ButtonLeft;
        __bb_InsertEvent(Event);
      } break;

      case WM_RBUTTONDOWN: {
        Event.Type = bb_EventButtonDown;
        Event.Button = bb_ButtonRight;
        __bb_InsertEvent(Event);
      } break;

      case WM_RBUTTONUP: {
        Event.Type = bb_EventButtonUp;
        Event.Button = bb_ButtonRight;
        __bb_InsertEvent(Event);
      } break;

      case WM_MBUTTONDOWN: {
        Event.Type = bb_EventButtonDown;
        Event.Button = bb_ButtonMiddle;
        __bb_InsertEvent(Event);
      } break;

      case WM_MBUTTONUP: {
        Event.Type = bb_EventButtonUp;
        Event.Button = bb_ButtonMiddle;
        __bb_InsertEvent(Event);
      } break;

      case WM_MOUSEMOVE: {
        Event.Type = bb_EventMouseMove;
        Event.Mouse.X = GET_X_LPARAM(Message.lParam); 
        Event.Mouse.Y = GET_Y_LPARAM(Message.lParam);
        __bb_InsertEvent(Event);
      } break;     
      
      default: {
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
      } break;
    }*/
    
    TranslateMessage(&Message);
    DispatchMessageA(&Message);
  }
}

void 
bb_SetWindowCursorPosition(bb_window *Window, int X, int Y) {
  POINT Point;
  Point.x = X;
  Point.y = Y;
  ClientToScreen(Window->Win32Handle, &Point);
  SetCursorPos(Point.x, Point.y);
}

void
bb_SetWindowTitle(bb_window *Window, const char *Title) {
  SetWindowText(Window->Win32Handle, Title);
}

void
bb_GetWindowSize(bb_window *Window, int *Width, int *Height) {
  RECT Rect;
  GetClientRect(Window->Win32Handle, &Rect);
  *Width = Rect.right - Rect.left;
  *Height = Rect.bottom - Rect.top;
}

void
bb_ShowCursor(bool Show) {
  ShowCursor(Show);
}

bool
bb_GetAsyncKeyState(int Key) {
  return (GetAsyncKeyState(Key) != 0);
}

void
bb_GetScreenMousePosition(int *X, int *Y) {
  POINT Point;
  GetCursorPos(&Point);

  *X = Point.x;
  *Y = Point.y;
}

void
bb_GetClientMousePosition(bb_window *Window, int *X, int *Y) {
  POINT Point;
  GetCursorPos(&Point);

  ScreenToClient(Window->Win32Handle, &Point);

  *X = Point.x;
  *Y = Point.y;
}

// events
bool
bb_PullEvent(bb_event *Event) {
  if (__bb_EventsQueue.EventCount == 0) {
    return false;
  }

  *Event = __bb_EventsQueue.Array[__bb_EventsQueue.Front++];

  if (__bb_EventsQueue.Front == __bb_MaxEventsQueue) {
    __bb_EventsQueue.Front = 0;
  }

  __bb_EventsQueue.EventCount--;
  return true;
}

// time
static DWORD __bb_TimerStart = 0;
static bool __bb_TimerInitialized = false;

unsigned int
bb_GetTicks() {
  if (!__bb_TimerInitialized) {
    __bb_TimerStart = GetTickCount();
    __bb_TimerInitialized = true;
  }

  return (GetTickCount() - __bb_TimerStart);
}

// opengl context
int
bb_CreateOpenGLContext(bb_window *Window, bb_opengl_context *Context) {
  Context->DeviceContext = GetDC(Window->Win32Handle);
  Context->WindowHandle = Window->Win32Handle;

  PIXELFORMATDESCRIPTOR PixelFormat = {};
  PixelFormat.nSize = sizeof(PixelFormat);
  PixelFormat.nVersion = 1;
  PixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  PixelFormat.cColorBits = 32;
  PixelFormat.cAlphaBits = 8;
  PixelFormat.iLayerType = PFD_MAIN_PLANE;
  PixelFormat.iPixelType = PFD_TYPE_RGBA;
  
  int PixelFormatIndex = ChoosePixelFormat(Context->DeviceContext, &PixelFormat);
  PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
  DescribePixelFormat(Context->DeviceContext, PixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
  SetPixelFormat(Context->DeviceContext, PixelFormatIndex, &SuggestedPixelFormat);

  Context->OpenGLContext = wglCreateContext(Context->DeviceContext);
  wglMakeCurrent(Context->DeviceContext, Context->OpenGLContext);
  return 0;
}

int
bb_DestroyOpenGLContext(bb_opengl_context *Context) {
  wglMakeCurrent(Context->DeviceContext, NULL);
  wglDeleteContext(Context->OpenGLContext);
  ReleaseDC(Context->WindowHandle, Context->DeviceContext);
  return 0;
}

void
bb_OpenGLSwapBuffers(bb_opengl_context *Context) {
  SwapBuffers(Context->DeviceContext);
}

// memory
//#include <stdio.h>
static bb_mutex __bb_MemoryMutex;

void *
bb_AllocateMemory(int Size) {
  if (__bb_MemoryMutex.MutexHandle == 0) {
    bb_CreateMutex(&__bb_MemoryMutex);
  }

  void *Mem = 0;

  bb_Lock(&__bb_MemoryMutex);
  Mem = VirtualAlloc(0, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  //Mem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
  bb_Unlock(&__bb_MemoryMutex);

  bb_Assert(Mem != 0);

  return Mem;
  //return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
  //return malloc(Size);
  //return VirtualAlloc(0, Size, MEM_COMMIT, PAGE_READWRITE);
}

void
bb_FreeMemory(void *Memory) {
  //free(Memory);
  bb_Lock(&__bb_MemoryMutex);
  VirtualFree(Memory, 0, MEM_RELEASE);
  //HeapFree(GetProcessHeap(), 0, Memory);
  bb_Unlock(&__bb_MemoryMutex);
}

// threads
static unsigned int __stdcall 
__bb_ThreadEntryPoint(void *Data) {
  bb_thread *Thread = (bb_thread *)Data;
  Thread->Function(Thread->Data);
  _endthreadex(0);
  return 0;
}

int
bb_CreateThread(bb_thread *Thread, void (*Function)(void *), void *Data) {
  Thread->Function = Function;
  Thread->Data = Data;

  Thread->ThreadId = 0;
  Thread->ThreadHandle = 0;
  Thread->ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, &__bb_ThreadEntryPoint, Thread, 0, &Thread->ThreadId);
  if (Thread->ThreadHandle != 0)
    return 1;
  return 0;
}

void
bb_DestroyThread(bb_thread *Thread) {
  if (Thread->ThreadHandle)
    CloseHandle(Thread->ThreadHandle);
}

// mutex
int
bb_CreateMutex(bb_mutex *Mutex) {
  Mutex->MutexHandle = CreateMutex(NULL, FALSE, NULL);
  return 0;
}

void
bb_DestroyMutex(bb_mutex *Mutex) {
  CloseHandle(Mutex->MutexHandle);
}

void
bb_Lock(bb_mutex *Mutex) {
  WaitForSingleObject(Mutex->MutexHandle, INFINITE);
}

void
bb_Unlock(bb_mutex *Mutex) {
  ReleaseMutex(Mutex->MutexHandle);
}

bool
bb_TryLock(bb_mutex *Mutex) {
  return WaitForSingleObject(Mutex->MutexHandle, 0) == WAIT_OBJECT_0;
}

// thread pool
struct __bb_worker_task {
  void(*Function)(void *);
  void *Data;
};

static bool
__bb_GetNextTask(bb_thread_pool *ThreadPool, __bb_worker_task *Task) {
  bb_Lock(&ThreadPool->Mutex);

  if (ThreadPool->NumTasks <= 0) {
    bb_Unlock(&ThreadPool->Mutex);
    return false;
  }

  *Task = ((__bb_worker_task *)ThreadPool->Tasks)[--ThreadPool->NumTasks];
  bb_Unlock(&ThreadPool->Mutex);
  return true;
}

static void
__bb_ThreadPoolWorker(void *Data) {
  bb_thread_pool *ThreadPool = (bb_thread_pool *)Data;
  __bb_worker_task Task;
  for (;;) {
    if (ThreadPool->StopFlag)
      return;

    if (__bb_GetNextTask(ThreadPool, &Task)) {
      Task.Function(Task.Data);
    }

    bb_Sleep(1);
  }
}

int
bb_CreateThreadPool(bb_thread_pool *ThreadPool, int NumWorkers, int MaxTasks) {
  ThreadPool->Workers = (bb_thread *)bb_AllocateMemory(sizeof(bb_thread) * NumWorkers);
  ThreadPool->NumWorkers = NumWorkers;

  ThreadPool->Tasks = (__bb_worker_task *)bb_AllocateMemory(sizeof(__bb_worker_task) * MaxTasks);
  ThreadPool->NumTasks = 0;
  ThreadPool->TasksCapacity = MaxTasks;
  bb_ZeroMemory(ThreadPool->Tasks, sizeof(__bb_worker_task) * MaxTasks);

  bb_CreateMutex(&ThreadPool->Mutex);
  ThreadPool->StopFlag = false;

  // set up workers
  for (int Index = 0; Index < NumWorkers; ++Index) {
    bb_CreateThread(&ThreadPool->Workers[Index], __bb_ThreadPoolWorker, ThreadPool);
  }

  return 0;
}

void
bb_DestroyThreadPool(bb_thread_pool *ThreadPool) {
  if (ThreadPool == 0)
    return;
  for (int Index = 0; Index < ThreadPool->NumWorkers; ++Index) {
    bb_DestroyThread(&ThreadPool->Workers[Index]);
  }

  bb_DestroyMutex(&ThreadPool->Mutex);

  bb_FreeMemory(ThreadPool->Tasks);
  bb_FreeMemory(ThreadPool->Workers);
}

void 
bb_StopThreadPool(bb_thread_pool *ThreadPool) {
  ThreadPool->StopFlag = true;
}

int
bb_PushTaskToThreadPool(bb_thread_pool *ThreadPool, void(*Function)(void *), void *Data) {
  bb_Lock(&ThreadPool->Mutex);
  if (ThreadPool->NumTasks >= ThreadPool->TasksCapacity) {
    bb_Unlock(&ThreadPool->Mutex);
    return 1;
  }

  __bb_worker_task Task;
  Task.Function = Function;
  Task.Data = Data;
  ((__bb_worker_task *)ThreadPool->Tasks)[ThreadPool->NumTasks++] = Task;

  bb_Unlock(&ThreadPool->Mutex);
  return 0;
}

// system
void
bb_Sleep(int Ms) {
  Sleep(Ms);
}

void
bb_SetTextClipboard(const char *Data, unsigned int Length) {
  HGLOBAL Memory = GlobalAlloc(GMEM_MOVEABLE, Length + 1);
  char *Dest = (char *)GlobalLock(Memory);
  for (unsigned int Index = 0; Index < Length; ++Index) {
    Dest[Index] = Data[Index];
  }
  Dest[Length] = '\0';
  GlobalUnlock(Memory);

  OpenClipboard(NULL);
  EmptyClipboard();
  SetClipboardData(CF_TEXT, Memory);
  CloseClipboard();
}

#include "Strsafe.h"

char *
bb_GetTextClipboard() {
  OpenClipboard(NULL);
  HANDLE Clipboard = GetClipboardData(CF_TEXT);  
  if (Clipboard != NULL) {
    char *ClipboardPtrData = (char *)GlobalLock(Clipboard);
    unsigned int ClipboardLength = lstrlen(ClipboardPtrData);
    char *Result = (char *)bb_AllocateMemory(sizeof(char) * ClipboardLength);

    StringCchCopyA(Result, ClipboardLength, ClipboardPtrData);

    GlobalUnlock(ClipboardPtrData);
    CloseClipboard();
    return Result;
  }
  CloseClipboard();
}

#endif

#define BB_PLATFORM_WIN32_H_
#endif