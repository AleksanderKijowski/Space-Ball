#pragma once
#include "FileNotFoundException.h"
#include "WrongFileContentException.h"
#include "FailedWindowInitializationException.h"

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

			WindowSettings() {};
		};
	
		WindowSettings _settings;

	public:
		RenderWindowBuilder();
		virtual ~RenderWindowBuilder() {};
	
		sf::RenderWindow* BuildRenderWindow();
	
	private:
		void InitializeWindowSettings();
};

