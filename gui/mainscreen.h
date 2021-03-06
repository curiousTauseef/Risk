#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <QMainWindow>
#include <QString>
#include "logscreen.h"
#include "map_editor.h"
#include "ui_mainscreen.h"

namespace Ui {
	class MainScreen;
}


class MainScreen : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	explicit MainScreen(GameDriver* driver, QWidget *parent = 0);
	~MainScreen();
	bool setupPlayers();
	void observedUpdated();
	void nextTurn();

private slots:
	/**
	 * @brief Callback to handle user selecting File > Load.
	 */
	void on_loadAction_triggered();

	/**
	 * @brief Callback to handle user selecting File > Save.
	 */
	void on_saveAction_triggered();

	/**
	 * @brief Callback to handle user selecting File > Map Editor.
	 */
	void on_mapEditorAction_triggered();
	void on_logButton_clicked();
	void on_useCardsButton_clicked();

	/**
	 * @brief Callback to end the current phase, or advance to the next turn.
	 */
	void on_endPhasePushButton_clicked();

private:
	std::string playerName = "";
	std::string mapPath = "";

	Ui::MainScreen* ui = nullptr;
	MapEditor* editor = nullptr;
	LogScreen* logScreen = nullptr;
	GameDriver* driver = nullptr;
	MapScene* scene = nullptr;

	void initializeMode();
	void allocateArmiesByNumberOfPlayers(const std::string playerName);
};

#endif // MAINSCREEN_H
