#pragma once
#include "stdafx.h"
#include "FileNotFoundException.hpp"
#include "WrongFileContentException.hpp"
#include "FailedWindowInitializationException.hpp"

class RenderWindowBuilder
{
private:
	struct WindowSettings
	{
		int Width;
		int Height;
		int FrameRateLimit;
		bool VerticalSyncEnabled;
		string Title;

		WindowSettings(int width, int height, int frameRateLimit, bool verticalSyncEnabled, string title)
			: Width(width), Height(height), FrameRateLimit(frameRateLimit), VerticalSyncEnabled(verticalSyncEnabled), Title(title)
		{
		}

		WindowSettings() = default;
	};

	WindowSettings _settings;

public:
	RenderWindowBuilder()
	{
		InitializeWindowSettings();
	}
	
	virtual ~RenderWindowBuilder() = default;

	sf::RenderWindow* BuildRenderWindow()
	{
		var result = new sf::RenderWindow(sf::VideoMode(_settings.Width, _settings.Height), _settings.Title, sf::Style::Fullscreen);
		result->setFramerateLimit(_settings.FrameRateLimit);
		result->setVerticalSyncEnabled(_settings.VerticalSyncEnabled);
		result->clear();
		result->display();

		return result != nullptr ? result : throw new FailedWindowInitializationFailedException();
	}

private:
	void InitializeWindowSettings()
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
				throw new WrongFileContentException(path);
			}
		}
		else
		{
			throw new FileNotFoundException(path);
		}

		settingsFile.close();
	}
};