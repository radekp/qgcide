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

    edit = new QLineEdit(this);
    connect(edit, SIGNAL(textChanged(const QString&)),
            this, SLOT(textChanged(const QString&)));

    browser = new QTextBrowser(this);

    layout->addWidget(edit, 0, 0);
    layout->addWidget(browser, 1, 0);

    setLayout(layout);
}

void QDictWidget::showErr(QString err)
{
    QMessageBox::critical(this, tr("English dictionary"), err);
}

bool QDictWidget::ensureDictFile()
{
    if(dictFile.exists())
    {
        return true;
    }
    QDir baseDir("/media/card");
    if(!baseDir.exists())
    {
        baseDir = QDir::home();
    }
    QDir dictDir(baseDir.path() + "/.qgcide");
    if(!dictDir.exists())
    {
        if(!baseDir.mkdir(".qgcide"))
        {
            showErr(tr("Unable to create dictionary dir ") + dictDir.absolutePath());
            return false;
        }
    }
    dictFile.setFileName(dictDir.absolutePath() + "/gcide-entries.xml");
    if(dictFile.exists())
    {
        return true;
    }
    // TODO: download from internet
}

QString QDictWidget::searchExpr(const QString &expr)
{
    if(!ensureDictFile())
    {
        return "";
    }
    if(!dictFile.open(QFile::ReadOnly))
    {
        return tr("Unable to open dictionary file ") + dictFile.fileName() + "\n\n" + dictFile.errorString();
    }
    QString exprString("<entry key=\"" + expr);
    char buf[4096];
    bool found = false;
    QString result;
    for(;;)
    {
        int readRes = dictFile.readLine(&buf[0], 4096);
        if(readRes < 0)
        {
            if(dictFile.atEnd())
            {
                break;
            }
            else
            {
                result += tr("Error reading from dictionary file") + ":\n\n" + dictFile.errorString();
            }
            break;
        }
        if(readRes == 0)
        {
            continue;   // empty line
        }
        if(found)
        {
            QString line(buf);
            int entryEnd = line.indexOf("</entry>");
            if(entryEnd < 0)
            {
                result += line;
                continue;
            }
            result += line.left(entryEnd + 8);
            found = false;
            continue;
        }
        if(!strstr(buf, "<entry key=\""))
        {
            continue;
        }
        QString str = QString::fromUtf8(buf);
        int entryStart = str.indexOf(exprString, 0, Qt::CaseInsensitive);
        if(entryStart < 0)
        {
            if(result.length() > 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        result += str.right(entryStart - exprString.length());
        found = true;
    }
    dictFile.close();
    if(result.length() == 0)
    {
        result = tr("Expression not found");
    }
    return result;
}

static QString toHtml(QString &xml)
{
    QByteArray bytes = xml.toUtf8();
    QBuffer buf(&bytes);
    QXmlInputSource source(&buf);
    GcideXmlHandler handler;
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    reader.parse(source);
    return handler.html;
}

void QDictWidget::textChanged(const QString &text)
{
    QString xml = "<entries>";
    xml += searchExpr(text);
    xml += "</entries>";
    QString html = toHtml(xml);
    browser->setText(html);
}

GcideXmlHandler::GcideXmlHandler()
{
}

bool GcideXmlHandler::startElement(const QString & /* namespaceURI */,
                                   const QString & /* localName */,
                                   const QString &qName,
                                   const QXmlAttributes &attributes)
{
    if(qName == "ex")               // expression
    {
        html += "<b>";
    }
    else if(qName == "def")         // definition
    {
        skip = false;
    }
    else if(qName == "sn")          // senses <sn no="1">....</sn>
    {
        if(html.endsWith("</ol>"))
        {
            html.chop(5);
        }
        else
        {
            html += "<ol>";
        }
        html += "<li>";
        skip = false;
    }
    if(qName == "entry")            // <entry key="Hell">
    {
        html += "<h1>";
        html += attributes.value("key");
        html += "</h1>";
        skip = true;
    }
    else if(qName == "entries")
    {
        html += "<html>";
    }

    return true;
}

bool GcideXmlHandler::endElement(const QString & /* namespaceURI */,
                                 const QString & /* localName */,
                                 const QString &qName)
{
    if(qName == "ex")
    {
        html += "</b>";
    }
    else if(qName == "def")
    {
        skip = true;
    }
    else if(qName == "sn")
    {
        html += "</li></ol>";
    }
    else if(qName == "entry")
    {
        html += "<br><br>";
    }
    else if(qName == "entries")
    {
        html += "</html>";
    }
    return true;
}

bool GcideXmlHandler::characters(const QString &str)
{
    if(skip)
    {
        return true;
    }
    html += str.trimmed();
    return true;
}


bool GcideXmlHandler::fatalError(const QXmlParseException &exception)
{
    html += QObject::tr("Parse error at line %1, column %2:\n%3")
                             .arg(exception.lineNumber())
                             .arg(exception.columnNumber())
                             .arg(exception.message());
    return false;
}

