#pragma once

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

namespace DashHook {
    struct VehicleDashboardData
    {
        float RPM; // 0x00
        float speed; // 0x04
        float fuel; // 0x08
        float temp; // 0x0C
        float vacuum; // 0x10
        float boost; // 0x14
        float waterTemp; // 0x18
        float oilTemperature; // 0x1C
        float oilPressure; // 0x20
        char _pad[0x3F]; // 0x24 aircraft data
        bool indicator_left; // 0x63
        bool indicator_right; // 0x64
        bool handbrakeLight; // 0x65
        bool engineLight; // 0x66
        bool ABSLight; // 0x67
        bool petrolLight; // 0x68
        bool oilLight; // 0x69
        bool headlights; // 0x6A
        bool fullBeam; // 0x6B
        bool batteryLight; // 0x6C
    };

   extern void (*DashHook_GetData)(VehicleDashboardData*);
   extern void (*DashHook_SetData)(VehicleDashboardData);
}

bool setupDash();
void releaseDash();
