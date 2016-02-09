#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <QObject>
#include <QWidget>

namespace qtreports {

	typedef QWidget* WidgetPtr;

	class Engine : public QObject {
		Q_OBJECT

	public:
		Engine(QObject * parent = 0);
		~Engine();

		bool		compile( std::string path );
		WidgetPtr	getWidget();


	private:

	};

}
#endif // ENGINE_H