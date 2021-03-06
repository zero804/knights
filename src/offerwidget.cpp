/*
    This file is part of Knights, a chess board for KDE SC 4.
    Copyright 2009,2010,2011  Miha Čančula <miha@noughmad.eu>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "offerwidget.h"
#include "gamemanager.h"
#include "ui_popup.h"

#include <QAction>

using namespace Knights;

OfferWidget::OfferWidget(const Knights::Offer& offer, QWidget* parent, Qt::WindowFlags f): KMessageWidget(offer.text, parent) {
	Q_UNUSED(f)
	offerId = offer.id;
	if ( offer.action != ActionNone ) {
		QAction* action;
		action = new QAction( QIcon::fromTheme(QStringLiteral("dialog-ok")), i18n("Accept"), this );
		connect ( action, &QAction::triggered, this, &OfferWidget::acceptClicked );
		addAction(action);
		action = new QAction( QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Decline"), this );
		connect ( action, &QAction::triggered, this, &OfferWidget::declineClicked );
		addAction ( action );
	}
	setCloseButtonVisible(true);
}

OfferWidget::~OfferWidget() {
	delete ui;
}

int OfferWidget::id() const {
	return offerId;
}

void OfferWidget::acceptClicked() {
	Q_EMIT close(offerId, AcceptOffer);
	deleteLater();
}

void OfferWidget::declineClicked() {
	Q_EMIT close(offerId, DeclineOffer);
	deleteLater();
}

void OfferWidget::closeClicked() {
	Q_EMIT close(offerId, IgnoreOffer);
	deleteLater();
}
