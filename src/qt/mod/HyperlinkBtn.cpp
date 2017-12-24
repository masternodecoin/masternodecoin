#include "HyperlinkBtn.h"


HyperlinkBtn::HyperlinkBtn(QString iconurl, QString url, QWidget *parent)
    :m_websiteUrl(url),
      m_icon(iconurl),
      QAbstractButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(this,SIGNAL(clicked(bool)),this,SLOT(onClicked(bool)));
}

const QString &HyperlinkBtn::getUrl()
{
    return m_websiteUrl;
}

void HyperlinkBtn::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    if( !m_icon.isEmpty())
        painter.drawPixmap(this->rect(),QPixmap(m_icon));
}

//void HyperlinkBtn::resizeEvent(QResizeEvent *event)
//{
//    int len = qMin(this->width(),this->height());
//    this->setFixedSize(len,len);
//}

void HyperlinkBtn::onClicked(bool b)
{
    QDesktopServices::openUrl(QUrl(m_websiteUrl));
}



