#include<stdio.h>
#include<proto/dos.h>
#include<proto/exec.h>
#include<proto/graphics.h>
#include<proto/gadtools.h>
#include<proto/intuition.h>
#include<proto/utility.h>
#include<intuition/imageclass.h>
#include<intuition/gadgetclass.h>
#include<libraries/gadtools.h>
#include<libraries/amigaguide.h>
#include<images/smartbitmap.h>
#include<proto/smartbitmap.h>

#define unless(x) if(!(x))
#define LEAVE goto end

struct Library *SmartBitMapBase=NULL;
struct Window *MainWnd=NULL;
Object *Im=NULL;
Class *ImClass=NULL;
struct Screen *Scr=NULL;

ULONG Size45UDPlanes[] = {
	0xF8000000, 0x88000000, 0x90000000, 0xA8000000, 0xD4000000, 0xA000000, 0x5000000, 0x2800000,
	0x1580000, 0xA80000, 0x480000, 0x880000, 0xF80000, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xF8000000, 0xF8000000, 0xF0000000, 0xF8000000, 0xDC000000, 0xE000000, 0x7000000, 0x3800000,
	0x1D80000, 0xF80000, 0x780000, 0xF80000, 0xF80000, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};
struct BitMap Size45UDBitMap = { 4, 32, NULL, 2, NULL, {(PLANEPTR)&Size45UDPlanes[0],(PLANEPTR)&Size45UDPlanes[32]} };

UBYTE TBNEWPlanes[] = {
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xF,	0xF8,	0x0,	0x0,	0x8,	0xC,	0x0,	0x0,	0x8,	0xA,	0x0,	0x0,	0x8,	0xF,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0x8,	0x1,	0x0,	0x0,	0xF,	0xFF,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x7,	0xF0,	0x0,	0x0,	0x7,	0xF4,	0x0,	0x0,	0x7,	0xF0,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x7,	0xFE,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
};
struct BitMap TBNEWBitMap = { 4, 20, NULL, 4, NULL, {(PLANEPTR)&TBNEWPlanes[0],(PLANEPTR)&TBNEWPlanes[80],(PLANEPTR)&TBNEWPlanes[160],(PLANEPTR)&TBNEWPlanes[240]} };

UBYTE TBCOLORWHEELPlanes[] = {
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x1,	0xF0,	0x0,	0x0,	0x7,	0xFC,	0x0,	0x0,	0xB,	0xFA,	0x0,	0x0,	0x11,	0x7D,	0x0,	0x0,	0x11,	0xB5,	0x0,	0x0,	0x20,	0x5C,	0x80,	0x0,	0x20,	0x0,	0x80,	0x0,	0x3D,	0x0,	0x80,	0x0,	0x3E,	0x80,	0x80,	0x0,	0x3B,	0x40,	0x80,	0x0,	0x1D,	0xB1,	0x0,	0x0,	0x1F,	0x61,	0x0,	0x0,	0xF,	0xFA,	0x0,	0x0,	0x7,	0xFC,	0x0,	0x0,	0x1,	0xF0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x4,	0x0,	0x0,	0x0,	0xE,	0x80,	0x0,	0x0,	0xE,	0x48,	0x0,	0x0,	0x1F,	0xA0,	0x0,	0x0,	0x1F,	0xD4,	0x0,	0x0,	0x1F,	0xFF,	0x0,	0x0,	0x1F,	0xFF,	0x0,	0x0,	0x1F,	0xBF,	0x0,	0x0,	0xE,	0x4E,	0x0,	0x0,	0xE,	0x9E,	0x0,	0x0,	0x4,	0x4,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x4,	0x4,	0x0,	0x0,	0xE,	0x2,	0x0,	0x0,	0xC,	0x2,	0x0,	0x0,	0x1F,	0x3,	0x0,	0x0,	0x1A,	0xAB,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x40,	0x0,	0x0,	0x1,	0xB0,	0x0,	0x0,	0x1,	0x60,	0x0,	0x0,	0x3,	0xF8,	0x0,	0x0,	0x1,	0xF0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x1,	0xF0,	0x0,	0x0,	0x7,	0xFC,	0x0,	0x0,	0xF,	0x62,	0x0,	0x0,	0xD,	0xA2,	0x0,	0x0,	0x1F,	0x43,	0x0,	0x0,	0x1A,	0xAB,	0x0,	0x0,	0x1D,	0x17,	0x0,	0x0,	0x1E,	0xAF,	0x0,	0x0,	0x1B,	0x5B,	0x0,	0x0,	0xD,	0xB6,	0x0,	0x0,	0xF,	0x6E,	0x0,	0x0,	0x7,	0xFC,	0x0,	0x0,	0x1,	0xF0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
};
struct BitMap TBCOLORWHEELBitMap = { 4, 20, NULL, 4, NULL, {(PLANEPTR)&TBCOLORWHEELPlanes[0],(PLANEPTR)&TBCOLORWHEELPlanes[80],(PLANEPTR)&TBCOLORWHEELPlanes[160],(PLANEPTR)&TBCOLORWHEELPlanes[240]} };

#define Bit32(x) ((ULONG)(x|(x<<8)|(x<<16)|(x<<24)))

struct SmartBitMapIRGB pal[]=
{
	{ 0,Bit32(189),Bit32(189),Bit32(189)},		// Background
	{-1,Bit32(  0),Bit32(  0),Bit32(  0)},		// Black
	{-1,Bit32(255),Bit32(255),Bit32(255)},		// White
	{-1,Bit32(123),Bit32(  0),Bit32(  0)},		// Red 50%
	{-1,Bit32(  0),Bit32(123),Bit32(  0)},		// Green 50%
	{-1,Bit32(  0),Bit32(  0),Bit32(123)},		// Blue 50%
	{-1,Bit32(123),Bit32(123),Bit32(  0)},		// Yellow 50%
	{-1,Bit32(  0),Bit32(123),Bit32(123)},		// Cyan 50%
	{-1,Bit32(123),Bit32(  0),Bit32(123)},		// Magenta 50%
	{-1,Bit32(255),Bit32(  0),Bit32(  0)},		// Red 100%
	{-1,Bit32(  0),Bit32(255),Bit32(  0)},		// Green 100%
	{-1,Bit32(  0),Bit32(  0),Bit32(255)},		// Blue 100%
	{-1,Bit32(255),Bit32(255),Bit32(  0)},		// Yellow 100%
	{-1,Bit32(  0),Bit32(255),Bit32(255)},		// Cyan 100%
	{-1,Bit32(255),Bit32(  0),Bit32(255)},		// Magenta 100%
	{-1,Bit32(123),Bit32(123),Bit32(123)}			// Dark Gray
};

void main()
{
	ULONG class,code;
	struct Gadget *gadget;
	struct IntuiMessage *message;
	struct DrawInfo *dri;
	BOOL running=TRUE;

	unless(Scr=LockPubScreen("Workbench")) LEAVE;
	unless(dri=GetScreenDrawInfo(Scr)) LEAVE;
	unless(SmartBitMapBase=OpenLibrary("images/smartbitmap.image",36L)) LEAVE;
	unless(ImClass=GetSmartBitMapClass()) LEAVE;

	GetRGB32(Scr->ViewPort.ColorMap,0,1,&pal[0].R);

	unless(Im=NewObject(ImClass,NULL,
		IA_Left,25,
		IA_Top,25,
		IA_Width,20,
		SMBM_Border,FALSE,
		SMBM_SelBorder,TRUE,
		SMBM_Screen,Scr,
		SMBM_BitMap,&TBCOLORWHEELBitMap,
//		SMBM_BitMap,&Size45UDBitMap,
		SMBM_Palette,pal,
		TAG_DONE)) LEAVE;
	unless(MainWnd=OpenWindowTags(NULL,
		WA_Left,0,
		WA_Top,0,
		WA_Width,600,
		WA_Height,200,
		WA_IDCMP,IDCMP_CLOSEWINDOW|IDCMP_GADGETUP,
		WA_Flags,WFLG_CLOSEGADGET|WFLG_DRAGBAR|WFLG_DEPTHGADGET|WFLG_ACTIVATE|WFLG_SIZEGADGET,
		WA_CustomScreen,Scr,
		TAG_DONE)) LEAVE;

	DrawImageState(MainWnd->RPort,(struct Image *)Im,0,0,IDS_NORMAL,dri);

	while(running)
	{
		Wait(1L<<MainWnd->UserPort->mp_SigBit);
		while(message=GT_GetIMsg(MainWnd->UserPort))
		{
			class=message->Class;
			code=message->Code;
			gadget=(struct Gadget *)message->IAddress;
			GT_ReplyIMsg(message);
			switch(class)
			{
				case IDCMP_CLOSEWINDOW:
					running=FALSE;
					break;
			}
		}
	}
end:
	if(MainWnd)
	{
		CloseWindow(MainWnd);
	}
	if(Im) DisposeObject(Im);
	if(SmartBitMapBase) CloseLibrary(SmartBitMapBase);
	if(dri) FreeScreenDrawInfo(Scr,dri);
	if(Scr) UnlockPubScreen(NULL,Scr);
}
