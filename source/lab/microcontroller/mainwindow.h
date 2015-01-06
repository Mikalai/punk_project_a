#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/qmainwindow.h>

#include "highlighter.h"

class QTextEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

	public slots:
	void about();
	void newFile();
	void openFile(const QString &path = QString());

private:
	void setupEditor();
	void setupFileMenu();
	void setupHelpMenu();

	QTextEdit *editor;
	Highlighter *highlighter;
};

#endif

