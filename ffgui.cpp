
#include "ffgui.h"

FFGUI::FFGUI()
{
    SetConsoleTitle(TEXT("FFGUI 1.3 Console"));
    Sleep(17);
    console_hwnd = FindWindow(nullptr, TEXT("FFGUI 1.3 Console"));
    ShowWindow(console_hwnd, SW_HIDE);

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

    this->list_bitrate << "1750"
                       << "1950"
                       << "2950"
                       << "5950";

    // file

    group_box_file = new QGroupBox(this);
    group_box_file->setTitle(tr("File"));

    label_input = new QLabel(group_box_file);
    label_input->setText(tr("Input"));
    line_edit_input_filename = new QLineEdit(group_box_file);

    push_button_open = new QPushButton(group_box_file);
    push_button_open->setText(tr("Open"));

    label_output = new QLabel(group_box_file);
    label_output->setText(tr("Output"));
    line_edit_output_filename = new QLineEdit(group_box_file);
    push_button_execute = new QPushButton(group_box_file);
    push_button_execute->setText(tr("Execute"));

    grid_layout_file = new QGridLayout(group_box_file);
    grid_layout_file->addWidget(label_input, 0, 0, 1, 1);
    grid_layout_file->addWidget(line_edit_input_filename, 0, 1, 1, 1);
    grid_layout_file->addWidget(push_button_open, 0, 2, 1, 1);
    grid_layout_file->addWidget(label_output, 1, 0, 1, 1);
    grid_layout_file->addWidget(line_edit_output_filename, 1, 1, 1, 1);
    grid_layout_file->addWidget(push_button_execute, 1, 2, 1, 1);
    grid_layout_file->setRowStretch(0, 1);
    grid_layout_file->setRowStretch(1, 1);
    grid_layout_file->setColumnStretch(0, 1);
    grid_layout_file->setColumnStretch(1, 8);
    grid_layout_file->setColumnStretch(2, 1);
    grid_layout_file->setSpacing(10);

    // video

    group_box_video = new QGroupBox(this);
    group_box_video->setTitle(tr("Video"));

    check_box_video_enable = new QCheckBox(group_box_video);
    check_box_video_enable->setText(tr("Enable"));
    check_box_video_enable->setChecked(true);

    check_box_video_crf = new QCheckBox(group_box_video);
    check_box_video_crf->setText("crf");
    check_box_video_2pass = new QCheckBox(group_box_video);
    check_box_video_2pass->setText("2pass");
    check_box_video_2pass->setChecked(true);

    label_video_codec = new QLabel(group_box_video);
    label_video_codec->setText(tr("Codec"));
    combo_box_video_codec = new QComboBox(group_box_video);
    combo_box_video_codec->addItem("copy");
    combo_box_video_codec->addItem("libx264");
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
    label_video_preset->setText(tr("Preset"));
    combo_box_video_preset = new QComboBox(group_box_video);
    combo_box_video_preset->addItem("ultrafast");
    combo_box_video_preset->addItem("superfast");
    combo_box_video_preset->addItem("veryfast");
    combo_box_video_preset->addItem("faster");
    combo_box_video_preset->addItem("fast");
    combo_box_video_preset->addItem("medium");
    combo_box_video_preset->addItem("slow");
    combo_box_video_preset->addItem("slower");
    combo_box_video_preset->addItem("veryslow");
    combo_box_video_preset->addItem("placebo");
    combo_box_video_preset->setCurrentIndex(8);

    label_video_keyframe = new QLabel(group_box_video);
    label_video_keyframe->setText(tr("Keyframe Interval (s)"));
    line_edit_video_keyframe = new QLineEdit(group_box_video);
    line_edit_video_keyframe->setText("10");

    QIntValidator *validator_video_keyframe = new QIntValidator;
    validator_video_keyframe->setRange(1, 999);
    line_edit_video_keyframe->setValidator(validator_video_keyframe);

    label_video_frame_size = new QLabel(group_box_video);
    label_video_frame_size->setText(tr("Frame size"));
    line_edit_video_frame_size = new QLineEdit(group_box_video);
    line_edit_video_frame_size->setText("800x600");

    this->list_frame_size.removeDuplicates();
    QCompleter *completer_frame_size = new QCompleter(list_frame_size);
    line_edit_video_frame_size->setCompleter(completer_frame_size);

    QRegExp reg_frame_size("[1-9][0-9]{1,5}[x][1-9][0-9]{1,5}");
    line_edit_video_frame_size->setValidator(new QRegExpValidator(reg_frame_size, this));

    label_video_frame_rate = new QLabel(group_box_video);
    label_video_frame_rate->setText(tr("Frame rate (fps)"));
    combo_box_video_frame_rate = new QComboBox(group_box_video);
    combo_box_video_frame_rate->addItem("10");
    combo_box_video_frame_rate->addItem("20");
    combo_box_video_frame_rate->addItem("23.976");
    combo_box_video_frame_rate->addItem("24");
    combo_box_video_frame_rate->addItem("29.97");
    combo_box_video_frame_rate->addItem("30");
    combo_box_video_frame_rate->addItem("48");
    combo_box_video_frame_rate->addItem("59.94");
    combo_box_video_frame_rate->addItem("60");
    combo_box_video_frame_rate->addItem("100");
    combo_box_video_frame_rate->addItem("120");
    combo_box_video_frame_rate->addItem("144");
    combo_box_video_frame_rate->setCurrentIndex(8);

    label_video_factor = new QLabel(group_box_video);
    label_video_factor->setText(tr("Rate Factor (0-51)"));
    label_video_factor->setEnabled(false);
    spin_box_video_factor = new QDoubleSpinBox(group_box_video);
    spin_box_video_factor->setRange(0.0, 51.0);
    spin_box_video_factor->setSingleStep(0.1);
    spin_box_video_factor->setDecimals(1);
    spin_box_video_factor->setValue(23.5);
    spin_box_video_factor->setEnabled(false);

    label_video_bitrate = new QLabel(group_box_video);
    label_video_bitrate->setText(tr("Bitrate (kbps)"));
    line_edit_video_bitrate = new QLineEdit(group_box_video);
    line_edit_video_bitrate->setText("1950");

    QIntValidator *validator_video_bitrate = new QIntValidator;
    validator_video_bitrate->setRange(0, 99999999);
    line_edit_video_bitrate->setValidator(validator_video_bitrate);

    this->list_bitrate.removeDuplicates();
    QCompleter *completer_bitrate = new QCompleter(list_bitrate);
    line_edit_video_bitrate->setCompleter(completer_bitrate);

    grid_layout_video = new QGridLayout(group_box_video);
    grid_layout_video->addWidget(check_box_video_enable, 0, 0, 1, 1);
    grid_layout_video->addWidget(check_box_video_crf, 0, 2, 1, 1);
    grid_layout_video->addWidget(check_box_video_2pass, 0, 3, 1, 1);
    grid_layout_video->addWidget(label_video_codec, 1, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_codec, 1, 1, 1, 1);
    grid_layout_video->addWidget(label_video_container, 1, 2, 1, 1);
    grid_layout_video->addWidget(combo_box_video_container, 1, 3, 1, 1);
    grid_layout_video->addWidget(label_video_preset, 2, 0, 1, 1);
    grid_layout_video->addWidget(combo_box_video_preset, 2, 1, 1, 1);
    grid_layout_video->addWidget(label_video_keyframe, 2, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_keyframe, 2, 3, 1, 1);
    grid_layout_video->addWidget(label_video_frame_size, 3, 0, 1, 1);
    grid_layout_video->addWidget(line_edit_video_frame_size, 3, 1, 1, 1);
    grid_layout_video->addWidget(label_video_frame_rate, 3, 2, 1, 1);
    grid_layout_video->addWidget(combo_box_video_frame_rate, 3, 3, 1, 1);
    grid_layout_video->addWidget(label_video_factor, 4, 0, 1, 1);
    grid_layout_video->addWidget(spin_box_video_factor, 4, 1, 1, 1);
    grid_layout_video->addWidget(label_video_bitrate, 4, 2, 1, 1);
    grid_layout_video->addWidget(line_edit_video_bitrate, 4, 3, 1, 1);
    grid_layout_video->setRowStretch(0, 1);
    grid_layout_video->setRowStretch(1, 1);
    grid_layout_video->setRowStretch(2, 1);
    grid_layout_video->setRowStretch(3, 1);
    grid_layout_video->setRowStretch(4, 1);
    grid_layout_video->setColumnStretch(0, 1);
    grid_layout_video->setColumnStretch(1, 1);
    grid_layout_video->setColumnStretch(2, 1);
    grid_layout_video->setColumnStretch(3, 1);
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
    label_audio_bitrate->setText(tr("Bitrate (kbps)"));
    combo_box_audio_bitrate = new QComboBox(group_box_audio);
    combo_box_audio_bitrate->addItem("64");
    combo_box_audio_bitrate->addItem("96");
    combo_box_audio_bitrate->addItem("128");
    combo_box_audio_bitrate->addItem("160");
    combo_box_audio_bitrate->addItem("192");
    combo_box_audio_bitrate->addItem("256");
    combo_box_audio_bitrate->addItem("320");
    combo_box_audio_bitrate->setCurrentIndex(3);

    label_audio_frequency = new QLabel(group_box_audio);
    label_audio_frequency->setText(tr("Sampling Frequency (Hz)"));
    combo_box_audio_frequency = new QComboBox(group_box_audio);
    combo_box_audio_frequency->addItem("44100");
    combo_box_audio_frequency->addItem("48000");
    combo_box_audio_frequency->setCurrentIndex(1);

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
    grid_layout_audio->setRowStretch(0, 1);
    grid_layout_audio->setRowStretch(1, 1);
    grid_layout_audio->setRowStretch(2, 1);
    grid_layout_audio->setRowStretch(3, 1);
    grid_layout_audio->setRowStretch(4, 1);
    grid_layout_audio->setColumnStretch(0, 1);
    grid_layout_audio->setColumnStretch(1, 1);
    grid_layout_audio->setSpacing(10);

    // other

    group_box_other = new QGroupBox(this);
    group_box_other->setTitle(tr("Others"));

    check_box_cutting = new QCheckBox(group_box_other);
    check_box_cutting->setText(tr("Cutting"));
    check_box_cutting->setChecked(false);

    label_cutting_start = new QLabel(group_box_other);
    label_cutting_start->setAlignment(Qt::AlignCenter);
    label_cutting_start->setText(tr("Start"));
    label_cutting_start->setEnabled(false);
    line_edit_cutting_start = new QLineEdit(group_box_other);
    line_edit_cutting_start->setInputMask("00:00:00.000");
    line_edit_cutting_start->setText("00:00:00.000");
    line_edit_cutting_start->setEnabled(false);

    label_cutting_duration = new QLabel(group_box_other);
    label_cutting_duration->setAlignment(Qt::AlignCenter);
    label_cutting_duration->setText(tr("Duration"));
    label_cutting_duration->setEnabled(false);
    line_edit_cutting_duration = new QLineEdit(group_box_other);
    line_edit_cutting_duration->setInputMask("00:00:00.000");
    line_edit_cutting_duration->setText("00:00:00.000");
    line_edit_cutting_duration->setEnabled(false);

    grid_layout_other = new QGridLayout(group_box_other);
    grid_layout_other->addWidget(check_box_cutting, 0, 0, 1, 1);
    grid_layout_other->addWidget(label_cutting_start, 0, 1, 1, 1);
    grid_layout_other->addWidget(line_edit_cutting_start, 0, 2, 1, 1);
    grid_layout_other->addWidget(label_cutting_duration, 0, 3, 1, 1);
    grid_layout_other->addWidget(line_edit_cutting_duration, 0, 4, 1, 1);
    grid_layout_other->setRowStretch(0, 1);
    grid_layout_other->setColumnStretch(0, 2);
    grid_layout_other->setColumnStretch(1, 1);
    grid_layout_other->setColumnStretch(2, 2);
    grid_layout_other->setColumnStretch(3, 1);
    grid_layout_other->setColumnStretch(4, 2);
    grid_layout_other->setSpacing(10);

    // main

    main_layout = new QGridLayout(this);
    main_layout->addWidget(group_box_file, 0, 0, 1, 2);
    main_layout->addWidget(group_box_video, 1, 0, 1, 1);
    main_layout->addWidget(group_box_audio, 1, 1, 1, 1);
    main_layout->addWidget(group_box_other, 2, 0, 1, 2);
    main_layout->setRowStretch(0, 3);
    main_layout->setRowStretch(1, 6);
    main_layout->setRowStretch(2, 2);
    main_layout->setColumnStretch(0, 2);
    main_layout->setColumnStretch(1, 1);
    setLayout(main_layout);

    // signal and slots

    connect(check_box_video_enable, &QCheckBox::stateChanged, [=](int state) {
        EnableVideoWidgets(state == Qt::Checked);
        ChangeOutputFileExt();
    });

    connect(check_box_video_crf, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
            check_box_video_2pass->setChecked(false);
        else
            check_box_video_2pass->setChecked(true);
        SwitchCRF2PASS();
    });

    connect(check_box_video_2pass, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked)
            check_box_video_crf->setChecked(false);
        else
            check_box_video_crf->setChecked(true);
        SwitchCRF2PASS();
    });

    connect(check_box_audio_enable, &QCheckBox::stateChanged, [=](int state) {
        EnableAudioWidgets(state == Qt::Checked);
    });

    connect(combo_box_audio_codec, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &FFGUI::ChangeOutputFileExt);

    connect(check_box_cutting, &QCheckBox::stateChanged, [=](int state) {
        EnableCuttingWidgets(state == Qt::Checked);
    });

    connect(push_button_open, &QPushButton::clicked, this, &FFGUI::OpenFile);

    connect(combo_box_video_container, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &FFGUI::ChangeOutputFileExt);

    connect(push_button_execute, &QPushButton::clicked, [=]() {
        bool video_enabled = check_box_video_enable->isChecked();
        bool audio_enabled = check_box_audio_enable->isChecked();
        if (!video_enabled && !audio_enabled)
            return;

        QString full_script = GetScript();
        bool success = ExecuteScript(full_script);
        if (success)
        {
            MessageBeep(MB_OK);
        }
        else
        {
            QMessageBox msg_box;
            msg_box.setWindowTitle(tr("Error"));
            msg_box.setIcon(QMessageBox::Critical);
            msg_box.setText(tr("Encoding Error!"));
            msg_box.exec();
        }
    });
}

FFGUI::~FFGUI()
{
}

void FFGUI::EnableVideoWidgets(bool enabled)
{
    if (enabled)
    {
        check_box_video_crf->setEnabled(true);
        check_box_video_2pass->setEnabled(true);
        label_video_codec->setEnabled(true);
        combo_box_video_codec->setEnabled(true);
        // label_video_container->setEnabled(true);
        // combo_box_video_container->setEnabled(true);
        label_video_preset->setEnabled(true);
        combo_box_video_preset->setEnabled(true);
        label_video_keyframe->setEnabled(true);
        line_edit_video_keyframe->setEnabled(true);
        label_video_frame_size->setEnabled(true);
        line_edit_video_frame_size->setEnabled(true);
        label_video_frame_rate->setEnabled(true);
        combo_box_video_frame_rate->setEnabled(true);
        if (check_box_video_crf->isChecked())
        {
            label_video_factor->setEnabled(true);
            spin_box_video_factor->setEnabled(true);
        }
        if (check_box_video_2pass->isChecked())
        {
            label_video_bitrate->setEnabled(true);
            line_edit_video_bitrate->setEnabled(true);
        }
    }
    else
    {
        check_box_video_crf->setEnabled(false);
        check_box_video_2pass->setEnabled(false);
        label_video_codec->setEnabled(false);
        combo_box_video_codec->setEnabled(false);
        // label_video_container->setEnabled(false);
        // combo_box_video_container->setEnabled(false);
        label_video_preset->setEnabled(false);
        combo_box_video_preset->setEnabled(false);
        label_video_keyframe->setEnabled(false);
        line_edit_video_keyframe->setEnabled(false);
        label_video_frame_size->setEnabled(false);
        line_edit_video_frame_size->setEnabled(false);
        label_video_frame_rate->setEnabled(false);
        combo_box_video_frame_rate->setEnabled(false);
        label_video_factor->setEnabled(false);
        spin_box_video_factor->setEnabled(false);
        label_video_bitrate->setEnabled(false);
        line_edit_video_bitrate->setEnabled(false);
    }
}

void FFGUI::EnableAudioWidgets(bool enabled)
{
    if (enabled)
    {
        label_audio_codec->setEnabled(true);
        combo_box_audio_codec->setEnabled(true);
        label_audio_bitrate->setEnabled(true);
        combo_box_audio_bitrate->setEnabled(true);
        label_audio_frequency->setEnabled(true);
        combo_box_audio_frequency->setEnabled(true);
        label_audio_channels->setEnabled(true);
        combo_box_audio_channels->setEnabled(true);
    }
    else
    {
        label_audio_codec->setEnabled(false);
        combo_box_audio_codec->setEnabled(false);
        label_audio_bitrate->setEnabled(false);
        combo_box_audio_bitrate->setEnabled(false);
        label_audio_frequency->setEnabled(false);
        combo_box_audio_frequency->setEnabled(false);
        label_audio_channels->setEnabled(false);
        combo_box_audio_channels->setEnabled(false);
    }
}

void FFGUI::EnableCuttingWidgets(bool enabled)
{
    if (enabled)
    {
        label_cutting_start->setEnabled(true);
        line_edit_cutting_start->setEnabled(true);
        label_cutting_duration->setEnabled(true);
        line_edit_cutting_duration->setEnabled(true);
    }
    else
    {
        label_cutting_start->setEnabled(false);
        line_edit_cutting_start->setEnabled(false);
        label_cutting_duration->setEnabled(false);
        line_edit_cutting_duration->setEnabled(false);
    }
}

void FFGUI::SwitchCRF2PASS()
{
    if (check_box_video_crf->isChecked())
    {
        label_video_factor->setEnabled(true);
        spin_box_video_factor->setEnabled(true);
        label_video_bitrate->setEnabled(false);
        line_edit_video_bitrate->setEnabled(false);
    }
    else
    {
        label_video_factor->setEnabled(false);
        spin_box_video_factor->setEnabled(false);
        label_video_bitrate->setEnabled(true);
        line_edit_video_bitrate->setEnabled(true);
    }
}

void FFGUI::OpenFile()
{
    QString input_file_full_name = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ".",
        tr("Video files (*.flv *.mp4 *.avi *.mov *.mkv) ;; All files (*.*)"));
    if (!input_file_full_name.isNull())
    {
        line_edit_input_filename->setText(input_file_full_name);
        QString output_file_full_name = input_file_full_name.mid(0, input_file_full_name.lastIndexOf('.'))   //
                                        + "_" + QString::number(QDateTime::currentDateTime().toTime_t(), 16) //
                                        + "." + combo_box_video_container->currentText();
        line_edit_output_filename->setText(output_file_full_name);
    }
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

    QString script_cutting = check_box_cutting->isChecked()                                                                                             //
                                 ?                                                                                                                      //
                                 (QString(" ") + "-ss" + " " + line_edit_cutting_start->text() + " " + "-t" + " " + line_edit_cutting_duration->text()) //
                                 :                                                                                                                      //
                                 QString("");

    QString script_input_file = QString(" ") + "-i" + " " + "\"" + line_edit_input_filename->text() + "\"";

    QString script_video;
    if (!check_box_video_enable->isChecked())
        script_video = QString(" ") + "-vn";
    else
    {
        if (combo_box_video_codec->currentText() == "copy")
            script_video = QString(" ") + "-vcodec copy";
        else
            script_video = QString(" ") + "-vcodec" + QString(" ") + combo_box_video_codec->currentText()                                                                //
                           + " " + "-preset" + " " + combo_box_video_preset->currentText()                                                                               //
                           + " " + "-profile:v high" + " " + "-level:v 4.1"                                                                                              //
                           + " " + "-x264-params" + " "                                                                                                                  //
                           + "keyint=" + QString::number(int(combo_box_video_frame_rate->currentText().toDouble() * line_edit_video_keyframe->text().toDouble() * 0.95)) //
                           + ":" + "min-keyint=" + combo_box_video_frame_rate->currentText()                                                                             //
                           + " " + "-pix_fmt" + " " + "yuv420p"                                                                                                          //
                           + ((check_box_video_crf->isChecked()) ?                                                                                                       //
                                  (QString(" ") + "-crf" + " " + spin_box_video_factor->text())                                                                          //
                                                                 :                                                                                                       //
                                  (QString(" ") + "-b:v" + " " + line_edit_video_bitrate->text() + "k"))                                                                 //
                           + " " + "-s" + " " + line_edit_video_frame_size->text()                                                                                       //
                           + " " + "-r" + " " + combo_box_video_frame_rate->currentText();
    }

    QString script_audio;
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

    QString full_script;
    if (check_box_video_enable->isChecked() && check_box_video_2pass->isChecked())
    {
        full_script = QString("")                                                                              //
                      + script_ffmpeg                                                                          //
                      + script_cutting                                                                         //
                      + script_input_file                                                                      //
                      + script_video                                                                           //
                      + " " + "-pass" + " " + "1"                                                              //
                      + script_audio                                                                           //
                      + " " + "-f" + " " + combo_box_video_container->currentText() + " " + "NUL" + " " + "-y" //
                      + " " + "&&" + " "                                                                       //
                      + script_ffmpeg                                                                          //
                      + script_cutting                                                                         //
                      + script_input_file                                                                      //
                      + script_video                                                                           //
                      + " " + "-pass" + " " + "2"                                                              //
                      + script_audio                                                                           //
                      + script_output_file + " " + "-y";
    }
    else
    {
        full_script = QString("")         //
                      + script_ffmpeg     //
                      + script_cutting    //
                      + script_input_file //
                      + script_video      //
                      + script_audio      //
                      + script_output_file + " " + "-y";
    }

    return full_script;
}

bool FFGUI::ExecuteScript(QString full_script)
{
    QString temp_dir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) //
                       + "/" + "ffgui_temp_"                                          //
                       + QString::number(QDateTime::currentDateTime().toTime_t(), 16) //
                       + "_a9efe77ad90194dc";

    QDir temp;
    bool exist = temp.exists(temp_dir);
    if (exist)
        return false;
    else
    {
        bool ok = temp.mkdir(temp_dir);
        if (!ok)
            return false;
    }

    QString app_dir = QCoreApplication::applicationDirPath();
    QDir::setCurrent(temp_dir);

    QString script_file = temp_dir + "/" + "ffmpeg_script.bat";
    QString temp_file_0 = temp_dir + "/" + "ffmpeg2pass-0.log";
    QString temp_file_1 = temp_dir + "/" + "ffmpeg2pass-0.log.mbtree";
    QFile file_s(script_file);
    QFile file_0(temp_file_0);
    QFile file_1(temp_file_1);

    if (!file_s.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return false;
    QTextStream out(&file_s);
    out << full_script << endl;
    out.flush();
    file_s.close();

    this->hide();
    ShowWindow(console_hwnd, SW_SHOWNORMAL);
    SetForegroundWindow(console_hwnd);

    int ret = system(script_file.toStdString().c_str());

    ShowWindow(console_hwnd, SW_HIDE);
    this->show();

    QDir::setCurrent(app_dir);

    file_s.remove();
    file_0.remove();
    file_1.remove();
    temp.rmdir(temp_dir);

    return ret == 0 ? true : false;
}
