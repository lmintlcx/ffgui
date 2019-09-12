#pragma once

#include <QDebug>
#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QCompleter>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QThread>

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
  void SwitchX264Mode();
  void OpenFileVideo();
  void OpenFileAudio();
  void OpenFilePicture();
  void ChangeOutputFileName(QString);
  void ChangeOutputFileExt();
  QString GetScript();

public slots:
  void ExecuteResult(bool);

signals:
  void ExecuteScript(QString);

private:
  // list
  QStringList list_frame_size;
  QStringList list_frame_rate;
  // worker
  FFmpeg *ffmpeg;
  QThread *thread;
  // input
  QGroupBox *group_box_input;
  QGridLayout *grid_layout_input;
  QLabel *label_input_video;
  QLineEdit *line_edit_input_filename_video;
  QPushButton *push_button_open_video;
  QLabel *label_input_audio;
  QLineEdit *line_edit_input_filename_audio;
  QPushButton *push_button_open_audio;
  // output
  QGroupBox *group_box_output;
  QGridLayout *grid_layout_output;
  QLabel *label_output;
  QLineEdit *line_edit_output_filename;
  // video
  QGroupBox *group_box_video;
  QGridLayout *grid_layout_video;
  QCheckBox *check_box_video_enable;
  QCheckBox *check_box_video_crf;
  QCheckBox *check_box_video_2pass;
  QLabel *label_video_codec;
  QComboBox *combo_box_video_codec;
  QLabel *label_video_container;
  QComboBox *combo_box_video_container;
  QLabel *label_video_preset;
  QComboBox *combo_box_video_x264_preset;
  QComboBox *combo_box_video_nvenc_preset;
  QLabel *label_video_bitrate;
  QDoubleSpinBox *spin_box_video_bitrate;
  QLabel *label_video_factor;
  QDoubleSpinBox *spin_box_video_factor;
  QLabel *label_video_frame_size;
  QLineEdit *line_edit_video_frame_size;
  QLabel *label_video_frame_rate;
  QLineEdit *line_edit_video_frame_rate;
  QLabel *label_video_profile_level;
  QComboBox *combo_box_video_profile_level;
  QLabel *label_video_x264_keyint;
  QLineEdit *line_edit_video_x264_keyint;
  // audio
  QGroupBox *group_box_audio;
  QGridLayout *grid_layout_audio;
  QCheckBox *check_box_audio_enable;
  QLabel *label_audio_codec;
  QComboBox *combo_box_audio_codec;
  QLabel *label_audio_bitrate;
  QComboBox *combo_box_audio_bitrate;
  QLabel *label_audio_frequency;
  QComboBox *combo_box_audio_frequency;
  QLabel *label_audio_channels;
  QComboBox *combo_box_audio_channels;
  // filter
  QGroupBox *group_box_filter;
  QGridLayout *grid_layout_filter;
  QCheckBox *check_box_watermark;
  QLabel *label_watermark_x;
  QLineEdit *line_edit_watermark_x;
  QLabel *label_watermark_y;
  QLineEdit *line_edit_watermark_y;
  QLineEdit *line_edit_input_watermark;
  QPushButton *push_button_open_watermark;
  QCheckBox *check_box_crop;
  QLabel *label_crop_x;
  QLineEdit *line_edit_crop_x;
  QLabel *label_crop_y;
  QLineEdit *line_edit_crop_y;
  QLabel *label_crop_width;
  QLineEdit *line_edit_crop_width;
  QLabel *label_crop_height;
  QLineEdit *line_edit_crop_height;
  QCheckBox *check_box_cutting;
  QLabel *label_cutting_start;
  QLineEdit *line_edit_cutting_start;
  QLabel *label_cutting_duration;
  QLineEdit *line_edit_cutting_duration;
  QCheckBox *check_box_half_speed;
  QCheckBox *check_box_double_speed;
  // scripts
  QWidget *widget_scripts;
  QGridLayout *grid_layout_scripts;
  QPushButton *push_button_check_updates;
  QPushButton *push_button_show_scripts;
  QPushButton *push_button_execute;
  // main
  QGridLayout *main_layout;
};
