/*****************************************************************************/
/*    WDMTMK API v4.00 for Microsoft Windows 98/2000/XP. ELCUS, 1998, 2008.  */
/*    Interface to driver TMK1553B.SYS v4.00 for Windows 98/ME/2000/XP       */
/*    Interface to driver USB_TA_DRV.dll v1.7 for Windows 98/ME/2000/XP      */ 
/*****************************************************************************/

//#ifndef _TMK1553B_
//#define _TMK1553B_
#include <windows.h>
#include <stdio.h>
#include "WDMTMKv2.h"

#pragma warning (disable: 4244) 
#pragma warning (disable: 4700) 
#pragma warning (disable: 4715) 
#pragma warning (disable: 4996) 

int _VTMK4tmkNumber;
HANDLE _ahVTMK4Event[MAX_TMK_NUMBER+1+MAX_USBTA_NUM+1];
HANDLE _hVTMK4VxD[MAX_TMK_NUMBER+1+MAX_USBTA_NUM+1];
int _VTMK4tmkMaxNum = -1;
int _VTMK4mrtMaxNum = -1;
int _VTMK4tmkCurNum;
char _VTMK4usbFlag[MAX_TMK_NUMBER+1+MAX_USBTA_NUM+1];
int _VTMK4tmkDrvnum[MAX_TMK_NUMBER+1+MAX_USBTA_NUM+1];

HINSTANCE hUSBDrvDll = NULL;

DWORD TmkOpen()
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[6];
  DWORD _cbVTMK4Ret;
  PEZUSB_DRIVER_VERSION version;
  int iTMK;
  int nTMK = -1;
  int nMRT = -1;
  int loaded = 1;
  int nTMKb = -1;
  char tmkName[32];
  char cc = 0x5c;

  for (iTMK = 0; iTMK <= MAX_TMK_NUMBER; ++iTMK)
  {
    _VTMK4usbFlag[iTMK] = 0;
    sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",cc,cc,cc,iTMK);
    _hVTMK4VxD[iTMK] = CreateFile(tmkName,
					GENERIC_READ | GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL
					);

    if (_hVTMK4VxD[iTMK] != INVALID_HANDLE_VALUE)
    {
      if (!DeviceIoControl(_hVTMK4VxD[iTMK], (DWORD)IOCTL_TMK_GetVersion, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL) ||
              _awVTMK4OutBuf[0] < TMK_VERSION_MIN)
      {
        CloseHandle(_hVTMK4VxD[iTMK]);
        _hVTMK4VxD[iTMK] = 0;
         return VTMK_BAD_VERSION;
      }
      _VTMK4tmkDrvnum[iTMK] = iTMK;
      nTMK = iTMK;
      if (iTMK < 8)
        nMRT = iTMK;
    }
  }

  if(!hUSBDrvDll)
    hUSBDrvDll = LoadLibrary("USB_TA_DRV.dll");


  if(hUSBDrvDll != NULL)
  {
    if(!(ptmkError = (int*)GetProcAddress(hUSBDrvDll, "tmkError")))
      {ptmkError = &ftmkError;loaded = 0;}
    if(!(tmkconfig_usb = (htmkconfig_usb) GetProcAddress(hUSBDrvDll, "tmkconfig_usb")))
      {tmkconfig_usb = ftmkconfig_usb;loaded = 0;}
    if(!(tmkdone_usb = (htmkdone_usb) GetProcAddress(hUSBDrvDll, "tmkdone_usb")))
      {tmkdone_usb = ftmkdone_usb;loaded = 0;}
    if(!(tmkselect_usb = (htmkselect_usb) GetProcAddress(hUSBDrvDll, "tmkselect_usb")))
      {tmkselect_usb = ftmkselect_usb;loaded = 0;}
    if(!(Read_DLL_EvD_usb = (hRead_DLL_EvD_usb) GetProcAddress(hUSBDrvDll, "Read_DLL_EvD_usb")))
      {Read_DLL_EvD_usb = fRead_DLL_EvD_usb;loaded = 0;}
    if(!(tmktimeout_usb = (htmktimeout_usb) GetProcAddress(hUSBDrvDll, "tmktimeout_usb")))
      {tmktimeout_usb = ftmktimeout_usb;loaded = 0;}
    if(!(tmksetcwbits_usb = (htmksetcwbits_usb) GetProcAddress(hUSBDrvDll, "tmksetcwbits_usb")))
      {tmksetcwbits_usb = ftmksetcwbits_usb;loaded = 0;}
    if(!(tmkclrcwbits_usb = (htmkclrcwbits_usb) GetProcAddress(hUSBDrvDll, "tmkclrcwbits_usb")))
      {tmkclrcwbits_usb = ftmkclrcwbits_usb;loaded = 0;}
    if(!(tmkgetcwbits_usb = (htmkgetcwbits_usb) GetProcAddress(hUSBDrvDll, "tmkclrcwbits_usb")))
      {tmkgetcwbits_usb = ftmkgetcwbits_usb;loaded = 0;}
    if(!(tmkgetmode_usb = (htmkgetmode_usb) GetProcAddress(hUSBDrvDll, "tmkgetmode_usb")))
      {tmkgetmode_usb = ftmkgetmode_usb;loaded = 0;}
    if(!(tmkdefdac_usb = (htmkdefdac_usb) GetProcAddress(hUSBDrvDll, "tmkdefdac_usb")))
      {tmkdefdac_usb = ftmkdefdac_usb;loaded = 0;}
    if(!(tmkgetdac_usb = (htmkgetdac_usb) GetProcAddress(hUSBDrvDll, "tmkgetdac_usb")))
      {tmkgetdac_usb = ftmkgetdac_usb;loaded = 0;}
    if(!(bcreset_usb = (hbcreset_usb) GetProcAddress(hUSBDrvDll, "bcreset_usb")))
      {bcreset_usb = fbcreset_usb;loaded = 0;}
    if(!(bcdefirqmode_usb = (hbcdefirqmode_usb) GetProcAddress(hUSBDrvDll, "bcdefirqmode_usb")))
      {bcdefirqmode_usb = fbcdefirqmode_usb;loaded = 0;}
    if(!(bcgetirqmode_usb = (hbcgetirqmode_usb) GetProcAddress(hUSBDrvDll, "bcgetirqmode_usb")))
      {bcgetirqmode_usb = fbcgetirqmode_usb;loaded = 0;}
    if(!(bcgetmaxbase_usb = (hbcgetmaxbase_usb) GetProcAddress(hUSBDrvDll, "bcgetmaxbase_usb")))
      {bcgetmaxbase_usb = fbcgetmaxbase_usb;loaded = 0;}
    if(!(bcgetmaxbase_usb = (hbcgetmaxbase_usb) GetProcAddress(hUSBDrvDll, "bcgetmaxbase_usb")))
      {bcgetmaxbase_usb = fbcgetmaxbase_usb;loaded = 0;}
    if(!(bcdefbase_usb = (hbcdefbase_usb) GetProcAddress(hUSBDrvDll, "bcdefbase_usb")))
      {bcdefbase_usb = fbcdefbase_usb;loaded = 0;}
    if(!(bcgetbase_usb = (hbcgetbase_usb) GetProcAddress(hUSBDrvDll, "bcgetbase_usb")))
      {bcgetbase_usb = fbcgetbase_usb;loaded = 0;}
    if(!(bcputw_usb = (hbcputw_usb) GetProcAddress(hUSBDrvDll, "bcputw_usb")))
      {bcputw_usb = fbcputw_usb;loaded = 0;}
    if(!(bcgetw_usb = (hbcgetw_usb) GetProcAddress(hUSBDrvDll, "bcgetw_usb")))
      {bcgetw_usb = fbcgetw_usb;loaded = 0;}
    if(!(bcgetansw_usb = (hbcgetansw_usb) GetProcAddress(hUSBDrvDll, "bcgetansw_usb")))
      {bcgetansw_usb = fbcgetansw_usb;loaded = 0;}
    if(!(bcputblk_usb = (hbcputblk_usb) GetProcAddress(hUSBDrvDll, "bcputblk_usb")))
      {bcputblk_usb = fbcputblk_usb;loaded = 0;}
    if(!(bcgetblk_usb = (hbcgetblk_usb) GetProcAddress(hUSBDrvDll, "bcgetblk_usb")))
      {bcgetblk_usb = fbcgetblk_usb;loaded = 0;}
    if(!(bcdefbus_usb = (hbcdefbus_usb) GetProcAddress(hUSBDrvDll, "bcdefbus_usb")))
      {bcdefbus_usb = fbcdefbus_usb;loaded = 0;}
    if(!(bcgetbus_usb = (hbcgetbus_usb) GetProcAddress(hUSBDrvDll, "bcgetbus_usb")))
      {bcgetbus_usb = fbcgetbus_usb;loaded = 0;}
    if(!(bcstart_usb = (hbcstart_usb) GetProcAddress(hUSBDrvDll, "bcstart_usb")))
      {bcstart_usb = fbcstart_usb;loaded = 0;}
    if(!(bcstartx_usb = (hbcstartx_usb) GetProcAddress(hUSBDrvDll, "bcstartx_usb")))
      {bcstartx_usb = fbcstartx_usb;loaded = 0;}
    if(!(bcdeflink_usb = (hbcdeflink_usb) GetProcAddress(hUSBDrvDll, "bcdeflink_usb")))
      {bcdeflink_usb = fbcdeflink_usb;loaded = 0;}
    if(!(bcgetlink_usb = (hbcgetlink_usb) GetProcAddress(hUSBDrvDll, "bcgetlink_usb")))
      {bcgetlink_usb = fbcgetlink_usb;loaded = 0;}
    if(!(bcstop_usb = (hbcstop_usb) GetProcAddress(hUSBDrvDll, "bcstop_usb")))
      {bcstop_usb = fbcstop_usb;loaded = 0;}
    if(!(bcgetstate_usb = (hbcgetstate_usb) GetProcAddress(hUSBDrvDll, "bcgetstate_usb")))
      {bcgetstate_usb = fbcgetstate_usb;loaded = 0;}
    if(!(rtreset_usb = (hrtreset_usb) GetProcAddress(hUSBDrvDll, "rtreset_usb")))
      {rtreset_usb = frtreset_usb;loaded = 0;}
    if(!(rtdefirqmode_usb = (hrtdefirqmode_usb) GetProcAddress(hUSBDrvDll, "rtdefirqmode_usb")))
      {rtdefirqmode_usb = frtdefirqmode_usb;loaded = 0;}
    if(!(rtgetirqmode_usb = (hrtgetirqmode_usb) GetProcAddress(hUSBDrvDll, "rtgetirqmode_usb")))
      {rtgetirqmode_usb = frtgetirqmode_usb;loaded = 0;}
    if(!(rtdefmode_usb = (hrtdefmode_usb) GetProcAddress(hUSBDrvDll, "rtdefmode_usb")))
      {rtdefmode_usb = frtdefmode_usb;loaded = 0;}
    if(!(rtgetmode_usb = (hrtgetmode_usb) GetProcAddress(hUSBDrvDll, "rtgetmode_usb")))
      {rtgetmode_usb = frtgetmode_usb;loaded = 0;}
    if(!(rtgetmaxpage_usb = (hrtgetmaxpage_usb) GetProcAddress(hUSBDrvDll, "rtgetmaxpage_usb")))
      {rtgetmaxpage_usb = frtgetmaxpage_usb;loaded = 0;}
    if(!(rtdefpage_usb = (hrtdefpage_usb) GetProcAddress(hUSBDrvDll, "rtdefpage_usb")))
      {rtdefpage_usb = frtdefpage_usb;loaded = 0;}
    if(!(rtgetpage_usb = (hrtgetpage_usb) GetProcAddress(hUSBDrvDll, "rtgetpage_usb")))
      {rtgetpage_usb = frtgetpage_usb;loaded = 0;}
    if(!(rtdefpagepc_usb = (hrtdefpagepc_usb) GetProcAddress(hUSBDrvDll, "rtdefpagepc_usb")))
      {rtdefpagepc_usb = frtdefpagepc_usb;loaded = 0;}
    if(!(rtdefpagebus_usb = (hrtdefpagebus_usb) GetProcAddress(hUSBDrvDll, "rtdefpagebus_usb")))
      {rtdefpagebus_usb = frtdefpagebus_usb;loaded = 0;}
    if(!(rtgetpagepc_usb = (hrtgetpagepc_usb) GetProcAddress(hUSBDrvDll, "rtgetpagepc_usb")))
      {rtgetpagepc_usb = frtgetpagepc_usb;loaded = 0;}
    if(!(rtgetpagebus_usb = (hrtgetpagebus_usb) GetProcAddress(hUSBDrvDll, "rtgetpagebus_usb")))
      {rtgetpagebus_usb = frtgetpagebus_usb;loaded = 0;}
    if(!(rtdefaddress_usb = (hrtdefaddress_usb) GetProcAddress(hUSBDrvDll, "rtdefaddress_usb")))
      {rtdefaddress_usb = frtdefaddress_usb;loaded = 0;}
    if(!(rtgetaddress_usb = (hrtgetaddress_usb) GetProcAddress(hUSBDrvDll, "rtgetaddress_usb")))
      {rtgetaddress_usb = frtgetaddress_usb;loaded = 0;}
    if(!(rtdefsubaddr_usb = (hrtdefsubaddr_usb) GetProcAddress(hUSBDrvDll, "rtdefsubaddr_usb")))
      {rtdefsubaddr_usb = frtdefsubaddr_usb;loaded = 0;}
    if(!(rtgetsubaddr_usb = (hrtgetsubaddr_usb) GetProcAddress(hUSBDrvDll, "rtgetsubaddr_usb")))
      {rtgetsubaddr_usb = frtgetsubaddr_usb;loaded = 0;}
    if(!(rtputw_usb = (hrtputw_usb) GetProcAddress(hUSBDrvDll, "rtputw_usb")))
      {rtputw_usb = frtputw_usb;loaded = 0;}
    if(!(rtgetw_usb = (hrtgetw_usb) GetProcAddress(hUSBDrvDll, "rtgetw_usb")))
      {rtgetw_usb = frtgetw_usb;loaded = 0;}
    if(!(rtputblk_usb = (hrtputblk_usb) GetProcAddress(hUSBDrvDll, "rtputblk_usb")))
      {rtputblk_usb = frtputblk_usb;loaded = 0;}
    if(!(rtgetblk_usb = (hrtgetblk_usb) GetProcAddress(hUSBDrvDll, "rtgetblk_usb")))
      {rtgetblk_usb = frtgetblk_usb;loaded = 0;}
    if(!(rtsetanswbits_usb = (hrtsetanswbits_usb) GetProcAddress(hUSBDrvDll, "rtsetanswbits_usb")))
      {rtsetanswbits_usb = frtsetanswbits_usb;loaded = 0;}
    if(!(rtclranswbits_usb = (hrtclranswbits_usb) GetProcAddress(hUSBDrvDll, "rtclranswbits_usb")))
      {rtclranswbits_usb = frtclranswbits_usb;loaded = 0;}
    if(!(rtgetanswbits_usb = (hrtgetanswbits_usb) GetProcAddress(hUSBDrvDll, "rtgetanswbits_usb")))
      {rtgetanswbits_usb = frtgetanswbits_usb;loaded = 0;}
    if(!(rtgetflags_usb = (hrtgetflags_usb) GetProcAddress(hUSBDrvDll, "rtgetflags_usb")))
      {rtgetflags_usb = frtgetflags_usb;loaded = 0;}
    if(!(rtputflags_usb = (hrtputflags_usb) GetProcAddress(hUSBDrvDll, "rtputflags_usb")))
      {rtputflags_usb = frtputflags_usb;loaded = 0;}
    if(!(rtsetflag_usb = (hrtsetflag_usb) GetProcAddress(hUSBDrvDll, "rtsetflag_usb")))
      {rtsetflag_usb = frtsetflag_usb;loaded = 0;}
    if(!(rtclrflag_usb = (hrtclrflag_usb) GetProcAddress(hUSBDrvDll, "rtclrflag_usb")))
      {rtclrflag_usb = frtclrflag_usb;loaded = 0;}
    if(!(rtgetflag_usb = (hrtgetflag_usb) GetProcAddress(hUSBDrvDll, "rtgetflag_usb")))
      {rtgetflag_usb = frtgetflag_usb;loaded = 0;}
    if(!(rtputflag_usb = (hrtputflag_usb) GetProcAddress(hUSBDrvDll, "rtputflag_usb")))
      {rtputflag_usb = frtputflag_usb;loaded = 0;}
    if(!(rtgetstate_usb = (hrtgetstate_usb) GetProcAddress(hUSBDrvDll, "rtgetstate_usb")))
      {rtgetstate_usb = frtgetstate_usb;loaded = 0;}
    if(!(rtbusy_usb = (hrtbusy_usb) GetProcAddress(hUSBDrvDll, "rtbusy_usb")))
      {rtbusy_usb = frtbusy_usb;loaded = 0;}
    if(!(rtlock_usb = (hrtlock_usb) GetProcAddress(hUSBDrvDll, "rtlock_usb")))
      {rtlock_usb = frtlock_usb;loaded = 0;}
    if(!(rtunlock_usb = (hrtunlock_usb) GetProcAddress(hUSBDrvDll, "rtunlock_usb")))
      {rtunlock_usb = frtunlock_usb;loaded = 0;}
    if(!(rtgetcmddata_usb = (hrtgetcmddata_usb) GetProcAddress(hUSBDrvDll, "rtgetcmddata_usb")))
      {rtgetcmddata_usb = frtgetcmddata_usb;loaded = 0;}
    if(!(rtputcmddata_usb = (hrtputcmddata_usb) GetProcAddress(hUSBDrvDll, "rtputcmddata_usb")))
      {rtputcmddata_usb = frtputcmddata_usb;loaded = 0;}
    if(!(mtreset_usb = (hmtreset_usb) GetProcAddress(hUSBDrvDll, "mtreset_usb")))
      {mtreset_usb = fmtreset_usb;loaded = 0;}
    if(!(mtgetsw_usb = (hmtgetsw_usb) GetProcAddress(hUSBDrvDll, "mtgetsw_usb")))
      {mtgetsw_usb = fmtgetsw_usb;loaded = 0;}
    if(!(rtenable_usb = (hrtenable_usb) GetProcAddress(hUSBDrvDll, "rtenable_usb")))
      {rtenable_usb = frtenable_usb;loaded = 0;}
    if(!(mrtselected_usb = (hmrtselected_usb) GetProcAddress(hUSBDrvDll, "mrtselected_usb")))
      {mrtselected_usb = fmrtselected_usb;loaded = 0;}
    if(!(mrtgetstate_usb = (hmrtgetstate_usb) GetProcAddress(hUSBDrvDll, "mrtgetstate_usb")))
      {mrtgetstate_usb = fmrtgetstate_usb;loaded = 0;}
    if(!(mrtdefbrcsubaddr0_usb = (hmrtdefbrcsubaddr0_usb) GetProcAddress(hUSBDrvDll, "mrtdefbrcsubaddr0_usb")))
      {mrtdefbrcsubaddr0_usb = fmrtdefbrcsubaddr0_usb;loaded = 0;}
    if(!(mrtreset_usb = (hmrtreset_usb) GetProcAddress(hUSBDrvDll, "mrtreset_usb")))
      {mrtreset_usb = fmrtreset_usb;loaded = 0;}
    if(!(tmktimer_usb = (htmktimer_usb) GetProcAddress(hUSBDrvDll, "tmktimer_usb")))
      {tmktimer_usb = ftmktimer_usb;loaded = 0;}
    if(!(tmkgettimer_usb = (htmkgettimer_usb) GetProcAddress(hUSBDrvDll, "tmkgettimer_usb")))
      {tmkgettimer_usb = ftmkgettimer_usb;loaded = 0;}
    if(!(tmkgettimerl_usb = (htmkgettimerl_usb) GetProcAddress(hUSBDrvDll, "tmkgettimerl_usb")))
      {tmkgettimerl_usb = ftmkgettimerl_usb;loaded = 0;}
    if(!(bcgetmsgtime_usb = (hbcgetmsgtime_usb) GetProcAddress(hUSBDrvDll, "bcgetmsgtime_usb")))
      {bcgetmsgtime_usb = fbcgetmsgtime_usb;loaded = 0;}
    if(!(rtgetmsgtime_usb = (hrtgetmsgtime_usb) GetProcAddress(hUSBDrvDll, "rtgetmsgtime_usb")))
      {rtgetmsgtime_usb = frtgetmsgtime_usb;loaded = 0;}
    if(!(tmkgethwver_usb = (htmkgethwver_usb) GetProcAddress(hUSBDrvDll, "tmkgethwver_usb")))
      {tmkgethwver_usb = ftmkgethwver_usb;loaded = 0;}
    if(!(tmkgetevtime_usb = (htmkgetevtime_usb) GetProcAddress(hUSBDrvDll, "tmkgetevtime_usb")))
      {tmkgetevtime_usb = ftmkgetevtime_usb;loaded = 0;}
    if(!(tmkdefevent_usb = (htmkdefevent_usb) GetProcAddress(hUSBDrvDll, "tmkdefevent_usb")))
      {tmkdefevent_usb = ftmkdefevent_usb;loaded = 0;}
    if(!(tmkswtimer_usb = (htmkswtimer_usb) GetProcAddress(hUSBDrvDll, "tmkswtimer_usb")))
      {tmkswtimer_usb = ftmkswtimer_usb;loaded = 0;}
    if(!(tmkgetswtimer_usb = (htmkgetswtimer_usb) GetProcAddress(hUSBDrvDll, "tmkgetswtimer_usb")))
      {tmkgetswtimer_usb = ftmkgetswtimer_usb;loaded = 0;}
    if(!(tmktimeout_usb = (htmktimeout_usb) GetProcAddress(hUSBDrvDll, "tmktimeout_usb")))
      {tmktimeout_usb = ftmktimeout_usb;loaded = 0;}
    if(!(mrtdefbrcpage_usb = (hmrtdefbrcpage_usb) GetProcAddress(hUSBDrvDll, "mrtdefbrcpage_usb")))
      {mrtdefbrcpage_usb = fmrtdefbrcpage_usb;loaded = 0;}
    if(!(mrtgetbrcpage_usb = (hmrtgetbrcpage_usb) GetProcAddress(hUSBDrvDll, "mrtgetbrcpage_usb")))
      {mrtgetbrcpage_usb = fmrtgetbrcpage_usb;loaded = 0;}

    if(!(MonitorHwStart_usb = (hMonitorHwStart_usb) GetProcAddress(hUSBDrvDll, "MonitorHwStart_usb")))
      {MonitorHwStart_usb = fMonitorHwStart_usb;loaded = 0;}
    if(!(MonitorHwGetMessage_usb = (hMonitorHwGetMessage_usb) GetProcAddress(hUSBDrvDll, "MonitorHwGetMessage_usb")))
      {MonitorHwGetMessage_usb = fMonitorHwGetMessage_usb;loaded = 0;}
    if(!(MonitorHwStop_usb = (hMonitorHwStop_usb) GetProcAddress(hUSBDrvDll, "MonitorHwStop_usb")))
      {MonitorHwStop_usb = fMonitorHwStop_usb;loaded = 0;}
                
    if(loaded)
    {
      nTMKb = nTMK;
      for(iTMK = 0; iTMK <= MAX_USBTA_NUM; ++iTMK)
      {
        _VTMK4usbFlag[nTMKb+1+iTMK] = 0;
        sprintf (tmkName,"%c%c.%cEZUSB-%d",cc,cc,cc,iTMK);
        _hVTMK4VxD[nTMKb+1+iTMK] = CreateFile(tmkName,
				 GENERIC_READ | GENERIC_WRITE,
				 0,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL,
				 NULL
				);

        if (_hVTMK4VxD[nTMKb+1+iTMK] != INVALID_HANDLE_VALUE)
        {
          DeviceIoControl(_hVTMK4VxD[nTMKb+1+iTMK], (DWORD)IOCTL_EZUSB_GET_DRIVER_VERSION, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 6, &_cbVTMK4Ret, NULL);
          version = (PEZUSB_DRIVER_VERSION) _awVTMK4OutBuf;

          if(((DWORD)(version->MajorVersion << 16)+(DWORD)(version->MinorVersion)) < ((DWORD)(EZUSB_MAJOR_VERSION_MIN << 16)+(DWORD)(EZUSB_MINOR_VERSION_MIN)))
          {
            CloseHandle(_hVTMK4VxD[nTMKb+1+iTMK]);
          }
          else
          {
            _VTMK4usbFlag[iTMK+1 + nTMKb] = 1;
            _VTMK4tmkDrvnum[iTMK+1+nTMKb]=iTMK;
            nTMK = iTMK+1+nTMKb;
            if (nTMK < 8)
              nMRT = nTMK;
            CloseHandle(_hVTMK4VxD[nTMKb+1+iTMK]);
          }
        }
      }
    }
  }

  if (nTMK == -1) 
    return 1;
  
  _VTMK4tmkMaxNum = nTMK;
  _VTMK4mrtMaxNum = nMRT;
  for (iTMK = 0; iTMK <= _VTMK4tmkMaxNum; ++iTMK)
  {
    if (_hVTMK4VxD[iTMK] != INVALID_HANDLE_VALUE) 
    {
      CloseHandle(_hVTMK4VxD[iTMK]);
    }
    _ahVTMK4Event[iTMK] = 0;
    _hVTMK4VxD[iTMK] = 0;
  }
  return 0;
}

void TmkClose()
{
  int iTMK;
  for (iTMK = 0; iTMK <= _VTMK4tmkMaxNum; ++iTMK)
  {
    if (_hVTMK4VxD[iTMK])
    CloseHandle(_hVTMK4VxD[iTMK]);
    _ahVTMK4Event[iTMK] = 0;
    _hVTMK4VxD[iTMK] = 0;
    _VTMK4usbFlag[iTMK] = 0;
    _VTMK4tmkDrvnum[iTMK] = -1;
  }

  _VTMK4tmkMaxNum = -1;

  tmkconfig_usb = ftmkconfig_usb;
  tmkdone_usb = ftmkdone_usb;
  tmkselect_usb = ftmkselect_usb;
  tmkdefevent_usb = ftmkdefevent_usb;
  Read_DLL_EvD_usb = fRead_DLL_EvD_usb;
  tmksetcwbits_usb = ftmksetcwbits_usb;
  tmkclrcwbits_usb = ftmkclrcwbits_usb;
  tmkgetcwbits_usb = ftmkgetcwbits_usb;
  tmkgetmode_usb = ftmkgetmode_usb;
  tmkdefdac_usb = ftmkdefdac_usb;
  tmkgetdac_usb = ftmkgetdac_usb;
  bcreset_usb = fbcreset_usb;
  bcdefirqmode_usb = fbcdefirqmode_usb;
  bcgetirqmode_usb = fbcgetirqmode_usb;
  bcgetmaxbase_usb = fbcgetmaxbase_usb;
  bcdefbase_usb = fbcdefbase_usb;
  bcgetbase_usb = fbcgetbase_usb;
  bcputw_usb = fbcputw_usb;
  bcgetw_usb = fbcgetw_usb;
  bcgetansw_usb = fbcgetansw_usb;
  bcputblk_usb = fbcputblk_usb;
  bcgetblk_usb = fbcgetblk_usb;
  bcdefbus_usb = fbcdefbus_usb;
  bcgetbus_usb = fbcgetbus_usb;
  bcstart_usb = fbcstart_usb;
  bcstartx_usb = fbcstartx_usb;
  bcdeflink_usb = fbcdeflink_usb;
  bcgetlink_usb = fbcgetlink_usb;
  bcstop_usb = fbcstop_usb;
  bcgetstate_usb = fbcgetstate_usb;
  rtreset_usb = frtreset_usb;
  rtdefirqmode_usb = frtdefirqmode_usb;
  rtgetirqmode_usb = frtgetirqmode_usb;
  rtdefmode_usb = frtdefmode_usb;
  rtgetmode_usb = frtgetmode_usb;
  rtgetmaxpage_usb = frtgetmaxpage_usb;
  rtdefpage_usb = frtdefpage_usb;
  rtgetpage_usb = frtgetpage_usb;
  rtdefpagepc_usb = frtdefpagepc_usb;
  rtdefpagebus_usb = frtdefpagebus_usb;
  rtgetpagepc_usb = frtgetpagepc_usb;
  rtgetpagebus_usb = frtgetpagebus_usb;
  rtdefaddress_usb = frtdefaddress_usb;
  rtgetaddress_usb = frtgetaddress_usb;
  rtdefsubaddr_usb = frtdefsubaddr_usb;
  rtgetsubaddr_usb = frtgetsubaddr_usb;
  rtputw_usb = frtputw_usb;
  rtgetw_usb = frtgetw_usb;
  rtputblk_usb = frtputblk_usb;
  rtgetblk_usb = frtgetblk_usb;
  rtsetanswbits_usb = frtsetanswbits_usb;
  rtclranswbits_usb = frtclranswbits_usb;
  rtgetanswbits_usb = frtgetanswbits_usb;
  rtgetflags_usb = frtgetflags_usb;
  rtputflags_usb = frtputflags_usb;
  rtsetflag_usb = frtsetflag_usb;
  rtclrflag_usb = frtclrflag_usb;
  rtgetflag_usb = frtgetflag_usb;
  rtputflag_usb = frtputflag_usb;
  rtgetstate_usb = frtgetstate_usb;
  rtbusy_usb = frtbusy_usb;
  rtlock_usb = frtlock_usb;
  rtunlock_usb = frtunlock_usb;
  rtgetcmddata_usb = frtgetcmddata_usb;
  rtputcmddata_usb = frtputcmddata_usb;
  mtreset_usb = fmtreset_usb;
  mtgetsw_usb = fmtgetsw_usb;
  rtenable_usb = frtenable_usb;
  mrtselected_usb = fmrtselected_usb;
  mrtgetstate_usb = fmrtgetstate_usb;
  mrtdefbrcsubaddr0_usb = fmrtdefbrcsubaddr0_usb;
  mrtreset_usb = fmrtreset_usb;
  tmktimer_usb = ftmktimer_usb;
  tmkgettimer_usb = ftmkgettimer_usb;
  tmkgettimerl_usb = ftmkgettimerl_usb;
  bcgetmsgtime_usb = fbcgetmsgtime_usb;
  rtgetmsgtime_usb = frtgetmsgtime_usb;
  tmkgethwver_usb = ftmkgethwver_usb;
  tmkgetevtime_usb = ftmkgetevtime_usb;
  tmkswtimer_usb = ftmkswtimer_usb;
  tmkgetswtimer_usb = ftmkgetswtimer_usb;
  tmktimeout_usb = ftmktimeout_usb;
  mrtdefbrcpage_usb = fmrtdefbrcpage_usb;
  mrtgetbrcpage_usb = fmrtgetbrcpage_usb;

  MonitorHwStart_usb = fMonitorHwStart_usb;
  MonitorHwGetMessage_usb = fMonitorHwGetMessage_usb;
  MonitorHwStop_usb = fMonitorHwStop_usb;

  if(hUSBDrvDll)
    FreeLibrary(hUSBDrvDll);
  hUSBDrvDll = NULL;
}

int tmkgetmaxn()
{
	return _VTMK4tmkMaxNum;
}

int tmkconfig(int tmkNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  char tmkName[32];

  if (_VTMK4tmkMaxNum == -1)
     return TMK_BAD_NUMBER;
  
  if (_hVTMK4VxD[tmkNumber] != 0)
     return TMK_BAD_NUMBER;

  if (_VTMK4usbFlag[tmkNumber])
  {
    sprintf (tmkName,"%c%c.%cEZUSB-%d",0x5c,0x5c,0x5c,_VTMK4tmkDrvnum[tmkNumber]);
    _hVTMK4VxD[tmkNumber] = CreateFile(tmkName,
				 GENERIC_READ | GENERIC_WRITE,
				 0,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL,
				 NULL
				);
    if (_hVTMK4VxD[tmkNumber] == INVALID_HANDLE_VALUE)
      return TMK_BAD_NUMBER;
    else
    {
      if(DeviceIoControl(_hVTMK4VxD[tmkNumber], (DWORD)IOCTL_EZUSB_SET_CURPROC, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL))
      {
        _VTMK4tmkCurNum = tmkNumber;
        return tmkconfig_usb(_VTMK4tmkDrvnum[tmkNumber], 9, 0, 0);
      }
      else
      {
        CloseHandle (_hVTMK4VxD[tmkNumber]);
        _hVTMK4VxD[tmkNumber] = 0;
        return TMK_BAD_NUMBER;
      }
        
    }
  }

  sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,tmkNumber);
  _hVTMK4VxD[tmkNumber] = CreateFile(tmkName,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL
                                     );
  if (_hVTMK4VxD[tmkNumber] == INVALID_HANDLE_VALUE)
    return TMK_BAD_NUMBER;
  else
  {
    _awVTMK4InBuf[0] = (WORD)tmkNumber;
    DeviceIoControl(_hVTMK4VxD[tmkNumber], (DWORD)IOCTL_TMK_tmkconfig, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
    if (_awVTMK4OutBuf[0] != 0) 
    {
      CloseHandle (_hVTMK4VxD[tmkNumber]);
      _hVTMK4VxD[tmkNumber] = 0;
    }
    _VTMK4tmkCurNum = tmkNumber;
    return (int)_awVTMK4OutBuf[0];
  }
}

int tmkdone(int tmkNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  int iTMK;

  if (tmkNumber == ALL_TMKS)
  {
    for (iTMK = 0; iTMK <= _VTMK4tmkMaxNum; ++iTMK)
    {
	if(_VTMK4usbFlag[iTMK])
	{
		_ahVTMK4Event[iTMK] = 0;
  	        if(_hVTMK4VxD[tmkNumber])
  	          CloseHandle (_hVTMK4VxD[tmkNumber]);
	 	_hVTMK4VxD[iTMK] = 0;
		tmkdone_usb(_VTMK4tmkDrvnum[iTMK]);
	}
	else
	{
		_awVTMK4InBuf[0] = (WORD)iTMK;
		DeviceIoControl(_hVTMK4VxD[iTMK], (DWORD)IOCTL_TMK_tmkdone, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);

		_ahVTMK4Event[iTMK] = 0;
		CloseHandle(_hVTMK4VxD[iTMK]);
		_hVTMK4VxD[iTMK] = 0;
	}
    }
  }
  else if (tmkNumber >= 0 && tmkNumber <= _VTMK4tmkMaxNum)
  {
	  if(_VTMK4usbFlag[tmkNumber])
	  {
		  _ahVTMK4Event[tmkNumber] = 0;
		  if(_hVTMK4VxD[tmkNumber])
  		    CloseHandle (_hVTMK4VxD[tmkNumber]);
		  _hVTMK4VxD[tmkNumber] = 0;
		  tmkdone_usb(_VTMK4tmkDrvnum[tmkNumber]);
	  }
	  else
	  {
		  _awVTMK4InBuf[0] = (WORD)tmkNumber;
		  DeviceIoControl(_hVTMK4VxD[tmkNumber], (DWORD)IOCTL_TMK_tmkdone, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);

		  _ahVTMK4Event[tmkNumber] = 0;
		  CloseHandle (_hVTMK4VxD[tmkNumber]);
		  _hVTMK4VxD[tmkNumber] = 0;
	  }
  }

return 0;
}

int tmkselect(int tmkNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;

  if ((_hVTMK4VxD[tmkNumber] != INVALID_HANDLE_VALUE) && (_hVTMK4VxD[tmkNumber] != 0))
  {
    if (_VTMK4usbFlag[tmkNumber])
    {
      _VTMK4tmkCurNum = tmkNumber;
      tmkselect_usb(_VTMK4tmkDrvnum[tmkNumber]);
      return 0;
    }

    _VTMK4tmkCurNum = tmkNumber;

     //**************��������� ��� ��������� ������������� ����**********************************************************
    _awVTMK4InBuf[0] = _VTMK4tmkCurNum; 
    DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkselect, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
    return _awVTMK4OutBuf[0];
    //*******************************************************************************************************************
    //return 0;
  }
  else 
  return TMK_BAD_NUMBER;
}

int tmkselected()
{
	return _VTMK4tmkCurNum;
}

TMK_DATA tmkgetmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int tmkdefdac(int dacValue)
{

  if ((_hVTMK4VxD[_VTMK4tmkCurNum])&&(_VTMK4usbFlag[_VTMK4tmkCurNum]))
    return tmkdefdac_usb(dacValue);
  else
    return TMK_BAD_NUMBER;

}

int tmkgetdac(int *dacValue, int *dacMode)
{
  if ((_hVTMK4VxD[_VTMK4tmkCurNum])&&(_VTMK4usbFlag[_VTMK4tmkCurNum]))
    return tmkgetdac_usb(dacValue, dacMode);
  else
  {
    *dacValue = 0;
    *dacMode = 0;
    return TMK_BAD_NUMBER;
  }
}

void tmksetcwbits(TMK_DATA tmkSetControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkSetControl;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmksetcwbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void tmkclrcwbits(TMK_DATA tmkClrControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkClrControl;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkclrcwbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA tmkgetcwbits()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetcwbits, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void tmkdefevent(HANDLE hEvent, BOOL fEventSet)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DWORD hVxDEvent;

  int iTMK;
  if (hEvent != 0)
  {
    for (iTMK = 0; iTMK <= MAX_TMK_NUMBER; ++iTMK)
    {
      if (hEvent == _ahVTMK4Event[iTMK])
        break;
    }
    if (iTMK > MAX_TMK_NUMBER)
    {
      hVxDEvent = (DWORD)hEvent;
      _ahVTMK4Event[_VTMK4tmkNumber] = hEvent;
    }
  }
  else
  {
    hVxDEvent = 0;
    _ahVTMK4Event[_VTMK4tmkNumber] = 0;
  }

//  hVxDEvent = (DWORD)hEvent;
  _ahVTMK4Event[_VTMK4tmkNumber] = hEvent;
  _awVTMK4InBuf[0] = LOWORD(hVxDEvent);
  _awVTMK4InBuf[1] = HIWORD(hVxDEvent);
  _awVTMK4InBuf[2] = LOWORD(fEventSet);
  _awVTMK4InBuf[3] = HIWORD(fEventSet);
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkdefevent, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void tmkgetevd(TTmkEventData *pEvD)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[6];
  DWORD _cbVTMK4Ret;
  if (!_VTMK4usbFlag[_VTMK4tmkCurNum])
  {
        DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetevd, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 12, &_cbVTMK4Ret, NULL);

	    pEvD->nInt = ((DWORD*)(_awVTMK4OutBuf))[0];
		switch (pEvD->wMode = _awVTMK4OutBuf[2])
		{
		case BC_MODE:
			switch (pEvD->nInt)
			{
			case 1:
			pEvD->bc.wResult = _awVTMK4OutBuf[3];
			break;
			case 2:
			pEvD->bc.wResult = _awVTMK4OutBuf[3];
			pEvD->bc.wAW1 = _awVTMK4OutBuf[4];
			pEvD->bc.wAW2 = _awVTMK4OutBuf[5];
			break;
			case 3:
			pEvD->bcx.wResultX = _awVTMK4OutBuf[3];
			pEvD->bcx.wBase = _awVTMK4OutBuf[4];
			break;
			case 4:
			pEvD->bcx.wBase = _awVTMK4OutBuf[3];
			break;
			}
			break;
		case MT_MODE:
			switch (pEvD->nInt)
			{
			case 3:
			pEvD->mt.wResultX = _awVTMK4OutBuf[3];
			pEvD->mt.wBase = _awVTMK4OutBuf[4];
			break;
			case 4:
			pEvD->mt.wBase = _awVTMK4OutBuf[3];
			break;
			}
			break;
		case RT_MODE:
			switch (pEvD->nInt)
			{
			case 1:
			pEvD->rt.wCmd = _awVTMK4OutBuf[3];
			break;
			case 2:
			case 3:
			pEvD->rt.wStatus = _awVTMK4OutBuf[3];
			break;
			}
			break;
		}
  }
  else
  {
        TListEvD evd_s;
	Read_DLL_EvD_usb(&evd_s);

	pEvD->nInt = evd_s.nInt;
	pEvD->wMode = evd_s.wMode;
	switch (pEvD->wMode)
	{
	case BC_MODE:
	    switch (pEvD->nInt)
	    {
	    case 1:
		pEvD->bc.wResult = evd_s.awEvData[0];
		break;
		case 2:
		pEvD->bc.wResult = evd_s.awEvData[0];
		pEvD->bc.wAW1 = evd_s.awEvData[1];
		pEvD->bc.wAW2 = evd_s.awEvData[2];
		break;
		case 3:
		pEvD->bcx.wResultX = evd_s.awEvData[0];
		pEvD->bcx.wBase = evd_s.awEvData[1];
		break;
		case 4:
		pEvD->bcx.wBase = evd_s.awEvData[0];
		break;
		}
		break;
	case MT_MODE:
	    switch (pEvD->nInt)
	    {
	    case 3:
		pEvD->mt.wResultX = evd_s.awEvData[0];
		pEvD->mt.wBase = evd_s.awEvData[1];
		break;
		case 4:
		pEvD->mt.wBase = evd_s.awEvData[0];
		break;
		}
		break;
	case RT_MODE:
	    switch (pEvD->nInt)
	    {
	    case 1:
		pEvD->rt.wCmd = evd_s.awEvData[0];
		break;
		case 2:
		case 3:
		pEvD->rt.wStatus = evd_s.awEvData[0];
		break;
		}
		break;
	}
  }
}

void tmkgetinfo(TTmkConfigData *pConfD)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = LOWORD(pConfD);
  _awVTMK4InBuf[1] = HIWORD(pConfD);
  if (!_VTMK4usbFlag[_VTMK4tmkCurNum])
  {
      DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetinfo, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
  }
  else
  {
	  pConfD->nType = TA;
	  strcpy(pConfD->szName, "TA1USB");
	  pConfD->wPorts1 = 0;//__tmkPortsAddr1[realnum];
	  pConfD->wPorts2 = 0;//__tmkPortsAddr2[realnum];
	  pConfD->wIrq1 = 0;
	  pConfD->wIrq2 = 0;
	  pConfD->wIODelay = 0;
  }

}

int bcreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void bc_def_tldw(TMK_DATA wTLDW)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = wTLDW;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_def_tldw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void bc_enable_di()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_enable_di, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void bc_disable_di()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_disable_di, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int bcdefirqmode(TMK_DATA bcIrqMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcIrqMode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefirqmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA bcgetirqmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetirqmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA bcgetmaxbase()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetmaxbase, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int bcdefbase(TMK_DATA bcBasePC)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBasePC;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefbase, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA bcgetbase()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetbase, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void bcputw(TMK_DATA bcAddr, TMK_DATA bcData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = bcData;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcputw, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA bcgetw(TMK_DATA bcAddr)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

DWORD bcgetansw(TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcCtrlCode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetansw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}

void bcputblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcputblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void bcgetblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int bcdefbus(TMK_DATA bcBus)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBus;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefbus, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA bcgetbus()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetbus, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int bcstart(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstart, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int bcstartx(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstartx, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int bcdeflink(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdeflink, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

DWORD bcgetlink()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetlink, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}

TMK_DATA bcstop()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstop, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

DWORD bcgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}

int rtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int rtdefirqmode(TMK_DATA rtIrqMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtIrqMode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefirqmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL)
}

TMK_DATA rtgetirqmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetirqmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int rtdefmode(TMK_DATA rtMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtMode;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtgetmaxpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmaxpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int rtdefpage(TMK_DATA rtPage)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPage;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpage, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int rtdefpagepc(TMK_DATA rtPagePC)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPagePC;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpagepc, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int rtdefpagebus(TMK_DATA rtPageBus)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPageBus;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpagebus, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetpagepc()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpagepc, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtgetpagebus()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpagebus, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int rtdefaddress(TMK_DATA rtAddress)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddress;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefaddress, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetaddress()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetaddress, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void rtdefsubaddr(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefsubaddr, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetsubaddr()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetsubaddr, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void rtputw(TMK_DATA rtAddr, TMK_DATA rtData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = rtData;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputw, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetw(TMK_DATA rtAddr)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void rtputblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtgetblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtsetanswbits(TMK_DATA rtSetControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtSetControl;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtsetanswbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtclranswbits(TMK_DATA rtClrControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtClrControl;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtclranswbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetanswbits()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetanswbits, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void rtgetflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax)
{
  WORD _awVTMK4InBuf[5], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetflags, _awVTMK4InBuf, 10, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtputflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax)
{
  WORD _awVTMK4InBuf[5], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputflags, _awVTMK4InBuf, 10, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtsetflag()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtsetflag, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtclrflag()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtclrflag, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetflag(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetflag, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtbusy()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtbusy, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void rtlock(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtlock, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

void rtunlock()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtunlock, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA rtgetcmddata(TMK_DATA rtBusCommand)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtBusCommand;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetcmddata, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtputcmddata(TMK_DATA rtBusCommand, TMK_DATA rtData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtBusCommand;
  _awVTMK4InBuf[1] = rtData;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputcmddata, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int mtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA mtgetsw()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mtgetsw, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtenable(TMK_DATA rtEnable)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtEnable;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtenable, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int mrtgetmaxn()
{
  return _VTMK4mrtMaxNum;
/*
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetmaxn, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return ((int)(_awVTMK4OutBuf[0]));
*/
}

DWORD mrtconfig(int mrtNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  WORD nRT,RT0,iRT;
  char tmkName[32];


  if (_hVTMK4VxD[mrtNumber] != 0)
    return 0;

  if (!_VTMK4usbFlag[mrtNumber])
  {	

  sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,mrtNumber);
  _hVTMK4VxD[mrtNumber] = CreateFile(tmkName,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL
                                    );
  if (_hVTMK4VxD[mrtNumber] == INVALID_HANDLE_VALUE)
    return 0;

  _awVTMK4InBuf[0] = (WORD)mrtNumber;
  DeviceIoControl(_hVTMK4VxD[mrtNumber], (DWORD)IOCTL_TMK_mrtconfig, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  if (_awVTMK4OutBuf[0] != 0&&_awVTMK4OutBuf[1] != 0)
  {
    RT0 =  _awVTMK4OutBuf[0];
    nRT =  _awVTMK4OutBuf[1];
    //������� ����������� ����������
    for (iRT = RT0; iRT < (RT0+nRT); ++iRT)
    {
      if (_hVTMK4VxD[iRT] != 0)
        return 0;
      sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,iRT);
      _hVTMK4VxD[iRT] = CreateFile(tmkName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                        );
      if (_hVTMK4VxD[iRT] == INVALID_HANDLE_VALUE)
        return 0;
    }//for(iRT = RT0;iRT < (RT0+nRT);iRT++)
  }//if(_awVTMK4OutBuf[0] != 0&&_awVTMK4OutBuf[1] != 0)
  return (_awVTMK4OutBuf[0]+(_awVTMK4OutBuf[1]<<16));
  }
  else 
	return 0;						
}

int mrtselected()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtselected, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return ((int)(_awVTMK4OutBuf[0]));
}

TMK_DATA mrtgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

void mrtdefbrcsubaddr0()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCaseVoid(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtdefbrcsubaddr0, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

int mrtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}

TMK_DATA tmktimer(TMK_DATA tmkTimerCtrl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimerCtrl;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmktimer, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD tmkgettimer()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgettimer, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmkgettimerl()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgettimerl, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD bcgetmsgtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetmsgtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
DWORD rtgetmsgtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmsgtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}

TMK_DATA tmkgethwver()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgethwver, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

DWORD tmkgetevtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetevtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmkswtimer(TMK_DATA tmkTimerCtrl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimerCtrl;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkswtimer, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD tmkgetswtimer()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetswtimer, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}

TMK_DATA tmktimeout(TMK_DATA tmkTimeOut)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimeOut;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmktimeout, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int mrtdefbrcpage(TMK_DATA mrtBrcPage)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mrtBrcPage;
//  return (DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtdefbrcpage, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtdefbrcpage, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA mrtgetbrcpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControlCase(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetbrcpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

DWORD MT_Start(DWORD dwBufSize, HANDLE hEvent)
{
  if (_VTMK4usbFlag[_VTMK4tmkCurNum])
  {
    return MonitorHwStart_usb(dwBufSize, hEvent);
  }
  else
    return TMK_BAD_NUMBER;
}

DWORD MT_GetMessage(WORD * Data, DWORD dwBufSize, int FillFlag, DWORD * dwMsWritten)
{
  if (_VTMK4usbFlag[_VTMK4tmkCurNum])
  {
    return MonitorHwGetMessage_usb(Data, dwBufSize, FillFlag, dwMsWritten);
  }
  else
    return TMK_BAD_NUMBER;
}

DWORD MT_Stop()
{
  if (_VTMK4usbFlag[_VTMK4tmkCurNum])
  {
    return MonitorHwStop_usb();
  }
  else
    return TMK_BAD_NUMBER;
}

#pragma warning (default: 4244) 
#pragma warning (default: 4700) 
#pragma warning (default: 4715) 
#pragma warning (default: 4996) 

//#endif
