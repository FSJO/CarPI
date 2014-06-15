#ifndef CARPI_H
#define CARPI_H

#include <QObject>
#include <QMainWindow>
#include "mainboard.h"
#include "displayemulator.h"
#include "bluetooth.h"
#include "changeremulator.h"
#include "mp3player.h"
#include "navit.h"
#include "elm327.h"
#include "carpidial.h"

enum CarPISource {
    sourceFM = 0,
    sourceCD,
    sourceCDChanger,
    sourceAUX,
    sourceUnknown
};

enum CarPIDialsID {
    dialIntakeTemp = 0x00,
    dialBoost,
    dialFuelPressure,
    dialCoolantTemp,
    dialEngineLoad,
    dialVoltage
};

enum CarPIKeyMode {
    keyModeNormal = 0,
    keyModeMenu
};

enum CarPIKey {
    keyReturn = 0,
    keyUp,
    keyRight,
    keyDown,
    keyLeft,
    keyEscape
};

class CarPI : public QObject {
    Q_OBJECT
private:
    MainBoard * _mainboard;
    DisplayEmulator * _displayEmulator;
    ChangerEmulator * _changerEmulator;
    Bluetooth * _bluetooth;
    MP3Player * _mp3Player;
    Navit * _navit;
    Elm327 * _elm327;
    enum CarPIKeyMode _keyMode;

    QList<int> _id2pid;

    int _atmosphericPressure; /* Ciśnienie atmosferyczne w kPa, używane do obliczania ciśnienia doładowania */

    enum CarPISource _sourceCurrent;
    bool _sourcePaused;

    void _switchToSoruce(enum CarPISource source);

private slots:
    void _displayTextChanged(QString text);
    void _displayIconsChanged(int iconmask);

    void _displayMenuShow(int items);
    void _displayMenuHide(void);
    void _displayMenuSetItem(int itemno, QString text, bool isSelected);

    void _bluetoothConnectionStateChanged(bool isConnected);
    void _bluetoothCallStateChanged(enum BluetoothCallState state);

    void _pilotKeyStateChanged(int keymask);

    void _mp3PlayerTextChanged(QString text);

    void _changerEmulatorLoadCD(int num);

    void _ignitionStateChanged(bool enabled);

    void _elm327PidChanged(int pid, QVector<int> data);
    void _elm327VoltageChanged(double voltage);

public:
    explicit CarPI(QObject *parent = 0);
    ~CarPI();

    void updateStatus(void);
    void setDials(CarpiDial ** dials);

signals:
    void sourceChanged(enum CarPISource source);
    void volumeChanged(int volume);
    void pauseStateChanged(bool paused);

    void radioTextChanged(QString text);
    void radioIconsChanged(bool news, bool traffic, bool afrds);

    void menuShow(int items);
    void menuHide(void);
    void menuSetItem(int itemno, QString text, bool isSelected);

    void pilotKeyPressed(int keycode);

    void bluetoothConnectionStateChanged(bool isConnected);
    void bluetoothCallStateChanged(enum BluetoothCallState state);

    void mp3PlayerNextAlbum(void);
    void mp3PlayerPrevAlbum(void);
    void mp3PlayerSwitchDisplayMode(void);

    void elm327addWatchPid(int pid);
    void elm327stop(void);
    void elm327start(void);

    void dialValueChanged(enum CarPIDialsID dialID, double value);

    void changeDisplayMode(void);

    void mainMenuKeyPressed(enum CarPIKey key);
    void mainMenuEnter(void);

public slots:
    void mainMenuExit(void);
    void shutdown(void);
};

#endif // CARPI_H
