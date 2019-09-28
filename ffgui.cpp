
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
    QString temp_file_0 = temp_dir + "/" + "ffmpeg2pass-0.log";
    QString temp_file_1 = temp_dir + "/" + "ffmpeg2pass-0.log.mbtree";
    QFile file_s(script_file);
    QFile file_0(temp_file_0);
    QFile file_1(temp_file_1);

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
    int ret = system(script_file_path_with_quotation_mark.toStdString().c_str());

    QDir::setCurrent(app_dir);

    file_s.remove();
    file_0.remove();
    file_1.remove();
    temp.rmdir(temp_dir);

    emit ExecuteResult(ret == 0 ? true : false);
}

// FFGUI

FFGUI::FFGUI()
{
    SetConsoleTitle(TEXT("FFGUI 1.6.7 Console"));

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
                          << "960x720"    // ..
                          << "1440x1080"; // ..

    this->list_frame_rate << "10"
                          << "20"
                          << "23.976"
                          << "24"
                          << "25"
                          << "29.97"
                          << "30"
                          << "48"
                          << "50"
                          << "59.94"
                          << "60"
                          << "75"
                          << "100"
                          << "120"
                          << "144"
                          << "240";

    // worker

    ffmpeg = new FFmpeg();
    thread = new QThread(this);
    ffmpeg->moveToThread(thread);
    thread->start();

    // input

    group_box_input = new QGroupBox(this);
    group_box_input->setTitle(tr("Input"));

    label_input_video = new QLabel(group_box_input);
    label_input_video->setText(tr("Video"));
    line_edit_input_filename_video = new QLineEdit(group_box_input);
    push_button_open_video = new QPushButton(group_box_input);
    push_button_open_video->setText(tr("Open"));

    label_input_audio = new QLabel(group_box_input);
    label_input_audio->setText(tr("Audio"));
    line_edit_input_filename_audio = new QLineEdit(group_box_input);
    push_button_open_audio = new QPushButton(group_box_input);
    push_button_open_audio->setText(tr("Open"));

    grid_layout_input = new QGridLayout(group_box_input);
    grid_layout_input->addWidget(label_input_video, 0, 0, 1, 1);
    grid_layout_input->addWidget(line_edit_input_filename_video, 0, 1, 1, 8);
    grid_layout_input->addWidget(push_button_open_video, 0, 9, 1, 1);
    grid_layout_input->addWidget(label_input_audio, 1, 0, 1, 1);
    grid_layout_input->addWidget(line_edit_input_filename_audio, 1, 1, 1, 8);
    grid_layout_input->addWidget(push_button_open_audio, 1, 9, 1, 1);
    for (int i = 0; i < grid_layout_input->rowCount(); i++)
        grid_layout_input->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_input->columnCount(); i++)
        grid_layout_input->setColumnStretch(i, 1);
    grid_layout_input->setSpacing(10);

    // output

    group_box_output = new QGroupBox(this);
    group_box_output->setTitle(tr("Output"));

    label_output = new QLabel(group_box_output);
    label_output->setText(tr("File"));
    line_edit_output_filename = new QLineEdit(group_box_output);

    grid_layout_output = new QGridLayout(group_box_output);
    grid_layout_output->addWidget(label_output, 0, 0, 1, 1);
    grid_layout_output->addWidget(line_edit_output_filename, 0, 1, 1, 9);
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

    check_box_video_crf = new QCheckBox(group_box_video);
    check_box_video_crf->setText("crf");
    check_box_video_crf->setChecked(false);
    check_box_video_2pass = new QCheckBox(group_box_video);
    check_box_video_2pass->setText("2pass");
    check_box_video_2pass->setChecked(true);

    label_video_codec = new QLabel(group_box_video);
    label_video_codec->setText(tr("Codec"));
    combo_box_video_codec = new QComboBox(group_box_video);
    combo_box_video_codec->addItem("copy");
    combo_box_video_codec->addItem("x264");
    combo_box_video_codec->addItem("nvenc");
    combo_box_video_codec->setCurrentIndex(1);

    label_video_container = new QLabel(group_box_video);
    label_video_container->setText(tr("Container"));
    combo_box_video_container = new QComboBox(group_box_video);
    combo_box_video_container->addItem("flv");
    combo_box_video_container->addItem("mp4");
    combo_box_video_container->addItem("avi");
    combo_box_video_container->addItem("mov");
    combo_box_video_container->addItem("mkv");
    combo_box_video_container->setCurrentIndex(0);

    label_video_preset = new QLabel(group_box_video);
    label_video_preset->setText(tr("Preset") + " (x264)");

    combo_box_video_x264_preset = new QComboBox(group_box_video);
    combo_box_video_x264_preset->addItem("ultrafast");
    combo_box_video_x264_preset->addItem("superfast");
    combo_box_video_x264_preset->addItem("veryfast");
    combo_box_video_x264_preset->addItem("faster");
    combo_box_video_x264_preset->addItem("fast");
    combo_box_video_x264_preset->addItem("medium");
    combo_box_video_x264_preset->addItem("slow");
    combo_box_video_x264_preset->addItem("slower");
    combo_box_video_x264_preset->addItem("veryslow");
    combo_box_video_x264_preset->addItem("placebo");
    combo_box_video_x264_preset->setCurrentIndex(8);

    combo_box_video_nvenc_preset = new QComboBox(group_box_video);
    combo_box_video_nvenc_preset->addItem("default");
    combo_box_video_nvenc_preset->addItem("slow");
    combo_box_video_nvenc_preset->addItem("medium");
    combo_box_video_nvenc_preset->addItem("fast");
    combo_box_video_nvenc_preset->addItem("hp");
    combo_box_video_nvenc_preset->addItem("hq");
    combo_box_video_nvenc_preset->addItem("bd");
    combo_box_video_nvenc_preset->addItem("ll");
    combo_box_video_nvenc_preset->addItem("llhq");
    combo_box_video_nvenc_preset->addItem("llhp");
    combo_box_video_nvenc_preset->addItem("lossless");
    combo_box_video_nvenc_preset->addItem("losslesshp");
    combo_box_video_nvenc_preset->setCurrentIndex(1);

    label_video_bitrate = new QLabel(group_box_video);
    label_video_bitrate->setText(tr("Bitrate") + " (kbps)");
    spin_box_video_bitrate = new QDoubleSpinBox(group_box_video);
    spin_box_video_bitrate->setRange(0.0, 99999999.0);
    spin_box_video_bitrate->setSingleStep(100);
    spin_box_video_bitrate->setDecimals(0);
    spin_box_video_bitrate->setValue(2980);

    label_video_factor = new QLabel(group_box_video);
    label_video_factor->setText(tr("Rate Factor") + " (0-51)");
    spin_box_video_factor = new QDoubleSpinBox(group_box_video);
    spin_box_video_factor->setRange(0.0, 51.0);
    spin_box_video_factor->setSingleStep(0.1);
    spin_box_video_factor->setDecimals(1);
    spin_box_video_factor->setValue(23.5);

    label_video_frame_size = new QLabel(group_box_video);
    label_video_frame_size->setText(tr("Frame Size") + " (px*px)");
    line_edit_video_frame_size = new QLineEdit(group_box_video);
    // line_edit_video_frame_size->setText("1920x1080");
    line_edit_video_frame_size->setPlaceholderText(tr("Original"));

    this->list_frame_size.removeDuplicates();
    QCompleter *completer_frame_size = new QCompleter(list_frame_size);
    line_edit_video_frame_size->setCompleter(completer_frame_size);

    QRegExp reg_frame_size("[1-9][0-9]{1,5}[x][1-9][0-9]{1,5}");
    line_edit_video_frame_size->setValidator(new QRegExpValidator(reg_frame_size, this));

    label_video_frame_rate = new QLabel(group_box_video);
    label_video_frame_rate->setText(tr("Frame Rate") + " (fps)");
    line_edit_video_frame_rate = new QLineEdit(group_box_video);
    // line_edit_video_frame_rate->setText("60");
    line_edit_video_frame_rate->setPlaceholderText(tr("Original"));

    this->list_frame_rate.removeDuplicates();
    QCompleter *completer_frame_rate = new QCompleter(list_frame_rate);
    line_edit_video_frame_rate->setCompleter(completer_frame_rate);

    QRegExp reg_frame_rate("^([0]|[1-9][0-9]{0,2})([.][0-9]{1,3})$");
    line_edit_video_frame_rate->setValidator(new QRegExpValidator(reg_frame_rate, this));

    label_video_profile_level = new QLabel(group_box_video);
    label_video_profile_level->setText(tr("Profile") + " / " + tr("Level"));
    combo_box_video_profile_level = new QComboBox(group_box_video);
    combo_box_video_profile_level->addItem("baseline 3.0");
    combo_box_video_profile_level->addItem("baseline 3.1");
    combo_box_video_profile_level->addItem("main 3.1");
    combo_box_video_profile_level->addItem("main 4.0");
    combo_box_video_profile_level->addItem("high 4.0");
    combo_box_video_profile_level->addItem("high 4.1");
    combo_box_video_profile_level->addItem("high 4.2");
    combo_box_video_profile_level->addItem("high 5.0");
    combo_box_video_profile_level->addItem("high 5.1");
    combo_box_video_profile_level->setCurrentIndex(6);

    label_video_x264_keyint = new QLabel(group_box_video);
    label_video_x264_keyint->setText(tr("Keyframe Interval") + " (s)");
    line_edit_video_x264_keyint = new QLineEdit(group_box_video);
    // line_edit_video_x264_keyint->setText("10");
    line_edit_video_x264_keyint->setPlaceholderText("10");

    QIntValidator *validator_video_keyframe = new QIntValidator;
    validator_video_keyframe->setRange(1, 999);
    line_edit_video_x264_keyint->setValidator(validator_video_keyframe);

    // same position, hide one of them
    combo_box_video_nvenc_preset->setVisible(false);
    label_video_factor->setVisible(false);
    spin_box_video_factor->setVisible(false);

    grid_layout_video = new QGridLayout(group_box_video);
    grid_layout_video->addWidget(check_box_video_enable, 0, 0, 1, 1);
    grid_layout_video->addWidget(check_box_video_crf, 0, 2, 1, 1);
    grid_layout_video->addWidget(check_box_video_2pass, 0, 3, 1, 1);
    grid_layout_video->addWidget(label_video_codec, 1, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_codec, 1, 1, 1, 1);
    grid_layout_video->addWidget(label_video_container, 1, 2, 1, 1);
    grid_layout_video->addWidget(combo_box_video_container, 1, 3, 1, 1);
    grid_layout_video->addWidget(label_video_preset, 2, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_x264_preset, 2, 1, 1, 1);  // ..
    grid_layout_video->addWidget(combo_box_video_nvenc_preset, 2, 1, 1, 1); // ..
    grid_layout_video->addWidget(label_video_bitrate, 2, 2, 1, 1);          // ..
    grid_layout_video->addWidget(label_video_factor, 2, 2, 1, 1);           // ..
    grid_layout_video->addWidget(spin_box_video_bitrate, 2, 3, 1, 1);       // ..
    grid_layout_video->addWidget(spin_box_video_factor, 2, 3, 1, 1);        // ..
    grid_layout_video->addWidget(label_video_frame_size, 3, 0, 1, 1);
    grid_layout_video->addWidget(line_edit_video_frame_size, 3, 1, 1, 1);
    grid_layout_video->addWidget(label_video_frame_rate, 3, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_frame_rate, 3, 3, 1, 1);
    grid_layout_video->addWidget(label_video_profile_level, 4, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_profile_level, 4, 1, 1, 1);
    grid_layout_video->addWidget(label_video_x264_keyint, 4, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_x264_keyint, 4, 3, 1, 1);
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
    combo_box_audio_codec->addItem("aac");
    combo_box_audio_codec->addItem("mp3");
    combo_box_audio_codec->setCurrentIndex(1);

    label_audio_bitrate = new QLabel(group_box_audio);
    label_audio_bitrate->setText(tr("Bitrate") + " (kbps)");
    combo_box_audio_bitrate = new QComboBox(group_box_audio);
    combo_box_audio_bitrate->addItem("64");
    combo_box_audio_bitrate->addItem("96");
    combo_box_audio_bitrate->addItem("128");
    combo_box_audio_bitrate->addItem("160");
    combo_box_audio_bitrate->addItem("192");
    combo_box_audio_bitrate->addItem("256");
    combo_box_audio_bitrate->addItem("320");
    combo_box_audio_bitrate->setCurrentIndex(4);

    label_audio_frequency = new QLabel(group_box_audio);
    label_audio_frequency->setText(tr("Sampling Frequency") + " (Hz)");
    combo_box_audio_frequency = new QComboBox(group_box_audio);
    combo_box_audio_frequency->addItem("44100");
    combo_box_audio_frequency->addItem("48000");
    combo_box_audio_frequency->setCurrentIndex(0);

    label_audio_channels = new QLabel(group_box_audio);
    label_audio_channels->setText(tr("Channels"));
    combo_box_audio_channels = new QComboBox(group_box_audio);
    combo_box_audio_channels->addItem("1");
    combo_box_audio_channels->addItem("2");
    combo_box_audio_channels->setCurrentIndex(1);

    grid_layout_audio = new QGridLayout(group_box_audio);
    grid_layout_audio->addWidget(check_box_audio_enable, 0, 0, 1, 1);
    grid_layout_audio->addWidget(label_audio_codec, 1, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_audio_codec, 1, 1, 1, 1);
    grid_layout_audio->addWidget(label_audio_bitrate, 2, 0, 1, 1);
    grid_layout_audio->addWidget(combo_box_audio_bitrate, 2, 1, 1, 1);
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

    check_box_watermark = new QCheckBox(group_box_filter);
    check_box_watermark->setText(tr("Watermark"));
    check_box_watermark->setChecked(false);

    label_watermark_x = new QLabel(group_box_filter);
    label_watermark_x->setText(tr("X-axis"));
    line_edit_watermark_x = new QLineEdit(group_box_filter);
    line_edit_watermark_x->setText("0");

    label_watermark_y = new QLabel(group_box_filter);
    label_watermark_y->setText(tr("Y-axis"));
    line_edit_watermark_y = new QLineEdit(group_box_filter);
    line_edit_watermark_y->setText("0");

    line_edit_input_watermark = new QLineEdit(group_box_filter);
    push_button_open_watermark = new QPushButton(group_box_filter);
    push_button_open_watermark->setText(tr("Open"));

    label_watermark_x->setEnabled(false);
    line_edit_watermark_x->setEnabled(false);
    label_watermark_y->setEnabled(false);
    line_edit_watermark_y->setEnabled(false);
    line_edit_input_watermark->setEnabled(false);
    push_button_open_watermark->setEnabled(false);

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
    line_edit_crop_width->setText("1920");

    label_crop_height = new QLabel(group_box_filter);
    label_crop_height->setText(tr("Height"));
    line_edit_crop_height = new QLineEdit(group_box_filter);
    line_edit_crop_height->setText("1080");

    label_crop_x->setEnabled(false);
    line_edit_crop_x->setEnabled(false);
    label_crop_y->setEnabled(false);
    line_edit_crop_y->setEnabled(false);
    label_crop_width->setEnabled(false);
    line_edit_crop_width->setEnabled(false);
    label_crop_height->setEnabled(false);
    line_edit_crop_height->setEnabled(false);

    check_box_cutting = new QCheckBox(group_box_filter);
    check_box_cutting->setText(tr("Cutting"));
    check_box_cutting->setChecked(false);

    label_cutting_start = new QLabel(group_box_filter);
    label_cutting_start->setText(tr("Start"));
    line_edit_cutting_start = new QLineEdit(group_box_filter);
    line_edit_cutting_start->setInputMask("00:00:00.000");
    line_edit_cutting_start->setText("00:00:00.000");

    label_cutting_duration = new QLabel(group_box_filter);
    label_cutting_duration->setText(tr("Duration"));
    line_edit_cutting_duration = new QLineEdit(group_box_filter);
    line_edit_cutting_duration->setInputMask("00:00:00.000");
    line_edit_cutting_duration->setText("00:00:00.000");

    label_cutting_start->setEnabled(false);
    line_edit_cutting_start->setEnabled(false);
    label_cutting_duration->setEnabled(false);
    line_edit_cutting_duration->setEnabled(false);

    check_box_half_speed = new QCheckBox(group_box_filter);
    check_box_half_speed->setText(tr("Half Speed") + " (0.5x)");
    check_box_half_speed->setChecked(false);
    check_box_double_speed = new QCheckBox(group_box_filter);
    check_box_double_speed->setText(tr("Double Speed") + " (2x)");
    check_box_double_speed->setChecked(false);

    grid_layout_filter = new QGridLayout(group_box_filter);
    grid_layout_filter->addWidget(check_box_watermark, 0, 0, 1, 1);
    grid_layout_filter->addWidget(label_watermark_x, 0, 1, 1, 1);
    grid_layout_filter->addWidget(line_edit_watermark_x, 0, 2, 1, 1);
    grid_layout_filter->addWidget(label_watermark_y, 0, 3, 1, 1);
    grid_layout_filter->addWidget(line_edit_watermark_y, 0, 4, 1, 1);
    grid_layout_filter->addWidget(line_edit_input_watermark, 0, 5, 1, 6);
    grid_layout_filter->addWidget(push_button_open_watermark, 0, 11, 1, 1);
    grid_layout_filter->addWidget(check_box_crop, 1, 0, 1, 1);
    grid_layout_filter->addWidget(label_crop_x, 1, 1, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_x, 1, 2, 1, 1);
    grid_layout_filter->addWidget(label_crop_y, 1, 3, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_y, 1, 4, 1, 1);
    grid_layout_filter->addWidget(label_crop_width, 1, 5, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_width, 1, 6, 1, 1);
    grid_layout_filter->addWidget(label_crop_height, 1, 7, 1, 1);
    grid_layout_filter->addWidget(line_edit_crop_height, 1, 8, 1, 1);
    grid_layout_filter->addWidget(check_box_cutting, 2, 0, 1, 1);
    grid_layout_filter->addWidget(label_cutting_start, 2, 1, 1, 1);
    grid_layout_filter->addWidget(line_edit_cutting_start, 2, 2, 1, 2);
    grid_layout_filter->addWidget(label_cutting_duration, 2, 4, 1, 1);
    grid_layout_filter->addWidget(line_edit_cutting_duration, 2, 5, 1, 2);
    grid_layout_filter->addWidget(check_box_half_speed, 2, 10, 1, 1);
    grid_layout_filter->addWidget(check_box_double_speed, 2, 11, 1, 1);
    for (int i = 0; i < grid_layout_filter->rowCount(); i++)
        grid_layout_filter->setRowStretch(i, 1);
    for (int i = 0; i < grid_layout_filter->columnCount(); i++)
        grid_layout_filter->setColumnStretch(i, 1);
    grid_layout_filter->setSpacing(10);

    // scripts

    widget_scripts = new QWidget(this);

    push_button_check_updates = new QPushButton(widget_scripts);
    push_button_check_updates->setText(tr("Check Updates"));
    push_button_show_scripts = new QPushButton(widget_scripts);
    push_button_show_scripts->setText(tr("Show Scripts"));
    push_button_execute = new QPushButton(widget_scripts);
    push_button_execute->setText(tr("Start Convert"));

    grid_layout_scripts = new QGridLayout(widget_scripts);
    grid_layout_scripts->addWidget(push_button_check_updates, 0, 0, 1, 1);
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
    // 3x+1
    main_layout->setRowStretch(0, 7);  // 2
    main_layout->setRowStretch(1, 4);  // 1
    main_layout->setRowStretch(2, 16); // 5
    main_layout->setRowStretch(3, 10); // 3
    main_layout->setRowStretch(4, 4);  // 1
    main_layout->setColumnStretch(0, 2);
    main_layout->setColumnStretch(1, 1);
    setLayout(main_layout);

    // signal and slots

    connect(thread, &QThread::finished,
            ffmpeg, &QObject::deleteLater);

    connect(push_button_open_video, &QPushButton::clicked,
            this, &FFGUI::OpenFileVideo);

    connect(push_button_open_audio, &QPushButton::clicked,
            this, &FFGUI::OpenFileAudio);

    connect(push_button_open_watermark, &QPushButton::clicked,
            this, &FFGUI::OpenFilePicture);

    connect(check_box_video_enable, &QCheckBox::stateChanged, [=](int state) {
        bool enabled = state == Qt::Checked;
        check_box_video_crf->setEnabled(enabled);
        check_box_video_2pass->setEnabled(enabled);
        label_video_codec->setEnabled(enabled);
        combo_box_video_codec->setEnabled(enabled);
        label_video_container->setEnabled(enabled);
        combo_box_video_container->setEnabled(enabled);
        label_video_preset->setEnabled(enabled);
        combo_box_video_x264_preset->setEnabled(enabled);
        combo_box_video_nvenc_preset->setEnabled(enabled);
        label_video_bitrate->setEnabled(enabled);
        spin_box_video_bitrate->setEnabled(enabled);
        label_video_factor->setEnabled(enabled);
        spin_box_video_factor->setEnabled(enabled);
        label_video_frame_size->setEnabled(enabled);
        line_edit_video_frame_size->setEnabled(enabled);
        label_video_frame_rate->setEnabled(enabled);
        line_edit_video_frame_rate->setEnabled(enabled);
        label_video_profile_level->setEnabled(enabled);
        combo_box_video_profile_level->setEnabled(enabled);
        label_video_x264_keyint->setEnabled(enabled);
        line_edit_video_x264_keyint->setEnabled(enabled);
        ChangeOutputFileExt();
    });

    connect(combo_box_video_codec, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) // copy
        {
            check_box_video_crf->setVisible(false);           //
            check_box_video_2pass->setVisible(false);         //
            label_video_container->setVisible(true);          // x
            combo_box_video_container->setVisible(true);      // x
            label_video_preset->setVisible(false);            //
            combo_box_video_x264_preset->setVisible(false);   //
            combo_box_video_nvenc_preset->setVisible(false);  //
            label_video_bitrate->setVisible(false);           //
            spin_box_video_bitrate->setVisible(false);        //
            label_video_factor->setVisible(false);            //
            spin_box_video_factor->setVisible(false);         //
            label_video_frame_size->setVisible(false);        //
            line_edit_video_frame_size->setVisible(false);    //
            label_video_frame_rate->setVisible(false);        //
            line_edit_video_frame_rate->setVisible(false);    //
            label_video_profile_level->setVisible(false);     //
            combo_box_video_profile_level->setVisible(false); //
            label_video_x264_keyint->setVisible(false);       //
            line_edit_video_x264_keyint->setVisible(false);   //
        }
        else if (index == 1) // x264
        {
            check_box_video_crf->setVisible(true);           // x
            check_box_video_2pass->setVisible(true);         // x
            label_video_container->setVisible(true);         // x
            combo_box_video_container->setVisible(true);     // x
            label_video_preset->setVisible(true);            // x
            combo_box_video_x264_preset->setVisible(true);   // x
            combo_box_video_nvenc_preset->setVisible(false); //
            label_video_bitrate->setVisible(true);           // x
            spin_box_video_bitrate->setVisible(true);        // x
            label_video_factor->setVisible(true);            // x
            spin_box_video_factor->setVisible(true);         // x
            label_video_frame_size->setVisible(true);        // x
            line_edit_video_frame_size->setVisible(true);    // x
            label_video_frame_rate->setVisible(true);        // x
            line_edit_video_frame_rate->setVisible(true);    // x
            label_video_profile_level->setVisible(true);     // x
            combo_box_video_profile_level->setVisible(true); // x
            label_video_x264_keyint->setVisible(true);       // x
            line_edit_video_x264_keyint->setVisible(true);   // x

            label_video_preset->setText(tr("Preset") + " (x264)");
            SwitchX264Mode();
        }
        else if (index == 2) // nvenc
        {
            check_box_video_crf->setVisible(false);           //
            check_box_video_2pass->setVisible(false);         //
            label_video_container->setVisible(true);          // x
            combo_box_video_container->setVisible(true);      // x
            label_video_preset->setVisible(true);             // x
            combo_box_video_x264_preset->setVisible(false);   //
            combo_box_video_nvenc_preset->setVisible(true);   // x
            label_video_bitrate->setVisible(true);            // x
            spin_box_video_bitrate->setVisible(true);         // x
            label_video_factor->setVisible(false);            //
            spin_box_video_factor->setVisible(false);         //
            label_video_frame_size->setVisible(false);        //
            line_edit_video_frame_size->setVisible(false);    //
            label_video_frame_rate->setVisible(false);        //
            line_edit_video_frame_rate->setVisible(false);    //
            label_video_profile_level->setVisible(false);     //
            combo_box_video_profile_level->setVisible(false); //
            label_video_x264_keyint->setVisible(false);       //
            line_edit_video_x264_keyint->setVisible(false);   //

            label_video_preset->setText(tr("Preset") + " (nvenc)");
        }
    });

    connect(check_box_video_crf, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
        {
            check_box_video_2pass->setChecked(false);
            SwitchX264Mode();
        }
        else
        {
            check_box_video_2pass->setChecked(true);
        }
    });

    connect(check_box_video_2pass, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
        {
            check_box_video_crf->setChecked(false);
            SwitchX264Mode();
        }
        else
        {
            check_box_video_crf->setChecked(true);
        }
    });

    connect(combo_box_video_container, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FFGUI::ChangeOutputFileExt);

    connect(check_box_audio_enable, &QCheckBox::stateChanged, [=](int state) {
        bool enabled = state == Qt::Checked;
        label_audio_codec->setEnabled(enabled);
        combo_box_audio_codec->setEnabled(enabled);
        label_audio_bitrate->setEnabled(enabled);
        combo_box_audio_bitrate->setEnabled(enabled);
        label_audio_frequency->setEnabled(enabled);
        combo_box_audio_frequency->setEnabled(enabled);
        label_audio_channels->setEnabled(enabled);
        combo_box_audio_channels->setEnabled(enabled);
        ChangeOutputFileExt();
    });

    connect(combo_box_audio_codec, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) // copy
        {
            label_audio_bitrate->setVisible(false);       //
            combo_box_audio_bitrate->setVisible(false);   //
            label_audio_frequency->setVisible(false);     //
            combo_box_audio_frequency->setVisible(false); //
            label_audio_channels->setVisible(false);      //
            combo_box_audio_channels->setVisible(false);  //
        }
        else if (index == 1 || index == 2) // aac mp3
        {
            label_audio_bitrate->setVisible(true);       // x
            combo_box_audio_bitrate->setVisible(true);   // x
            label_audio_frequency->setVisible(true);     // x
            combo_box_audio_frequency->setVisible(true); // x
            label_audio_channels->setVisible(true);      // x
            combo_box_audio_channels->setVisible(true);  // x
        }
        ChangeOutputFileExt();
    });

    connect(check_box_watermark, &QCheckBox::stateChanged, [=](int state) {
        bool enabled = state == Qt::Checked;
        label_watermark_x->setEnabled(enabled);
        line_edit_watermark_x->setEnabled(enabled);
        label_watermark_y->setEnabled(enabled);
        line_edit_watermark_y->setEnabled(enabled);
        line_edit_input_watermark->setEnabled(enabled);
        push_button_open_watermark->setEnabled(enabled);
    });

    connect(check_box_crop, &QCheckBox::stateChanged, [=](int state) {
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

    connect(check_box_cutting, &QCheckBox::stateChanged, [=](int state) {
        bool enabled = state == Qt::Checked;
        label_cutting_start->setEnabled(enabled);
        line_edit_cutting_start->setEnabled(enabled);
        label_cutting_duration->setEnabled(enabled);
        line_edit_cutting_duration->setEnabled(enabled);
    });

    connect(check_box_half_speed, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
            check_box_double_speed->setChecked(false);
    });

    connect(check_box_double_speed, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
            check_box_half_speed->setChecked(false);
    });

    connect(push_button_check_updates, &QPushButton::clicked,
            this, [=]() {
                QDesktopServices::openUrl(QUrl("https://github.com/lmintlcx/ffgui/releases"));
            });

    connect(push_button_show_scripts, &QPushButton::clicked, [=]() {
        QString script_input_file_video = line_edit_input_filename_video->text();
        QString script_input_file_audio = line_edit_input_filename_audio->text();
        if (script_input_file_video == "" && script_input_file_audio == "")
            return;

        QString full_script = GetScript();

        QMessageBox msg_box;
        msg_box.setWindowTitle(tr("FFmpeg Scripts"));
        msg_box.setText(full_script);
        msg_box.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.exec();
    });

    connect(push_button_execute, &QPushButton::clicked, [=]() {
        bool ffmpeg_exists = CheckFFmpeg();
        if (!ffmpeg_exists)
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

void FFGUI::SwitchX264Mode()
{
    if (check_box_video_crf->isChecked())
    {
        label_video_factor->setVisible(true);
        spin_box_video_factor->setVisible(true);
        label_video_bitrate->setVisible(false);
        spin_box_video_bitrate->setVisible(false);
    }
    else
    {
        label_video_bitrate->setVisible(true);
        spin_box_video_bitrate->setVisible(true);
        label_video_factor->setVisible(false);
        spin_box_video_factor->setVisible(false);
    }
}

void FFGUI::OpenFileVideo()
{
    QString input_file_full_name = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        tr("All files (*.*) ;; Video files (*.flv *.mp4 *.avi *.mov *.mkv)"));
    if (!input_file_full_name.isNull())
    {
        line_edit_input_filename_video->setText(input_file_full_name);
        ChangeOutputFileName(input_file_full_name);
    }
}

void FFGUI::OpenFileAudio()
{
    QString input_file_full_name = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        tr("All files (*.*) ;; Audio files (*.mp3 *.aac *.flac)"));
    if (!input_file_full_name.isNull())
    {
        line_edit_input_filename_audio->setText(input_file_full_name);
        if (line_edit_input_filename_video->text() == "")
        {
            ChangeOutputFileName(input_file_full_name);
        }
        else
        {
            ChangeOutputFileName(line_edit_input_filename_video->text());
        }
    }
}

void FFGUI::OpenFilePicture()
{
    QString input_file_full_name = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        tr("All files (*.*) ;; Picture files (*.png *.jpg *.gif *.tiff *.webp)"));
    if (!input_file_full_name.isNull())
    {
        line_edit_input_watermark->setText(input_file_full_name);
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
    if (output_file_full_name != "")
    {
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
}

QString FFGUI::GetScript()
{
    QString script_ffmpeg = QString("")                              //
                            + "\""                                   //
                            + QCoreApplication::applicationDirPath() //
                            + "/"                                    //
                            + "ffmpeg.exe"                           //
                            + "\"";
    if (combo_box_video_codec->currentText() == "nvenc")
        script_ffmpeg += " -hwaccel cuvid -c:v h264_cuvid";

    QString script_filter_watermark = QString("");
    if (check_box_watermark->isChecked() && line_edit_input_watermark->text() != "")
    {
        script_filter_watermark = QString(" ") + "-i"                                     //
                                  + " " + "\"" + line_edit_input_watermark->text() + "\"" //
                                  + " " + "-filter_complex"                               //
                                  + " " + "\"" + "overlay"                                //
                                  + "=" + line_edit_watermark_x->text()                   //
                                  + ":" + line_edit_watermark_y->text() + "\"";           //
    }

    QString script_filter_crop = QString("");
    if (check_box_crop->isChecked())
    {
        script_filter_crop = QString(" ") + "-vf"                     //
                             + " " + "\"" + "crop"                    //
                             + "=" + line_edit_crop_width->text()     //
                             + ":" + line_edit_crop_height->text()    //
                             + ":" + line_edit_crop_x->text()         //
                             + ":" + line_edit_crop_y->text() + "\""; //
    }

    QString script_filter_cutting = QString("");
    if (check_box_cutting->isChecked())
    {
        script_filter_cutting = (QString(" ") + "-ss" + " " + line_edit_cutting_start->text() //
                                 + " " + "-t" + " " + line_edit_cutting_duration->text());    //
    }

    QString script_filter_speed = QString("");
    if (check_box_half_speed->isChecked())
        script_filter_speed = QString(" -filter_complex [0:v]setpts=2.0*PTS[v];[0:a]atempo=0.5[a] -map [v] -map [a]");
    else if (check_box_double_speed->isChecked())
        script_filter_speed = QString(" -filter_complex [0:v]setpts=0.5*PTS[v];[0:a]atempo=2.0[a] -map [v] -map [a]");

    QString script_filter = QString("") + script_filter_watermark + script_filter_crop + script_filter_cutting + script_filter_speed;

    QString script_input_file_video = QString("");
    QString script_input_file_audio = QString("");

    if (line_edit_input_filename_video->text() != "")
        script_input_file_video = QString(" ") + "-i" + " " + "\"" + line_edit_input_filename_video->text() + "\"";
    if (line_edit_input_filename_audio->text() != "")
        script_input_file_audio = QString(" ") + "-i" + " " + "\"" + line_edit_input_filename_audio->text() + "\"";

    QString script_input = QString("") + script_input_file_video + script_input_file_audio;

    QString script_video = QString("");
    if (!check_box_video_enable->isChecked())
    {
        script_video = QString(" ") + "-vn";
    }
    else
    {
        QString script_video_x264_preset = QString(" ") + "-preset" + " " + combo_box_video_x264_preset->currentText();
        QString script_video_nvenc_preset = QString(" ") + "-preset" + " " + combo_box_video_nvenc_preset->currentText();

        QString script_video_profile = QString(" ") + "-profile:v" + " " + combo_box_video_profile_level->currentText().split(" ", QString::SkipEmptyParts)[0];
        QString script_video_level = QString(" ") + "-level:v" + " " + combo_box_video_profile_level->currentText().split(" ", QString::SkipEmptyParts)[1];
        QString script_video_profile_level = script_video_profile + script_video_level;

        double input_frame_rate = 25.0;
        double input_keyint_sec = 10.0;
        if (line_edit_video_frame_rate->text() != "")
            input_frame_rate = line_edit_video_frame_rate->text().toDouble();
        if (line_edit_video_x264_keyint->text() != "")
            input_keyint_sec = line_edit_video_x264_keyint->text().toDouble();
        QString script_video_x264_params = QString(" ") + "-x264-params" + " "                                            //
                                           + "keyint=" + QString::number(int(input_frame_rate * input_keyint_sec * 0.95)) //
                                           + ":" + "min-keyint=" + QString::number(int(input_frame_rate));

        QString script_video_pix_fmt = QString(" ") + "-pix_fmt" + " " + "yuv420p";

        QString script_video_rate_control = QString("");
        if (combo_box_video_codec->currentText() == "x264")
            if (check_box_video_crf->isChecked())
                script_video_rate_control = QString(" ") + "-crf" + " " + spin_box_video_factor->text();
            else
                script_video_rate_control = QString(" ") + "-b:v" + " " + spin_box_video_bitrate->text() + "k";
        else if (combo_box_video_codec->currentText() == "nvenc")
            script_video_rate_control = QString(" ") + "-rc:v vbr_2pass" + " " + "-b:v" + " " + spin_box_video_bitrate->text() + "k";

        QString script_video_frame_size = QString("");
        if (line_edit_video_frame_size->text() != "")
            script_video_frame_size = QString(" ") + "-s" + " " + line_edit_video_frame_size->text();

        QString script_video_frame_rate = QString("");
        if (line_edit_video_frame_rate->text() != "")
            script_video_frame_rate = QString(" ") + "-r" + " " + line_edit_video_frame_rate->text();

        if (combo_box_video_codec->currentText() == "copy")
        {
            script_video = QString(" ") + "-vcodec copy";
        }
        else if (combo_box_video_codec->currentText() == "x264")
        {
            script_video = QString(" ") + "-vcodec libx264" //
                           + script_video_x264_preset       //
                           + script_video_profile_level     //
                           + script_video_x264_params       //
                           + script_video_pix_fmt           //
                           + script_video_rate_control      //
                           + script_video_frame_size        //
                           + script_video_frame_rate;       //
        }
        else if (combo_box_video_codec->currentText() == "nvenc")
        {
            // TODO
            // script_video_profile_level
            // script_video_pix_fmt
            // script_video_frame_size
            // script_video_frame_rate
            script_video = QString(" ") + "-vcodec h264_nvenc" //
                           + script_video_nvenc_preset         //
                           + QString(" -profile:v high")       //
                           + script_video_rate_control;        //
        }
    }

    QString script_audio = QString("");
    if (!check_box_audio_enable->isChecked())
        script_audio = QString(" ") + "-an";
    else
    {
        if (combo_box_audio_codec->currentText() == "copy")
            script_audio = QString(" ") + "-acodec copy";
        else
            script_audio = QString(" ") + "-acodec" + QString(" ") + combo_box_audio_codec->currentText() //
                           + " " + "-ac" + " " + combo_box_audio_channels->currentText()                  //
                           + " " + "-ab" + " " + combo_box_audio_bitrate->currentText() + "k"             //
                           + " " + "-ar" + " " + combo_box_audio_frequency->currentText();
    }

    QString script_output_file = QString(" ") + "\"" + line_edit_output_filename->text() + "\"";

    QString full_script = QString("");
    if (combo_box_video_codec->currentText() == "x264" && check_box_video_2pass->isChecked())
    {
        full_script = QString("")                                                   //
                      + script_ffmpeg                                               //
                      + script_input                                                //
                      + script_filter                                               //
                      + script_video                                                //
                      + " " + "-pass" + " " + "1"                                   //
                      + " -acodec copy"                                             //
                      + " " + "-f" + " " + combo_box_video_container->currentText() //
                      + " " + "NUL" + " " + "-y"                                    //
                      + " " + "&&" + " "                                            //
                      + script_ffmpeg                                               //
                      + script_input                                                //
                      + script_filter                                               //
                      + script_video                                                //
                      + " " + "-pass" + " " + "2"                                   //
                      + script_audio                                                //
                      + script_output_file + " " + "-y";
    }
    else
    {
        full_script = QString("")     //
                      + script_ffmpeg //
                      + script_input  //
                      + script_filter //
                      + script_video  //
                      + script_audio  //
                      + script_output_file + " " + "-y";
    }

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
        // qDebug() << u.toString().mid(8);
        QString input_file_full_name = u.toString().mid(8);
        QString input_file_suffix = QFileInfo::QFileInfo(input_file_full_name).suffix();

        QStringList video_formats;
        video_formats << "flv"
                      << "mp4"
                      << "avi"
                      << "mov"
                      << "mkv";
        QStringList audio_formats;
        audio_formats << "mp3"
                      << "aac"
                      << "flac";

        if (audio_formats.contains(input_file_suffix)) // audio
        {
            line_edit_input_filename_audio->setText(input_file_full_name);
            if (line_edit_input_filename_video->text() == "")
            {
                ChangeOutputFileName(input_file_full_name);
            }
            else
            {
                ChangeOutputFileName(line_edit_input_filename_video->text());
            }
        }
        else // video / others
        {
            line_edit_input_filename_video->setText(input_file_full_name);
            ChangeOutputFileName(input_file_full_name);
        }
    }
    // qDebug() << urls.size();
}

void FFGUI::ExecuteResult(bool success)
{
    push_button_execute->setEnabled(true);
    this->end_time = QDateTime::currentDateTime();

    // TODO
    if (success)
        qDebug() << "Conversion success!";

    qDebug() << "";

    if (success)
    {
        qDebug() << tr("Encoding success!")
                 << " " << tr("Time span") << ": "
                 << QDateTime::fromMSecsSinceEpoch(this->end_time.toMSecsSinceEpoch() - this->begin_time.toMSecsSinceEpoch()).toUTC().toString("hh:mm:ss");
        MessageBeep(MB_OK);
    }
    else
    {
        qDebug() << tr("Encoding failure!")
                 << " " << tr("Time span") << ": "
                 << QDateTime::fromMSecsSinceEpoch(this->end_time.toMSecsSinceEpoch() - this->begin_time.toMSecsSinceEpoch()).toUTC().toString("hh:mm:ss");
        MessageBeep(MB_ICONWARNING);
    }

    qDebug() << ""
             << "";
}
