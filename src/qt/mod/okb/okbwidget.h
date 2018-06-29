#ifndef OKBWIDGET_H
#define OKBWIDGET_H

#include <QWidget>
#include <QBitmap>
#include <QPalette>
#include <QPaintEvent>
#include <QDoubleValidator>
#include <QTimer>
#include <QSettings>
#include <QMutexLocker>

#include "bitcoingui.h"
#include "ui_interface.h"
#include "bitcoinunits.h"
#include "wallet.h"
#include "walletmodel.h"
#include "sendcoinsdialog.h"
#include "overviewpage.h"
#include "bitcoinunits.h"

extern bool fWalletUnlockStakingOnly;

namespace Ui {
class OKBWidget;
}

class OKBWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OKBWidget(QWidget* overView,QWidget* sendwidget, QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) ;
    void okbAction(const QString &str);
    void setOutOfSync(bool r);
    void setWalletSta(bool r);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
private slots:
    void on_pb20_clicked();

    void on_pb50_clicked();

    void on_pb100_clicked();

    void on_pb200_clicked();

    void on_pb500_clicked();

    void on_pb1000_clicked();

    void on_pbCustomizedReward_clicked();

    void on_pbClose_clicked();

    void timerOut();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::OKBWidget *ui;
    void send();

private:
    QPixmap m_Pixmap;
    bool m_bPressed;
    QPoint m_point;
    QString m_address;//one key bounty address
    bool isOutOfSync;
    bool isWalletAvailable; //unlock 
    QDoubleValidator *coustomizedValidator;
    OverviewPage *overViewPage;
    SendCoinsDialog *sendWidget;
    SendCoinsRecipient recipient;

    QTimer *m_timer;
//    int m_SendCount = 0; //set count
    bool sendLock;
    double m_avCoins;//ava MTNC
    double m_rec;//send MTNC
    QString m_name;//unit
//    CAmount m_atCoins;//total balance MTNC

signals:
    // Fired when a message should be reported to the user
    void message(const QString &title, const QString &message, bool modal, unsigned int style);
};


#endif // OKBWIDGET_H
