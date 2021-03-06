#ifndef PLAYBACKVIEW_H
#define PLAYBACKVIEW_H

#include <QDialog>

namespace Ui {
    class PlaybackView;
}

class MainWindow;
class QTimer;

class PlaybackView : public QWidget
{
    Q_OBJECT

public:
    explicit PlaybackView(QWidget *parent = 0);
    ~PlaybackView();

    virtual QSize sizeHint() const;

    void setMainWindow(MainWindow *mainWindow) { mMainWindow = mainWindow; }

private:
    enum {
        Paused, Playing
    } mState;

    Ui::PlaybackView *ui;
    MainWindow       *mMainWindow;

    bool              mBusy;
    QTimer           *mTimer;

public slots:
    void play();
    void updateView();

private slots:
    void setPosition(int position);
    void tick();
};

#endif // PLAYBACKVIEW_H
