#include "common.h"

#include "debughelper.h"


//------------------------------------------------------------------------------
QString getEncodingFromFile(QString file, QString language)
{
    QProcess pr;

#ifdef Q_OS_WIN
    pr.start("enca.exe -L " +language + " \""  + file + "\"");
#endif
#ifdef Q_OS_LINUX
    pr.start("enca -L " + language + " \""  + file + "\"");
#endif
    //    pr.start("pwd");

    QString encoding = "";
    if (pr.waitForFinished() == true)
    {
        QByteArray b = pr.readAll();
        encoding = QString(b);
    }
    if (encoding.indexOf("Universal transformation format 8 bits;") >= 0 ) encoding = "UTF-8";
    if (encoding.indexOf("Universal transformation format 16 bits;") >= 0 ) encoding = "UTF-16";
    if (encoding.indexOf("Universal transformation format 32 bits;") >= 0 ) encoding = "UTF-32";
    if (encoding.indexOf("Universal character set 2 bytes; UCS-2; BMP") >= 0) encoding = "UCS-2";
    if (encoding.indexOf("MS-Windows code page 1251") >= 0) encoding = "Windows-1251";
    if (encoding.indexOf("MS-Windows code page 1252") >= 0) encoding = "Windows-1252";
    if (encoding.indexOf("MS-Windows code page 1253") >= 0) encoding = "Windows-1253";
    if (encoding.indexOf("MS-Windows code page 1254") >= 0) encoding = "Windows-1254";
    if (encoding.indexOf("MS-Windows code page 1255") >= 0) encoding = "Windows-1255";
    if (encoding.indexOf("MS-Windows code page 1256") >= 0) encoding = "Windows-1256";
    if (encoding.indexOf("MS-Windows code page 1257") >= 0) encoding = "Windows-1257";
    if (encoding.indexOf("MS-Windows code page 1258") >= 0) encoding = "Windows-1258";
    if (encoding.indexOf("7bit ASCII characters") >= 0) encoding = "ASCII";
    if (encoding.indexOf("KOI8-R Cyrillic") >= 0) encoding = "KOI8-R";
    if (encoding.indexOf("KOI8-U Cyrillic") >= 0) encoding = "KOI8-U";
    if (encoding.indexOf("Unrecognized encoding") >= 0) encoding = "UTF-8";
    //    qDebug() << "encoding = " << encoding;
    return encoding;
}
//------------------------------------------------------------------------------
QString getFileNameAbs(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    list = str.split(".");
    str = list.first();
    return str;
}
//------------------------------------------------------------------------------
QString getFileName(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    return str;
}
//------------------------------------------------------------------------------
QString absolutifyFileName(QString fn, QString path)
{
    QString afn;
    if (!fn.isEmpty()){
        QDir dir(path);
        afn = dir.cleanPath( dir.absoluteFilePath(fn) );
    }
    return afn;
}
//------------------------------------------------------------------------------
QTextCodec * getCodecOfEncoding(QString encoding)
{
    //    encoding = encoding.toUpper ();
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    if (encoding.toUpper ()== "UTF-8")        codec = QTextCodec::codecForName("UTF-8");
    if (encoding.toUpper ()== "UTF-16")       codec = QTextCodec::codecForName("UTF-16");
    if (encoding.toUpper ()== "UTF-16BE")       codec = QTextCodec::codecForName("UTF-16BE");
    if (encoding.toUpper ()== "UTF-16LE")       codec = QTextCodec::codecForName("UTF-16LE");
    if (encoding.toUpper ()== "UTF-32")       codec = QTextCodec::codecForName("UTF-32");
    if (encoding.toUpper ()== "UTF-32BE")       codec = QTextCodec::codecForName("UTF-32BE");
    if (encoding.toUpper ()== "UTF-32LE")       codec = QTextCodec::codecForName("UTF-32LE");
    if (encoding == "Windows-1251") codec = QTextCodec::codecForName("Windows-1251");
    if (encoding == "Windows-1252") codec = QTextCodec::codecForName("Windows-1252");
    if (encoding == "Windows-1253") codec = QTextCodec::codecForName("Windows-1253");
    if (encoding == "Windows-1254") codec = QTextCodec::codecForName("Windows-1254");
    if (encoding == "Windows-1255") codec = QTextCodec::codecForName("Windows-1255");
    if (encoding == "Windows-1256") codec = QTextCodec::codecForName("Windows-1256");
    if (encoding == "Windows-1257") codec = QTextCodec::codecForName("Windows-1257");
    if (encoding == "Windows-1258") codec = QTextCodec::codecForName("Windows-1258");
    if (encoding.toUpper ()== "KOI8-R")       codec = QTextCodec::codecForName("KOI8-R");
    if (encoding.toUpper ()== "KOI8-U")       codec = QTextCodec::codecForName("KOI8-U");

    //        qDebug() << " encoding = " << encoding;
    return codec;
}
//------------------------------------------------------------------------------
QStringList getFillLang()
{
    QStringList items;
    items << QString ("rus")
          << QString ("eng")
          << QString ("ukr")
          << QString ("he-rus")
          << QString ("gr-rus")
          << QString ("he");
    return items;
}
//------------------------------------------------------------------------------
QStringList getFillType()
{
    //    Dictionary/Справочник
    //   Encyclopedia/Энциклопедия
    //   Glossary/Глоссарий
    //   Lexicon/Симфония
    //   Thesaurus/Тезаурус
    //   Vocabulary/Толковый
    //   Wordbook/Словарь
    QStringList items;
    items << QString::fromUtf8( ("Dictionary/Справочник"))
          << QString::fromUtf8( ("Encyclopedia/Энциклопедия"))
          << QString::fromUtf8( ("Glossary/Глоссарий"))
          << QString::fromUtf8( ("Lexicon/Симфония"))
          << QString::fromUtf8( ("Thesaurus/Тезаурус"))
          << QString::fromUtf8( ("Vocabulary/Толковый"))
          << QString::fromUtf8( ("Wordbook/Словарь"));
    return items;
}
//------------------------------------------------------------------------------
QStringList getListWord(QString filename)
{
    QStringList r_list;
    QXmlStreamReader xmlReader;
    xmlReader.addData(getTextFromHtmlFile(filename));

    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            //         myDebug() << attrs.value("name").toString();
            r_list.append(attrs.value("name").toString());
        }

        //        if (xmlReader.isEndElement())
        //        {

        //        }
        xmlReader.readNext();
    }
    r_list = removeEmptyQStringFromQStringList(&r_list);
    return r_list;
}

//------------------------------------------------------------------------------
bool createEmptyHtml(QString fileName, QString title, QString text)
{
    bool ret = true;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "<html>\n<head>" << endl;
            ts << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />" << endl;
            ts << "<title>" << title <<"</title>" << endl;
            ts << "</head>\n<body>\n" << text << "\n</body>\n</html>" << endl;
            file.close();
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool createEmpty(QString fileName, QString text)
{
    bool ret = false;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << text;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool createEmptyHtml(QString fileName, QString title)
{
    bool ret = true;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "<html>\n<head>" << endl;
            ts << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />" << endl;
            ts << "<title>" << title <<"</title>" << endl;
            ts << "</head>\n<body>\n</body></html>" << endl;
            file.close();
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
void replaceStrInFile(QString filepath, QString old, QString newstr)
{
    QFile file(filepath);
    QString str;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(getCodecOfEncoding("UTF-8"));
        str = stream.readAll();
        str.replace(old, newstr);
    }
    else
    {
        qDebug() << "Error: not open file (replacestrinfile):" << filepath;
    }
    file.close();

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(getCodecOfEncoding("UTF-8"));
        stream << str;
        file.close();
    }
    else
    {
        qDebug() << "Error: not open file (replacestrinfile write):" << filepath;
    }

}
//------------------------------------------------------------------------------
QString getTextFromHtmlFile(QString filePath)
{
    QString str = "";
    QFile file(filePath);
    //    qDebug() << filePath;
    file.close();
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QString encoding = getEncodingFromFile(filePath);
            stream.setCodec(getCodecOfEncoding(encoding));
            str = stream.readAll();
            //        //        qDebug() << "str = " << str;
            //        int body = QString("<body>").length();
            //        int posBegin = str.indexOf("<body>");

            //        int posEnd = str.indexOf("</body>");
            //        str = str.mid(posBegin + body,
            //                      posEnd - posBegin - body);
            file.close();
        }
        else
        {
            myDebug() << "Error: not open file(getTextFromHtmlFile):" << filePath;
        }
    }

    return str;
}
//------------------------------------------------------------------------------
QStringList getInfoFromFile(QString file_path)
{
    QStringList list;
    if(QFile::exists(file_path))
    {
        QString encoding = getEncodingFromFile(file_path);
        QFile file(file_path);
        QString str;
        QString info[7];
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding(encoding));
            do
            {
                str = stream.readLine();
                if (str.indexOf("<meta name=\"Author\"") != -1)
                    info[0] = getParamInfo(&str, "Author");
                if (str.indexOf("<meta name=\"Revision\"") != -1)
                    info[1] = getParamInfo(&str, "Revision");
                if (str.indexOf("<meta name=\"Language\"") != -1)
                    info[2] = getParamInfo(&str, "Language");
                if (str.indexOf("<meta name=\"Type\"") != -1)
                    info[3] = getParamInfo(&str, "Type");
                if (str.indexOf("<meta name=\"Description\"") != -1)
                    info[4] = getParamInfo(&str, "Description");
                if (str.indexOf("<meta name=\"Rights\"") != -1)
                    info[5] = getParamInfo(&str, "Rights");
                if (str.indexOf("<meta name=\"Numbering\"") != -1)
                    info[6] = getParamInfo(&str, "Numbering");
            } while(!stream.atEnd());
            file.close();

            for (int i = 0; i < 7; i++)
            {
                list << info[i];
            }
        }
        else
        {
            qDebug() << "Error: not open file for read(get info from file):"
                     << file_path;
        }
    }

    return list;
}
//------------------------------------------------------------------------------
QString getParamInfo(QString *inputstr, QString param)
{
    QString str = *inputstr;
    QString remove = "<meta name=\"" + param + "\" content=\"";
    str.remove(remove)
            .remove("\">");
    str = removeSpaces(str);

    if (str == "RU")
        str = "rus";

    if (str == "En")
        str = "eng";

    return str;
}

//------------------------------------------------------------------------------
QString removeSpaces(QString str)
{
    /// translate to hindi
    /// bad work
    /// str.simplified()
    /// remove after word
    bool flag = true;
    int i = 0;
    do
    {
        if(str.at(i) == ' ')
        {
            str.remove(i,1);
            i--;
        }
        else
        {
            flag = false;
        }

        i++;
    } while(flag);

    /// remove before word
    i = 1;
    flag = true;
    do
    {
        if(str.at(str.length()-i) == ' ')
        {
            str.remove(str.length()-i,1);
            i++;
        }
        else
        {
            flag = false;
        }

        i--;
    } while(flag);

    return str;
}
//------------------------------------------------------------------------------
void deleteWordFromDict(QString filePath, QString word, QString description)
{
    QString text = getTextFromHtmlFile(filePath);
    text.remove(QString("<h4>%1</h4>").arg(word))
            .remove(description);
    QFile::remove(filePath);
    createEmpty(filePath, text);
}
//------------------------------------------------------------------------------
void addWordToDict(QString filePath, QString word, QString description)
{
    QString text = getTextFromHtmlFile(filePath);

    QString oldPos = findPosWord(filePath, word);
    QString newText = QString("<h4>%1</h4> %2")
            .arg(word)
            .arg(description) + "\r\n" + oldPos;
    text.replace(oldPos, newText);

    QFile::remove(filePath);
    createEmpty(filePath, text);
}
//------------------------------------------------------------------------------
QString getDescriptionFromHtmlFile(QString filePath)
{
    QString str = "";
    QFile file(filePath);
    //    qDebug() << filePath;
    file.close();
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString encoding = getEncodingFromFile(filePath);
        stream.setCodec(getCodecOfEncoding(encoding));
        str = stream.readAll();
        //        qDebug() << "str = " << str;
        int body = QString("<body>").length();
        int posBegin = str.indexOf("<body>");

        int posEnd = str.indexOf("</body>");
        str = str.mid(posBegin + body,
                      posEnd - posBegin - body);
        str.remove("\n")
                .remove("\r");
        file.close();
    }
    else
    {
        qDebug() << "Error: not open file(getTextFromHtmlFile):" << filePath;
    }

    return str;
}
//-------------------------------------------------------------------------------
QString findPosWord(QString file, QString text)
{
    QString t_output_str = "";
    if(QFile::exists(file))
    {
        QString t_text = getTextFromHtmlFile(file);
        QStringList t_list = t_text.split("\n");

        QString t_find_text = text;
        bool flag = true;
        do
        {
            for (int i = 0; i < t_list.size(); i++)
            {
                if (QString(t_list.at(i)).indexOf(t_find_text) != -1)
                {
                    t_output_str = t_list.at(i);
                    flag = false;
                    break;
                }
            }
            t_find_text.remove(t_find_text.length() -1, 1);
        } while(flag and
                !t_find_text.isEmpty());
    }
    return t_output_str;
}
//------------------------------------------------------------------------------
bool createEmptyXML(QString fileName)
{
    bool ret = false;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
            ts << "<!DOCTYPE xbel>" << endl;
            ts << "<xbel version=\"1.0\">" << endl;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}

//------------------------------------------------------------------------------
bool endXML(QString fileName)
{
    bool ret = false;
    QFile file(fileName);
    if (file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::Append))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "</xbel>" << endl;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
QString getParamModule(QString filename, QString param)
{
    // translate to hindi
    QString str = "";
    QString line;
    QString parama = param + " = ";
    QFile file(filename);
    file.close();
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream( &file );
        do {
            line = stream.readLine();
            if (line.indexOf(parama) >= 0)
            {
                str = line.remove(parama);
            }
        } while (str.isEmpty() and !line.isNull());
        file.close();
    }
    else
    {
        qDebug() << "Error";
    }
    return str;
}
//------------------------------------------------------------------------------
QStringList getBookList(QString file)
{
    QStringList bookList;
    QString param = "BookList";
    // translate to hindi
    QString str = getParamModule(file, param);
    bookList << str.split(":");
    return bookList;
}
//------------------------------------------------------------------------------
QHash<QString, int> getNumberOfChaptersInBook(QString filename)
{

    QStringList bookList;
    QString param = "NumberChapter";
    //     translate to hindi
    QString str = getParamModule(filename, param);
    bookList << str.split("::");
    bookList = removeEmptyQStringFromQStringList(&bookList);
    QHash<QString, int> list;



    for (int i = 0; i < bookList.size(); i++)
    {
        QStringList test;
        test << bookList.at(i).split("^");
        //        myDebug() <<  bookList.at(i) << test.size();

        list[test.at(0)] = test.at(1).toInt();
    }
    return list;
}
//------------------------------------------------------------------------------
QStringList removeEmptyQStringFromQStringList(QStringList *list)
{
    QStringList listn;
    for(int i = 0; i < list->size(); i++)
    {
        if(!list->at(i).isEmpty()
                && list->at(i) != ""
                && list->at(i) != " ")
        {
            listn << list->at(i);
        }
    }
    //    myDebug() << listn;
    return listn;
}
//------------------------------------------------------------------------------
QString getClearText(QString *text)
{
    QString clearText = *text;
    QRegExp rx("(<[^>]*>)");
    //    QRegExp rxp("(<[Pp].*?>)");
    //    QRegExp rxi("( [a-zA-Z:]+=)|(\"[^\"]*\")");
    //    QRegExp regP("(<[a-zA-Z]+) [^>]*");  // убирает атрибуты у p Тега
    //    // html атрибуты  (?:[\w]*) *= *"(?:(?:(?:(?:(?:\\\W)*\\\W)*[^"]*)\\\W)*[^"]*")
    //    // все теги </?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>+(.*?|[\s\S]*?)+</?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>
    //    </?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>+(.*?|[\s\S]*?)+</?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>
    clearText.remove(rx);
    QString tab = "    ";
    clearText.remove(tab);
    //    myDebug() << clearText;


    return clearText;

}
//------------------------------------------------------------------------------
QString getEndOfTag(QString tag)
{
    QString newtag = tag;
    if(newtag[newtag.length() - 1] != QChar(62))
    {
        //        myDebug() << newtag[newtag.length()-1];
        newtag = newtag + "><";
    }
    return newtag;
}
//------------------------------------------------------------------------------
QStringList getListModulesFromPath(QString path, QString format)
{
    QStringList files = recursiveFind(path);
    QStringList list;
    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).indexOf(format) >= 0
                or files.at(i).indexOf(format.toUpper()) >= 0)
        {
            list << files.at(i);
        }
    }
    return list;
}
//------------------------------------------------------------------------------
QStringList recursiveFind(QString directory)
{
    //// подумать, нужен ли чистый рекурсивный поиск
    //// если нет, то сюда вставить обработку getModuleFilesList
    QStringList list;
    QDirIterator iterator (directory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext())
    {
        iterator.next();
        list << iterator.fileInfo().absoluteFilePath();
    }
    return list;
}
//------------------------------------------------------------------------------
QHash<int, QString> getNoteOfParams(QString curPath,
                                    QString curModule,
                                    QString curBook,
                                    QString curChapter,
                                    QString firstVerse)
{
    QHash<int, QString> hash;
    Q_UNUSED (firstVerse)

    QString text = getTextFromHtmlFile(curPath);
    QStringList list;
    int count = 0;
    text.remove("<xml>").remove("</xml>");

    list << text.split("</note>");
    list = removeEmptyQStringFromQStringList(&list);
    for (int i = 0; i < list.size(); i++)
    {
        QString str1 = "module=\"" + curModule + "\"";
        QString str2 = "book=\"" + curBook + "\"";
        QString str3 = "chapter=\"" + curChapter + "\"";
        QString line = list.at(i);
        if (line.contains(str1) &&
                line.contains(str2) &&
                line.contains(str3) &&
                getVerseBeginNumberFromNote(&line) <= firstVerse &&
                getVerseEndNumberFromNote(&line) >= firstVerse)
        {
            //            QString text = "<note " + str1 + str2 + str3;
            //            hash[count] = strat.remove(text).remove("</note>");
//            myDebug() << getVerseBeginNumberFromNote(&line) << getVerseEndNumberFromNote(&line);

            /// remove tag before text
            int pos = line.indexOf(">");
            line.remove(0, pos + 1);
            hash[count] = line;
        }
    }
    return hash;
}

//------------------------------------------------------------------------------
QString getVerseBeginNumberFromNote(QString* line)
{

    QString str = *line;
    QString t_str ="versebegin=\"";
    int pos = str.indexOf(t_str);
    int pos2 = str.indexOf("\"", pos + t_str.length());

    str = str.mid(pos + t_str.length(), pos2  - pos - t_str.length());
    return str;
}
//------------------------------------------------------------------------------
QString getVerseEndNumberFromNote(QString* line)
{

    QString str = *line;
    QString t_str ="verseend=\"";
    int pos = str.indexOf(t_str);
    int pos2 = str.indexOf("\"", pos + t_str.length());

    str = str.mid(pos + t_str.length(), pos2  - pos - t_str.length());
    return str;
}
//------------------------------------------------------------------------------
QString getCoolLine(QString str)
{
    QString t_str = getClearText(&str);

    QStringList list;
    list << t_str.split("\n");
    list = removeEmptyQStringFromQStringList(&list);
    //    myDebug() << list;
    QString tab = "    ";
    t_str = "";
    for (int i = 0; i < list.size(); i++)
    {
        if (!list.at(i).isEmpty())
        {
            //            myDebug() << list.at(i);
            t_str.append(QString(tab + tab + list.at(i)));
        }
    }
    return t_str;
}
//------------------------------------------------------------------------------
QString getNextWord(QString str, int pos)
{
    /// translate to hindi
    QString t_str = "";
    bool flag1 = false;
    bool flag2 = false;

    str.append(" ");

    if (pos == 0)
    {
        flag1 = true;
    }
    else
    {
        int j = 0;
        while (str.at(pos + j) != ' ' and str.length() >= pos + j )
        {
            j++;
        }
        pos += j + 1;
        flag1 = true;
    }

    for (int i = pos; i < str.length(); i++)
    {
        if (str.at(i) != ' ')
            t_str.append(str.at(i));

        if (str.at(i) == ' ' && flag1 && !flag2)
            flag2 = true;

        if (flag2 && flag1)
            break;
    }

    return t_str;
}
//------------------------------------------------------------------------------
QString getShortLang(QString str)
{
    if (str == "Russian")
        return "ru";
    if (str == "English")
        return "en";
    if (str == "Deutch")
        return "de";
    if (str == "Français")
        return "fr";

    return "en";
}
//------------------------------------------------------------------------------
QString getDescriptionForWordFromDict(QString t_pathToFile, QString word)
{
    QXmlStreamReader xmlReader;
    QString r_str;
    xmlReader.addData(getTextFromHtmlFile(t_pathToFile));
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            if (attrs.value("name") == word)
            {
                r_str = xmlReader.readElementText();
                r_str.remove("    ");
                break;
            }
        }
//        if (xmlReader.isEndElement())
//        {

//        }
        xmlReader.readNext();
    }
    return r_str;
}
//------------------------------------------------------------------------------
QStringList getBookmarks(QString pathToFile)
{
    QXmlStreamReader xmlReader;
    QString r_str;
    QStringList r_list;
    xmlReader.addData(getTextFromHtmlFile(pathToFile));
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            r_list  << attrs.value("name").toString();
        }
//        if (xmlReader.isEndElement())
//        {

//        }
        xmlReader.readNext();
    }
    r_list = removeEmptyQStringFromQStringList(&r_list);
    return r_list;
}
//------------------------------------------------------------------------------
QString getNameBook(const QString &m_str)
{
    QString str = m_str;
    int pos1 = str.indexOf(">");
    int pos2 = str.indexOf("<", 3);
    str = str.mid(pos1 + 1, pos2 - pos1 - 1);
    return str;
}
//------------------------------------------------------------------------------
//QString getUrlChapter(const QString &url)
//{
//    QString str = url;
//    int pos1 = str.indexOf("href=\"");
//    int pos2 = str.indexOf("\"", pos1 + 7);
//    str = str.mid(pos1 + 6, pos2 - pos1 - 6);
//    myDebug() << str;


//    // /passage/?search=%D0%9E%D1%82%D0%BA%D1%80%D0%BE%D0%B2%D0%B5%D0%BD%D0%B8%D0%B5+22&amp;version=RUSV
//    //http://www.biblegateway.com/passage/?search=1+Kongebok+8&version=DNB1930
//    return str;
//}
//------------------------------------------------------------------------------
//QString getUrlChapter(const QString &url, const QString &bookName, const QString &chapterValue)
//{
//    QString str = url;
//    int pos1 = str.indexOf("href=\"");
//    int pos2 = str.indexOf("\"", pos1 + 7);
//    str = str.mid(pos1 + 6, pos2 - pos1 - 6);
//    myDebug() << str;


//    // /passage/?search=%D0%9E%D1%82%D0%BA%D1%80%D0%BE%D0%B2%D0%B5%D0%BD%D0%B8%D0%B5+22&amp;version=RUSV
//    //http://www.biblegateway.com/passage/?search=1+Kongebok+8&version=DNB1930
//    return str;
//}
//------------------------------------------------------------------------------
int removeFolder(QDir dir)
{

   int res = 0;
   //Получаем список каталогов
   QStringList lstDirs  = dir.entryList(QDir::Dirs  |

                                   QDir::AllDirs |
                                   QDir::NoDotAndDotDot);
   //Получаем список файлов
   QStringList lstFiles = dir.entryList(QDir::Files);

   //Удаляем файлы
   foreach (QString entry, lstFiles)
   {
      QString entryAbsPath = dir.absolutePath() + "/" + entry;

      QFile::remove(entryAbsPath);
   }

   //Для папок делаем рекурсивный вызов
   foreach (QString entry, lstDirs)
   {

      QString entryAbsPath = dir.absolutePath() + "/" + entry;

      removeFolder(QDir(entryAbsPath));
   }

   //Удаляем обрабатываемую папку
   if (!QDir().rmdir(dir.absolutePath()))
   {

      res = 1;
   }
   return res;
}
//------------------------------------------------------------------------------
QString getTextChapter(const QString &m_text)
{
    QString text = m_text;
    QStringList list;
//    list << m_text.split("\n");


    int pos1 = text.indexOf("<div class=\"passage version-");
    int pos2 = text.indexOf("</div>", pos1);

    text = text.mid(pos1, pos2 - pos1);
    list << text.split("</p>");
    list = removeEmptyQStringFromQStringList(&list);
    text = "";

    for (int i = 0; i < list.size(); i++)
    {

        QString t_str;
//        <span class="chapternum">1 </span>

        t_str = list.at(i);
//        t_str.replace("<span class=\"chapternum\">", "<sup class=\"versenum\">");



//        pos1 = t_str.indexOf("</sup>");
//        pos2 = t_str.indexOf("</span>", pos1);
        pos1 = t_str.indexOf("<p");
        pos2 = t_str.indexOf("</p>");

        t_str = t_str.mid(pos1, pos2 - pos1);
//        t_str.remove("</sup>");
//        t_str.remove("<\/sup");

        t_str = getClearText(&t_str);
//        myDebug() << list.at(i);

        text.append("<p>" + t_str + "</p>\n");
    }

//    myDebug() << list.size();

    return text;

}
//------------------------------------------------------------------------------

