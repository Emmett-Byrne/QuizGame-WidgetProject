#pragma once

enum Menu
{
	StateCutscene,
	StateSplash,
	StateLicense,
	StateMainMenu,
	StateOptions,
	StateQuiz,
	StateHighScore,
	StateCredits,
	StateQuit
};

struct Options
{
	int musicVol;
	int soundVol;
	bool mute;
	int animSpeed;
	int fontSize;
};