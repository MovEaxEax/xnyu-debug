#pragma once

// --- Structs ---
enum DEBUGMENUFORM : short {
    FORM_NONE = -1,
    FORM_OVERVIEW = 0,
    FORM_DEBUGVALUES = 1,
    FORM_DEBUGFUNCTIONS = 2,
    FORM_SAVEFILEEDITOR = 3,
    FORM_SUPERVISION = 4,
    FORM_EDITORMODE = 5
};

// --- Variables ---
extern const int FontTextureWidth;
extern const int FontTextureHeight;
extern const int FontTextureDimension;
extern unsigned char FontTextureRaw[];

extern const int SurfaceTextureWidth;
extern const int SurfaceTextureHeight;
extern const int SurfaceTextureDimension;
extern unsigned char SurfaceTextureRaw[];

extern const int FontTextureRGBBufferSize;
extern unsigned char* FontTextureRGBBuffer;;

extern unsigned char FormTextureOverview[];
extern unsigned char FormTextureDebugValues[];
extern unsigned char FormTextureDebugFunctions[];
extern unsigned char FormTextureSavefileEditor[];
extern unsigned char FormTextureSavefileEditorSelect[];
extern unsigned char FormTextureSupervision[];
extern unsigned char FormTextureEditormode[];

extern const int CustomCursorTextureWidth;
extern const int CustomCursorTextureHeight;
extern const int CustomCursorTextureDimension;
extern unsigned char CustomCursorTextureRaw[];

extern HFONT FontSmallest;
extern HFONT FontExtraSmall;
extern HFONT FontSmall;
extern HFONT FontSmallMedium;
extern HFONT FontMedium;
extern HFONT FontBigMedium;
extern HFONT FontBig;
extern HFONT FontExtraBig;
extern HFONT FontBiggest;

extern unsigned char ColorRed[];
extern unsigned char ColorGreen[];
extern unsigned char ColorDarkGreen[];
extern unsigned char ColorBlue[];
extern unsigned char ColorDarkBlue[];
extern unsigned char ColorBlack[];
extern unsigned char ColorWhite[];
extern unsigned char ColorGray[];
extern unsigned char ColorYellow[];
extern unsigned char ColorPurple[];
extern unsigned char ColorPink[];
extern unsigned char ColorOrange[];
extern unsigned char ColorCyan[];

extern HDC hdc;



// --- Functions ---
void ClearSurface(DEBUGMENUFORM form, int subform);
void SetTexturePixel(int offset, unsigned char* color, unsigned char alpha);
void DrawTextToTexture(int x, int y, std::string text, HFONT hFont, unsigned char* color, unsigned char alpha, std::string align = "left");
void DrawRectangleToTexture(int x, int y, int w, int h, unsigned char* color, unsigned char alpha);
void DrawCursorToTexture(int x, int y);
void LoadFormTextures();


