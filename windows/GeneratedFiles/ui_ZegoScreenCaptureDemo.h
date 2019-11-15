/********************************************************************************
** Form generated from reading UI file 'ZegoScreenCaptureDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOSCREENCAPTUREDEMO_H
#define UI_ZEGOSCREENCAPTUREDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZegoScreenCaptureDemo
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *target_group;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radio_screen;
    QComboBox *combo_screen;
    QToolButton *btn_refresh_screen;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radio_window;
    QComboBox *combo_window;
    QToolButton *btn_refresh_window;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radio_rect;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *btn_random_rect;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_y;
    QSlider *slider_y;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_w;
    QSlider *slider_w;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_x;
    QSlider *slider_x;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_h;
    QSlider *slider_h;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *settings_group;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QComboBox *combo_resolution;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_10;
    QSlider *slider_bitrate;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_bitrate;
    QLabel *label;
    QHBoxLayout *horizontalLayout_11;
    QSlider *slider_framerate;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_framerate;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *check_cursor;
    QCheckBox *check_clickanimation;
    QGridLayout *gridLayout_2;
    QToolButton *btn_add_excluded_window;
    QToolButton *btn_remove_excluded_window;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_thumbnail;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btn_capture;
    QListWidget *list_log;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *edit_rtmpurl;
    QLineEdit *edit_hlsurl;
    QToolButton *btn_publish;

    void setupUi(QWidget *ZegoScreenCaptureDemo)
    {
        if (ZegoScreenCaptureDemo->objectName().isEmpty())
            ZegoScreenCaptureDemo->setObjectName(QStringLiteral("ZegoScreenCaptureDemo"));
        ZegoScreenCaptureDemo->resize(738, 502);
        ZegoScreenCaptureDemo->setMinimumSize(QSize(640, 480));
        ZegoScreenCaptureDemo->setMaximumSize(QSize(738, 502));
        verticalLayout_5 = new QVBoxLayout(ZegoScreenCaptureDemo);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(15, 15, 15, 15);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(15);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        target_group = new QGroupBox(ZegoScreenCaptureDemo);
        target_group->setObjectName(QStringLiteral("target_group"));
        target_group->setMinimumSize(QSize(0, 0));
        target_group->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(target_group);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radio_screen = new QRadioButton(target_group);
        radio_screen->setObjectName(QStringLiteral("radio_screen"));

        horizontalLayout_2->addWidget(radio_screen);

        combo_screen = new QComboBox(target_group);
        combo_screen->setObjectName(QStringLiteral("combo_screen"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(combo_screen->sizePolicy().hasHeightForWidth());
        combo_screen->setSizePolicy(sizePolicy);
        combo_screen->setMinimumSize(QSize(0, 25));
        combo_screen->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(combo_screen);

        btn_refresh_screen = new QToolButton(target_group);
        btn_refresh_screen->setObjectName(QStringLiteral("btn_refresh_screen"));
        btn_refresh_screen->setMinimumSize(QSize(0, 25));
        btn_refresh_screen->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(btn_refresh_screen);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radio_window = new QRadioButton(target_group);
        radio_window->setObjectName(QStringLiteral("radio_window"));

        horizontalLayout_3->addWidget(radio_window);

        combo_window = new QComboBox(target_group);
        combo_window->setObjectName(QStringLiteral("combo_window"));
        sizePolicy.setHeightForWidth(combo_window->sizePolicy().hasHeightForWidth());
        combo_window->setSizePolicy(sizePolicy);
        combo_window->setMinimumSize(QSize(0, 25));
        combo_window->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(combo_window);

        btn_refresh_window = new QToolButton(target_group);
        btn_refresh_window->setObjectName(QStringLiteral("btn_refresh_window"));
        btn_refresh_window->setMinimumSize(QSize(0, 25));
        btn_refresh_window->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(btn_refresh_window);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radio_rect = new QRadioButton(target_group);
        radio_rect->setObjectName(QStringLiteral("radio_rect"));

        horizontalLayout_8->addWidget(radio_rect);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        btn_random_rect = new QToolButton(target_group);
        btn_random_rect->setObjectName(QStringLiteral("btn_random_rect"));
        btn_random_rect->setMinimumSize(QSize(0, 25));
        btn_random_rect->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_8->addWidget(btn_random_rect);


        verticalLayout->addLayout(horizontalLayout_8);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_y = new QLabel(target_group);
        label_y->setObjectName(QStringLiteral("label_y"));
        label_y->setMinimumSize(QSize(60, 0));
        label_y->setMaximumSize(QSize(60, 16777215));
        QFont font;
        font.setPointSize(12);
        label_y->setFont(font);

        horizontalLayout_7->addWidget(label_y);

        slider_y = new QSlider(target_group);
        slider_y->setObjectName(QStringLiteral("slider_y"));
        slider_y->setMinimumSize(QSize(0, 20));
        slider_y->setMaximumSize(QSize(16777215, 20));
        slider_y->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(slider_y);


        gridLayout->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_w = new QLabel(target_group);
        label_w->setObjectName(QStringLiteral("label_w"));
        label_w->setMinimumSize(QSize(60, 0));
        label_w->setMaximumSize(QSize(60, 16777215));
        label_w->setFont(font);

        horizontalLayout_5->addWidget(label_w);

        slider_w = new QSlider(target_group);
        slider_w->setObjectName(QStringLiteral("slider_w"));
        slider_w->setMinimumSize(QSize(0, 20));
        slider_w->setMaximumSize(QSize(16777215, 20));
        slider_w->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider_w);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_x = new QLabel(target_group);
        label_x->setObjectName(QStringLiteral("label_x"));
        label_x->setMinimumSize(QSize(60, 0));
        label_x->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(label_x);

        slider_x = new QSlider(target_group);
        slider_x->setObjectName(QStringLiteral("slider_x"));
        slider_x->setMinimumSize(QSize(0, 20));
        slider_x->setMaximumSize(QSize(16777215, 20));
        slider_x->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider_x);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_h = new QLabel(target_group);
        label_h->setObjectName(QStringLiteral("label_h"));
        label_h->setMinimumSize(QSize(60, 0));
        label_h->setMaximumSize(QSize(60, 16777215));
        label_h->setFont(font);

        horizontalLayout_6->addWidget(label_h);

        slider_h = new QSlider(target_group);
        slider_h->setObjectName(QStringLiteral("slider_h"));
        slider_h->setMinimumSize(QSize(0, 20));
        slider_h->setMaximumSize(QSize(16777215, 20));
        slider_h->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(slider_h);


        gridLayout->addLayout(horizontalLayout_6, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout_12->addWidget(target_group);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        settings_group = new QGroupBox(ZegoScreenCaptureDemo);
        settings_group->setObjectName(QStringLiteral("settings_group"));
        verticalLayout_2 = new QVBoxLayout(settings_group);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, 15, 15, 15);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(15);
        formLayout->setVerticalSpacing(15);
        label_3 = new QLabel(settings_group);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        combo_resolution = new QComboBox(settings_group);
        combo_resolution->setObjectName(QStringLiteral("combo_resolution"));
        combo_resolution->setMinimumSize(QSize(0, 25));
        combo_resolution->setMaximumSize(QSize(16777215, 25));

        formLayout->setWidget(0, QFormLayout::FieldRole, combo_resolution);

        label_2 = new QLabel(settings_group);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        slider_bitrate = new QSlider(settings_group);
        slider_bitrate->setObjectName(QStringLiteral("slider_bitrate"));
        slider_bitrate->setMinimumSize(QSize(0, 20));
        slider_bitrate->setMaximumSize(QSize(16777215, 20));
        slider_bitrate->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(slider_bitrate);

        horizontalSpacer_4 = new QSpacerItem(4, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);

        label_bitrate = new QLabel(settings_group);
        label_bitrate->setObjectName(QStringLiteral("label_bitrate"));
        label_bitrate->setMinimumSize(QSize(30, 0));
        label_bitrate->setMaximumSize(QSize(30, 16777215));
        QFont font1;
        font1.setPointSize(8);
        label_bitrate->setFont(font1);
        label_bitrate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_bitrate);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_10);

        label = new QLabel(settings_group);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        slider_framerate = new QSlider(settings_group);
        slider_framerate->setObjectName(QStringLiteral("slider_framerate"));
        slider_framerate->setMinimumSize(QSize(0, 20));
        slider_framerate->setMaximumSize(QSize(16777215, 20));
        slider_framerate->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(slider_framerate);

        horizontalSpacer_5 = new QSpacerItem(4, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        label_framerate = new QLabel(settings_group);
        label_framerate->setObjectName(QStringLiteral("label_framerate"));
        label_framerate->setMinimumSize(QSize(30, 0));
        label_framerate->setMaximumSize(QSize(30, 16777215));
        label_framerate->setFont(font);
        label_framerate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_framerate);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_11);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        check_cursor = new QCheckBox(settings_group);
        check_cursor->setObjectName(QStringLiteral("check_cursor"));

        horizontalLayout_9->addWidget(check_cursor);

        check_clickanimation = new QCheckBox(settings_group);
        check_clickanimation->setObjectName(QStringLiteral("check_clickanimation"));

        horizontalLayout_9->addWidget(check_clickanimation);


        verticalLayout_2->addLayout(horizontalLayout_9);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        btn_add_excluded_window = new QToolButton(settings_group);
        btn_add_excluded_window->setObjectName(QStringLiteral("btn_add_excluded_window"));
        btn_add_excluded_window->setMinimumSize(QSize(120, 30));
        btn_add_excluded_window->setMaximumSize(QSize(120, 30));

        gridLayout_2->addWidget(btn_add_excluded_window, 0, 0, 1, 1);

        btn_remove_excluded_window = new QToolButton(settings_group);
        btn_remove_excluded_window->setObjectName(QStringLiteral("btn_remove_excluded_window"));
        btn_remove_excluded_window->setMinimumSize(QSize(120, 30));
        btn_remove_excluded_window->setMaximumSize(QSize(120, 30));

        gridLayout_2->addWidget(btn_remove_excluded_window, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_3->addWidget(settings_group);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btn_thumbnail = new QToolButton(ZegoScreenCaptureDemo);
        btn_thumbnail->setObjectName(QStringLiteral("btn_thumbnail"));
        btn_thumbnail->setMinimumSize(QSize(120, 30));
        btn_thumbnail->setMaximumSize(QSize(120, 25));

        horizontalLayout->addWidget(btn_thumbnail);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_capture = new QToolButton(ZegoScreenCaptureDemo);
        btn_capture->setObjectName(QStringLiteral("btn_capture"));
        btn_capture->setMinimumSize(QSize(120, 30));
        btn_capture->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(btn_capture);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_12->addLayout(verticalLayout_3);

        horizontalLayout_12->setStretch(0, 6);
        horizontalLayout_12->setStretch(1, 4);

        verticalLayout_5->addLayout(horizontalLayout_12);

        list_log = new QListWidget(ZegoScreenCaptureDemo);
        list_log->setObjectName(QStringLiteral("list_log"));
        list_log->setAutoScroll(true);

        verticalLayout_5->addWidget(list_log);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(25);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        edit_rtmpurl = new QLineEdit(ZegoScreenCaptureDemo);
        edit_rtmpurl->setObjectName(QStringLiteral("edit_rtmpurl"));
        edit_rtmpurl->setMinimumSize(QSize(0, 25));
        edit_rtmpurl->setMaximumSize(QSize(16777215, 25));
        edit_rtmpurl->setReadOnly(true);

        verticalLayout_4->addWidget(edit_rtmpurl);

        edit_hlsurl = new QLineEdit(ZegoScreenCaptureDemo);
        edit_hlsurl->setObjectName(QStringLiteral("edit_hlsurl"));
        edit_hlsurl->setMinimumSize(QSize(0, 25));
        edit_hlsurl->setMaximumSize(QSize(16777215, 25));
        edit_hlsurl->setReadOnly(true);

        verticalLayout_4->addWidget(edit_hlsurl);


        horizontalLayout_13->addLayout(verticalLayout_4);

        btn_publish = new QToolButton(ZegoScreenCaptureDemo);
        btn_publish->setObjectName(QStringLiteral("btn_publish"));
        btn_publish->setMinimumSize(QSize(120, 30));
        btn_publish->setMaximumSize(QSize(120, 30));

        horizontalLayout_13->addWidget(btn_publish);


        verticalLayout_5->addLayout(horizontalLayout_13);


        retranslateUi(ZegoScreenCaptureDemo);

        QMetaObject::connectSlotsByName(ZegoScreenCaptureDemo);
    } // setupUi

    void retranslateUi(QWidget *ZegoScreenCaptureDemo)
    {
        ZegoScreenCaptureDemo->setWindowTitle(QApplication::translate("ZegoScreenCaptureDemo", "ZegoScreenCaptureDemo", Q_NULLPTR));
        target_group->setTitle(QApplication::translate("ZegoScreenCaptureDemo", "\345\210\206\344\272\253\347\233\256\346\240\207", Q_NULLPTR));
        radio_screen->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\261\217\345\271\225", Q_NULLPTR));
        btn_refresh_screen->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\210\267\346\226\260", Q_NULLPTR));
        radio_window->setText(QApplication::translate("ZegoScreenCaptureDemo", "\347\252\227\345\217\243", Q_NULLPTR));
        btn_refresh_window->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\210\267\346\226\260", Q_NULLPTR));
        radio_rect->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\214\272\345\237\237", Q_NULLPTR));
        btn_random_rect->setText(QApplication::translate("ZegoScreenCaptureDemo", "\351\232\217\346\234\272", Q_NULLPTR));
        label_y->setText(QApplication::translate("ZegoScreenCaptureDemo", "y", Q_NULLPTR));
        label_w->setText(QApplication::translate("ZegoScreenCaptureDemo", "w", Q_NULLPTR));
        label_x->setText(QApplication::translate("ZegoScreenCaptureDemo", "x", Q_NULLPTR));
        label_h->setText(QApplication::translate("ZegoScreenCaptureDemo", "h", Q_NULLPTR));
        settings_group->setTitle(QApplication::translate("ZegoScreenCaptureDemo", "\346\216\250\346\265\201 | \346\235\202\351\241\271\350\256\276\347\275\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        label_2->setText(QApplication::translate("ZegoScreenCaptureDemo", "\347\240\201\347\216\207", Q_NULLPTR));
        label_bitrate->setText(QString());
        label->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\270\247\347\216\207", Q_NULLPTR));
        label_framerate->setText(QString());
        check_cursor->setText(QApplication::translate("ZegoScreenCaptureDemo", "\346\230\276\347\244\272\345\205\211\346\240\207", Q_NULLPTR));
        check_clickanimation->setText(QApplication::translate("ZegoScreenCaptureDemo", "\347\202\271\345\207\273\345\212\250\347\224\273", Q_NULLPTR));
        btn_add_excluded_window->setText(QApplication::translate("ZegoScreenCaptureDemo", "\346\267\273\345\212\240\350\277\207\346\273\244\347\252\227\345\217\243", Q_NULLPTR));
        btn_remove_excluded_window->setText(QApplication::translate("ZegoScreenCaptureDemo", "\347\247\273\351\231\244\350\277\207\346\273\244\347\252\227\345\217\243", Q_NULLPTR));
        btn_thumbnail->setText(QApplication::translate("ZegoScreenCaptureDemo", "\347\252\227\345\217\243\351\242\204\350\247\210", Q_NULLPTR));
        btn_capture->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\274\200\345\247\213\346\215\225\346\215\211", Q_NULLPTR));
        edit_rtmpurl->setPlaceholderText(QApplication::translate("ZegoScreenCaptureDemo", "rtmp url", Q_NULLPTR));
        edit_hlsurl->setPlaceholderText(QApplication::translate("ZegoScreenCaptureDemo", "hls url", Q_NULLPTR));
        btn_publish->setText(QApplication::translate("ZegoScreenCaptureDemo", "\345\274\200\345\247\213\346\216\250\346\265\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoScreenCaptureDemo: public Ui_ZegoScreenCaptureDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOSCREENCAPTUREDEMO_H
