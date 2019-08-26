/********************************************************************************
** Form generated from reading UI file 'ZegoThumbnailView.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOTHUMBNAILVIEW_H
#define UI_ZEGOTHUMBNAILVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ZegoThumbnailView
{
public:

    void setupUi(QDialog *ZegoThumbnailView)
    {
        if (ZegoThumbnailView->objectName().isEmpty())
            ZegoThumbnailView->setObjectName(QStringLiteral("ZegoThumbnailView"));
        ZegoThumbnailView->resize(400, 300);

        retranslateUi(ZegoThumbnailView);

        QMetaObject::connectSlotsByName(ZegoThumbnailView);
    } // setupUi

    void retranslateUi(QDialog *ZegoThumbnailView)
    {
        ZegoThumbnailView->setWindowTitle(QApplication::translate("ZegoThumbnailView", "ZegoThumbnailView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoThumbnailView: public Ui_ZegoThumbnailView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOTHUMBNAILVIEW_H
