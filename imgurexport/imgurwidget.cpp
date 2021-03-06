/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2012-02-12
 * Description : a kipi plugin to export images to the Imgur web service
 *
 * Copyright (C) 2010-2012 by Marius Orcsik <marius at habarnam dot ro>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "imgurwidget.moc"

// Qt includes

#include <QBoxLayout>

// KDE includes

#include <klocale.h>

namespace KIPIImgurExportPlugin
{

class ImgurWidget::ImgurWidgetPriv
{
public:

    ImgurWidgetPriv()
    {
        headerLbl   = 0;
        textLbl     = 0;
        imagesList  = 0;
        progressBar = 0;
    }

    QLabel*           headerLbl;
    QLabel*           textLbl;
    ImgurImagesList*  imagesList;
    KPProgressWidget* progressBar;
};

ImgurWidget::ImgurWidget(QWidget* const parent)
    : QWidget(parent), d(new ImgurWidgetPriv)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    d->imagesList           = new ImgurImagesList(this);
    d->imagesList->loadImagesFromCurrentSelection();

    QWidget* settingsBox           = new QWidget(this);
    QVBoxLayout* settingsBoxLayout = new QVBoxLayout(settingsBox);

    d->headerLbl = new QLabel(settingsBox);
    d->headerLbl->setWhatsThis(i18n("This is a clickable link to open the Imgur home page in a web browser"));
    d->headerLbl->setText(QString("<h2><a href='http://imgur.com'>imgur.com</a></h2>"));
    d->headerLbl->setOpenExternalLinks(true);
    d->headerLbl->setFocusPolicy(Qt::NoFocus);

    d->textLbl = new QLabel(settingsBox);
/*
    d->textLbl->setText(i18n("You can retreive the\nimage URLs from the Xmp tags:\n"
                             "\"Imgur URL\" and \"Imgur Delete URL\". \n"));
*/
    d->textLbl->setFocusPolicy(Qt::NoFocus);
    d->textLbl->setWordWrap(true);

    d->progressBar = new KPProgressWidget(settingsBox);
    d->progressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    d->progressBar->setVisible(false);

    // --------------------------------------------

    settingsBoxLayout->addWidget(d->headerLbl);
    settingsBoxLayout->addWidget(d->textLbl);
    settingsBoxLayout->addWidget(d->progressBar);
    settingsBoxLayout->addStretch(10);
    settingsBoxLayout->setAlignment(d->textLbl, Qt::AlignTop);
    settingsBoxLayout->setAlignment(d->progressBar, Qt::AlignBottom);
    settingsBoxLayout->setSpacing(KDialog::spacingHint());
    settingsBoxLayout->setMargin(KDialog::spacingHint());

    // --------------------------------------------

    mainLayout->addWidget(d->imagesList);
    mainLayout->addWidget(settingsBox);
    mainLayout->setSpacing(KDialog::spacingHint());
    mainLayout->setMargin(0);

    connect(d->imagesList, SIGNAL(signalAddItems(KUrl::List)),
            this, SLOT(slotAddItems(KUrl::List)));

    connect(d->imagesList, SIGNAL(signalRemovedItems(KUrl::List)),
            this, SLOT(slotRemoveItems(KUrl::List)));

    connect(d->imagesList, SIGNAL(signalImageListChanged()),
            this, SLOT(slotImageListChanged()));

    connect(this, SIGNAL(signalImageUploadSuccess(KUrl, ImgurSuccess)),
            d->imagesList, SLOT(slotUploadSuccess(KUrl, ImgurSuccess)));

    connect(this, SIGNAL(signalImageUploadError(KUrl, ImgurError)),
            d->imagesList, SLOT(slotUploadError(KUrl, ImgurError)));
}

ImgurWidget::~ImgurWidget()
{
    delete d;
}

void ImgurWidget::slotAddItems(const KUrl::List& list)
{
    emit signalAddItems(list);
}

void ImgurWidget::slotRemoveItems(const KUrl::List& list)
{
    emit signalRemoveItems(list);
}

void ImgurWidget::slotImageListChanged()
{
    emit signalImageListChanged();
}

void ImgurWidget::slotImageUploadSuccess(const KUrl& imgPath, ImgurSuccess success)
{
    emit signalImageUploadSuccess(imgPath, success);
}

void ImgurWidget::slotImageUploadError(const KUrl& imgPath, ImgurError error)
{
    emit signalImageUploadError(imgPath, error);
}

ImgurImagesList* ImgurWidget::imagesList() const
{
    return d->imagesList;
}

KPProgressWidget* ImgurWidget::progressBar() const
{
    return d->progressBar;
}

} // namespace KIPIImgurExportPlugin
