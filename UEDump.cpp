#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "global.h"

char* GetName(UObject* Object)
{
	//Set your own offset for name (In this case is 0x18)
	DWORD NameIndex = *(PDWORD64)((DWORD64)Object + 0x18);

	if (NameIndex < 0 || NameIndex > GNames->Num())
	{
		return NULL;
	}
	else
	{
		if (GNames->IsValidIndex(NameIndex))
		{
			return (char*)GNames->GetById(NameIndex)->AnsiName;
		}
		else
		{
			return (char*)("Unknown");
		}
	}
}

void ObjectDump()
{
	FILE* Log;
	fopen_s(&Log, "ObjectDump.txt", "w+");

	fprintf(Log, "GObjects generated by zWolfi (Circleus)\n\n");

	printf("Total Objects: %d\n", GlobalObjects->ObjObjects.Num());

	for (DWORD64 i = 0x0; i < GlobalObjects->ObjObjects.Num(); i++)
	{
		if (!GlobalObjects->ObjObjects.GetByIndex(i))
		{
			continue; 
		}

		//Uncomment this to print in console
		//printf("Object[%06i] %-50s 0x%llX\n", i, GetName(GObjObjects->ObjObjects.GetByIndex(i)), GObjObjects->ObjObjects.GetByIndex(i));
		
		fprintf(Log, "Object[%06i] %-50s 0x%llX\n", i, GetName(GlobalObjects->ObjObjects.GetByIndex(i)), GlobalObjects->ObjObjects.GetByIndex(i));
	}

	fclose(Log);
	printf("GObjects completed\n");
}

void NameDump()
{
	FILE* Log;
	Log = fopen("NameDump.txt", "w+");

	fprintf(Log, "GNames generated by zWolfi (Circleus)\n\n");

	printf("Total GNames: %d\n", GNames->Num());

	for (DWORD64 i = 0x0; i < GNames->Num(); i++)
	{
		if (GNames->IsValidIndex(i))
		{
			//Uncomment this to print in console
			//printf("Name[%06d] %s\n", i, GNames->GetById(i)->AnsiName);
			
			fprintf(Log, "Name[%06d] %s\n", i, GNames->GetById(i)->AnsiName);
		}
	}

	fclose(Log);
	printf("GNames completed\n");
}