#ifndef SDL_API_H
#define SDL_API_H

extern int MainFrameGetMsg(void);
extern void MainFrameRefresh(void);
extern void CanvasSetColor(int color);
extern void CanvasDrawPixel(int x1, int y1, int color, int alpha);
extern void MiscTrace(const char *fmt, ... );
extern void MiscSleep(int n);
extern void CanvasLock(void);
extern void CanvasUnlock(void);
extern void CanvasFillRect(int x1, int y1, int x2, int y2, int color);
extern void MainFrameResize(int w, int h);
extern int KeyboardGetKeyboardStatus(void);

#ifndef printf
#define printf MiscTrace
#endif

#ifndef WINDOW_WIDTH
#if 1
#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 240
#else
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#endif
#endif

#ifndef WINDOW_BGCOLOR
#define WINDOW_BGCOLOR 0xffffff
#endif


#endif