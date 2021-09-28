#ifndef CONTROL_H
# define CONTROL_H

// # define KEY_ESC				53
// # define KEY_LEFT			123
// # define KEY_RIGHT			124
// # define KEY_DOWN			126
// # define KEY_MINUS			78
// # define KEY_UP				125
// # define KEY_PLUS			69
// # define KEY_C				8
// # define SCROLL_UP			4
// # define SCROLL_DOWN			5
// # define KEY_PRESS			2
// # define KEY_RELEASE			3
// # define WHEEL				4
// # define BUTTON_RELEASE		5
// # define MOTION_NOTIFY		6
// # define EXPOSE				12
// # define DESTROY				17

# define KEY_ESC				65307
# define KEY_LEFT				65361
# define KEY_RIGHT				65363
# define KEY_DOWN				65364
# define KEY_UP					65362
# define KEY_MINUS				65453
# define KEY_PLUS				65451
# define KEY_C					99
# define SCROLL_UP				4
# define SCROLL_DOWN			5
# define KEY_PRESS				2
# define KEY_RELEASE			3
# define WHEEL					4
# define BUTTON_RELEASE			5
# define MOTION_NOTIFY			6
# define EXPOSE					12
# define DESTROY				17

# define MASK_KEY_PRESS			1L
# define MASK_KEY_RELEASE		2L
# define MASK_WHEEL				4L
# define MASK_BUTTON_RELEASE	8L
# define MASK_POINTER_MOTION	64L
# define MASK_EXPOSE			32768L
# define MASK_DESTROY			131072L

# define ZOOM_PLUS				1.2
# define ZOOM_MINUS				0.8
# define SHIFT					0.11

#endif

// 0L		NoEventMask
// (1L<<0)	KeyPressMask
// (1L<<1)	KeyReleaseMask
// (1L<<2)	ButtonPressMask
// (1L<<3)	ButtonReleaseMask
// (1L<<4)	EnterWindowMask
// (1L<<5)	LeaveWindowMask
// (1L<<6)	PointerMotionMask
// (1L<<7)	PointerMotionHintMask
// (1L<<8)	Button1MotionMask
// (1L<<9)	Button2MotionMask
// (1L<<10)	Button3MotionMask
// (1L<<11)	Button4MotionMask
// (1L<<12)	Button5MotionMask
// (1L<<13)	ButtonMotionMask
// (1L<<14)	KeymapStateMask
// (1L<<15)	ExposureMask
// (1L<<16)	VisibilityChangeMask
// (1L<<17)	StructureNotifyMask
// (1L<<18)	ResizeRedirectMask
// (1L<<19)	SubstructureNotifyMask
// (1L<<20)	SubstructureRedirectMask
// (1L<<21)	FocusChangeMask
// (1L<<22)	PropertyChangeMask
// (1L<<23)	ColormapChangeMask
// (1L<<24)	OwnerGrabButtonMask
