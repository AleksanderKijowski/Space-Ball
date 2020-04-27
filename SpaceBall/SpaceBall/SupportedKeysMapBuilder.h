#pragma once
#include "FileNotFoundException.h"
#include "WrongFileContentException.h"

class SupportedKeysMapBuilder
{
	public:
		SupportedKeysMapBuilder() {};

		Map<string, int>* BuildSupportedKeysMap();
};