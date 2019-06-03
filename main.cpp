
#define EVERYTHING 42

#include <QApplication>
#include <QProcess>
#include <QFont>
#include <QTranslator>

#include "Windows.h"

#include "ffgui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFont font = app.font();
    font.setPointSize(9);
    font.setFamily("Microsoft YaHei");
    app.setFont(font);

    QTranslator tr_ffgui_zh_CN;
    QTranslator tr_qt_zh_CN;
    tr_ffgui_zh_CN.load(":/ffgui_zh_CN.qm");
    tr_qt_zh_CN.load(":/qt_zh_CN.qm");
    QString locale = QLocale::system().name();
    if (locale.mid(0, 2) == "zh")
    {
        app.installTranslator(&tr_ffgui_zh_CN);
        app.installTranslator(&tr_qt_zh_CN);
    }

    HDC screen = GetDC(nullptr);
    int dpi_x = GetDeviceCaps(screen, LOGPIXELSX);
    int dpi_y = GetDeviceCaps(screen, LOGPIXELSY);
    ReleaseDC(nullptr, screen);
    const float default_dpi = 96.0f;
    float scale_x = dpi_x / default_dpi;
    float scale_y = dpi_y / default_dpi;
    int width = 740 * scale_x;
    int height = 560 * scale_y;

    FFGUI *ui = new FFGUI;
    ui->setAttribute(Qt::WA_DeleteOnClose);
    ui->setWindowTitle("FFGUI 1.5");
    ui->resize(width, height);
    ui->setFixedSize(width, height);
    ui->show();

    return app.exec();
}
