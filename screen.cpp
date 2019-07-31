/* screen.cpp */ 
#include <QtGui> 
#include "screen.h" 

Screen::Screen(QWidget *parent) 
  : QWidget(parent)
{ 
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); /* ���ñ������� */ 
	setFocus();          //��ȡ���㣬���ڽ��ռ����¼�
	setFixedSize(370, 175);       //���ù̶���Ϸ�����С
	init_var();        
	timer = new QTimer(this);       //������ʱ��
	scoreLabel = new QLabel(tr("Your Scores:0 "), this); 		//������ʾ
	scoreLabel->setGeometry(210, 20, 100, 50); 
	upButton = new QPushButton(tr("Up"), this); 				//����ť��ʾ
	upButton->setGeometry(260, 90, 50, 40); 
	downButton = new QPushButton(tr("Down"), this); 
	downButton->setGeometry(260, 130, 50, 40); 
	rightButton = new QPushButton(tr("Right"), this); 
	rightButton->setGeometry(310, 130, 50, 40); 
	leftButton = new QPushButton(tr("Left"), this); 
	leftButton->setGeometry(210, 130, 50, 40); 
	
	
	

	QFont font; 
	font.setPointSize(10); 
	scoreLabel->setFont(font); 
	QPalette palette; 
	palette.setColor(QPalette::WindowText, Qt::red); 
	scoreLabel->setPalette(palette); 
	connect(upButton, SIGNAL(clicked()), this, SLOT(upClicked())); 
	connect(downButton, SIGNAL(clicked()), this, SLOT(downClicked())); 
	connect(rightButton, SIGNAL(clicked()), this, SLOT(rightClicked())); 
	connect(leftButton, SIGNAL(clicked()), this, SLOT(leftClicked())); 
	connect(timer, SIGNAL(timeout()), this, SLOT(my_timeout())); 
	times = 200; 
	timer->start(times);       //ÿ 200 ���뷢��һ���ź�
}

Screen::~Screen() 
{ 
}

void Screen::init_var(void) 
{ 
	IsRun = false; 
	IsPause = false; 
	IsDie = false; 
	IsWin = false; 
	score = 0; 
}
void Screen::keyPressEvent(QKeyEvent *event)   //��׽�����¼�
{ 
	switch(event->key()) 
	{ 
		case Qt::Key_Up: 
			snake.ChangeDirection(1);     //�ı� Snake ���ƶ�����
			break; 
		case Qt::Key_Right: 
			snake.ChangeDirection(2); 
			break; 
		case Qt::Key_Down: 
			snake.ChangeDirection(3); 
			break; 
		case Qt::Key_Left: 
			snake.ChangeDirection(4); 
			break; 
		default: 
			break; 
	}
	QWidget::keyPressEvent(event);
}

void Screen::my_timeout(void) 
{ 
	if(IsRun == false)
	{ 
		timer->stop(); 
		return; 
	}
	snake.Move(); 
	IsDie = snake.IsDie(); 
	IsWin = snake.IsWin(); 
	if(IsDie) { 
		timer->stop(); 
		IsRun = false; 
		QMessageBox::information(this, tr("Game Over"),tr("Game Over,You loss!")); 
		IsDie = false; 
		snake.Clear(); 
		return; 
	} 
	if(IsWin) { 
		timer->stop(); 
		IsRun = false; 
		QMessageBox::information(this, tr("You win"),tr("Congratulation, You Win!")); 
		IsDie = false; 
		snake.Clear(); 
		return; 
	}

	score = snake.getScore(); 
	QString str = QString("Your Score:\n   %1").arg(score); 
	scoreLabel->setText(str); 
	update(); 
}

void Screen::paintEvent(QPaintEvent *event) 
{ 
	QPainter  painter(this); 
	painter.setBrush(Qt::black); 
	painter.drawRect(0, 0, 205, 175); 
	if(IsDie || !IsRun) 
		return; 
	vector<Node> node; 
	Node food; 
	snake.getCoordinate(node, food);      //��ȡSnake�͹�ʵ������
	
	painter.setBrush(Qt::red); //����ʵ
	painter.drawEllipse(5 * food.x, 5 * food.y,5, 5); 

	painter.setBrush(Qt::white); 	//��ǽ
	painter.drawRect(0, 0, 205, 5); 
	painter.drawRect(0, 170, 205, 5); 
	painter.drawRect(0, 0, 5, 175); 
	painter.drawRect(200, 0, 5, 175); 
	 //���ߣ���ͷ�������ò�ͬ����ɫ����
	painter.setBrush(Qt::yellow); 
	painter.drawRect(5 * node[0].x, 5 * node[0].y,5, 5); 
	//������
	painter.setBrush(Qt::blue); 
	int n = node.size(); 
	for(int i = 1; i < n; i++) 
		painter.drawRect(5 *node[i].x, 5 *node[i].y,5, 5); 
	node.clear(); 
	QWidget::paintEvent(event); 
}

void Screen::upClicked(void) 
{ 
	snake.ChangeDirection(1); 
	setFocus(); 
}

void Screen::rightClicked(void) 
{ 
	snake.ChangeDirection(2); 
	setFocus(); 
} 

void Screen::downClicked(void) 
{ 
	snake.ChangeDirection(3); 
	setFocus(); 
}

void Screen::leftClicked(void) 
{ 
	snake.ChangeDirection(4); 
	setFocus(); 
}

void Screen::startGame(void) 
{ 
	snake.Clear();         // ���snake ������
	snake.init_var();         //��ʼ�� snake ����
	IsRun   = true; 
	times   = 200; 
	timer->start(times); 
} 

void Screen::continueGame(void) 
{ 
	if(!IsPause) 
	return; 
	timer->start(times);        //������ʱ�����������»��� 
	setFocus(); 
}

void Screen::pauseGame(void) 
{ 
	IsPause = true; 
	timer->stop();         // ��ͣ��ʱ������ͣ����
	setFocus(); 
}

void Screen::speedUp(void) 
{ 
	times -= 20; 
	if(times <= 20) 
	times = 20; 
	timer->stop(); 
	timer->start(times);        //�ӿ춨ʱ����Ƶ��
	setFocus(); 
}

void Screen::speedDown(void) 
{ 
	times += 20; 
	if(times >= 500) 
	times = 500; 
	timer->stop(); 
	timer->start(times); 
	setFocus(); 
}  

