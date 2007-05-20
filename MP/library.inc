$nolist

SWI0                               equ 0x0     ; SWI0
SWI1                               equ 0x1     ; SWI1
SWI2                               equ 0x2     ; SWI2
SWI3                               equ 0x3     ; SWI3
SWI4                               equ 0x4     ; SWI4
DecToHex                           equ 0x5     ; DecToHex
GetAkku                            equ 0x6     ; __arm int GetAkku(int param1,int param2);
GetLP                              equ 0x7     ; GetLP
SetIllumination                    equ 0x8     ; __arm long SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay);
SwitchPhoneOff                     equ 0x9     ; SwitchPhoneOff
fopen                              equ 0xA     ; __arm int fopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber);
fread                              equ 0xB     ; __arm int fread(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);
fwrite                             equ 0xC     ; __arm unsigned int fwrite(int FileHandler, char * cBuffer, int iByteCount, unsigned int *ErrorNumber);
fclose                             equ 0xD     ; __arm void fclose(int FileHandler, unsigned int *ErrorNumber);
fflush                             equ 0xE     ; fflush
lseek                              equ 0xF     ; __arm unsigned int lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2);

mkdir                              equ 0x10    ; __arm int mkdir(const char * cFileName, unsigned int *ErrorNumber);
OpenReadCloseFile                  equ 0x11    ; OpenReadCloseFile
GetFileAttrib                      equ 0x12    ; __arm int GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber);
SetFileAttrib                      equ 0x13    ; __arm int SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber);
malloc                             equ 0x14    ; __arm void *malloc(unsigned int size);
mfree                              equ 0x15    ; __arm void mfree(void *);
sprintf                            equ 0x16    ; __thumb int sprintf(char *buf, char *str, ...);
strcat                             equ 0x17    ; __thumb char * strcat (char *,const char *);
strchr                             equ 0x18    ; __thumb char * strchr (const char *,int);
strcmp                             equ 0x19    ; __arm int  strcmp (const char *,const char *);
strcpy                             equ 0x1A    ; __thumb char * strcpy (char *dest,const char *source);
strlen                             equ 0x1B    ; __thumb unsigned int strlen(char *);
wsAppendChar                       equ 0x1C    ; __thumb void  wsAppendChar (void *WSHDR,int wchar);
wsInsertChar                       equ 0x1D    ; __thumb int wsInsertChar(void *WSHDR,int wchar, int pos);
GetPITaddr                         equ 0x1E    ; __thumb IMGHDR *GetPITaddr(int num);
DrawMainScreen                     equ 0x1F    ; DrawMainScreen

DrawScreenSaver                    equ 0x20    ; DrawScreenSaver
GetImgHeight                       equ 0x21    ; __thumb int GetImgHeight(int picture);
GetImgWidth                        equ 0x22    ; __thumb int GetImgWidth(int picture);
DrawImg                            equ 0x23    ; __thumb void DrawImg(unsigned char x, unsigned char y, short picture);
DrawImage2                         equ 0x24    ; DrawImage2
DrawCanvas                         equ 0x25    ; __thumb void DrawCanvas(void *data, int x1, int y1, int x2, int y2, int flag_one);
DrawImgBW                          equ 0x26    ; __thumb void DrawImgBW(unsigned int x, unsigned int y, unsigned int picture, char *pen, char *brush);
AddIconToIconbar                   equ 0x27    ; AddIconToIconbar
getEELiteMaxID                     equ 0x28    ; getEELiteMaxID
getEEFullMaxID                     equ 0x29    ; getEEFullMaxID
GetEELiteBlockAddress              equ 0x2A    ; __arm int *GetEELiteBlockAddress(short blocknum);
getEELiteBlockSizeVersion          equ 0x2B    ; getEELiteBlockSizeVersion
getEEFullBlockSizeVersion          equ 0x2C    ; getEEFullBlockSizeVersion
StartWriteEELiteBlock              equ 0x2D    ; StartWriteEELiteBlock
FinishWriteEELiteBlock             equ 0x2E    ; FinishWriteEELiteBlock
DeleteEELiteBlock                  equ 0x2F    ; DeleteEELiteBlock

WriteEELiteBlock                   equ 0x30    ; WriteEELiteBlock
StrChrRev                          equ 0x31    ; StrChrRev
PlaySound                          equ 0x32    ; __arm void PlaySound(long param1, long param2, long param3, long tone, long param5);
PlaySound2                         equ 0x33    ; PlaySound2
PlaySoundLoop                      equ 0x34    ; PlaySoundLoop
AlarmClockRing                     equ 0x35    ; AlarmClockRing
GetATCmdString                     equ 0x36    ; GetATCmdString
OriginalATCGSN                     equ 0x37    ; OriginalATCGSN
PostAtCommand                      equ 0x38    ; PostAtCommand
SendATAnswerStr                    equ 0x39    ; SendATAnswerStr
mfree_high                         equ 0x3A    ; mfree_high
MemChr                             equ 0x3B    ; MemChr
setfilesize                        equ 0x3C    ; __arm int setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber);
editOrNewTXTModule                 equ 0x3D    ; editOrNewTXTModule
LoadProcesses                      equ 0x3E    ; LoadProcesses
SelectColor                        equ 0x3F    ; SelectColor

GetVibraStatus                     equ 0x40    ; GetVibraStatus
GetProvider                        equ 0x41    ; GetProvider
IsScreenSaver                      equ 0x42    ; IsScreenSaver
IsUnlocked                         equ 0x43    ; __arm int IsUnlocked(void);
TempLightOn                        equ 0x44    ; TempLightOn
GetWavLen                          equ 0x45    ; GetWavLen
HasNewSMS                          equ 0x46    ; HasNewSMS
HasFlashSMS                        equ 0x47    ; HasFlashSMS
ReadNewSMS                         equ 0x48    ; ReadNewSMS
ReadFlashSMS                       equ 0x49    ; ReadFlashSMS
PlayFile                           equ 0x4A    ; __arm short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int CepId, int Msg, const PLAYFILE_OPT *sfo);
StartMidlet                        equ 0x4B    ; StartMidlet
GetMissedCallsCount                equ 0x4C    ; GetMissedCallsCount
GBS_StartTimerProc                 equ 0x4D    ; __arm void GBS_StartTimerProc(void *htimer, long ms, void ptr());
MsgBoxError                        equ 0x4E    ; __thumb int MsgBoxError(int flag, int LgpId);
MsgBoxYesNo                        equ 0x4F    ; __thumb int MsgBoxYesNo(int flag, int LgpID, void CallBackProc(int));

MsgBoxOkCancel                     equ 0x50    ; __thumb int MsgBoxOkCancel(int flag, int LgpID, void CallBackProc(int));
GetNetMode                         equ 0x51    ; GetNetMode
GetIlluminationDataTable           equ 0x52    ; GetIlluminationDataTable
memcmp_2                           equ 0x53    ; memcmp
StrToInt                           equ 0x54    ; StrToInt
SwitchVibraOnOff                   equ 0x55    ; SwitchVibraOnOff
PlayVibra                          equ 0x56    ; PlayVibra
IsCallAfterTimerStillRunning       equ 0x57    ; IsCallAfterTimerStillRunning
zeromem_2                          equ 0x58    ; __arm void zeromem_2(void *dest,int n);
memcpy_2                           equ 0x59    ; __arm void *memcpy_2(void *dest,const void *source,int cnt);
KeypressOn                         equ 0x5A    ; KeypressOn
KeypressOff                        equ 0x5B    ; KeypressOff
GetCPUClock                        equ 0x5C    ; __arm unsigned char GetCPUClock();
GetCPULoad                         equ 0x5D    ; __thumb unsigned char GetCPULoad();
GetMMIMemUsed                      equ 0x5E    ; GetMMIMemUsed
GetFreeRamAvail                    equ 0x5F    ; __arm int GetFreeRamAvail();

ShowMainMenu                       equ 0x60    ; ShowMainMenu
ShowNativeMenu                     equ 0x61    ; ShowNativeMenu
SetVibraStatus                     equ 0x62    ; SetVibraStatus
Screen_Wallpaper_Flush             equ 0x63    ; Screen_Wallpaper_Flush
TriggerUpdate                      equ 0x64    ; TriggerUpdate
EndCall                            equ 0x65    ; EndCall
EndCallBusy                        equ 0x66    ; EndCallBusy
IsDirectCallActive                 equ 0x67    ; IsDirectCallActive
GetScreenSaverRam                  equ 0x68    ; GetScreenSaverRam
LockShed                           equ 0x69    ; LockShed
UnLockShed                         equ 0x6A    ; UnLockShed
FindFirstFile                      equ 0x6B    ; __arm int FindFirstFile (DIR_ENTRY *DIRENTRY,char *mask,unsigned int *ErrorNumber);
FindNextFile                       equ 0x6C    ; __arm int FindNextFile (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);
FindClose                          equ 0x6D    ; __arm int FindClose (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);
IsCalling                          equ 0x6E    ; __thumb int IsCalling(void);
RefreshGPRSTraffic                 equ 0x6F    ; __thumb void RefreshGPRSTraffic();

GetGPRSTrafficPointer              equ 0x70    ; __arm int *GetGPRSTrafficPointer();
DrawRoundRect                      equ 0x71    ; DrawRoundRect
GetCurrentSecondOfCall             equ 0x72    ; GetCurrentSecondOfCall
GetTypeOfCall                      equ 0x73    ; GetTypeOfCall
GetFunctionPointer                 equ 0x74    ; __thumb void *GetFunctionPointer(char * _shortcut);
IsCanvasBufferSet                  equ 0x75    ; IsCanvasBufferSet(char CanvasID)
GetCanvasBufferPicPtr              equ 0x76    ; GetCanvasBufferPicPtr
set2color_byPaletteAdr             equ 0x77    ; set2color_byPaletteAdr
GetTimeFormat                      equ 0x78    ; GetTimeFormat
DrawObject2Layer                   equ 0x79    ; DrawObject2Layer(LCD_Layer *, DRWOBJ *);
UpdateDisplayByLayerPtr            equ 0x7A    ; UpdateDisplayByLayerPtr(LCD_Layer *);
GetProfileFilter                   equ 0x7B    ; GetProfileFilter
SetVibration                       equ 0x7C    ; __arm unsigned int SetVibration(unsigned int power);
IsIncognitoCall                    equ 0x7D    ; IsIncognitoCall
Rand                               equ 0x7E    ; Rand
IsPlayerOn                         equ 0x7F    ; IsPlayerOn

ShowCallList                       equ 0x80    ; __thumb void int ShowCallList(int list, int zero);
HexToDec                           equ 0x81    ; HexToDec
GetCurrentTrackFilename            equ 0x82    ; GetCurrentTrackFilename
GetPathOfFoundFile                 equ 0x83    ; GetPathOfFoundFile
GetFileStats                       equ 0x84    ; __arm int GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber);
StrCmpNoCase                       equ 0x85    ; StrCmpNoCase
ReadEEPROMData                     equ 0x86    ; ReadEEPROMData
WriteEEPROMData                    equ 0x87    ; WriteEEPROMData
GetAccessoryType                   equ 0x88    ; GetAccessoryType
GetLangMesIntoWS                   equ 0x89    ; GetLangMesIntoWS
GetFreeFlexSpace                   equ 0x8A    ; GetFreeFlexSpace
GetTotalFlexSpace                  equ 0x8B    ; GetTotalFlexSpace
RegExplorerExt                     equ 0x8C    ; RegExplorerExt
GetProfileName                     equ 0x8D    ; GetProfileName
fmove                              equ 0x8E    ; fmove
rmdir                              equ 0x8F    ; rmdir

truncate                           equ 0x90    ; truncate
isdir                              equ 0x91    ; isdir
calloc                             equ 0x92    ; __arm void *calloc(size_t nelem, size_t elsize);
RebootPhone                        equ 0x93    ; RebootPhone
ExecuteFile                        equ 0x94    ; __arm int ExecuteFile (WSHDR *filepath, WSHDR *mimetype);
UnRegExplorerExt                   equ 0x95    ; int UnRegExplorerExt(REGEXPLEXT const *)
GetWavLenByContent                 equ 0x96    ; GetWavLenByContent
CreatePath                         equ 0x97    ; CreatePath
PlaySoundVibra                     equ 0x98    ; PlaySoundVibra
PlayMelodyInMem                    equ 0x99    ; int PlayMelodyInMem(char Unk_0x11,void *MelAddr,int MelSize,int unk2_0xFFFF,int Unk3_0,int Unk4_0);
ChangeVolume                       equ 0x9A    ; int ChangeVolume(unsigned char Volume);
RamAudioParamsAddr                 equ 0x9B    ; RamAudioParamsAddr
CloseScreensaver                   equ 0x9C    ; CloseScreensaver
GetMissedEventsPtr                 equ 0x9D    ; GetMissedEventsPtr ???
GetMissedEventCount                equ 0x9E    ; int GetMissedEventCount(unsigned int Event);
DrawRect                           equ 0x9F    ; DrawRect

ws_sprintf                         equ 0xA0    ; ws_sprintf
wstrcpy_2                          equ 0xA1    ; __thumb WSHDR * wstrcpy_2(WSHDR *wshdr_d,WSHDR *wshdr_s);
ws_GetChar                         equ 0xA2    ; ws_GetChar
ws_2str                            equ 0xA3    ; ws_2str
wsAlloc                            equ 0xA4    ; wsAlloc
wsFree                             equ 0xA5    ; wsFree
ResetGPRSTraffic                   equ 0xA6    ; ResetGPRSTraffic
IsGPRSEnabled                      equ 0xA7    ; IsGPRSEnabled
IsGPRSConnected                    equ 0xA8    ; IsGPRSConnected
KbdLock                            equ 0xA9    ; __thumb void KbdLock();
GetCurrentLocale                   equ 0xAA    ; __thumb char *GetCurrentLocale();
SWI_AB                             equ 0xAB    ; SWI_AB
DrawText                           equ 0xAC    ; DrawText
StrAnsi2Uni                        equ 0xAD    ; StrAnsi2Uni
StrUni2Ansi                        equ 0xAE    ; StrUni2Ansi
Hex2Int                            equ 0xAF    ; Hex2Int

DrawPicWithCanvas                  equ 0xB0    ; DrawPicWithCanvas
DrawColorPicWithCanvas             equ 0xB1    ; DrawColorPicWithCanvas
GetBuildCanvas                     equ 0xB2    ; GetBuildCanvas
Seconds2iTime                      equ 0xB3    ; Seconds2iTime
GetDateTime                        equ 0xB4    ; GetDateTime
GetWeek                            equ 0xB5    ; GetWeek
GetProfile                         equ 0xB6    ; GetProfile
SetProfile                         equ 0xB7    ; SetProfile
dwMODdw                            equ 0xB8    ; dwMODdw
KbdUnlock                          equ 0xB9    ; __thumb void KbdUnlock();
realloc                            equ 0xBA    ; __arm void *realloc(void *ptr, int size);
memset                             equ 0xBB    ; __arm void *memset(void *s, int c, int n);
divide                             equ 0xBC    ; __arm int divide(int divisor, int dividend);
DivBy10                            equ 0xBD    ; __arm int DivBy10(int divident);
RunScaner                          equ 0xBE    ; RunScaner
SpellTime                          equ 0xBF    ; SpellTime

MiniGPS                            equ 0xC0    ; MiniGPS
RunDispatcher                      equ 0xC1    ; RunDispatcher
GetAllPatchesByInject              equ 0xC2    ; GetAllPatchesByInject
ProcessFiles                       equ 0xC3    ; ProcessFiles
GetBuffer                          equ 0xC4    ; GetBuffer
PIT_Manager_Core                   equ 0xC5    ; PIT_Manager_Core
GetAkkuCapacity                    equ 0xC6    ; __arm char GetAkkuCapacity();
CallLibFunByNumber                 equ 0xC7    ; CallLibFunByNumber
RamCap                             equ 0xC8    ; RamCap
RamLS                              equ 0xC9    ; RamLS
RamNet                             equ 0xCA    ; __arm RAMNET* RamNet();
RamRingtoneStatus                  equ 0xCB    ; RamRingtoneStatus
RamMissedCalls                     equ 0xCC    ; RamMissedCalls
RamMissedSMS                       equ 0xCD    ; RamMissedSMS
RamDateTime                        equ 0xCE    ; RamDateTime
RamAlarm                           equ 0xCF    ; RamAlarm

RamAccPoint                        equ 0xD0    ; RamAccPoint
RamScreensaver                     equ 0xD1    ; RamScreensaver
RamAutoTime                        equ 0xD2    ; RamAutoTime
RamStby                            equ 0xD3    ; RamStby
RamMissedMes                       equ 0xD4    ; RamMissedMes
RamIsLocked                        equ 0xD5    ; RamIsLocked
RamNetOnline                       equ 0xD6    ; RamNetOnline
RamScreenBrightness                equ 0xD7    ; RamScreenBrightness
RamMenuAnywhere                    equ 0xD8    ; RamMenuAnywhere
RamShutdownMode                    equ 0xD9    ; RamShutdownMode
RamIsShutdown                      equ 0xDA    ; RamIsShutdown
RamMainscreenAccuIcon              equ 0xDB    ; RamMainscreenAccuIcon
RamRandSeed                        equ 0xDC    ; RamRandSeed
RamCurrentTrack                    equ 0xDD    ; RamCurrentTrack
RamIsSimPresent                    equ 0xDE    ; RamIsSimPresent
RamPressedKey                      equ 0xDF    ; RamPressedKey

RamScreenBuffer                    equ 0xE0    ; __arm void* RamScreenBuffer();
RamMPlayer_CtrlCode                equ 0xE1    ; RamMPlayer_CtrlCode
RamKeyBuffer                       equ 0xE2    ; RamKeyBuffer
RamProfileNum                      equ 0xE3    ; RamProfileNum
FreeRAM                            equ 0xE4    ; FreeRAM
LP_MonthsShort                     equ 0xE5    ; LP_MonthsShort
Pic_Big0                           equ 0xE6    ; Pic_Big0
Pic_Little0                        equ 0xE7    ; Pic_Little0
Pic_Extra                          equ 0xE8    ; Pic_Extra
Pic_Profiles                       equ 0xE9    ; Pic_Profiles
Pic_Vibra                          equ 0xEA    ; Pic_Vibra
Pic_Call                           equ 0xEB    ; Pic_Call
Pic_AdvNet                         equ 0xEC    ; Pic_AdvNet
LP_MonthsLong                      equ 0xED    ; LP_MonthsLong
LP_Weekdays                        equ 0xEE    ; LP_Weekdays
Pic_Calendar                       equ 0xEF    ; Pic_Calendar

Pic_AccuGraph                      equ 0xF0    ; Pic_AccuGraph
BuildCanvas                        equ 0xF1    ; BuildCanvas
lpRAM_PIT                          equ 0xF2    ; lpRAM_PIT
RAM_PIT_Cap                        equ 0xF3    ; RAM_PIT_Cap
strcspn                            equ 0xF4    ; __thumb size_t strcspn(const char *s1, const char *s2);
Ram_LCD_Overlay_Layer              equ 0xF5    ; Ram_LCD_Overlay_Layer
RAM_LCD_Layer_Base_Ptr             equ 0xF6    ; RAM_LCD_Layer_Base_Ptr
;                                  equ 0xF7    ; 
Additional_PIT_address             equ 0xF8    ; Additional_PIT_address
Additional_PIT_start               equ 0xF9    ; Additional_PIT_start
Additional_PIT_end                 equ 0xFA    ; Additional_PIT_end
;                                  equ 0xFB    ; 
PictureRelocationTable             equ 0xFC    ; PictureRelocationTable
PictureRelocationBase              equ 0xFD    ; PictureRelocationBase
NextPictureMagic                   equ 0xFE    ; NextPictureMagic
AddrLibrary                        equ 0xFF    ; AddrLibrary()

GBS_SendMessage                    equ 0x100   ; GBS_SendMessage(int cepid_to, int msg, ...)
GBS_RecieveMessage                 equ 0x101   ; GBS_RecieveMessage(GBS_MSG *)
GBS_AcceptMessage                  equ 0x102   ; GBS_AcceptMessage(void)
GBS_ClearMessage                   equ 0x103   ; GBS_ClearMessage(void)
GBS_PendMessage                    equ 0x104   ; GBS_PendMessage(GBS_MSG *)
CreateGBSproc                      equ 0x105   ; CreateGBSproc(int cepid, const char *name, void (*onMsg)(void), int prio, int unk_zero)
CSM_root                           equ 0x106   ; CSM_root()
CreateCSM                          equ 0x107   ; CreateCSM(const CSM_DESC*,void *,int)
FindCSMbyID                        equ 0x108   ; FindCSMbyID(int id)
DoIDLE                             equ 0x109   ; DoIDLE(void)
GetConfig                          equ 0x10A   ; GetConfig(unsigned int id)
GetMinAdrScan                      equ 0x10B   ; GetMinAdrScan()
GetMaxAdrScan                      equ 0x10C   ; GetMaxAdrScan()
GetCI                              equ 0x10D   ; GetCI()
Vibration                          equ 0x10E   ; Vibration(unsigned int power, unsigned int duration)
freeUSSD                           equ 0x10F   ; freeUSSD()

wstrcopy                           equ 0x110   ; wstrcopy(char *dst, char *src)
GetTypeUSSD                        equ 0x111   ; GetTypeUSSD()
SetUSSD                            equ 0x112   ; SetUSSD(StructUSSDStr *)
strpbrk                            equ 0x113   ; strpbrk(const char *s1,const char *s2)
strncat                            equ 0x114   ; strncat(char *dest,const char *substr,int maxSubLen)
strncmp                            equ 0x115   ; strncmp(const char *s1,const char *s2,int n)
strncpy                            equ 0x116   ; strncpy(char *dest,const char *source,int maxlen)
strrchr                            equ 0x117   ; strrchr(const char *s,int c)
strstr                             equ 0x118   ; strstr(const char *s1,const char *s2)
strtol                             equ 0x119   ; strtol(const char *nptr,char **endptr,int base)
strtoul                            equ 0x11A   ; strtoul(const char *nptr,char **endptr,int base)
snprintf                           equ 0x11B   ; snprintf(char *,int n,const char *format,...)
memcmp                             equ 0x11C   ; memcmp(void *m1,void *m2,int n)
zeromem                            equ 0x11D   ; zeromem(void *dest,int n)
memcpy                             equ 0x11E   ; memcpy(void *dest,const void *source,int cnt)
wstrcpy                            equ 0x11F   ; wstrcpy(WSHDR *wshdr_d,WSHDR *wshdr_s)

wstrncpy                           equ 0x120   ; wstrncpy(WSHDR *,WSHDR *,int)
wstrcat                            equ 0x121   ; wstrcat(WSHDR *wshdr_d,WSHDR *wshdr_s)
wstrncat                           equ 0x122   ; wstrncat(WSHDR *wshdr_d,WSHDR *wshdr_s,int n)
wstrlen                            equ 0x123   ; wstrlen(WSHDR *wshdr)
wsprintf                           equ 0x124   ; wsprintf(WSHDR *,const char *format,...)
AllocWS                            equ 0x125   ; AllocWS(int len)
CutWSTR                            equ 0x126   ; CutWSTR(void *WSHDR,int len)
CreateLocalWS                      equ 0x127   ; CreateLocalWS(WSHDR *wshdr,unsigned __int16 *wsbody,int len)
CreateWS                           equ 0x128   ; CreateWS(void *malloc,void *mfree,int len)
FreeWS                             equ 0x129   ; FreeWS(WSHDR *wshdr)
DrawObject                         equ 0x12A   ; DrawObject(DRWOBJ *)
AddKeybMsgHook                     equ 0x12B   ; AddKeybMsgHook(void *proc)
AddKeybMsgHook_end                 equ 0x12C   ; AddKeybMsgHook_end(void *proc)
RemoveKeybMsgHook                  equ 0x12D   ; RemoveKeybMsgHook(void *proc)
GetPaletteAdrByColorIndex          equ 0x12E   ; GetPaletteAdrByColorIndex(int ColorIndex)
getRGBcolor                        equ 0x12F   ; getRGBcolor(int ColorIndex,void *dest)

getRGBbyPaletteAdr                 equ 0x130   ; getRGBbyPaletteAdr(int *paletteAdr,void *dest)
setColor                           equ 0x131   ; setColor(int a,int r,int g,int b,void *dest)
memmove                            equ 0x132   ; void *memmove(void *dest,const void *source,int cnt);
StoreXYWHtoRECT                    equ 0x133   ; StoreXYWHtoRECT(void *RECT,int x,int y,int w,int h)
StoreXYXYtoRECT                    equ 0x134   ; StoreXYXYtoRECT(void *RECT,int x,int y,int x2,int y2)
IsGuiOnTop                         equ 0x135   ; IsGuiOnTop(int id)
CreateGUI_ID                       equ 0x136   ; CreateGUI_ID(void *gui,int id)
CreateGUI                          equ 0x137   ; CreateGUI(void *gui)
CreateGUI_30or2                    equ 0x138   ; CreateGUI_30or2(void *gui)
CreateGUIWithDummyCSM              equ 0x139   ; CreateGUIWithDummyCSM(void *gui,int flag)
CreateGUIWithDummyCSM_30or2        equ 0x13A   ; CreateGUIWithDummyCSM_30or2(void *gui,int flag)
GeneralFuncF1                      equ 0x13B   ; GeneralFuncF1(int cmd)
GeneralFuncF0                      equ 0x13C   ; GeneralFuncF0(int cmd)
GeneralFunc_flag1                  equ 0x13D   ; GeneralFunc_flag1(int id,int cmd)
GeneralFunc_flag0                  equ 0x13E   ; GeneralFunc_flag0(int id,int cmd)
DirectRedrawGUI                    equ 0x13F   ; DirectRedrawGUI(void)

DirectRedrawGUI_ID                 equ 0x140   ; DirectRedrawGUI_ID(int id)
PendedRedrawGUI                    equ 0x141   ; PendedRedrawGUI(void)
FindCSM                            equ 0x142   ; FindCSM(void *csm_q,int id)
GBS_StartTimer                     equ 0x143   ; GBS_StartTimer(GBSTMR *tmr,int time,int msg,int unk,int cepid)
GBS_StopTimer                      equ 0x144   ; GBS_StopTimer(GBSTMR *tmr)
GBS_GetCurCepid                    equ 0x145   ; GBS_GetCurCepid(void)
LockSched                          equ 0x146   ; LockSched(void)
UnlockSched                        equ 0x147   ; UnlockSched(void)
ShowMSG                            equ 0x148   ; ShowMSG(int flag, int lgp_id)
SetPropTo_Obj1                     equ 0x149   ; SetPropTo_Obj1(DRWOBJ *drwobj,void *rect,int rect_flag,WSHDR *wshdr,int font,int text_flag) !!!=SetWindowText
FreeDrawObject_subobj              equ 0x14A   ; FreeDrawObject_subobj(DRWOBJ *drwobj)
SetColor                           equ 0x14B   ; SetColor(DRWOBJ *drwobj, int *color1, int *color2)
DrawString                         equ 0x14C   ; DrawString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int font,int text_attribute,int *Pen,int *Brush)
GetTopGUI                          equ 0x14D   ; GetTopGUI(void)
FindItemByID                       equ 0x14E   ; FindItemByID(GUI *gui,int id)
GetDataOfItemByID                  equ 0x14F   ; GetDataOfItemByID(GUI *gui,int id)

DrawRoundedFrame                   equ 0x150   ; DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,int *pen,int *brush)
SetPropTo_Obj5                     equ 0x151   ; SetPropTo_Obj5(DRWOBJ *, RECT *, int zero, IMGHDR *Image)
CreateMenu                         equ 0x152   ; CreateMenu(int is_small,int zero1,MENU_DESC *menu,HEADER_DESC *hdr,int zero2,int n_items,int zero4,int zero5)
GBS_RecActDstMessage               equ 0x153   ; GBS_RecActDstMessage(GBS_MSG *)
KillGBSproc                        equ 0x154   ; KillGBSproc(int cepid)
png_create_read_struct             equ 0x155   ; png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
png_create_info_struct             equ 0x156   ; png_create_info_struct(png_structp png_ptr)
png_destroy_read_struct            equ 0x157   ; png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
png_set_sig_bytes                  equ 0x158   ; png_set_sig_bytes(png_structp png_ptr,int num_bytes)
png_read_info                      equ 0x159   ; png_read_info(png_structp png_ptr, png_infop info_ptr)
png_get_IHDR                       equ 0x15A   ; png_get_IHDR(png_structp png_ptr,png_infop info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)
png_malloc                         equ 0x15B   ; png_malloc(png_structp png_ptr, png_uint_32 size)
png_read_image                     equ 0x15C   ; png_read_image(png_structp png_ptr, png_bytepp image)
png_read_end                       equ 0x15D   ; png_read_end(png_structp png_ptr, png_infop info_ptr)
png_get_io_ptr                     equ 0x15E   ; png_voidp png_get_io_ptr(png_structp png_ptr);
png_get_rowbytes                   equ 0x15F   ; png_get_rowbytes(png_structp png_ptr,png_infop info_ptr)

png_read_row                       equ 0x160   ; png_read_row(png_structp png_ptr,png_bytep row,png_bytep dsp_row)
png_init_io                        equ 0x161   ; png_init_io(png_structp png_ptr, int fp)
setjmp                             equ 0x162   ; setjmp(jmp_buf jmpbuf)
AllocEQueue                        equ 0x163   ; AllocEQueue(void *malloc_a, void *mfree_a)
PrepareEditControl                 equ 0x164   ; PrepareEditControl(EDITCONTROL *)
ConstructEditControl               equ 0x165   ; ConstructEditControl(EDITCONTROL *EditControl,int type,int flag,WSHDR *ws,int maxlen)
AddEditControlToEditQend           equ 0x166   ; AddEditControlToEditQend(void *EditQ,EDITCONTROL *EditControl,void *malloc_a)
CreateInputTextDialog              equ 0x167   ; CreateInputTextDialog(const INPUTDIA_DESC *input_desc, const HEADER_DESC *header_desc,void *editq,int do_mfree,WSHDR *)
SetSoftKey                         equ 0x168   ; SetSoftKey(void *gui,SOFTKEY_DESC *,int n)
ExtractEditControl                 equ 0x169   ; ExtractEditControl(void *guidata,int n,EDITCONTROL *)
StoreEditControl                   equ 0x16A   ; StoreEditControl(void *guidata,int n,EDITCONTROL *)
unlink                             equ 0x16B   ; unlink(const char *cFileName,unsigned int *errornumber)
str_2ws                            equ 0x16C   ; str_2ws(WSHDR *ws,char *str,unsigned int size)
UnpackABentry                      equ 0x16D   ; UnpackABentry(AB_UNPRES *,void *abentry,int filesz,int flag);
FreeUnpackABentry                  equ 0x16E   ; FreeUnpackABentry(AB_UNPRES *, void *mfree_adr);
GetTypeOfAB_UNPRES_ITEM            equ 0x16F   ; GetTypeOfAB_UNPRES_ITEM(int);

MakeVoiceCall                      equ 0x170   ; MakeVoiceCall(char *number,int _0x10, int _0x20C0);
SUBPROC                            equ 0x171   ; 171 __arm void SUBPROC(void *,...); //(void (*)(void *, int),void *, int);
REDRAW                             equ 0x172   ; 172 __arm void REDRAW(void);
socket                             equ 0x173   ; __thumb int socket(int af,int type,int protocol);
connect                            equ 0x174   ; __thumb int connect(int sock,SOCK_ADDR *,int name_length);
bind                               equ 0x175   ; __thumb int bind(int sock,SOCK_ADDR *,int name_length);
closesocket                        equ 0x176   ; __thumb int closesocket(int socket);
shutdown                           equ 0x177   ; __thumb int shutdown(int socket,int how);
recv                               equ 0x178   ; __thumb int recv(int socket,void *buf,int len,int flag);
send                               equ 0x179   ; __thumb int send(int socket,const void *buf,int len,int flag);
htons                              equ 0x17A   ; __thumb unsigned __int16 htons(unsigned __int16);
htonl                              equ 0x17B   ; __thumb unsigned int htonl(unsigned int);
socklasterr                        equ 0x17C   ; __arm int socklasterr(void);
SetIDLETMR                         equ 0x17D   ; __thumb void SetIDLETMR(int time_ms,int msg);
RestartIDLETMR                     equ 0x17E   ; __thumb void RestartIDLETMR(void);
DisableIDLETMR                     equ 0x17F   ; __thumb void DisableIDLETMR(void);

EDIT_GetItemNumInFocusedComboBox   equ 0x180   ; __thumb int EDIT_GetItemNumInFocusedComboBox(void *gui);
EDIT_SetTextToFocused              equ 0x181   ; __thumb void EDIT_SetTextToFocused(void *gui,WSHDR *ws);
EDIT_GetFocus                      equ 0x182   ; __thumb int EDIT_GetFocus(void *gui);
EDIT_GetUnFocus                    equ 0x183   ; __thumb int EDIT_GetUnFocus(void *gui);
ConstructComboBox                  equ 0x184   ; __thumb void ConstructComboBox(EDITCONTROL *EditControl,int type,int attr,WSHDR*,int maxlen,int unk_zero,int num_of_items,int start_item);
GBS_WaitForMsg                     equ 0x185   ; __arm int GBS_WaitForMsg(const int *msg_list, int msgs_num, GBS_MSG*, int timeout);
RegisterCepidForSocketWork         equ 0x186   ; __thumb int RegisterCepidForSocketWork(REGSOCKCEPID_DATA *);
RequestLMANConnect                 equ 0x187   ; __thumb int RequestLMANConnect(LMAN_DATA *);
ScreenW                            equ 0x188   ; __arm int ScreenW(void);
ScreenH                            equ 0x189   ; __arm int ScreenH(void);
HeaderH                            equ 0x18A   ; __arm int HeaderH(void);
SoftkeyH                           equ 0x18B   ; __arm int SoftkeyH(void);
GBS_DelTimer                       equ 0x18C   ; void GBS_DelTimer(GBSTMR *)
available0                         equ 0x18D   ; int available0(int sock)
GPRS_OnOff                         equ 0x18E   ; void GPRS_OnOff(int on, int _1)
GetCurMenuItem                     equ 0x18F   ; int GetCurMenuItem(void *gui)

MutexCreate                        equ 0x190   ; void MutexCreate(MUTEX *mtx)
MutexDestroy                       equ 0x191   ; void MutexDestroy(MUTEX *mtx)
MutexLock                          equ 0x192   ; void MutexLock(MUTEX *mtx)
MutexLockEx                        equ 0x193   ; void MutexLockEx(MUTEX *mtx, int flag)
MutexUnlock                        equ 0x194   ; void MutexUnlock(MUTEX *mtx)
SetMenuItemIcon                    equ 0x195   ; void SetMenuItemIcon(void *gui,int item_n,int icon_n)
RefreshGUI                         equ 0x196   ; void RefreshGUI(void)
AllocMenuItem                      equ 0x197   ; void *AllocMenuItem(void *gui)
AllocMenuWS                        equ 0x198   ; WSHDR *AllocMenuWS(void *gui, int len)
SetMenuItemIconArray               equ 0x199   ; void SetMenuItemIconArray(void *gui,void *item,const int *icons)
SetMenuItemText                    equ 0x19A   ; void SetMenuItemText(void *gui,void *item,WSHDR *text,int item_n)
EDIT_SetFocus                      equ 0x19B   ; void EDIT_SetFocus(void *gui, int item)
SEQKILLER                          equ 0x19C   ; 19C __arm void SEQKILLER(void *data, void(*next_in_seq)(void *), void *data_to_kill);
getCpuUsedTime_if_ena              equ 0x19D   ; __arm long long getCpuUsedTime_if_ena(void);
StartCpuUsageCount                 equ 0x19E   ; __arm void StartCpuUsageCount(void);
inflateInit2_                      equ 0x19F   ; __thumb int inflateInit2_(z_streamp strm, int windowBits,const char *version, int stream_size);

inflate                            equ 0x1A0   ; __thumb int inflate(z_streamp strm, int flush);
inflateEnd                         equ 0x1A1   ; __thumb int inflateEnd(z_streamp strm);
ActivateDialUpProfile              equ 0x1A2   ; __thumb int ActivateDialUpProfile(unsigned int cep_id,int profile_num);
GetCurrentGPRSProfile              equ 0x1A3   ; __arm int GetCurrentGPRSProfile(void);
GetDisconnectTime                  equ 0x1A4   ; __arm int GetDisconnectTime(void);
RegisterCepIdForCurProfile         equ 0x1A5   ; __thumb void RegisterCepIdForCurProfile(unsigned int cep_id,int profile_num,unsigned int unk);
IsTimerProc                        equ 0x1A6   ; __arm int IsTimerProc(GBSTMR *);
Get_CC_NC                          equ 0x1A7   ; __thumb char* Get_CC_NC();
png_create_read_struct_2           equ 0x1A8   ; __thumb png_structp png_create_read_struct_2(png_const_charp user_png_ver, png_voidp error_ptr,png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,png_malloc_ptr malloc_fn, png_free_ptr free_fn);
png_set_read_fn                    equ 0x1A9   ; __thumb void png_set_read_fn(png_structp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);
png_read_update_info               equ 0x1AA   ; __thumb void png_read_update_info(png_structp png_ptr,void *info_ptr);
png_set_palette_to_rgb             equ 0x1AB   ; __thumb void png_set_palette_to_rgb(png_structp png_ptr);
png_get_valid                      equ 0x1AC   ; __thumb png_uint_32 png_get_valid(png_structp png_ptr,png_infop info_ptr, png_uint_32 flag);
png_set_tRNS_to_alpha              equ 0x1AD   ; __thumb void png_set_tRNS_to_alpha(png_structp png_ptr);
png_set_filler                     equ 0x1AE   ; __thumb void png_set_filler(png_structp png_ptr,png_uint_32 filler, int flags);
png_set_strip_16                   equ 0x1AF   ; __thumb void png_set_strip_16(png_structp png_ptr);

png_set_packing                    equ 0x1B0   ; __thumb void png_set_packing(png_structp png_ptr);
png_set_gray_to_rgb                equ 0x1B1   ; __thumb void png_set_gray_to_rgb(png_structp png_ptr);
png_check_sig                      equ 0x1B2   ; __thumb int png_check_sig(png_bytep sig, int num);
DrawLine                           equ 0x1B3   ; __thumb void DrawLine(int x,int y,int x2,int y2,int type,int *pen);
DrawRectangle                      equ 0x1B4   ; __thumb void DrawRectangle(int x,int y,int x2,int y2,int flags,int *pen,int *brush);
isnewSGold                         equ 0x1B5   ; int isnewSGold(void);
async_gethostbyname                equ 0x1B6   ; __thumb int async_gethostbyname(const char *host_name,int ****DNR_RES,int *DNR_ID);
str2ip                             equ 0x1B7   ; __thumb unsigned int str2ip(const char *);
EXT_TOP                            equ 0x81B8  ; void *EXT_TOP(void);
PNG_TOP                            equ 0x81B9  ; void *PNG_TOP(void);
LIB_TOP                            equ 0x81BA  ; void *LIB_TOP(void);
DATA_N_SFB                         equ 0x81BB  ; void *DATA_N_SFB(void);
SHA1_Init                          equ 0x1BC   ; __thumb void SHA1_Init(SHA_CTX *c);
SHA1_Update                        equ 0x1BD   ; __thumb void SHA1_Update(SHA_CTX *c, const void *data, unsigned long len);
SHA1_Final                         equ 0x1BE   ; __thumb void SHA1_Final(char *md, SHA_CTX *c);
RSA_new_method                     equ 0x1BF   ; __thumb RSA * RSA_new_method(RSA_METHOD *method);

RSA_free                           equ 0x1C0   ; __thumb void RSA_free (RSA *r);
RSA_sign                           equ 0x1C1   ; __thumb int RSA_sign(int type, char *m, unsigned int m_len, char *sigret, unsigned int *siglen, RSA *rsa);
BN_bin2bn                          equ 0x1C2   ; __thumb BIGNUM *BN_bin2bn(const char *s,int len,BIGNUM *ret);
SetMenuItemCount                   equ 0x1C3   ; __thumb void SetMenuItemCount(void *gui,int n);
SetCursorToMenuItem                equ 0x1C4   ; __thumb void SetCursorToMenuItem(void *gui,int n);
GetFontYSIZE                       equ 0x1C5   ; __thumb int GetFontYSIZE(int font);
EDIT_ExtractFocusedControl         equ 0x1C6   ; __thumb void EDIT_ExtractFocusedControl(void *gui,EDITCONTROL *ec);
EDIT_StoreControlToFocused         equ 0x1C7   ; __thumb int EDIT_StoreControlToFocused(void *gui,EDITCONTROL *ec);
PrepareEditCOptions                equ 0x1C8   ; __thumb EDITC_OPTIONS *PrepareEditCOptions(EDITC_OPTIONS *ec_options);
SetInvertToEditCOptions            equ 0x1C9   ; __thumb void SetInvertToEditCOptions(EDITC_OPTIONS *ec_options, int invert);
SetFontToEditCOptions              equ 0x1CA   ; __thumb void SetFontToEditCOptions(EDITC_OPTIONS *ec_options, int font);
SetAlignToEditCOptions             equ 0x1CB   ; __thumb void SetAlignToEditCOptions(EDITC_OPTIONS *ec_options, int align);
SetPenColorToEditCOptions          equ 0x1CC   ; __thumb void SetPenColorToEditCOptions(EDITC_OPTIONS *ec_options, int pen);
SetBrushColorToEditCOptions        equ 0x1CD   ; __thumb void SetBrushColorToEditCOptions(EDITC_OPTIONS *ec_options, int brush);
CopyOptionsToEditControl           equ 0x1CE   ; __thumb void CopyOptionsToEditControl(EDITCONTROL *ec,EDITC_OPTIONS *ec_options);
get_regextpnt_by_uid               equ 0x1CF   ; __arm REGEXPLEXT_ARM_NEW *get_regextpnt_by_uid(int uid);

GetExtUid_ws                       equ 0x1D0   ; __arm int GetExtUid_ws(WSHDR * ext);
EDIT_RemoveEditControl             equ 0x1D1   ; __thumb void EDIT_RemoveEditControl(void *gui,int n,EDITCONTROL *);
EDIT_InsertEditControl             equ 0x1D2   ; __thumb void EDIT_InsertEditControl(void *gui,int n,EDITCONTROL *);
EDIT_GetCursorPos                  equ 0x1D3   ; __thumb int EDIT_GetCursorPos(void *gui);
EDIT_SetCursorPos                  equ 0x1D4   ; __thumb void EDIT_SetCursorPos(void *gui, int pos);
Get_Phone_Info                     equ 0x1D5   ; __arm char *Get_Phone_Info(int InfoIndex);
png_set_gray_1_2_4_to_8            equ 0x1D6   ; __thumb void png_set_gray_1_2_4_to_8(png_structp png_ptr);
png_set_invert_mono                equ 0x1D7   ; __thumb void png_set_invert_mono(png_structp png_ptr);
EDIT_IsMarkModeActive              equ 0x1D8   ; __thumb int EDIT_IsMarkModeActive(void *gui);
EDIT_GetMarkedText                 equ 0x1D9   ; __thumb int EDIT_GetMarkedText(void *gui,WSHDR *dest);
SendSMS                            equ 0x1DA   ; __thumb void SendSMS(WSHDR *ws,const char *num,int cepid,int msg,int flag);
IncommingPDU                       equ 0x1DB   ; __arm PDU *IncommingPDU(void);
wstrchr                            equ 0x1DC   ; __thumb short wstrchr(WSHDR *ws,unsigned int start_pos,unsigned int wchar);
wstrrchr                           equ 0x1DD   ; __thumb short wstrrchr(WSHDR *ws,unsigned int max_pos,unsigned int wchar);
EDIT_SetTextToEditControl          equ 0x1DE   ; __thumb int EDIT_SetTextToEditControl(void *gui,int n,WSHDR *ws);
EDIT_GetUserPointer                equ 0x1DF   ; __thumb void *EDIT_GetUserPointer(void *gui);

MenuGetUserPointer                 equ 0x1E0   ; __thumb void *MenuGetUserPointer(void *gui);
GetSymbolWidth                     equ 0x1E1   ; __thumb int GetSymbolWidth(int wchar,int font);
ws_2utf8                           equ 0x1E2   ; __thumb int ws_2utf8(WSHDR *from, char *to , int *result_length, int max_len);
utf8_2ws                           equ 0x1E3   ; __thumb int utf8_2ws(WSHDR *ws,char *utf8_str, unsigned int maxLen);
GetPicNByUnicodeSymbol             equ 0x1E4   ; __thumb int GetPicNByUnicodeSymbol(int wchar);
EDIT_OpenOptionMenuWithUserItems   equ 0x1E5   ; __thumb int EDIT_OpenOptionMenuWithUserItems(void *gui, void (*itemhandler)(USR_MENU_ITEM *item), int zero, int to_add);
Menu_SetItemCountDyn               equ 0x1E6   ; __thumb void Menu_SetItemCountDyn(void *gui, int n);
GetLastJavaApplication             equ 0x1E7   ; char *GetLastJavaApplication()
IsNoJava                           equ 0x1E8   ; __arm int IsNoJava();
create_imghdr                      equ 0x1E9   ; __arm IMGHDR *create_imghdr(const char *fname, int type);
GetMaxDynIcon                      equ 0x1EA   ; __thumb int GetMaxDynIcon(void);
RAM_IMSI                           equ 0x81EB  ; char *RAM_IMSI()
FreeDynIcon                        equ 0x1EC   ; __thumb void FreeDynIcon(int picture);
IsDynIconBusy                      equ 0x1ED   ; __thumb int IsDynIconBusy(int picture);
ProgressCalculate                  equ 0x1EE   ; ProgressCalculate(int current, int total)
SetDynIcon                         equ 0x1EF   ; __thumb void SetDynIcon(int picture,IMGHDR *img,char *bitmap);

filecopy                           equ 0x1F0   ; filecopy
filecopy_op_announce               equ 0x1F1   ; filecopy_op_announce
devmenu_config_IsCheckboxOff       equ 0x1F2   ; devmenu_config_IsCheckboxOff
GetSessionAge                      equ 0x1F3   ; GetSessionAge
RAM_SPN                            equ 0x81F4  ; char *RAM_SPN();
sscanf                             equ 0x1F5   ; __thumb int sscanf(const char *, const char *, ...);
GetPitAdrBy0xE200Symbol            equ 0x1F6   ; __thumb IMGHDR* GetPitAdrBy0xE200Symbol(int uni_symbol);
GetFileSize                        equ 0x1F7   ; long GetFileSize(char *Filename)
GetPlayStatus                      equ 0x1F8   ; int GetPlayStatus(void)
SendMP_cmd                         equ 0x1F9   ; void SendMP_cmd(cmd,substract);
RamVolumeStep                      equ 0x1FA   ; char *RamVolumeStep();
RamMediaIsPlaying                  equ 0x1FB   ; __arm char *RamMediaIsPlaying()
CloseCSM                           equ 0x1FC   ; __thumb void CloseCSM(int id);
SetProp2Square_v2                  equ 0x1FD   ; SetProp2Square_v2
RamLighterPower                    equ 0x1FE   ; char *RamLighterPower();
MEDIA_PLAYLAST                     equ 0x1FF   ; void MEDIA_PLAYLAST();

ScreenShoot                        equ 0x200   ; ScreenShoot
SetProp2ImageOrCanvas              equ 0x201   ; void SetProp2ImageOrCanvas(DRWOBJ *, RECT *, int zero, IMGHDR *Image, int bleed_x, int bleed_y);
fillTriangle                       equ 0x202   ; void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int flag, char *pen, char *brush);
SetPixel                           equ 0x203   ; void SetPixel(int x,int y,char *color);
drawArc                            equ 0x204   ; void drawArc(int x1,int y1,int x2,int y2,int a1,int a2,int flag,char *pen,char *brush);
SetProp2Square_v1                  equ 0x205   ; SetProp2Square_v1
srand                              equ 0x206   ; __thumb void srand(unsigned int seed);
DrawScrollString                   equ 0x207   ; __thumb DrawScrollString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int xdisp,int font,int text_attribute,char *Pen,char *Brush);
Get_WS_width                       equ 0x208   ; int Get_WS_width(WSHDR *ws, int font);
FindGUIbyId                        equ 0x209   ; __thumb void *FindGUIbyId(int id, CSM_RAM **csm);
EDIT_SetDate                       equ 0x20A   ; __thumb void EDIT_SetDate(void *gui,int n,TDate *dd);
EDIT_SetTime                       equ 0x20B   ; __thumb void EDIT_SetTime(void *gui,int n,TTime *tt);
EDIT_GetDate                       equ 0x20C   ; __thumb void EDIT_GetDate(void *gui,int n,TDate *dd);
EDIT_GetTime                       equ 0x20D   ; __thumb void EDIT_GetTime(void *gui,int n,TTime *tt);
ConstructEditTime                  equ 0x20E   ; __thumb int ConstructEditTime(EDITCONTROL *EditControl,TTime *time);
ConstructEditDate                  equ 0x20F   ; __thumb int ConstructEditDate(EDITCONTROL *EditControl,TDate *date);

GetCurGuiID                        equ 0x210   ; __thumb int GetCurGuiID(void);

$list
