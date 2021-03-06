/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef CMAKEVALIDATOR_H
#define CMAKEVALIDATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <texteditor/codeassist/keywordscompletionassist.h>

QT_FORWARD_DECLARE_CLASS(QProcess)

namespace CMakeProjectManager {
namespace Internal {

class CMakeTool : public QObject
{
    Q_OBJECT
public:
    CMakeTool();
    ~CMakeTool();

    enum State { Invalid, RunningBasic, RunningFunctionList, RunningFunctionDetails,
                 RunningPropertyList, RunningVariableList, RunningDone };
    void cancel();
    bool isValid() const;

    void setCMakeExecutable(const QString &executable);
    QString cmakeExecutable() const;
    bool hasCodeBlocksMsvcGenerator() const;
    bool hasCodeBlocksNinjaGenerator() const;
    TextEditor::Keywords keywords();
private slots:
    void finished(int exitCode);

private:
    void finishStep();
    void startNextStep();
    bool startProcess(const QStringList &args);
    void parseFunctionOutput(const QByteArray &output);
    void parseFunctionDetailsOutput(const QByteArray &output);
    void parseVariableOutput(const QByteArray &output);
    void parseDone();
    QString formatFunctionDetails(const QString &command, const QString &args);

    State m_state;
    QProcess *m_process;
    bool m_hasCodeBlocksMsvcGenerator;
    bool m_hasCodeBlocksNinjaGenerator;
    QString m_executable;

    QMap<QString, QStringList> m_functionArgs;
    QStringList m_variables;
    QStringList m_functions;
};

} // namespace Internal
} // namespace CMakeProjectManager

#endif // CMAKEVALIDATOR_H
