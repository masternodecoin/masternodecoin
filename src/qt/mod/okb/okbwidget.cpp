#include "okbwidget.h"
#include "ui_okbwidget.h"

//#include "stdio.h"
//using namespace std;

OKBWidget::OKBWidget(QWidget *overView, QWidget *sendwidget, QWidget *parent) :
    QWidget(parent),
    overViewPage(overView),
    sendWidget(sendwidget),
    ui(new Ui::OKBWidget)
{
    ui->setupUi(this);
    //
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //
    m_Pixmap.load(":/mod/onekeybounty/onekeybounty.png");
    resize(1000, 514);
    //
    m_Pixmap = m_Pixmap.scaled(size());
    //
    setAutoFillBackground(true);

    //
    setMask( m_Pixmap.mask() );

    coustomizedValidator = new QDoubleValidator();
    coustomizedValidator->setRange(0,99999999.99999999);
    ui->lineEdit->setValidator(coustomizedValidator);
    ui->lineEdit->setContextMenuPolicy (Qt::NoContextMenu);

    isOutOfSync = true; //SNYC not finish yet

    m_timer = new QTimer();
    m_timer->setInterval(5*1000);
    m_timer->setSingleShot(true);
    //m_SendCount = 0;
    sendLock = false;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timerOut()));

    QSettings settings;
    if (!settings.contains("dCustomized"))
        settings.setValue("dCustomized", 0.0);

    double customized = settings.value("dCustomized").toDouble();
    ui->lineEdit->setText(QString::number(customized));
}

void OKBWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    //background
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,m_Pixmap);
    this->setPalette(bgPalette);
}

//one key bounty function ,address proved then loading address
void OKBWidget::okbAction(const QString &str)
{
    m_address = str;
    this->show();
}

// mouse position event->globalPos() - this->pos()
void OKBWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// move the size
void OKBWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

// not click the mouse
void OKBWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}

//get data
void OKBWidget::showEvent(QShowEvent *event)
{
    QString avc = overViewPage->OKBGetAvailableCoins();
    QString atc = overViewPage->OKBGetTotalCoins();

    atc.remove(BitcoinUnits::name(BitcoinUnits::BTC));
    avc.remove(BitcoinUnits::name(BitcoinUnits::BTC));
    double datc = 0;
    if(atc.contains("m"))
    {
        atc.remove("m");
        avc.remove("m");
        m_avCoins = avc.toDouble()/1000;
        datc = atc.toDouble()/1000;
    }else if(atc.contains("μ"))
    {
        atc.remove("μ");
        avc.remove("μ");
        m_avCoins = avc.toDouble()/1000/1000;
        datc = atc.toDouble()/1000/1000;
    }else
    {
        datc = atc.toDouble();
        m_avCoins = avc.toDouble();
    }
    ui->okbTotal->setText(QString::number((CAmount)datc)+" " +BitcoinUnits::name(BitcoinUnits::BTC));
    ui->okbAvailable->setText(QString::number((CAmount)m_avCoins)+" "+BitcoinUnits::name(BitcoinUnits::BTC));
}

void OKBWidget::setOutOfSync(bool r)
{
    isOutOfSync = r;
}

void OKBWidget::setWalletSta(bool r)
{
    isWalletAvailable = r;
}

void OKBWidget::on_pb20_clicked()
{
    m_rec = 20;
    send();
}

void OKBWidget::on_pb50_clicked()
{
    m_rec = 50;
    send();
}

void OKBWidget::on_pb100_clicked()
{
    m_rec = 100;
    send();
}

void OKBWidget::on_pb200_clicked()
{
    m_rec = 200;
    send();
}

void OKBWidget::on_pb500_clicked()
{
    m_rec = 500;
    send();
}

void OKBWidget::on_pb1000_clicked()
{
    m_rec = 1000;
    send();
}

void OKBWidget::on_pbCustomizedReward_clicked()
{
    m_rec = ui->lineEdit->text().toDouble();
    send();
}

void OKBWidget::send()
{
    if(isWalletAvailable == false) //lock the wallet
    {
        emit message(tr("MTNC O-K bounty"),
                     tr("Please unlock wallet first!"),
                     false,CClientUIInterface::MSG_WARNING);
        recipient.amount = 0;
        recipient.address.clear();
        this->close();
        return;
    }
    if(fWalletUnlockStakingOnly == true) //lock wallet only pos
    {
        emit message(tr("MTNC O-K bounty"),
                     tr("Please unlock wallet first!"),
                     false,CClientUIInterface::MSG_WARNING);
        recipient.amount = 0;
        recipient.address.clear();
        this->close();
        return;
    }

    if(isOutOfSync)//not sync
    {
        emit message(tr("MTNC O-K bounty"),
                     tr("Please make sure sync is finished!"),
                     false,CClientUIInterface::MSG_WARNING);
        recipient.amount = 0;
        recipient.address.clear();
        return;
    }

    //（send money+1）> Available balance
    if(m_avCoins < m_rec + 1)
    {
        emit message(tr("MTNC O-K bounty"),
                     tr("Please make sure you have enough MTNC in your wallet!"),
                     false,CClientUIInterface::MSG_WARNING);
        recipient.amount = 0;
        recipient.address.clear();
        return;
    }

    recipient.amount = m_rec *COIN;
    if(m_name == BitcoinUnits::name(BitcoinUnits::mBTC))
    {
        recipient.amount *= 1000;
    }else if(m_name == BitcoinUnits::name(BitcoinUnits::uBTC))
    {
        recipient.amount *= 1000*1000;
    }

    if(sendLock != false)//(m_SendCount > 3)
    {
        emit message(tr("MTNC O-K bounty"),
                     tr("Please reduce transmission frequency!"),
                     false,CClientUIInterface::MSG_WARNING);
        recipient.amount = 0;
        recipient.address.clear();
        return;
    }


    recipient.address = m_address;

    sendWidget->OKBSend(recipient);
    sendLock = true;
    m_timer->start(); //time start
    this->close();
}

void OKBWidget::on_pbClose_clicked()
{
    this->close();
}

void OKBWidget::timerOut()
{
    //m_SendCount = 0;
    sendLock = false;
}


void OKBWidget::on_lineEdit_textChanged(const QString &arg1)
{
    QSettings settings;
    settings.setValue("dCustomized", ui->lineEdit->text().toDouble());
}
