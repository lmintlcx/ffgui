
#define EVERYTHING 42

#include <QApplication>
#include <QFont>
#include <QProcess>
#include <QTranslator>

#include "Windows.h"

#include "ffgui.h"

#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication app(argc, argv);

    QFont font = app.font();
    font.setPointSize(9);
    font.setFamily("Microsoft YaHei");
    app.setFont(font);

    // QTranslator tr_ffgui_zh_CN;
    // QTranslator tr_qt_zh_CN;
    // QTranslator tr_widgets_zh_CN;
    // tr_ffgui_zh_CN.load(":/ffgui_zh_CN.qm");
    // tr_qt_zh_CN.load(":/qt_zh_CN.qm");
    // tr_widgets_zh_CN.load(":/widgets_zh_CN.qm");
    // QString locale = QLocale::system().name();
    // if (true) // locale.mid(0, 2) == "zh"
    // {
    //     app.installTranslator(&tr_ffgui_zh_CN);
    //     app.installTranslator(&tr_qt_zh_CN);
    //     app.installTranslator(&tr_widgets_zh_CN);
    // }

    // HDC screen = GetDC(nullptr);
    // int dpi_x = GetDeviceCaps(screen, LOGPIXELSX);
    // int dpi_y = GetDeviceCaps(screen, LOGPIXELSY);
    // ReleaseDC(nullptr, screen);
    // const float default_dpi = 96.0f;
    // float scale_x = dpi_x / default_dpi;
    // float scale_y = dpi_y / default_dpi;
    // int width = 780 * scale_x;
    // int height = 564 * scale_y;

    FFGUI *ui = new FFGUI;
    ui->setAttribute(Qt::WA_DeleteOnClose);
    ui->setWindowTitle(QString("FFGUI") + "  -  " //
                       + QObject::tr("FFmpeg Script Generator"));
    ui->resize(750, 510);
    ui->setFixedSize(750, 510);
    ui->show();

    return app.exec();
}
