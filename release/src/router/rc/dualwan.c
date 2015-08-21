
#include <string.h>
#include "rc.h"

#ifdef RTCONFIG_DUALWAN

#if defined(RTAC88U)
#define MODEL_PROTECT "RT-AC88U"
#endif

#if defined(RTAC3100)
#define MODEL_PROTECT "RT-AC3100"
#endif

#if defined(RTAC5300)
#define MODEL_PROTECT "RT-AC5300"
#endif

#if defined(RTAC87U)
#define MODEL_PROTECT "RT-AC87U"
#endif

#ifndef MODEL_PROTECT
#define MODEL_PROTECT "NOT_SUPPORT"
#endif

void dualwan_control(void)
{
	int sw_mode;
	char dualwan_mode[8];
	char dualwan_wans[16];

#if defined(RTCONFIG_CFEZ) && defined(RTCONFIG_BCMARM)
	if (strcmp(nvram_safe_get("model"), MODEL_PROTECT) != 0){
#else
	if (strcmp(cfe_nvram_safe_get_raw("model"), MODEL_PROTECT) != 0){
#endif
		_dprintf("illegal, cannot enable DualWAN\n");
		return;
	}

	memset(dualwan_mode, 0, 8);
	strcpy(dualwan_mode, nvram_safe_get("wans_mode"));
	memset(dualwan_wans, 0, 16);
	strcpy(dualwan_wans, nvram_safe_get("wans_dualwan"));

	sw_mode = nvram_get_int("sw_mode");

	if(strcmp(dualwan_mode, "lb") != 0) return;

	if (sw_mode != SW_MODE_ROUTER) return;

	while(1){
		f_write_string("/proc/sys/net/ipv4/route/flush", "1", 0, 0);
		f_write_string("/proc/sys/net/ipv4/route/flush", "1", 0, 0);
		f_write_string("/proc/sys/net/ipv4/route/flush", "1", 0, 0);
		sleep(1);
	}
}

#endif

