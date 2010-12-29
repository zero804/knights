/*
    This file is part of Knights, a chess board for KDE SC 4.
    Copyright 2009-2010  Miha Čančula <miha.cancula@gmail.com>

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

#ifndef KNIGHTS_FICSPROTOCOL_H
#define KNIGHTS_FICSPROTOCOL_H

#include "proto/protocol.h"

#include <QtCore/QTextStream>

class QTcpSocket;

namespace Knights
{
    class FicsDialog;
    class FicsConsole;

    typedef QPair<QString, int> FicsPlayer;

    struct FicsGameOffer
    {
        FicsPlayer player;
        int baseTime;
        int timeIncrement;
        bool rated;
        QString variant;
        Color color;
        bool manual;
        bool formula;
        int gameId;
        QPair< int, int > ratingRange;
        bool automatic;
    };

    enum Stage
    {
        ConnectStage,
        SeekStage,
        PlayStage
    };

    class FicsProtocol : public Protocol
    {
            Q_OBJECT
        public:
            FicsProtocol ( QObject* parent = 0 );
            virtual ~FicsProtocol();

            virtual Features supportedFeatures();

            virtual void startGame();
            virtual void move ( const Move& m );
            virtual QWidgetList toolWidgets();

        private:
            static const int Timeout;

            static const QString ratingPattern;
            static const QString timePattern;
            static const QString variantPattern;
            static const QString argsPattern;
            static const QString pieces;
            static const QString coordinate;
            static const QString remainingTime;
            static const QString movePattern;
            static const QString currentPlayerPattern;

            static const QRegExp moveRegExp;
            static const QRegExp moveStringExp;
            static const QRegExp seekRegExp;
            static const QRegExp soughtRegExp;
            static const QRegExp challengeRegExp;
            static const QRegExp gameStartedExp;
            static const QRegExp gameInfoExp;

            QTcpSocket* m_socket;
            QTextStream m_stream;
            Stage m_stage;
            QString password;
            bool sendPassword;
            FicsDialog* m_widget;
            bool forcePrompt;
            bool m_seeking;
            FicsConsole* m_console;
            
        public Q_SLOTS:
            virtual void init ( const QVariantMap& options );
            virtual void adjourn();
            virtual void resign();

            void socketError();
            void dialogRejected();
            void acceptSeek ( int id );
            void acceptChallenge();
            void declineChallenge();
            void login(const QString& username, const QString& password);

           

        private Q_SLOTS:
            void readFromSocket();
            void writeToSocket(const QString& text);
            void flushSocket();
            void openGameDialog();
            void checkSought();
            void setSeeking ( bool seek );
            void setupOptions();
    Color parseColor( QString str);

        Q_SIGNALS:
            void sessionStarted();
            void clearSeeks();
            void gameOfferRemoved ( int id );
            void gameOfferReceived ( const FicsGameOffer& offer );
            void challengeReceived ( const FicsPlayer& challenger );
    };
}

#endif // KNIGHTS_FICSPROTOCOL_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on;  replace-tabs on;  replace-tabs on;
