#ifndef WNDCALLINFO_H
#define WNDCALLINFO_H

#include <QDialog>
#include <QTimer>
#include <QPoint>
#include <QTime>

namespace Ui {
    class WndCallInfo;
}

class WndCallInfo : public QDialog {
    Q_OBJECT

public:
    explicit WndCallInfo(QWidget *parent = 0);
    ~WndCallInfo();

    void setPhoneNumber(QString number);
    void incomingCall(void);
    void outgoingCall(void);
    void talking(void);
    void idle(void);

private slots:
    void _durationTimerTick(void);

private:
    Ui::WndCallInfo * _ui;
    QTimer * _hideTimer;
    QTimer * _durationTimer;
    QPoint _showPoint;
    int _callDuration;

    void _showWindow(void);
};

#endif // WNDCALLINFO_H
