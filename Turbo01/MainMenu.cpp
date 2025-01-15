#include "MainMenu.hpp"
#include "TurboGame.hpp"

int MainMenu::start = 1;
int MainMenu::lasty = 60;
float MainMenu::alphaa = 0.0f;
float MainMenu::y_final = 4.0f;
int MainMenu::initial_flag = 1;

int MainMenu::selection_ = 0;
int MainMenu::extremeLow_ = 0;
int MainMenu::extremeUp_ = 0;
int MainMenu::flag_ = 0;
float MainMenu::menuCursorPos_ = 0.0f;

const std::array<int, 5> MainMenu::MainMenuPos = { 3.0, 2.0, 1.0, 0.0, -1 };


GLuint MainMenu::textureApp_ = 0;

void MainMenu::Enter() {
	menuCursorPos_ = MainMenuPos[selection_];
	flag_ = 1;
	RenderNewTextrue();
	ResetPosition();

	glutDisplayFunc(Render);
	glutSpecialFunc(HandleSpecialKey);
	glutKeyboardFunc(HandleAsciiKey);

	Loop(12);
}

void MainMenu::RenderNewTextrue() {
	switch (flag_) {
	case 1:
		textureApp_ = ResourceManager::Instance().GetTexture(TextureID::Menu1);
		break;

	case 2:
		textureApp_ = ResourceManager::Instance().GetTexture(TextureID::Menu2);
		break;
	}
}

void MainMenu::ResetPosition() {
	selection_ = 0;
	menuCursorPos_ = MainMenuPos[selection_];
	switch (flag_)
	{
	case 1:
		extremeLow_ = 0;
		extremeUp_ = 3;
		break;
	case 2:
		extremeLow_ = 0;
		extremeUp_ = 4;
		break;
	}
}

void MainMenu::Render() {
	if (alphaa > 1.0) {
		initial_flag = 2;
		//alphaa=0;
	}
	ShowNew();

	if (alphaa < 0) {
		start = 2;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	gluLookAt(-0, 0, 10.0, 0, 0, 0, 0, 1.0, 0.0);

	if (start == 1) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

		glEnable(GL_BLEND);     // Turn Blending On
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor4f(1.0, 1.0, 1.0, alphaa);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ResourceManager::Instance().GetTexture(TextureID::IntroBackground));
		//printf("%f",alphaa);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0);  
		glVertex2f(-4.0, -3.0);
		glTexCoord2f(1.0, 0); 
		glVertex2f(4.0, -3.0);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(4.0, 3.0);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-4.0, 3.0);
		glEnd();


		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);     // Turn B
		glEnable(GL_DEPTH_TEST);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();
	}
	else {
		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ResourceManager::Instance().GetTexture(TextureID::MenuBackground));
		glScalef(4.3, 4.3, 1.0);
		glTranslatef(0, 0, -5.0);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0);glVertex2f(-2.0, -1.5);
		glTexCoord2f(1.0, 0);glVertex2f(2.0, -1.5);
		glTexCoord2f(1.0, 1.0);glVertex2f(2.0, 1.5);
		glTexCoord2f(0.0, 1.0);glVertex2f(-2.0, 1.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		glPushMatrix();
		glPushMatrix();

		glEnable(GL_BLEND);     // Turn Blending On
		//glDisable(GL_DEPTH_TEST);
		glColor4f(1.0, 1.0, 1.0, 0.3);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glScalef(0.8, 0.7, 1.0);
		glTranslatef(0.0, 0.6, 0.00);
		glTranslatef(-5.0, menuCursorPos_, 0.00);
		glScalef(1.0, 0.8, 1.0);


		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0);glVertex2f(0, 0);
		glTexCoord2f(1.0, 0);glVertex2f(5.0, 0);
		glTexCoord2f(1.0, 1.0);glVertex2f(5.0 + menuCursorPos_ / 3, 1.0);
		glTexCoord2f(0.0, 1.0);glVertex2f(0 - menuCursorPos_ / 20, 1.0);
		glEnd();

		glDisable(GL_BLEND);     // Turn B
		glEnable(GL_DEPTH_TEST);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();


		//for menu
		glPushMatrix();
		glEnable(GL_BLEND);     // Turn Blending On
		glDisable(GL_DEPTH_TEST);
		glColor4f(1.0, 1.0, 1.0, 0.9);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureApp_);
		glTranslatef(0, 0.5, -2.0);
		glScalef(0.8, 0.8, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0);glVertex2f(-7.0, 0);
		glTexCoord2f(1.0, 0);glVertex2f(0.0, 0);
		glTexCoord2f(1.0, 1.0);glVertex2f(0.0, y_final);
		glTexCoord2f(0.0, 1.0);glVertex2f(-7.0, y_final);
		glEnd();
		glDisable(GL_BLEND);     // Turn B
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();

	}

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void MainMenu::ShowNew() {
	switch (initial_flag)
	{
	case 1:
		alphaa += 0.025;
		break;
	case 2:
		alphaa -= 0.025;
		break;
	}
}

void MainMenu::HandleSpecialKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP:
		if (selection_ > extremeLow_)
		{
			menuCursorPos_ = MainMenuPos[selection_];
			//printf("key up top condition selection=%d and el=%d and eu=%d\n",selection,extreme_low,extreme_up);
			for (int i = 0; i <= 40; i++)
			{
				menuCursorPos_ += 0.025;
				Render();
			}
			selection_--;

		}
		else
		{
			//printf("key up down condition selection=%d and el=%d and eu=%d\n",selection,extreme_low,extreme_up);
			selection_ = extremeUp_;

		}
		menuCursorPos_ = MainMenuPos[selection_];
		Render();
		break;
	case GLUT_KEY_DOWN:
		if (selection_ < extremeUp_)
		{
			menuCursorPos_ = MainMenuPos[selection_];
			//printf("key down top condition selection=%d and el=%d and eu=%d\n",selection,extreme_low,extreme_up);
			for (int i = 0; i <= 40; i++)
			{
				menuCursorPos_ -= 0.025;
				Render();
			}
			selection_++;

		}
		else
		{
			//printf("key down down condition selection=%d and el=%d and eu=%d\n",selection,extreme_low,extreme_up);
			selection_ = extremeLow_;
		}
		menuCursorPos_ = MainMenuPos[selection_];
		Render();
		break;
	}
}

void MainMenu::HandleAsciiKey(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 13:
		HandleEnterEvents();
		break;
	}
}

void MainMenu::Loop(int x) {
	if (flag_ > 0)
	{
		glutPostRedisplay();
		glutTimerFunc(1000.f/30.f, Loop, 0);
	}
	else
	{
		//do nothing....
	}
}

void MainMenu::HandleEnterEvents() {
	if (initial_flag < 2)
		return;
	switch (flag_)
	{

	case 1:
		if (selection_ == MenuSelection::StartGame)
		{
			//start game
			Leave();
			TurboGame::Instance().EnterGame();
            
			std::cout << "Start the Game" << std::endl;

		}
		if (selection_ == MenuSelection::Options)
		{
			flag_ = 2;
			MenuModify();
			ResetPosition();
		}
		if (selection_ == MenuSelection::Credits)
		{
			//blah blah
		}

		if (selection_ == MenuSelection::Quit)
		{
			exit(0);
		}
		break;

	case 2:
		if (selection_ == MenuSelection::Back)
		{
			flag_ = 1;
			MenuModify();
			ResetPosition();
		}
		break;
	}
}

void MainMenu::Leave() {
	flag_ = 0;
	/*
	It's illigal to set the display callback to NULL.
	The initgame function will register its own callback function
	so we don not have to worry
	*/
	// glutDisplayFunc(NULL);

	glutSpecialFunc(NULL);
	glutKeyboardFunc(NULL);
}

void MainMenu::MenuModify() {
	for (int i = 0; i <= 40; i++) {
		y_final -= 0.1;
		Render();
	}
	RenderNewTextrue();
	for (int i = 0; i < 40; i++) {
		y_final += 0.1;
		Render();
	}
}