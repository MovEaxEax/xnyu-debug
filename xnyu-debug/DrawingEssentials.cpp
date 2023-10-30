#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "DrawingEssentials.h"



// --- Variables ---
const int FontTextureWidth = 400;
const int FontTextureHeight = 100;
const int FontTextureDimension = FontTextureWidth * FontTextureHeight * 4;
unsigned char FontTextureRaw[FontTextureDimension];

const int SurfaceTextureWidth = 1920;
const int SurfaceTextureHeight = 1080;
const int SurfaceTextureDimension = SurfaceTextureWidth * SurfaceTextureHeight * 4;
unsigned char SurfaceTextureRaw[SurfaceTextureDimension];

const int FontTextureRGBBufferSize = FontTextureWidth * FontTextureHeight * 3;
unsigned char* FontTextureRGBBuffer = new unsigned char[FontTextureRGBBufferSize];

unsigned char FormTextureOverview[SurfaceTextureDimension];
unsigned char FormTextureDebugValues[SurfaceTextureDimension];
unsigned char FormTextureDebugFunctions[SurfaceTextureDimension];
unsigned char FormTextureSavefileEditor[SurfaceTextureDimension];
unsigned char FormTextureSavefileEditorSelect[SurfaceTextureDimension];
unsigned char FormTextureSupervision[SurfaceTextureDimension];
unsigned char FormTextureEditormode[SurfaceTextureDimension];

const int CustomCursorTextureWidth = 52;
const int CustomCursorTextureHeight = 52;
const int CustomCursorTextureDimension = CustomCursorTextureWidth * CustomCursorTextureHeight * 4;
unsigned char CustomCursorTextureRaw[CustomCursorTextureDimension];

HFONT FontSmallest = CreateFontA(9, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontExtraSmall = CreateFontA(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontSmall = CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontSmallMedium = CreateFontA(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontMedium = CreateFontA(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontBigMedium = CreateFontA(28, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontBig = CreateFontA(36, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontExtraBig = CreateFontA(46, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
HFONT FontBiggest = CreateFontA(72, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");

unsigned char ColorRed[4] = { 255, 0, 0 };
unsigned char ColorGreen[4] = { 0, 255, 0 };
unsigned char ColorDarkGreen[4] = { 0, 190, 0 };
unsigned char ColorBlue[4] = { 0, 0, 255 };
unsigned char ColorDarkBlue[4] = { 0, 0, 140 };
unsigned char ColorBlack[4] = { 0, 0, 0 };
unsigned char ColorWhite[4] = { 255, 255, 255 };
unsigned char ColorGray[4] = { 150, 150, 150 };
unsigned char ColorYellow[4] = { 255, 247, 0 };
unsigned char ColorPurple[4] = { 170, 0, 255 };
unsigned char ColorPink[4] = { 255, 0, 221 };
unsigned char ColorOrange[4] = { 255, 157, 0 };
unsigned char ColorCyan[4] = { 0, 255, 242 };

HDC hdc = CreateCompatibleDC(0);



// --- Functions ---
void ClearSurface(DEBUGMENUFORM form, int subform)
{
    if (form == DEBUGMENUFORM::FORM_NONE) memset(SurfaceTextureRaw, 0x00, SurfaceTextureDimension);
    if (form == DEBUGMENUFORM::FORM_OVERVIEW) memcpy(SurfaceTextureRaw, FormTextureOverview, SurfaceTextureDimension);
    if (form == DEBUGMENUFORM::FORM_DEBUGVALUES) memcpy(SurfaceTextureRaw, FormTextureDebugValues, SurfaceTextureDimension);
    if (form == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS) memcpy(SurfaceTextureRaw, FormTextureDebugFunctions, SurfaceTextureDimension);
    if (form == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
    {
        if (subform == 2) memcpy(SurfaceTextureRaw, FormTextureSavefileEditorSelect, SurfaceTextureDimension);
        else memcpy(SurfaceTextureRaw, FormTextureSavefileEditor, SurfaceTextureDimension);
    }
    if (form == DEBUGMENUFORM::FORM_SUPERVISION) memcpy(SurfaceTextureRaw, FormTextureSupervision, SurfaceTextureDimension);
    if (form == DEBUGMENUFORM::FORM_EDITORMODE) memcpy(SurfaceTextureRaw, FormTextureEditormode, SurfaceTextureDimension);
}

void SetTexturePixel(int offset, unsigned char* color, unsigned char alpha)
{
    unsigned char orgR = SurfaceTextureRaw[offset + 0];
    unsigned char orgG = SurfaceTextureRaw[offset + 1];
    unsigned char orgB = SurfaceTextureRaw[offset + 2];
    unsigned char orgA = SurfaceTextureRaw[offset + 3];

    float alphaRatio = alpha / 255.0f;
    float orgAlphaRatio = orgA / 255.0f;
    float outAlpha = orgAlphaRatio + alphaRatio * (1.0f - orgAlphaRatio);

    SurfaceTextureRaw[offset + 0] = static_cast<unsigned char>((color[0] * alphaRatio + orgR * orgAlphaRatio * (1.0f - alphaRatio)) / outAlpha);
    SurfaceTextureRaw[offset + 1] = static_cast<unsigned char>((color[1] * alphaRatio + orgG * orgAlphaRatio * (1.0f - alphaRatio)) / outAlpha);
    SurfaceTextureRaw[offset + 2] = static_cast<unsigned char>((color[2] * alphaRatio + orgB * orgAlphaRatio * (1.0f - alphaRatio)) / outAlpha);
    SurfaceTextureRaw[offset + 3] = static_cast<unsigned char>(outAlpha * 255.0f);
}

void DrawTextToTexture(int x, int y, std::string text, HFONT hFont, unsigned char* color, unsigned char alpha, std::string align = "left")
{
    unsigned char emptyRGBA[4] = { 0x00, 0x00, 0x00, 0x00 };
    unsigned char emptyRGB[3] = { 0x00, 0x00, 0x00 };

    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, FontTextureWidth, FontTextureHeight);
    HGDIOBJ oldBitmap = SelectObject(hdc, hBitmap);

    HGDIOBJ oldFont = SelectObject(hdc, hFont);

    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkColor(hdc, RGB(0, 0, 255));

    SIZE textSize;
    if (!GetTextExtentPoint32A(hdc, text.c_str(), (int)text.length(), &textSize)) DebugConsoleOutput("Error: GetTextExtentPoint32A() inside font creation", false, "red");
    if (textSize.cx > FontTextureWidth) textSize.cx = FontTextureWidth;
    if (textSize.cy > FontTextureHeight) textSize.cy = FontTextureHeight;

    if (!TextOutA(hdc, 0, textSize.cy, text.c_str(), (int)text.length())) DebugConsoleOutput("Error: TextOutA() inside font creation", false, "red");

    if (!BitBlt(hdc, 0, 0, FontTextureWidth, FontTextureHeight, hdc, 0, 0, SRCCOPY)) DebugConsoleOutput("Error: BitBlt() inside font creation", false, "red");

    BITMAPINFO bitmapInfo;
    ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = FontTextureWidth;
    bitmapInfo.bmiHeader.biHeight = -FontTextureHeight;
    bitmapInfo.bmiHeader.biSizeImage = FontTextureWidth * FontTextureHeight * 4;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 24;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    ZeroMemory(FontTextureRGBBuffer, FontTextureRGBBufferSize);
    if (GetDIBits(hdc, hBitmap, 0, FontTextureHeight, FontTextureRGBBuffer, &bitmapInfo, DIB_RGB_COLORS) == 0) DebugConsoleOutput("Error: GetDIBits() inside font creation - 0 lines copied", false, "red");
    for (int h = textSize.cy; h < FontTextureHeight; h++)
    {
        int hPix = SurfaceTextureHeight - h - 1 - y + textSize.cy;
        if (hPix < 0) break;
        if (hPix >= 1080) continue;
        for (int w = 0; w < textSize.cx; w++)
        {
            if (FontTextureRGBBuffer[((h * FontTextureWidth) + w) * 3] > 0x00)
            {
                int wPix = 0;
                if (align == "left") wPix = x + w;
                if (align == "right") wPix = x + w - textSize.cx;
                if (align == "center") wPix = x + w - (textSize.cx / 2);
                if (wPix < 0) continue;
                if (wPix >= 1920) continue;
                int offset = ((hPix * SurfaceTextureWidth) + wPix) * 4;
                SetTexturePixel(offset, color, alpha);
            }
        }
    }

    SelectObject(hdc, oldFont);
    SelectObject(hdc, oldBitmap);
    DeleteObject(hBitmap);
}

void DrawRectangleToTexture(int x, int y, int w, int h, unsigned char* color, unsigned char alpha)
{
    for (int _h = 0; _h < h; _h++)
    {
        int hPix = SurfaceTextureHeight - _h - 1 - y;
        if (hPix < 0) break;
        if (hPix >= 1080) continue;
        for (int _w = 0; _w < w; _w++)
        {
            int wPix = x + _w;
            if (wPix < 0) continue;
            if (wPix >= 1920) continue;
            int offset = ((hPix * SurfaceTextureWidth) + wPix) * 4;
            SetTexturePixel(offset, color, alpha);
        }
    }
}

void DrawCursorToTexture(int x, int y)
{
    for (int _h = 0; _h < CustomCursorTextureHeight; _h++)
    {
        int hPix = SurfaceTextureHeight - _h - 1 - y;
        if (hPix < 0) break;
        if (hPix >= 1080) continue;
        for (int _w = 0; _w < CustomCursorTextureWidth; _w++)
        {
            int wPix = x + _w;
            if (wPix < 0) continue;
            if (wPix >= 1920) continue;
            int offset = ((hPix * SurfaceTextureWidth) + wPix) * 4;
            unsigned char arrowColor[4];
            std::memcpy(arrowColor, CustomCursorTextureRaw + ((((CustomCursorTextureHeight - (1 + _h)) * CustomCursorTextureWidth) + _w) * 4), 4);
            SetTexturePixel(offset, arrowColor, arrowColor[3]);
        }
    }
}

void LoadFormTextures()
{
    std::string csd = GetGlobalSetting("config_settings_directory");

    // Overview form
    std::string fileNameOverview = csd + "imgs\\" + "Overview.raw";
    FILE* fileOverview = fopen(fileNameOverview.c_str(), "rb");
    unsigned char* dataOverview = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataOverview, 1, SurfaceTextureDimension, fileOverview);
    fclose(fileOverview);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureOverview[pixelS + 0] = dataOverview[pixelT + 0];
            FormTextureOverview[pixelS + 1] = dataOverview[pixelT + 1];
            FormTextureOverview[pixelS + 2] = dataOverview[pixelT + 2];
            FormTextureOverview[pixelS + 3] = dataOverview[pixelT + 3];
        }
    }
    free(dataOverview);

    // Debug Values form
    std::string fileNameDebugValues = csd + "imgs\\" + "DebugValues.raw";
    FILE* fileDebugValues = fopen(fileNameDebugValues.c_str(), "rb");
    unsigned char* dataDebugValues = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataDebugValues, 1, SurfaceTextureDimension, fileDebugValues);
    fclose(fileDebugValues);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureDebugValues[pixelS + 0] = dataDebugValues[pixelT + 0];
            FormTextureDebugValues[pixelS + 1] = dataDebugValues[pixelT + 1];
            FormTextureDebugValues[pixelS + 2] = dataDebugValues[pixelT + 2];
            FormTextureDebugValues[pixelS + 3] = dataDebugValues[pixelT + 3];
        }
    }
    free(dataDebugValues);

    // Debug Functions form
    std::string fileNameDebugFunctions = csd + "imgs\\" + "DebugFunctions.raw";
    FILE* fileDebugFunctions = fopen(fileNameDebugFunctions.c_str(), "rb");
    unsigned char* dataDebugFunctions = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataDebugFunctions, 1, SurfaceTextureDimension, fileDebugFunctions);
    fclose(fileDebugFunctions);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureDebugFunctions[pixelS + 0] = dataDebugFunctions[pixelT + 0];
            FormTextureDebugFunctions[pixelS + 1] = dataDebugFunctions[pixelT + 1];
            FormTextureDebugFunctions[pixelS + 2] = dataDebugFunctions[pixelT + 2];
            FormTextureDebugFunctions[pixelS + 3] = dataDebugFunctions[pixelT + 3];
        }
    }
    free(dataDebugFunctions);

    // Savefile Editor form
    std::string fileNameSavefileEditor = csd + "imgs\\" + "SavefileEditor.raw";
    FILE* fileSavefileEditor = fopen(fileNameSavefileEditor.c_str(), "rb");
    unsigned char* dataSavefileEditor = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataSavefileEditor, 1, SurfaceTextureDimension, fileSavefileEditor);
    fclose(fileSavefileEditor);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureSavefileEditor[pixelS + 0] = dataSavefileEditor[pixelT + 0];
            FormTextureSavefileEditor[pixelS + 1] = dataSavefileEditor[pixelT + 1];
            FormTextureSavefileEditor[pixelS + 2] = dataSavefileEditor[pixelT + 2];
            FormTextureSavefileEditor[pixelS + 3] = dataSavefileEditor[pixelT + 3];
        }
    }
    free(dataSavefileEditor);

    // Savefile Editor Select form
    std::string fileNameSavefileEditorSelect = csd + "imgs\\" + "SavefileEditorSelect.raw";
    FILE* fileSavefileEditorSelect = fopen(fileNameSavefileEditorSelect.c_str(), "rb");
    unsigned char* dataSavefileEditorSelect = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataSavefileEditorSelect, 1, SurfaceTextureDimension, fileSavefileEditorSelect);
    fclose(fileSavefileEditorSelect);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureSavefileEditorSelect[pixelS + 0] = dataSavefileEditorSelect[pixelT + 0];
            FormTextureSavefileEditorSelect[pixelS + 1] = dataSavefileEditorSelect[pixelT + 1];
            FormTextureSavefileEditorSelect[pixelS + 2] = dataSavefileEditorSelect[pixelT + 2];
            FormTextureSavefileEditorSelect[pixelS + 3] = dataSavefileEditorSelect[pixelT + 3];
        }
    }
    free(dataSavefileEditorSelect);

    // Supervision form
    std::string fileNameSupervision = csd + "imgs\\" + "Supervision.raw";
    FILE* fileSupervision = fopen(fileNameSupervision.c_str(), "rb");
    unsigned char* dataSupervision = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataSupervision, 1, SurfaceTextureDimension, fileSupervision);
    fclose(fileSupervision);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureSupervision[pixelS + 0] = dataSupervision[pixelT + 0];
            FormTextureSupervision[pixelS + 1] = dataSupervision[pixelT + 1];
            FormTextureSupervision[pixelS + 2] = dataSupervision[pixelT + 2];
            FormTextureSupervision[pixelS + 3] = dataSupervision[pixelT + 3];
        }
    }
    free(dataSupervision);

    // Editor Mode form
    std::string fileNameEditormode = csd + "imgs\\" + "EditorMode.raw";
    FILE* fileEditormode = fopen(fileNameEditormode.c_str(), "rb");
    unsigned char* dataEditormode = (unsigned char*)malloc(SurfaceTextureDimension);
    fread(dataEditormode, 1, SurfaceTextureDimension, fileEditormode);
    fclose(fileEditormode);
    for (int h = 0; h < SurfaceTextureHeight; h++) {
        for (int w = 0; w < SurfaceTextureWidth; w++) {
            int pixelT = ((h * SurfaceTextureWidth) + w) * 4;
            int pixelS = (((SurfaceTextureHeight - h - 1) * SurfaceTextureWidth) + w) * 4;
            FormTextureEditormode[pixelS + 0] = dataEditormode[pixelT + 0];
            FormTextureEditormode[pixelS + 1] = dataEditormode[pixelT + 1];
            FormTextureEditormode[pixelS + 2] = dataEditormode[pixelT + 2];
            FormTextureEditormode[pixelS + 3] = dataEditormode[pixelT + 3];
        }
    }
    free(dataEditormode);

    // Custom cursor
    std::string fileNameCustomCursor = csd + "imgs\\" + "CustomCursor.raw";
    FILE* fileCustomCursor = fopen(fileNameCustomCursor.c_str(), "rb");
    unsigned char* dataCustomCursor = (unsigned char*)malloc(CustomCursorTextureDimension);
    fread(dataCustomCursor, 1, CustomCursorTextureDimension, fileCustomCursor);
    fclose(fileCustomCursor);
    for (int h = 0; h < CustomCursorTextureHeight; h++) {
        for (int w = 0; w < CustomCursorTextureWidth; w++) {
            int pixelT = ((h * CustomCursorTextureWidth) + w) * 4;
            int pixelS = (((CustomCursorTextureHeight - h - 1) * CustomCursorTextureWidth) + w) * 4;
            CustomCursorTextureRaw[pixelS + 0] = dataCustomCursor[pixelT + 0];
            CustomCursorTextureRaw[pixelS + 1] = dataCustomCursor[pixelT + 1];
            CustomCursorTextureRaw[pixelS + 2] = dataCustomCursor[pixelT + 2];
            CustomCursorTextureRaw[pixelS + 3] = dataCustomCursor[pixelT + 3];
        }
    }
    free(dataCustomCursor);
}


