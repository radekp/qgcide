#ifndef QGCIDE_H
#define QGCIDE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenuBar>

class QDictWidget : public QWidget
{
    Q_OBJECT
public:
    QDictWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
    QGridLayout *layout;
    QTextEdit *textEdit;
    QTextBrowser *textBrowser;

private slots:
    bool textChanged(const QString& text);
};

class QDictMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QDictMainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
    QDictWidget *dw;
};

#endif
