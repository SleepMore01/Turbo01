#pragma once

#include <string>
#include <vector>
#include <array>

#include "ResourceManager.hpp"

class MainMenu {
public:
	enum MenuSelection {
		StartGame,
		Options,
		Credits,
		Quit,
		Back
	};

	~MainMenu() = default;

	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator=(MainMenu&&) = delete;

	void static Enter();
	void static Leave();
	void static Render();
	void static RenderNewTextrue();
	void static Loop(int x);

	void static ResetPosition();
	//void static ResetMenu();
	void static HandleEnterEvents();

	void static ShowNew();

	void static HandleSpecialKey(int key, int x, int y);
	void static HandleAsciiKey(unsigned char key, int x, int y);

	void static MenuModify();

private:
	static int selection_;
	static float menuCursorPos_;
	std::vector<std::string> menuOptions_;
	std::vector<int> menuPositions_;
	static int extremeLow_, extremeUp_;
	static int flag_;

	static GLuint textureApp_;

	static int start;
	static int lasty;
	static float alphaa;
	static float y_final;
	static int initial_flag;

	const static std::array<int, 5> MainMenuPos;

	//void InitializeMenuOptions();
};
