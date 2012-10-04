//
// osekhook.cc
//
// TOPPERS/ATK(OSEK) hook functions for libecrobot.a library
//
// Originally written 9-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//
#include "kernel.h"

/* OSEK provided hooks */
void StartupHook(void){}

void PreTaskHook(void){}

void PostTaskHook(void){}

void ErrorHook(StatusType ercd){}

void ShutdownHook(StatusType ercd){}

