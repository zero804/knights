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

#ifndef KNIGHTS_TEXTPROTOCOL_H
#define KNIGHTS_TEXTPROTOCOL_H

#include <proto/protocol.h>
#include <QTextStream>
#include "chatwidget.h"
#include <QList>

namespace Knights {

class TextProtocol : public Knights::Protocol
{
    Q_OBJECT
public:
    TextProtocol(QObject* parent = 0);
    virtual ~TextProtocol();

protected:
    void setDevice(QIODevice* device);
    QIODevice* device() const;
    
    void setConsole(ChatWidget* widget);
    ChatWidget* console() const;
    
    void writeToConsole(const QString& text, ChatWidget::MessageType type);

    virtual void parseLine(const QString& line) = 0;
    virtual bool parseStub(const QString& line) = 0;

protected Q_SLOTS:
    void readFromDevice();
    void write(const QString& text);
    void write(const char* text);

    void writeCheckMoves(const QString& text);

private:
    QTextStream stream;
    QPointer < ChatWidget > m_console;
    QList < ChatWidget::Message > messages;
};

}

#endif // KNIGHTS_TEXTPROTOCOL_H
