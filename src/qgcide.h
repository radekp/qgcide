#ifndef QGCIDE_H
#define QGCIDE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextBrowser>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QDir>
#include <QMessageBox>
#include <QBuffer>
#include <QXmlSimpleReader>

class QDictWidget : public QWidget
{
    Q_OBJECT
public:
    QDictWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
    QGridLayout *layout;
    QLineEdit *edit;
    QTextBrowser *browser;
    QFile dictFile;
    void showErr(QString);
    bool ensureDictFile();
    QString searchExpr(const QString &);

private slots:
    void textChanged(const QString &);
};

class QDictMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QDictMainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
    QDictWidget *dw;
};

class GcideXmlHandler : public QXmlDefaultHandler
{
public:
    GcideXmlHandler();

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

    bool skip;
    QString html;
};

#endif
