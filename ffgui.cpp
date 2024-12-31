
#include "ffgui.h"

// FFmpeg

FFmpeg::FFmpeg()
{
}

FFmpeg::~FFmpeg()
{
}

void FFmpeg::ExecuteScript(QString full_script)
{
    QString app_dir = QCoreApplication::applicationDirPath();
    QString temp_dir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) //
                       + "/" + "ffgui_temp_"                                          //
                       + QString::number(QDateTime::currentDateTime().toTime_t(), 16) //
                       + "_a9efe77ad90194dc";

    QDir temp;
    bool exist = temp.exists(temp_dir);
    if (exist)
    {
        emit ExecuteResult(false);
        return;
    }
    else
    {
        bool ok = temp.mkdir(temp_dir);
        if (!ok)
        {
            emit ExecuteResult(false);
            return;
        }
    }

    QDir::setCurrent(temp_dir);

    QString script_file = temp_dir + "/" + "ffmpeg_script.bat";
    QFile file_s(script_file);

    if (!file_s.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        emit ExecuteResult(false);
        return;
    }
    QTextStream out(&file_s);
    out << full_script << endl;
    out.flush();
    file_s.close();

    QString script_file_path_with_quotation_mark = QString("") + "\"" + script_file + "\"";
    int ret = _wsystem(script_file_path_with_quotation_mark.toStdWString().c_str());

    QDir::setCurrent(app_dir);

    file_s.remove();
    temp.rmdir(temp_dir);

    emit ExecuteResult(ret == 0);
}

// FFGUI

FFGUI::FFGUI()
{
    SetConsoleTitleW(L"Output");

    this->list_frame_size << "320x200"
                          << "320x240"
                          << "480x272"
                          << "512x384"
                          << "480x320"
                          << "640x350"
                          << "640x360"
                          << "640x480"
                          << "720x348"
                          << "720x350"
                          << "720x360"
                          << "800x600"
                          << "800x480"
                          << "854x480"
                          << "960x540"
                          << "960x640"
                          << "1024x600"
                          << "1024x768"
                          << "1152x864"
                          << "1280x720"
                          << "1280x768"
                          << "1280x800"
                          << "1280x1024"
                          << "1366x768"
                          << "1440x900"
                          << "1400x1050"
                          << "1600x1024"
                          << "1680x1050"
                          << "1600x1200"
                          << "1920x1200"
                          << "1920x1080"
                          << "2048x1080"
                          << "2048x1536"
                          << "2560x1080"
                          << "2560x1440"
                          << "2560x1600"
                          << "2560x2048"
                          << "3200x2048"
                          << "3200x2400"
                          << "3440x1440"
                          << "3840x2160"
                          << "4096x2160"
                          << "3840x2400"
                          << "5120x4096"
                          << "6400x4096"
                          << "6400x4800"
                          << "7680x4320"
                          << "7680x4800"
                          << "720x576"
                          << "320x576"
                          << "720x480"
                          << "320x482"
                          << "648x486"
                          << "720x486"
                          << "720x540"
                          << "720x486"
                          << "720x576"
                          << "768x576"
                          << "1920x1080"
                          << "1366x768"
                          << "1280x720"
                          << "704x480"
                          << "2048x1536"
                          << "4096x3072"
                          << "720x480"
                          << "720x576"
                          << "352x240"
                          << "352x288"
                          << "560x360"
                          << "960x600"    // ..
                          << "960x720"    // ..
                          << "1440x1080"; // ..

    this->list_frame_rate << "10"
                          << "20"
                          << "24"
                          << "25"
                          << "29.97"
                          << "30"
                          << "48"
                          << "50"
                          << "59.94"
                          << "60"
                          << "100"
                          << "120"
                          << "144"
                          << "240";

    this->list_audio_rate << "32"
                          << "64"
                          << "96"
                          << "128"
                          << "160"
                          << "192"
                          << "256"
                          << "320";

    // worker

    ffmpeg = new FFmpeg();
    thread = new QThread(this);
    ffmpeg->moveToThread(thread);
    thread->start();

    // input

    group_box_input = new QGroupBox(this);
    group_box_input->setTitle(tr("Input"));

    line_edit_input_filename = new QLineEdit(group_box_input);
    line_edit_input_filename->setPlaceholderText(tr("Input File Path"));
    push_button_open = new QPushButton(group_box_input);
    push_button_open->setText(tr("Open File"));

    grid_layout_input = new QGridLayout(group_box_input);
    grid_layout_input->addWidget(line_edit_input_filename, 0, 0, 1, 5);
    grid_layout_input->addWidget(push_button_open, 0, 5, 1, 1);
    for (int i = 0; i < grid_layout_input->rowCount(); i++)
        grid_layout_input->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_input->columnCount(); i++)
        grid_layout_input->setColumnStretch(i, 1);
    grid_layout_input->setSpacing(10);

    // output

    group_box_output = new QGroupBox(this);
    group_box_output->setTitle(tr("Output"));

    line_edit_output_filename = new QLineEdit(group_box_output);
    line_edit_output_filename->setPlaceholderText(tr("Output File Path"));
    check_box_overwrite = new QCheckBox(group_box_output);
    check_box_overwrite->setText(tr("Overwrite"));
    check_box_overwrite->setChecked(false);

    grid_layout_output = new QGridLayout(group_box_output);
    grid_layout_output->addWidget(line_edit_output_filename, 0, 0, 1, 5);
    grid_layout_output->addWidget(check_box_overwrite, 0, 5, 1, 1);
    for (int i = 0; i < grid_layout_output->rowCount(); i++)
        grid_layout_output->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_output->columnCount(); i++)
        grid_layout_output->setColumnStretch(i, 1);
    grid_layout_output->setSpacing(10);

    // video

    group_box_video = new QGroupBox(this);
    group_box_video->setTitle(tr("Video"));

    check_box_video_enable = new QCheckBox(group_box_video);
    check_box_video_enable->setText(tr("Enable"));
    check_box_video_enable->setChecked(true);

    label_video_container = new QLabel(group_box_video);
    label_video_container->setText(tr("Container"));
    combo_box_video_container = new QComboBox(group_box_video);
    combo_box_video_container->addItem("mp4");
    combo_box_video_container->addItem("mkv");
    combo_box_video_container->addItem("webm");
    combo_box_video_container->setCurrentIndex(0);

    label_video_codec = new QLabel(group_box_video);
    label_video_codec->setText(tr("Codec"));
    combo_box_video_codec = new QComboBox(group_box_video);
    combo_box_video_codec->addItem("copy");
    combo_box_video_codec->addItem("x264");
    combo_box_video_codec->addItem("x265");
    combo_box_video_codec->addItem("svtav1");
    combo_box_video_codec->setCurrentIndex(1);

    label_video_profile = new QLabel(group_box_video);
    label_video_profile->setText(tr("Profile"));

    label_video_preset = new QLabel(group_box_video);
    label_video_preset->setText(tr("Preset"));

    label_video_factor = new QLabel(group_box_video);
    label_video_factor->setText(tr("Rate Factor"));

    combo_box_x264_profile = new QComboBox(group_box_video);
    combo_box_x264_profile->addItem("main");
    combo_box_x264_profile->addItem("high");
    combo_box_x264_profile->setCurrentIndex(1);

    combo_box_x264_preset = new QComboBox(group_box_video);
    combo_box_x264_preset->addItem("ultrafast");
    combo_box_x264_preset->addItem("superfast");
    combo_box_x264_preset->addItem("veryfast");
    combo_box_x264_preset->addItem("faster");
    combo_box_x264_preset->addItem("fast");
    combo_box_x264_preset->addItem("medium");
    combo_box_x264_preset->addItem("slow");
    combo_box_x264_preset->addItem("slower");
    combo_box_x264_preset->addItem("veryslow");
    combo_box_x264_preset->addItem("placebo");
    combo_box_x264_preset->setCurrentIndex(8);

    spin_box_x264_factor = new QDoubleSpinBox(group_box_video);
    spin_box_x264_factor->setRange(0.0, 51.0);
    spin_box_x264_factor->setSingleStep(0.4);
    spin_box_x264_factor->setDecimals(1);
    spin_box_x264_factor->setValue(19.2);

    combo_box_x265_profile = new QComboBox(group_box_video);
    combo_box_x265_profile->addItem("main");
    combo_box_x265_profile->addItem("main10");
    combo_box_x265_profile->addItem("main444-8");
    combo_box_x265_profile->addItem("main444-10");
    combo_box_x265_profile->setCurrentIndex(0);

    combo_box_x265_preset = new QComboBox(group_box_video);
    combo_box_x265_preset->addItem("ultrafast");
    combo_box_x265_preset->addItem("superfast");
    combo_box_x265_preset->addItem("veryfast");
    combo_box_x265_preset->addItem("faster");
    combo_box_x265_preset->addItem("fast");
    combo_box_x265_preset->addItem("medium");
    combo_box_x265_preset->addItem("slow");
    combo_box_x265_preset->addItem("slower");
    combo_box_x265_preset->addItem("veryslow");
    combo_box_x265_preset->addItem("placebo");
    combo_box_x265_preset->setCurrentIndex(8);

    spin_box_x265_factor = new QDoubleSpinBox(group_box_video);
    spin_box_x265_factor->setRange(0.0, 51.0);
    spin_box_x265_factor->setSingleStep(0.4);
    spin_box_x265_factor->setDecimals(1);
    spin_box_x265_factor->setValue(22.4);

    combo_box_svtav1_profile = new QComboBox(group_box_video);
    combo_box_svtav1_profile->addItem("main");
    // combo_box_svtav1_profile->addItem("high");
    // combo_box_svtav1_profile->addItem("professional");
    combo_box_svtav1_profile->setCurrentIndex(0);

    combo_box_svtav1_preset = new QComboBox(group_box_video);
    for (int i = 12; i >= 0; i--)
        combo_box_svtav1_preset->addItem(QString::number(i));
    combo_box_svtav1_preset->setCurrentIndex(12);

    spin_box_svtav1_factor = new QSpinBox(group_box_video);
    spin_box_svtav1_factor->setRange(1, 63);
    spin_box_svtav1_factor->setSingleStep(1);
    spin_box_svtav1_factor->setValue(48);

    label_video_pix_fmt = new QLabel(group_box_video);
    label_video_pix_fmt->setText(tr("Pixel Format"));

    combo_box_video_pix_fmt = new QComboBox(group_box_video);
    combo_box_video_pix_fmt->addItem(tr("Common")); // yuv420p
    combo_box_video_pix_fmt->addItem("yuv420p");
    combo_box_video_pix_fmt->addItem("yuv420p10le");
    combo_box_video_pix_fmt->addItem("yuv444p");
    combo_box_video_pix_fmt->addItem("yuv444p10le");
    combo_box_video_pix_fmt->setCurrentIndex(0);

    label_video_keyint = new QLabel(group_box_video);
    label_video_keyint->setText(tr("I-Frame Interval"));
    line_edit_video_keyint = new QLineEdit(group_box_video);
    // line_edit_video_keyint->setText("300");
    line_edit_video_keyint->setPlaceholderText("300");

    QIntValidator *validator_video_keyint = new QIntValidator;
    validator_video_keyint->setRange(1, 9999);
    line_edit_video_keyint->setValidator(validator_video_keyint);

    label_video_frame_size = new QLabel(group_box_video);
    label_video_frame_size->setText(tr("Frame Size"));
    line_edit_video_frame_size = new QLineEdit(group_box_video);
    // line_edit_video_frame_size->setText("1920x1080");
    line_edit_video_frame_size->setPlaceholderText(tr("Original"));

    this->list_frame_size.removeDuplicates();
    QCompleter *completer_frame_size = new QCompleter(list_frame_size);
    line_edit_video_frame_size->setCompleter(completer_frame_size);

    QRegularExpression reg_frame_size("[1-9][0-9]{1,5}[x][1-9][0-9]{1,5}");
    line_edit_video_frame_size->setValidator(new QRegularExpressionValidator(reg_frame_size, this));

    label_video_frame_rate = new QLabel(group_box_video);
    label_video_frame_rate->setText(tr("Frame Rate"));
    line_edit_video_frame_rate = new QLineEdit(group_box_video);
    // line_edit_video_frame_rate->setText("60");
    line_edit_video_frame_rate->setPlaceholderText(tr("Original"));

    this->list_frame_rate.removeDuplicates();
    QCompleter *completer_frame_rate = new QCompleter(list_frame_rate);
    line_edit_video_frame_rate->setCompleter(completer_frame_rate);

    QRegularExpression reg_frame_rate("^([0]|[1-9][0-9]{0,2})([.][0-9]{1,3})$");
    line_edit_video_frame_rate->setValidator(new QRegularExpressionValidator(reg_frame_rate, this));

    // hide

    combo_box_x265_profile->setVisible(false);
    combo_box_x265_preset->setVisible(false);
    spin_box_x265_factor->setVisible(false);

    combo_box_svtav1_profile->setVisible(false);
    combo_box_svtav1_preset->setVisible(false);
    spin_box_svtav1_factor->setVisible(false);

    grid_layout_video = new QGridLayout(group_box_video);
    grid_layout_video->addWidget(check_box_video_enable, 0, 0, 1, 1);
    grid_layout_video->addWidget(label_video_container, 0, 2, 1, 1);
    grid_layout_video->addWidget(combo_box_video_container, 0, 3, 1, 1);
    grid_layout_video->addWidget(label_video_codec, 1, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_codec, 1, 1, 1, 1);
    grid_layout_video->addWidget(label_video_profile, 1, 2, 1, 1);
    grid_layout_video->addWidget(combo_box_x264_profile, 1, 3, 1, 1);   // ..
    grid_layout_video->addWidget(combo_box_x265_profile, 1, 3, 1, 1);   // ..
    grid_layout_video->addWidget(combo_box_svtav1_profile, 1, 3, 1, 1); // ..
    grid_layout_video->addWidget(label_video_preset, 2, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_x264_preset, 2, 1, 1, 1);   // ..
    grid_layout_video->addWidget(combo_box_x265_preset, 2, 1, 1, 1);   // ..
    grid_layout_video->addWidget(combo_box_svtav1_preset, 2, 1, 1, 1); // ..
    grid_layout_video->addWidget(label_video_factor, 2, 2, 1, 1);
    grid_layout_video->addWidget(spin_box_x264_factor, 2, 3, 1, 1);   // ..
    grid_layout_video->addWidget(spin_box_x265_factor, 2, 3, 1, 1);   // ..
    grid_layout_video->addWidget(spin_box_svtav1_factor, 2, 3, 1, 1); // ..
    grid_layout_video->addWidget(label_video_pix_fmt, 3, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_pix_fmt, 3, 1, 1, 1);
    grid_layout_video->addWidget(label_video_keyint, 3, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_keyint, 3, 3, 1, 1);
    grid_layout_video->addWidget(label_video_frame_size, 4, 0, 1, 1);
    grid_layout_video->addWidget(line_edit_video_frame_size, 4, 1, 1, 1);
    grid_layout_video->addWidget(label_video_frame_rate, 4, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_frame_rate, 4, 3, 1, 1);
    for (int i = 0; i < grid_layout_video->rowCount(); i++)
        grid_layout_video->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_video->columnCount(); i++)
        grid_layout_video->setColumnStretch(i, 1);
    grid_layout_video->setSpacing(10);

    // audio

    group_box_audio = new QGroupBox(this);
    group_box_audio->setTitle(tr("Audio"));

    check_box_audio_enable = new QCheckBox(group_box_audio);
    check_box_audio_enable->setText(tr("Enable"));
    check_box_audio_enable->setChecked(true);

    label_audio_codec = new QLabel(group_box_audio);
    label_audio_codec->setText(tr("Codec"));
    combo_box_audio_codec = new QComboBox(group_box_audio);
    combo_box_audio_codec->addItem("copy");
    combo_box_audio_codec->addItem("mp3");
    combo_box_audio_codec->addItem("aac");
    combo_box_audio_codec->addItem("opus");
    combo_box_audio_codec->setCurrentIndex(2);

    label_audio_bitrate = new QLabel(group_box_audio);
    label_audio_bitrate->setText(tr("Bitrate"));

    combo_box_mp3_bitrate = new QComboBox(group_box_audio);
    combo_box_mp3_bitrate->addItems(list_audio_rate);
    combo_box_mp3_bitrate->setCurrentIndex(5);

    combo_box_aac_bitrate = new QComboBox(group_box_audio);
    combo_box_aac_bitrate->addItems(list_audio_rate);
    combo_box_aac_bitrate->setCurrentIndex(3);

    combo_box_opus_bitrate = new QComboBox(group_box_audio);
    combo_box_opus_bitrate->addItems(list_audio_rate);
    combo_box_opus_bitrate->setCurrentIndex(2);

    label_audio_frequency = new QLabel(group_box_audio);
    label_audio_frequency->setText(tr("Sample Rate"));
    combo_box_audio_frequency = new QComboBox(group_box_audio);
    combo_box_audio_frequency->addItem(tr("Original"));
    combo_box_audio_frequency->addItem("44100");
    combo_box_audio_frequency->addItem("48000");
    combo_box_audio_frequency->setCurrentIndex(0);

    label_audio_channels = new QLabel(group_box_audio);
    label_audio_channels->setText(tr("Channels"));
    combo_box_audio_channels = new QComboBox(group_box_audio);
    combo_box_audio_channels->addItem(tr("Original"));
    combo_box_audio_channels->addItem("1");
    combo_box_audio_channels->addItem("2");
    combo_box_audio_channels->setCurrentIndex(0);

    combo_box_aac_bitrate->setVisible(false);
    combo_box_opus_bitrate->setVisible(false);

    grid_layout_audio = new QGridLayout(group_box_audio);
    grid_layout_audio->addWidget(check_box_audio_enable, 0, 0, 1, 1);
    grid_layout_audio->addWidget(label_audio_codec, 1, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_audio_codec, 1, 1, 1, 1);
    grid_layout_audio->addWidget(label_audio_bitrate, 2, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_mp3_bitrate, 2, 1, 1, 1);
    grid_layout_audio->addWidget(combo_box_aac_bitrate, 2, 1, 1, 1);
    grid_layout_audio->addWidget(combo_box_opus_bitrate, 2, 1, 1, 1);
    grid_layout_audio->addWidget(label_audio_frequency, 3, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_audio_frequency, 3, 1, 1, 1);
    grid_layout_audio->addWidget(label_audio_channels, 4, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_audio_channels, 4, 1, 1, 1);
    for (int i = 0; i < grid_layout_audio->rowCount(); i++)
        grid_layout_audio->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_audio->columnCount(); i++)
        grid_layout_audio->setColumnStretch(i, 1);
    grid_layout_audio->setSpacing(10);

    // filter

    group_box_filter = new QGroupBox(this);
    group_box_filter->setTitle(tr("Filter"));

    check_box_crop = new QCheckBox(group_box_filter);
    check_box_crop->setText(tr("Crop"));
    check_box_crop->setChecked(false);

    label_crop_x = new QLabel(group_box_filter);
    label_crop_x->setText(tr("X-axis"));
    line_edit_crop_x = new QLineEdit(group_box_filter);
    line_edit_crop_x->setText("0");

    label_crop_y = new QLabel(group_box_filter);
    label_crop_y->setText(tr("Y-axis"));
    line_edit_crop_y = new QLineEdit(group_box_filter);
    line_edit_crop_y->setText("0");

    label_crop_width = new QLabel(group_box_filter);
    label_crop_width->setText(tr("Width"));
    line_edit_crop_width = new QLineEdit(group_box_filter);
    line_edit_crop_width->setText("800");

    label_crop_height = new QLabel(group_box_filter);
    label_crop_height->setText(tr("Height"));
    line_edit_crop_height = new QLineEdit(group_box_filter);
    line_edit_crop_height->setText("600");

    label_crop_x->setEnabled(false);
    line_edit_crop_x->setEnabled(false);
    label_crop_y->setEnabled(false);
    line_edit_crop_y->setEnabled(false);
    label_crop_width->setEnabled(false);
    line_edit_crop_width->setEnabled(false);
    label_crop_height->setEnabled(false);
    line_edit_crop_height->setEnabled(false);

    check_box_cut = new QCheckBox(group_box_filter);
    check_box_cut->setText(tr("Cut"));
    check_box_cut->setChecked(false);

    label_cut_start = new QLabel(group_box_filter);
    label_cut_start->setText(tr("Start"));
    line_edit_cut_start = new QLineEdit(group_box_filter);
    line_edit_cut_start->setInputMask("00:00:00.000");
    line_edit_cut_start->setText("00:00:00.000");

    label_cut_duration = new QLabel(group_box_filter);
    label_cut_duration->setText(tr("Duration"));
    line_edit_cut_duration = new QLineEdit(group_box_filter);
    line_edit_cut_duration->setInputMask("00:00:00.000");
    line_edit_cut_duration->setText("00:00:00.000");

    label_cut_start->setEnabled(false);
    line_edit_cut_start->setEnabled(false);
    label_cut_duration->setEnabled(false);
    line_edit_cut_duration->setEnabled(false);

    grid_layout_filter = new QGridLayout(group_box_filter);
    grid_layout_filter->addWidget(check_box_crop, 0, 0, 1, 1);
    grid_layout_filter->addWidget(label_crop_x, 0, 1, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_x, 0, 2, 1, 1);
    grid_layout_filter->addWidget(label_crop_y, 0, 3, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_y, 0, 4, 1, 1);
    grid_layout_filter->addWidget(label_crop_width, 0, 5, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_width, 0, 6, 1, 1);
    grid_layout_filter->addWidget(label_crop_height, 0, 7, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_height, 0, 8, 1, 1);
    grid_layout_filter->addWidget(check_box_cut, 1, 0, 1, 1);
    grid_layout_filter->addWidget(label_cut_start, 1, 1, 1, 1);
    grid_layout_filter->addWidget(line_edit_cut_start, 1, 2, 1, 3);
    grid_layout_filter->addWidget(label_cut_duration, 1, 5, 1, 1);
    grid_layout_filter->addWidget(line_edit_cut_duration, 1, 6, 1, 3);
    for (int i = 0; i < grid_layout_filter->rowCount(); i++)
        grid_layout_filter->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_filter->columnCount(); i++)
        grid_layout_filter->setColumnStretch(i, 1);
    grid_layout_filter->setSpacing(10);

    // scripts

    widget_scripts = new QWidget(this);

    push_button_check_updates = new QPushButton(widget_scripts);
    push_button_check_updates->setText(tr("Check Updates"));
    label_current_version = new QLabel(widget_scripts);
    label_current_version->setText(tr("Current Version") + ": " + "2.0.0");
    push_button_show_scripts = new QPushButton(widget_scripts);
    push_button_show_scripts->setText(tr("Show Scripts"));
    push_button_execute = new QPushButton(widget_scripts);
    push_button_execute->setText(tr("Start Convert"));

    grid_layout_scripts = new QGridLayout(widget_scripts);
    grid_layout_scripts->addWidget(push_button_check_updates, 0, 0, 1, 1);
    grid_layout_scripts->addWidget(label_current_version, 0, 1, 1, 1);
    grid_layout_scripts->addWidget(push_button_show_scripts, 0, 3, 1, 1);
    grid_layout_scripts->addWidget(push_button_execute, 0, 4, 1, 1);
    for (int i = 0; i < grid_layout_scripts->rowCount(); i++)
        grid_layout_scripts->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_scripts->columnCount(); i++)
        grid_layout_scripts->setColumnStretch(i, 1);
    grid_layout_scripts->setSpacing(10);

    // main

    main_layout = new QGridLayout(this);
    main_layout->addWidget(group_box_input, 0, 0, 1, 2);
    main_layout->addWidget(group_box_output, 1, 0, 1, 2);
    main_layout->addWidget(group_box_video, 2, 0, 1, 1);
    main_layout->addWidget(group_box_audio, 2, 1, 1, 1);
    main_layout->addWidget(group_box_filter, 3, 0, 1, 2);
    main_layout->addWidget(widget_scripts, 4, 0, 1, 2);
    main_layout->setRowStretch(0, 2);
    main_layout->setRowStretch(1, 2);
    main_layout->setRowStretch(2, 6);
    main_layout->setRowStretch(3, 3);
    main_layout->setRowStretch(4, 1);
    main_layout->setColumnStretch(0, 2);
    main_layout->setColumnStretch(1, 1);
    setLayout(main_layout);

    // signal and slots

    connect(thread, &QThread::finished,
            ffmpeg, &QObject::deleteLater);

    connect(push_button_open, &QPushButton::clicked,
            this, &FFGUI::OpenFile);

    connect(check_box_video_enable, &QCheckBox::stateChanged, [=](int state)
            {
                bool enabled = state == Qt::Checked;
                label_video_container->setEnabled(enabled);
                combo_box_video_container->setEnabled(enabled);
                label_video_codec->setEnabled(enabled);
                combo_box_video_codec->setEnabled(enabled);
                label_video_profile->setEnabled(enabled);
                label_video_preset->setEnabled(enabled);
                label_video_factor->setEnabled(enabled);
                combo_box_x264_profile->setEnabled(enabled);
                combo_box_x264_preset->setEnabled(enabled);
                spin_box_x264_factor->setEnabled(enabled);
                combo_box_x265_profile->setEnabled(enabled);
                combo_box_x265_preset->setEnabled(enabled);
                spin_box_x265_factor->setEnabled(enabled);
                combo_box_svtav1_profile->setEnabled(enabled);
                combo_box_svtav1_preset->setEnabled(enabled);
                spin_box_svtav1_factor->setEnabled(enabled);
                label_video_pix_fmt->setEnabled(enabled);
                combo_box_video_pix_fmt->setEnabled(enabled);
                label_video_keyint->setEnabled(enabled);
                line_edit_video_keyint->setEnabled(enabled);
                label_video_frame_size->setEnabled(enabled);
                line_edit_video_frame_size->setEnabled(enabled);
                label_video_frame_rate->setEnabled(enabled);
                line_edit_video_frame_rate->setEnabled(enabled);

                ChangeOutputFileExt();
            });

    connect(combo_box_video_codec, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index)
            {
                if (index == 0) // copy
                {
                    label_video_profile->setVisible(false);
                    label_video_preset->setVisible(false);
                    label_video_factor->setVisible(false);
                    combo_box_x264_profile->setVisible(false);
                    combo_box_x264_preset->setVisible(false);
                    spin_box_x264_factor->setVisible(false);
                    combo_box_x265_profile->setVisible(false);
                    combo_box_x265_preset->setVisible(false);
                    spin_box_x265_factor->setVisible(false);
                    combo_box_svtav1_profile->setVisible(false);
                    combo_box_svtav1_preset->setVisible(false);
                    spin_box_svtav1_factor->setVisible(false);
                    label_video_pix_fmt->setVisible(false);
                    combo_box_video_pix_fmt->setVisible(false);
                    label_video_keyint->setVisible(false);
                    line_edit_video_keyint->setVisible(false);
                    label_video_frame_size->setVisible(false);
                    line_edit_video_frame_size->setVisible(false);
                    label_video_frame_rate->setVisible(false);
                    line_edit_video_frame_rate->setVisible(false);
                }
                else
                {
                    label_video_profile->setVisible(true);
                    label_video_preset->setVisible(true);
                    label_video_factor->setVisible(true);
                    combo_box_x264_profile->setVisible(index == 1);
                    combo_box_x264_preset->setVisible(index == 1);
                    spin_box_x264_factor->setVisible(index == 1);
                    combo_box_x265_profile->setVisible(index == 2);
                    combo_box_x265_preset->setVisible(index == 2);
                    spin_box_x265_factor->setVisible(index == 2);
                    combo_box_svtav1_profile->setVisible(index == 3);
                    combo_box_svtav1_preset->setVisible(index == 3);
                    spin_box_svtav1_factor->setVisible(index == 3);
                    label_video_pix_fmt->setVisible(true);
                    combo_box_video_pix_fmt->setVisible(true);
                    label_video_keyint->setVisible(true);
                    line_edit_video_keyint->setVisible(true);
                    label_video_frame_size->setVisible(true);
                    line_edit_video_frame_size->setVisible(true);
                    label_video_frame_rate->setVisible(true);
                    line_edit_video_frame_rate->setVisible(true);
                }
            });

    connect(combo_box_video_container, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FFGUI::ChangeOutputFileExt);

    connect(check_box_audio_enable, &QCheckBox::stateChanged, [=](int state)
            {
                bool enabled = state == Qt::Checked;
                label_audio_codec->setEnabled(enabled);
                combo_box_audio_codec->setEnabled(enabled);
                label_audio_bitrate->setEnabled(enabled);
                combo_box_mp3_bitrate->setEnabled(enabled);
                combo_box_aac_bitrate->setEnabled(enabled);
                combo_box_opus_bitrate->setEnabled(enabled);
                label_audio_frequency->setEnabled(enabled);
                combo_box_audio_frequency->setEnabled(enabled);
                label_audio_channels->setEnabled(enabled);
                combo_box_audio_channels->setEnabled(enabled);
                ChangeOutputFileExt();
            });

    connect(combo_box_audio_codec, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index)
            {
                if (index == 0) // copy
                {
                    label_audio_bitrate->setVisible(false);
                    combo_box_mp3_bitrate->setVisible(false);
                    combo_box_aac_bitrate->setVisible(false);
                    combo_box_opus_bitrate->setVisible(false);
                    label_audio_frequency->setVisible(false);
                    combo_box_audio_frequency->setVisible(false);
                    label_audio_channels->setVisible(false);
                    combo_box_audio_channels->setVisible(false);
                }
                else
                {
                    label_audio_bitrate->setVisible(true);
                    combo_box_mp3_bitrate->setVisible(index == 1);
                    combo_box_aac_bitrate->setVisible(index == 2);
                    combo_box_opus_bitrate->setVisible(index == 3);
                    label_audio_frequency->setVisible(true);
                    combo_box_audio_frequency->setVisible(true);
                    label_audio_channels->setVisible(true);
                    combo_box_audio_channels->setVisible(true);
                }
                ChangeOutputFileExt();
            });

    connect(check_box_crop, &QCheckBox::stateChanged, [=](int state)
            {
                bool enabled = state == Qt::Checked;
                label_crop_x->setEnabled(enabled);
                line_edit_crop_x->setEnabled(enabled);
                label_crop_y->setEnabled(enabled);
                line_edit_crop_y->setEnabled(enabled);
                label_crop_width->setEnabled(enabled);
                line_edit_crop_width->setEnabled(enabled);
                label_crop_height->setEnabled(enabled);
                line_edit_crop_height->setEnabled(enabled);
            });

    connect(check_box_cut, &QCheckBox::stateChanged, [=](int state)
            {
                bool enabled = state == Qt::Checked;
                label_cut_start->setEnabled(enabled);
                line_edit_cut_start->setEnabled(enabled);
                label_cut_duration->setEnabled(enabled);
                line_edit_cut_duration->setEnabled(enabled);
            });

    connect(push_button_check_updates, &QPushButton::clicked,
            this, [=]()
            {
                QDesktopServices::openUrl(QUrl("https://github.com/lmintlcx/ffgui/releases"));
            });

    connect(push_button_show_scripts, &QPushButton::clicked, [=]()
            {
                QString script_input_file = line_edit_input_filename->text();
                if (script_input_file == "")
                    return;

                QString full_script = GetScript();

                qDebug() << "";
                qDebug() << full_script.toStdString().c_str();
                qDebug() << "";
            });

    connect(push_button_execute, &QPushButton::clicked, [=]()
            {
                bool ffmpeg_exists = CheckFFmpeg();
                if (!ffmpeg_exists)
                    return;

                QString script_input_file = line_edit_input_filename->text();
                if (script_input_file == "")
                    return;

                bool video_enabled = check_box_video_enable->isChecked();
                bool audio_enabled = check_box_audio_enable->isChecked();
                if (!video_enabled && !audio_enabled)
                    return;

                push_button_execute->setEnabled(false);
                this->begin_time = QDateTime::currentDateTime();

                QString full_script = GetScript();
                emit ExecuteScript(full_script);
            });

    connect(this, &FFGUI::ExecuteScript,
            ffmpeg, &FFmpeg::ExecuteScript);

    connect(ffmpeg, &FFmpeg::ExecuteResult,
            this, &FFGUI::ExecuteResult);

    setAcceptDrops(true);

    CheckFFmpeg();

    // setStyleSheet(QString::fromUtf8("border:1px solid red"));
}

FFGUI::~FFGUI()
{
    thread->quit();
    thread->wait();
}

void FFGUI::OpenFile()
{
    QString input_file_full_name = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        tr("All files (*.*) ;; Video files (*.avi *.mov *.flv *.mp4 *.mkv *.webm)"));
    if (!input_file_full_name.isNull())
    {
        line_edit_input_filename->setText(input_file_full_name);
        ChangeOutputFileName(input_file_full_name);
    }
}

void FFGUI::ChangeOutputFileName(QString input_file_full_name)
{
    QString output_file_full_name = input_file_full_name.mid(0, input_file_full_name.lastIndexOf('.'))   //
                                    + "_" + QString::number(QDateTime::currentDateTime().toTime_t(), 16) //
                                    + "." + combo_box_video_container->currentText();
    line_edit_output_filename->setText(output_file_full_name);
    ChangeOutputFileExt();
}

void FFGUI::ChangeOutputFileExt()
{
    QString output_file_full_name = line_edit_output_filename->text();
    if (output_file_full_name == "")
        return;

    int ext_size = output_file_full_name.length() - output_file_full_name.lastIndexOf('.') - 1;
    if (ext_size == 3 || ext_size == 4)
    {
        if (check_box_video_enable->checkState() == Qt::Checked || combo_box_audio_codec->currentText() == "copy")
            output_file_full_name = output_file_full_name.mid(0, output_file_full_name.lastIndexOf('.')) //
                                    + "." + combo_box_video_container->currentText();
        else
            output_file_full_name = output_file_full_name.mid(0, output_file_full_name.lastIndexOf('.')) //
                                    + "." + combo_box_audio_codec->currentText();
        line_edit_output_filename->setText(output_file_full_name);
    }
}

QString FFGUI::GetScript()
{
    QString script_ffmpeg = QString("")                              //
                            + "\""                                   //
                            + QCoreApplication::applicationDirPath() //
                            + "/"                                    //
                            + "ffmpeg.exe"                           //
                            + "\"";

    QString script_video;

    if (!check_box_video_enable->isChecked())
    {
        script_video += " -vn";
    }
    else
    {
        switch (combo_box_video_codec->currentIndex())
        {
        case 0: // copy
            script_video += " -vcodec copy";
            break;

        case 1: // x264
        default:
            script_video += " -vcodec libx264";
            script_video += QString(" -profile:v") + " " + combo_box_x264_profile->currentText();
            script_video += QString(" -preset") + " " + combo_box_x264_preset->currentText();
            script_video += QString(" -crf") + " " + spin_box_x264_factor->text();
            break;

        case 2: // x265
            script_video += " -vcodec libx265";
            script_video += QString(" -profile:v") + " " + combo_box_x265_profile->currentText();
            script_video += QString(" -preset") + " " + combo_box_x265_preset->currentText();
            script_video += QString(" -crf") + " " + spin_box_x265_factor->text();
            break;

        case 3: // svtav1
            script_video += " -vcodec libsvtav1";
            script_video += QString(" -profile:v") + " " + combo_box_svtav1_profile->currentText();
            script_video += QString(" -preset") + " " + combo_box_svtav1_preset->currentText();
            script_video += QString(" -crf") + " " + spin_box_svtav1_factor->text();
            break;
        }

        if (combo_box_video_codec->currentIndex() != 0)
        {
            if (combo_box_video_pix_fmt->currentIndex() == 0)
                script_video += " -pix_fmt yuv420p";
            else
                script_video += QString(" -pix_fmt") + " " + combo_box_video_pix_fmt->currentText();

            if (line_edit_video_keyint->text() == "")
                script_video += " -g 300";
            else
                script_video += QString(" -g") + " " + line_edit_video_keyint->text();

            if (line_edit_video_frame_size->text() != "")
                script_video += QString(" -s") + " " + line_edit_video_frame_size->text();

            if (line_edit_video_frame_rate->text() != "")
                script_video += QString(" -r") + " " + line_edit_video_frame_rate->text();
        }
    }

    QString script_audio;

    if (!check_box_audio_enable->isChecked())
    {
        script_audio += " -an";
    }
    else
    {
        switch (combo_box_audio_codec->currentIndex())
        {
        case 0: // copy
            script_audio += " -acodec copy";
            break;

        case 1: // mp3
            script_audio += " -acodec libmp3lame";
            script_audio += QString(" -ab") + " " + combo_box_mp3_bitrate->currentText() + "k";
            break;

        case 2: // aac
        default:
            script_audio += " -acodec aac";
            script_audio += QString(" -ab") + " " + combo_box_aac_bitrate->currentText() + "k";
            break;

        case 3: // opus
            script_audio += " -acodec libopus";
            script_audio += QString(" -ab") + " " + combo_box_opus_bitrate->currentText() + "k";
            break;
        }

        if (combo_box_audio_codec->currentIndex() != 0)
        {
            if (combo_box_audio_frequency->currentIndex() != 0)
                script_audio += QString(" -ar") + " " + combo_box_audio_frequency->currentText();

            if (combo_box_audio_channels->currentIndex() != 0)
                script_audio += QString(" -ac") + " " + combo_box_audio_channels->currentText();
        }
    }

    QString script_input;

    if (check_box_cut->isChecked())
        script_input += QString(" -ss") + " " + line_edit_cut_start->text();

    script_input += QString(" -i") + " " + "\"" + line_edit_input_filename->text() + "\"";

    if (check_box_cut->isChecked())
        script_input += QString(" -t") + " " + line_edit_cut_duration->text();

    if (check_box_crop->isChecked())
    {
        script_input += QString(" -vf")                       //
                        + " " + "\"" + "crop"                 //
                        + "=" + line_edit_crop_width->text()  //
                        + ":" + line_edit_crop_height->text() //
                        + ":" + line_edit_crop_x->text()      //
                        + ":" + line_edit_crop_y->text()      //
                        + "\"";                               //
    }

    QString script_output;

    QString fmt = combo_box_video_container->currentText();
    if (fmt == "mp4" || fmt == "m4v" || fmt == "mov")
        script_output += " -movflags +faststart";
    if (fmt == "mkv" || fmt == "mka" || fmt == "webm")
        script_output += " -cues_to_front 1";

    if (check_box_overwrite->isChecked())
        script_output += " -y";

    script_output += QString("") + " " + "\"" + line_edit_output_filename->text() + "\"";

    QString full_script = QString("")      //
                          + script_ffmpeg  //
                          + script_input   //
                          + script_video   //
                          + script_audio   //
                          + script_output; //

    return full_script;
}

bool FFGUI::CheckFFmpeg()
{
    QString file_name = QString("")                              //
                        + QCoreApplication::applicationDirPath() //
                        + "/"                                    //
                        + "ffmpeg.exe";

    QFileInfo file_info(file_name);
    bool ffmpeg_exists = file_info.isFile();

    if (!ffmpeg_exists)
    {
        QMessageBox::warning(this, tr("Check FFmpeg"), tr("Note that FFGUI is just a script generator for FFmpeg and does not include media transcoding function itself. Please download FFmpeg from <a href=\"https://www.ffmpeg.org/\">here</a>, then put ffgui.exe and ffmpeg.exe under the same folder after decompressing."), QMessageBox::Ok);
    }

    return ffmpeg_exists;
}

void FFGUI::dragEnterEvent(QDragEnterEvent *event)
{
    if (true)
        event->acceptProposedAction();
}

void FFGUI::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    QString first_file_name = urls.first().toLocalFile();
    if (first_file_name.isEmpty())
        return;

    foreach (QUrl u, urls)
    {
        // qDebug() << u.toString().mid(8).toStdString().c_str();
        QString input_file_full_name = u.toString().mid(8);
        QString input_file_suffix = QFileInfo(input_file_full_name).suffix();

        QStringList video_formats;
        video_formats << "avi"
                      << "mov"
                      << "flv"
                      << "mp4"
                      << "mkv"
                      << "webm";

        if (video_formats.contains(input_file_suffix))
        {
            line_edit_input_filename->setText(input_file_full_name);
            ChangeOutputFileName(input_file_full_name);
        }
    }
    // qDebug() << urls.size();
}

void FFGUI::ExecuteResult(bool success)
{
    push_button_execute->setEnabled(true);
    this->end_time = QDateTime::currentDateTime();

    if (success)
        MessageBeep(MB_OK);
    else
        MessageBeep(MB_ICONWARNING);

    qDebug() << "";
    QString str_result = QString("")                                                     //
                         + (success ? tr("Encoding success!") : tr("Encoding failure!")) //
                         + " " + tr("Time span") + ": "                                  //
                         + QDateTime::fromMSecsSinceEpoch(this->end_time.toMSecsSinceEpoch() - this->begin_time.toMSecsSinceEpoch()).toUTC().toString("hh:mm:ss");
    qDebug() << "";
    qDebug() << str_result.toStdString().c_str();
    qDebug() << "";
}
