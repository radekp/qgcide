#include "qgcide.h"

QDictMainWindow::QDictMainWindow(QWidget* parent, Qt::WindowFlags f) : QMainWindow(parent, f)
{
    setWindowTitle(tr("English dictionary"));

#ifdef QTOPIA
    QMenu* m = QSoftMenuBar::menuFor(this);
    m->addAction("");
#else
    QMenu *m = menuBar()->addMenu("&File");
    resize(640, 480);
#endif
    m->addAction(tr("Quit"), this, SLOT(close()));

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

    progress = new QProgressBar(this);
    progress->setVisible(false);

    layout->addWidget(edit, 0, 0);
    layout->addWidget(browser, 1, 0);
    layout->addWidget(progress);

    setLayout(layout);
}

void QDictWidget::showErr(QString err)
{
    QMessageBox::critical(this, tr("English dictionary"), err);
}

bool QDictWidget::download(QString url, QString destPath, QString filename)
{
    browser->setText(tr("Downloading") + " " + filename);

    QString host = url;
    QString reqPath;
    int port = 80;

    if(url.startsWith("http://"))
    {
        host.remove(0, 7);
    }

    int colonIndex = host.indexOf(':');
    int slashIndex = host.indexOf('/');
    if(slashIndex < 0)
    {
        return false;
    }
    reqPath = host.right(host.length() - slashIndex).replace(" ", "%20");
    host = host.left(slashIndex);
    if(colonIndex > 0)
    {
        QString portStr = host.right(host.length() - colonIndex - 1);
        host = host.left(colonIndex);
        port = portStr.toInt(0, 10);
    }

connect:
    QTcpSocket sock(this);
    sock.setReadBufferSize(65535);
    sock.connectToHost(host, port);
    if(!sock.waitForConnected(5000))
    {
        showErr(sock.errorString());
        return false;
    }

    QByteArray req("GET ");
    req.append(reqPath);
    req.append(" HTTP/1.1\r\nHost: ");
    req.append(host);
    req.append(':');
    req.append(QByteArray::number(port));
    req.append("\r\n\r\n");

    sock.write(req);
    sock.flush();
    sock.waitForBytesWritten();

    int contentLen = 0;
    bool html = false;
    QByteArray line;
    for(;;)
    {
        line = sock.readLine();
        if(line.isEmpty())
        {
            if(sock.waitForReadyRead(5000))
            {
                continue;
            }
            break;
        }
        if(line.trimmed().isEmpty())
        {
            break;
        }
        html = html | (line.indexOf("Content-Type: text/html") == 0);
        if(line.indexOf("Content-Length: ") == 0)
        {
            contentLen = line.remove(0, 16).trimmed().toInt(0, 10);
        }
    }

    if(html)
    {
        QByteArray text = sock.readAll();
        sock.close();
        if(text.length() == 0)
        {
            QMessageBox::critical(this, tr("English dictionary"),
                                  tr("No response from ") + host);
            return false;
        }
        text.replace("</br>", "\n");
        if(QMessageBox::information(this, tr("English dictionary"), text,
                                 QMessageBox::Ok | QMessageBox::Retry) == QMessageBox::Retry)
        {
            goto connect;
        }

        return false;
    }

    QFile f(destPath);
    if(!f.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this, tr("English dictionary"),
                              tr("Unable to save file:\r\n\r\n") + f.errorString());
        sock.close();
        return false;
    }

#ifdef QTOPIA
     QtopiaApplication::setPowerConstraint(QtopiaApplication::DisableSuspend);
#endif

    if(contentLen <= 0)
    {
        QMessageBox::critical(this, tr("English dictionary"), tr("Couldnt read content length"));
        contentLen = 0x7fffffff;
    }
    progress->setMaximum(contentLen);
    progress->setValue(0);
    int remains = contentLen;

    char buf[65535];
    int count;
    for(;;)
    {
        QApplication::processEvents();
        count = sock.read(buf, 65535);
        if(count < 0)
        {
            break;
        }
        f.write(buf, count);
        f.flush();
        remains -= count;
        if(remains <= 0)
        {
            break;
        }
        progress->setValue(contentLen - remains);
    }
    f.close();
    sock.close();

#ifdef QTOPIA
    QtopiaApplication::setPowerConstraint(QtopiaApplication::Enable);
#endif

    return true;
}

bool QDictWidget::ungzip(QString file)
{
    browser->setText(tr("Unpacking") + " " + file);
    progress->setMaximum(640);
    progress->setValue(0);

    QProcess gzip;
    gzip.start("gzip", QStringList() << "-d" << file);
    if(!gzip.waitForStarted())
    {
        showErr(tr("Unable to start gzip"));
        return false;
    }
    while(gzip.state() == QProcess::Running)
    {
        progress->setValue((progress->value() + 1) % 640);
        QApplication::processEvents();
        gzip.waitForFinished(100);
    }
    return true;
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
    if(QMessageBox::question(this, tr("English dictionary"),
                          tr("Dictionary must be downloaded. Please make sure you have internet connection and press yes to confirm download (14MB)."),
                          QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
    {
        return false;
    }
    progress->setVisible(true);
    QString gzFile = dictFile.fileName() + ".gz";
    if(!download("http://dl.linuxphone.ru/openmoko/qtmoko/packages/gcide-entries.xml.gz", gzFile, "gcide-entries.xml.gz"))
    {
        return false;
    }
    if(!ungzip(gzFile))
    {
        return false;
    }
    progress->setVisible(false);
    return true;
}

// Compare current key and searched expression.
static int compareExprKey(const QString &expr, const QString &key)
{
    for(int i = 0; i < expr.length(); i++)
    {
        if(i >= key.length())
        {
            return 1;       // expression is bigger
        }
        QChar ech = expr.at(i).toUpper();
        QChar kch = key.at(i).toUpper();
        if(ech == kch)
        {
            continue;
        }
        if(!kch.isLetterOrNumber() || kch.unicode() > 128)
        {
            return UNCOMPARABLE_CHARS;
        }
        return ech.unicode() - kch.unicode();
    }
    return 0;
}

QString QDictWidget::searchExpr(const QString &expr, int maxResults)
{
    if(!ensureDictFile())
    {
        return "";
    }
    if(!dictFile.open(QFile::ReadOnly))
    {
        return tr("Unable to open dictionary file ") + dictFile.fileName() + "\n\n" + dictFile.errorString();
    }

    // Start searching from the middle
    qint64 left = 0;
    qint64 right = dictFile.size() - 4096;
    dictFile.seek((left + right) / 2);

    // 0 = find some matching expression
    // 1 = go forward for first matching expr
    // 2 = appending text inside matching entry
    // 3 = skipping text outside entry
    int phase = 0;

    QString exprString("<entry key=\"" + expr);
    char buf[4096];    
    QString result;
    int numResults = 0;
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
        if(phase == 2)
        {
            QString line(buf);
            int entryEnd = line.indexOf("</entry>");
            if(entryEnd < 0)
            {
                result += line;
                continue;
            }
            result += line.left(entryEnd + 8);
            numResults++;
            if(numResults > maxResults)
            {
                break;
            }
            phase = 3;
            continue;
        }
        char *keyStart = strstr(buf, "<entry key=\"");
        if(keyStart == 0)
        {
            continue;
        }
        keyStart += 12;
        char *keyEnd = strchr(keyStart, '"');
        QString key = QString::fromUtf8(keyStart, keyEnd - keyStart);
        int cmp = compareExprKey(expr, key);
        if(cmp == UNCOMPARABLE_CHARS)
        {
            continue;        // skip uncomparable words
        }
        if(phase == 0)
        {
            bool changed = true;
            if(cmp > 0)      // expression is bigger then key
            {
                left = dictFile.pos();
            }
            else            // expression is smaller or matches
            {
                changed = (right != dictFile.pos());    // comparing twice same word
                right = dictFile.pos();
            }
            if(changed && (right - left > 4096))
            {
                dictFile.seek((left + right) / 2);
                continue;
            }
            phase = 1;
            dictFile.seek(left);
            continue;
        }
        if(phase == 1)
        {
            if(cmp > 0)
            {
                continue;           // first match still not found
            }
            else if(cmp < 0)
            {
                break;              // all matching words passed
            }
            phase = 2;
        }
        if(phase == 2 || phase == 3)
        {
            QString str = QString::fromUtf8(buf);
            int entryStart = str.indexOf(exprString, 0, Qt::CaseInsensitive);
            if(entryStart < 0)
            {
                break;      // first non matching entry was hit
            }
            result += str.right(entryStart - exprString.length());
            phase = 2;
        }
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
    xml += searchExpr(text, 32);
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

