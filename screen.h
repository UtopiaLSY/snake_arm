/* screen.h */  
#ifndef SCREEN_H 
#define SCREEN_H 
#include <QWidget> 
#include "snake.h" 
class Snake; 
class QTimer; 
class QLabel; 
class QPushButton; 

class Screen : public QWidget 
{ 
	Q_OBJECT; 
	public: 
		Screen(QWidget *parent = 0); 
		~Screen(void); 
	private slots: 
		void my_timeout(void); 
		void startGame(void); 
		void pauseGame(void); 
		void continueGame(void); 
		void speedUp(void); 
		void speedDown(void); 
		void upClicked(void);        /* ����ť Up ����Ĳ� */ 
		void downClicked(void);       /* ����ť Down ����Ĳ� */ 
		void rightClicked(void);       /* ����ť Right ����Ĳ� */ 
		void leftClicked(void);        /* ����ť Left ����Ĳ� */ 
	private: 
		void paintEvent(QPaintEvent *event);     /* ������Ϸ���� */ 
		void init_var(void);        /* ��ʼ������ */ 
		void keyPressEvent(QKeyEvent *event);    /* ��������¼��ĺ���*/ 
		QLabel *scoreLabel;        /* ��ʾ�÷ֵı�ǩ */ 
		QPushButton *upButton;       /* ���ϰ�ť */ 
		QPushButton *downButton;       /* ���°�ť */ 
		QPushButton *leftButton;       /* ����ť */ 
		QPushButton *rightButton;       /* ���Ұ�ť */ 
		Snake snake; 
		bool IsDie; 
		bool IsWin; 
		bool IsRun; 
		bool IsPause; 
		QTimer *timer;         /* ��ʱ�����������ø���ʱ�� */ 
		int times; 
		int score; 
}; 
#endif  
