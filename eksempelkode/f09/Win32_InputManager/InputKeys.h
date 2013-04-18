#ifndef INPUTKEYS_H
#define INPUTKEYS_H

// Return codes for various keys used by _getch() (conio.h)
// 78 y 110
static const int iKEY_NONE =				-1;		// "No key specified/unable to identify key."
static const int m_iFUNCTIONKEY_PREFIX =	0;		// _getch prefix code for any function key: 0.
static const int m_iARROWKEY_PREFIX =		224;	// _getch prefix code for any arrow key (decimal 224 = hexadecimal 0xE0).
static const int iKEY_N =					78;		// [N] key
static const int iKEY_n =					110;	// [n] key
static const int iKEY_Q =					81;		// [Q] key
static const int iKEY_q =					113;	// [q] key
static const int iKEY_W =					87;		// [W] key
static const int iKEY_w =					119;	// [w] key
static const int m_iARROW_UP =				72;		// [ARROW UP] key.
static const int m_iARROW_DOWN =			80;		// [ARROW DOWN] key.
static const int m_iARROW_LEFT =			75;		// [ARROW LEFT] key.
static const int m_iARROW_RIGHT =			77;		// [ARROW RIGHT] key.

#endif