#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QCompleter>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMimeData>
#include <QPushButton>
#include <QSpinBox>
#include <QStandardPaths>
#include <QThread>
#include <QUrl>
#include <QWidget>

#include "Windows.h"

// FFmpeg

class FFmpeg : public QObject
{
    Q_OBJECT

  public:
    FFmpeg();
    ~FFmpeg();

  public slots:
    void ExecuteScript(QString);

  signals:
    void ExecuteResult(bool);
};

// FFGUI

class FFGUI : public QWidget
{
    Q_OBJECT

  public:
    FFGUI();
    ~FFGUI();
    void OpenFile();
    void ChangeOutputFileName(QString);
    void ChangeOutputFileExt();
    QString GetScript();
    bool CheckFFmpeg();

  protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

  public slots:
    void ExecuteResult(bool);

  signals:
    void ExecuteScript(QString);

  private:
    // time
    QDateTime begin_time;
    QDateTime end_time;
    // list
    QStringList list_frame_size;
    QStringList list_frame_rate;
    QStringList list_audio_rate;
    // worker
    FFmpeg *ffmpeg;
    QThread *thread;
    // input
    QGroupBox *group_box_input;
    QGridLayout *grid_layout_input;
    QLineEdit *line_edit_input_filename;
    QPushButton *push_button_open;
    // output
    QGroupBox *group_box_output;
    QGridLayout *grid_layout_output;
    QLineEdit *line_edit_output_filename;
    QCheckBox *check_box_overwrite;
    // video
    QGroupBox *group_box_video;
    QGridLayout *grid_layout_video;
    QCheckBox *check_box_video_enable;
    QLabel *label_video_container;
    QComboBox *combo_box_video_container;
    QLabel *label_video_codec;
    QComboBox *combo_box_video_codec;
    // video label
    QLabel *label_video_profile;
    QLabel *label_video_preset;
    QLabel *label_video_factor;
    // video x264
    QComboBox *combo_box_x264_profile;
    QComboBox *combo_box_x264_preset;
    QDoubleSpinBox *spin_box_x264_factor;
    // video x265
    QComboBox *combo_box_x265_profile;
    QComboBox *combo_box_x265_preset;
    QDoubleSpinBox *spin_box_x265_factor;
    // video svtav1
    QComboBox *combo_box_svtav1_profile;
    QComboBox *combo_box_svtav1_preset;
    QSpinBox *spin_box_svtav1_factor;
    // video common
    QLabel *label_video_pix_fmt;
    QComboBox *combo_box_video_pix_fmt;
    QLabel *label_video_keyint;
    QLineEdit *line_edit_video_keyint;
    QLabel *label_video_frame_size;
    QLineEdit *line_edit_video_frame_size;
    QLabel *label_video_frame_rate;
    QLineEdit *line_edit_video_frame_rate;
    // audio
    QGroupBox *group_box_audio;
    QGridLayout *grid_layout_audio;
    QCheckBox *check_box_audio_enable;
    QLabel *label_audio_codec;
    QComboBox *combo_box_audio_codec;
    QLabel *label_audio_bitrate;
    QComboBox *combo_box_mp3_bitrate;
    QComboBox *combo_box_aac_bitrate;
    QComboBox *combo_box_opus_bitrate;
    QLabel *label_audio_frequency;
    QComboBox *combo_box_audio_frequency;
    QLabel *label_audio_channels;
    QComboBox *combo_box_audio_channels;
    // filter
    QGroupBox *group_box_filter;
    QGridLayout *grid_layout_filter;
    QCheckBox *check_box_crop;
    QLabel *label_crop_x;
    QLineEdit *line_edit_crop_x;
    QLabel *label_crop_y;
    QLineEdit *line_edit_crop_y;
    QLabel *label_crop_width;
    QLineEdit *line_edit_crop_width;
    QLabel *label_crop_height;
    QLineEdit *line_edit_crop_height;
    QCheckBox *check_box_cut;
    QLabel *label_cut_start;
    QLineEdit *line_edit_cut_start;
    QLabel *label_cut_duration;
    QLineEdit *line_edit_cut_duration;
    // scripts
    QWidget *widget_scripts;
    QGridLayout *grid_layout_scripts;
    QPushButton *push_button_check_updates;
    QLabel *label_current_version;
    QPushButton *push_button_show_scripts;
    QPushButton *push_button_execute;
    // main
    QGridLayout *main_layout;
};
