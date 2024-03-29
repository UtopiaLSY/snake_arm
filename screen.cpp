/* screen.cpp */ 
#include <QtGui> 
#include "screen.h" 

Screen::Screen(QWidget *parent) 
  : QWidget(parent)
{ 
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); /* 设置编码字体 */ 
	setFocus();          //获取焦点，用于接收键盘事件
	setFixedSize(370, 175);       //设置固定游戏界面大小
	init_var();        
	timer = new QTimer(this);       //创建定时器
	scoreLabel = new QLabel(tr("Your Scores:0 "), this); 		//分数显示
	scoreLabel->setGeometry(210, 20, 100, 50); 
	upButton = new QPushButton(tr("Up"), this); 				//方向按钮显示
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
	timer->start(times);       //每 200 毫秒发出一个信号
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
void Screen::keyPressEvent(QKeyEvent *event)   //捕捉键盘事件
{ 
	switch(event->key()) 
	{ 
		case Qt::Key_Up: 
			snake.ChangeDirection(1);     //改变 Snake 的移动方向
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
	snake.getCoordinate(node, food);      //获取Snake和果实的坐标
	
	painter.setBrush(Qt::red); //画果实
	painter.drawEllipse(5 * food.x, 5 * food.y,5, 5); 

	painter.setBrush(Qt::white); 	//画墙
	painter.drawRect(0, 0, 205, 5); 
	painter.drawRect(0, 170, 205, 5); 
	painter.drawRect(0, 0, 5, 175); 
	painter.drawRect(200, 0, 5, 175); 
	 //画蛇，蛇头与蛇身用不同的颜色区分
	painter.setBrush(Qt::yellow); 
	painter.drawRect(5 * node[0].x, 5 * node[0].y,5, 5); 
	//画蛇身
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
	snake.Clear();         // 清空snake 的坐标
	snake.init_var();         //初始化 snake 变量
	IsRun   = true; 
	times   = 200; 
	timer->start(times); 
} 

void Screen::continueGame(void) 
{ 
	if(!IsPause) 
	return; 
	timer->start(times);        //继续定时，即继续更新画面 
	setFocus(); 
}

void Screen::pauseGame(void) 
{ 
	IsPause = true; 
	timer->stop();         // 暂停定时，即暂停画面
	setFocus(); 
}

void Screen::speedUp(void) 
{ 
	times -= 20; 
	if(times <= 20) 
	times = 20; 
	timer->stop(); 
	timer->start(times);        //加快定时器的频率
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

