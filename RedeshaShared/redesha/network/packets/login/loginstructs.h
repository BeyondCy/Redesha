#include <stdint.h>

#pragma pack(1)

struct Login_World_RegisterRequest_Struct {
	char	name[201];				// name the worldserver wants
	char	account[31];			// account name for the worldserver
	char	password[31];			// password for the name
};

#pragma pack()