#include "stdafx.h"
#include "RenderWindowBuilder.h"

RenderWindowBuilder::RenderWindowBuilder()
{
	InitializeWindowSettings();
}

sf::RenderWindow * RenderWindowBuilder::BuildRenderWindow()
{
	var result = new sf::RenderWindow(sf::VideoMode(_settings.Width, _settings.Height), _settings.Title);
	result->setFramerateLimit(_settings.FrameRateLimit);
	result->setVerticalSyncEnabled(_settings.VerticalSyncEnabled);

	return result != nullptr ? result : throw FailedWindowInitializationFailedException();
}

void RenderWindowBuilder::InitializeWindowSettings()
{
	var path = WindowSettingsPath;
	var settingsFile = std::ifstream(path);
	
	if (settingsFile.is_open())
	{
		int width = 0;
		int height = 0;
		int frameRateLimit = 0;
		bool verticalSyncEnabled = false;
		string title = "";

		if (settingsFile >> width >> height >> frameRateLimit >> verticalSyncEnabled)
		{
			string temp = "";
			while (settingsFile >> temp)
			{
				title += temp + " ";
				temp = "";
			}
			
			_settings = WindowSettings(width, height, frameRateLimit, verticalSyncEnabled, title);
		}
		else
		{
			throw WrongFileContentException(path);
		}
	}
	else
	{
		throw FileNotFoundException(path);
	}

	settingsFile.close();
}
