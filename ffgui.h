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
  void OpenFile();
  void ChangeOutputFileExt();
  QString GetScript();
  bool ExecuteScript(QString);

private:
  HWND console_hwnd;
  QStringList list_frame_size;
  QStringList list_bitrate;
  // file
  QGroupBox *group_box_file;
  QGridLayout *grid_layout_file;
  QLabel *label_input;
  QLineEdit *line_edit_input_filename;
  QPushButton *push_button_open;
  QLabel *label_output;
  QLineEdit *line_edit_output_filename;
  QPushButton *push_button_execute;
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
  // other
  QGroupBox *group_box_other;
  QGridLayout *grid_layout_other;
  QCheckBox *check_box_cutting;
  QLabel *label_cutting_start;
  QLineEdit *line_edit_cutting_start;
  QLabel *label_cutting_duration;
  QLineEdit *line_edit_cutting_duration;
  // main
  QGridLayout *main_layout;
};
