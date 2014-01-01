#pragma once

#include <stdint.h>

#pragma pack(1)

struct Login_World_RegisterRequest_Struct {
	char	shortname[21];				// name the worldserver wants
	char	longname[101];				// name the worldserver wants
	char	account[31];			// account name for the worldserver
	char	password[31];			// password for the name
};

#pragma pack()