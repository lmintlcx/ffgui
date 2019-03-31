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

#include "Windows.h"

class FFGUI : public QWidget
{
  Q_OBJECT

public:
  FFGUI();
  ~FFGUI();
  void EnableVideoWidgets(bool);
  void EnableAudioWidgets(bool);
  void EnableCuttingWidgets(bool);
  void SwitchCRF2PASS();
  void OpenFile1();
  void OpenFile2();
  void ChangeOutputFileExt();
  QString GetScript();
  bool ExecuteScript(QString);

private:
  HWND console_hwnd;
  QStringList list_frame_size;
  QStringList list_bitrate;
  // input
  QGroupBox *group_box_input;
  QGridLayout *grid_layout_input;
  QLabel *label_input_1;
  QLineEdit *line_edit_input_filename_1;
  QPushButton *push_button_open_1;
  QLabel *label_input_2;
  QLineEdit *line_edit_input_filename_2;
  QPushButton *push_button_open_2;
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
  QComboBox *combo_box_video_preset;
  QLabel *label_video_keyframe;
  QLineEdit *line_edit_video_keyframe;
  QLabel *label_video_frame_size;
  QLineEdit *line_edit_video_frame_size;
  QLabel *label_video_frame_rate;
  QComboBox *combo_box_video_frame_rate;
  QLabel *label_video_factor;
  QDoubleSpinBox *spin_box_video_factor;
  QLabel *label_video_bitrate;
  QLineEdit *line_edit_video_bitrate;
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
  QPushButton *push_button_show_scripts;
  QPushButton *push_button_execute;
  // main
  QGridLayout *main_layout;
};
