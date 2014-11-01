#ifndef _H_GAME
#define _H_GAME

#include <QtCore/qobject.h>

class GlobalField;

class Game : public QObject {
	Q_OBJECT;
public:
private:
	GlobalField* m_field;
};

#endif	//	_H_GAME