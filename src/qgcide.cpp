#include "qgcide.h"

QDictMainWindow::QDictMainWindow(QWidget* parent, Qt::WindowFlags f) : QMainWindow(parent, f)
{
    setWindowTitle(tr("English dictionary"));
    QMenu *menu = menuBar()->addMenu("&File");

    dw = new QDictWidget(this);
    setCentralWidget(dw);
}

QDictWidget::QDictWidget(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    layout = new QGridLayout(this);

    textEdit = new QTextEdit(this);
    connect(textEdit, SIGNAL(textChanged(const QString&)),
                    this, SLOT(textChanged(const QString&)));

    textBrowser = new QTextBrowser(this);

    layout->addWidget(textEdit, 0, 0);
    layout->addWidget(textBrowser, 1, 0);

    setLayout(layout);
}

bool QDictWidget::textChanged(const QString& text)
{

}
