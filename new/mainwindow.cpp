#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include "mainwindow.h"
#include <QPushButton>
#include <QPalette>
#include <QLabel>
#include "ui_mainwindow.h"
// -------全局遍历-------//
#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"

const int kTOpBoardMargin = 30; // 棋盘边缘空隙30
const int kleftBoardMargin =40; //40
const int kRadius = 30; // 棋子半径30
const int kMarkSize = 6; // 落子标记边长6
const int kxBlockSize = 120; // 格子的大小120
const int kyBlockSize =90;//90
const int kPosDelta = 40; // 鼠标点击的模糊距离上限40

const int kAIDelay = 700; // AI下棋的思考时间

// -------------------- //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    // 开启鼠标hover功能，这两句一般要设置window的
    QPalette p=this->palette();
    p.setColor(QPalette::Window,QColor(255,255,0));
    setPalette(p);
    setMouseTracking(true);
    QFont font1("Timer",20,QFont::Bold);//40
    QLabel *Labal1=new QLabel(QObject::tr("与 弈"),this);
    Labal1->show();
    Labal1->setGeometry(1100,30,80,200);//1100,30,80,200
    Labal1->setFont(font1);
    QFont font("Timer",12,QFont::Bold);
    QPushButton *pvpbt=new QPushButton(QObject::tr("开始"),this);
    pvpbt->setGeometry(1100,300,200,80);//1100,300,200,80
    pvpbt->setFont(font);
    connect(pvpbt,SIGNAL(clicked(bool)),this,SLOT(initPVEGame()));

    // 开始游戏
    QPushButton *exitbt=new QPushButton(QObject::tr("退出"),this);
    exitbt->setGeometry(1100,450,200,80);//1100,450,200,80
    exitbt->setFont(font);
    connect(exitbt,SIGNAL(clicked(bool)),this,SLOT(close()));

    initGame();
}

MainWindow::~MainWindow()
{
    if (game)
    {
        delete game;
        game = nullptr;
        delete ui;
    }
}

void MainWindow::initGame()
{
    // 初始化游戏模型
    game = new GameModel;
    initPVPGame();
}

void MainWindow::initPVPGame()
{
    game_type = PERSON;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::initPVEGame()
{
    game_type = BOT;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制棋盘

    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
   // QPen penframe; // 调整线条宽度
   // penframe.setWidth(2);
   // painterFrame.setPen(penframe);
     painter.drawLine(kleftBoardMargin-5,kTOpBoardMargin-5,kleftBoardMargin + kxBlockSize*(kBoardSizeNum-1)+5,kTOpBoardMargin-5);
     painter.drawLine(kleftBoardMargin-5,kTOpBoardMargin-5,kleftBoardMargin-5,kTOpBoardMargin+ kyBlockSize *(kBoardSizeNum-1)+5);
     painter.drawLine(kleftBoardMargin-5,kTOpBoardMargin+ kyBlockSize *(kBoardSizeNum-1)+5,kleftBoardMargin + kxBlockSize*(kBoardSizeNum-1)+5,kTOpBoardMargin+ kyBlockSize *(kBoardSizeNum-1)+5);
     painter.drawLine(kleftBoardMargin + kxBlockSize*(kBoardSizeNum-1)+5,kTOpBoardMargin+ kyBlockSize *(kBoardSizeNum-1)+5,kleftBoardMargin + kxBlockSize*(kBoardSizeNum-1)+5,kTOpBoardMargin-5);

     for (int i = 0; i < kBoardSizeNum; i++)
    {
        painter.drawLine(kleftBoardMargin + kxBlockSize * i, kTOpBoardMargin, kleftBoardMargin + kxBlockSize * i, kTOpBoardMargin+ kyBlockSize *(kBoardSizeNum-1));
        painter.drawLine(kleftBoardMargin, kTOpBoardMargin + kyBlockSize * i, kleftBoardMargin + kxBlockSize*(kBoardSizeNum-1) , kTOpBoardMargin + kyBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > -1 && clickPosRow < kBoardSizeNum+1 &&
        clickPosCol > -1 && clickPosCol < kBoardSizeNum+1 &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(kleftBoardMargin + kxBlockSize * clickPosCol - kMarkSize / 2, kTOpBoardMargin + kyBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    // 绘制棋子
    for (int j = 0; j < kBoardSizeNum; j++)
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            if (game->gameMapVec[j][i] == 1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kleftBoardMargin + kxBlockSize * i - kRadius, kTOpBoardMargin + kyBlockSize * j - kRadius, kRadius * 2, kRadius * 2);
            }
            else if (game->gameMapVec[j][i] == -1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kleftBoardMargin + kxBlockSize * i - kRadius, kTOpBoardMargin + kyBlockSize * j - kRadius, kRadius * 2, kRadius * 2);

            }
        }

    // 判断输赢
    if (clickPosRow >= 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol >= 0 && clickPosCol < kBoardSizeNum &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            qDebug() << "win";
            game->gameStatus = WIN;
            QSound::play(WIN_SOUND);
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "white player";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "black player";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!");

            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
        }
    }


    // 判断死局
    if (game->isDeadGame())
    {
        QSound::play(LOSE_SOUND);
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(game_type);
            game->gameStatus = PLAYING;
        }

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= 0&&x < (kleftBoardMargin + kxBlockSize * (kBoardSizeNum-1)+40)&&y >=0&&y < (kTOpBoardMargin + kyBlockSize * (kBoardSizeNum-1)+40))
    {
        // 获取最近的左上角的点
        int col = x / kxBlockSize;
        int row = y / kyBlockSize;

        int leftTopPosX = kleftBoardMargin + kxBlockSize * col;
        int leftTopPosY = kTOpBoardMargin + kyBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kxBlockSize) * (x - leftTopPosX - kxBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kyBlockSize) * (y - leftTopPosY - kyBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kxBlockSize) * (x - leftTopPosX - kxBlockSize) + (y - leftTopPosY - kyBlockSize) * (y - leftTopPosY - kyBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 人下棋，并且不能抢机器的棋
    if (!(game_type == BOT && !game->playerFlag))
    {
        chessOneByPerson();
        // 如果是人机模式，需要调用AI下棋
        if (game->gameType == BOT && !game->playerFlag)
        {
            // 用定时器做一个延迟
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
        }
    }

}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        game->actionByPerson(clickPosRow, clickPosCol);
        QSound::play(CHESS_ONE_SOUND);

        // 重绘
        update();
    }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol);
    QSound::play(CHESS_ONE_SOUND);
    update();
}

