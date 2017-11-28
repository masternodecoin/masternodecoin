#ifndef IMGBTN_H
#define IMGBTN_H

#include <QAbstractButton>
#include <QPixmap>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
class HyperlinkBtn : public QAbstractButton
{
    Q_OBJECT
public:
    explicit HyperlinkBtn(QString iconurl,QString url,QWidget *parent = 0);
    const QString &getUrl();

protected:
    void paintEvent(QPaintEvent *);
    //void resizeEvent(QResizeEvent * event);

signals:

public slots:
    void onClicked(bool b);
private:
    const QString m_icon;
    const QString m_websiteUrl;
};

#endif // IMGBTN_H
