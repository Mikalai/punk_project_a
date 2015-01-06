#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qapplication.h>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupEditor();

	setCentralWidget(editor);
	setWindowTitle(tr("Syntax Highlighter"));
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Syntax Highlighter"),
		tr("<p>The <b>Syntax Highlighter</b> example shows how " \
		"to perform simple syntax highlighting by subclassing " \
		"the QSyntaxHighlighter class and describing " \
		"highlighting rules using regular expressions.</p>"));
}

void MainWindow::newFile()
{
	editor->clear();
}

void MainWindow::openFile(const QString &path)
{
	QString fileName = path;

	if (fileName.isNull())
		fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", "C++ Files (*.cpp *.h)");

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly | QFile::Text))
			editor->setPlainText(file.readAll());
	}
}

void MainWindow::setupEditor()
{
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	editor = new QTextEdit;
	editor->setFont(font);

	highlighter = new Highlighter(editor->document());

	QFile file("mainwindow.h");
	if (file.open(QFile::ReadOnly | QFile::Text))
		editor->setPlainText(file.readAll());
}

void MainWindow::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(tr("&New"), this, SLOT(newFile()),
		QKeySequence::New);

	fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
		QKeySequence::Open);

	fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
		QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
	QMenu *helpMenu = new QMenu(tr("&Help"), this);
	menuBar()->addMenu(helpMenu);

	helpMenu->addAction(tr("&About"), this, SLOT(about()));
	helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

