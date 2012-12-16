#ifndef __FILECOMMON__H
#define __FILECOMMON__H



#include <QString>
#include <QProcess>
#include <QDir>
#include <QTextCodec>

#include <QHash>
#include <QDirIterator>
#include <QXmlStreamReader>

#include <QStringList>

#include <QDebug>


/**
  \brief
  @function
  Auto detect encoding file
  @param filepath  QString of file path
  @param language  QString of language, default = russian
  @return encoding  QString encoding
  */
QString getEncodingFromFile(QString file, QString language="russian");


/**
  @function
  Retun name of file
  Example:
  /home/warmonger/develop/other/file.ru  return file
  @return name_file
  */
QString getFileNameAbs(const QString file);
/**
  @function
  Retun name of file
  Example:
  /home/warmonger/develop/other/file.ru  return file.ru
  @param filepath
  @return name_file
  */
QString getFileName(const QString file);
/**
  @function
  Returns absolute file path
  @param filepath
  @param folder
  @return filename
  */
QString absolutifyFileName(QString fn, QString path);
/**
  @function
  Return codec from string
  @param encoding(String)
  @return encoding(Codec)
   */
QTextCodec* getCodecOfEncoding(QString encoding); // получает строку с названием кодировки и возвращает кодес с этй кодировкой ( написана для уменьшения дублирования кода)
/**
  @fucnction
  Return list of lang
  @retun list
  */
QStringList getFillLang();
/**
    @fucnction
    Return list of type dict
    @return list
    */
QStringList getFillType();
/**
  @function
  Return list words from dict
  @param path_to_file
  @return list_of_words
  */
QStringList getListWord(QString);


/**
  @function
  Create empty html file,
  @param file_path
  @param title
  @return bool
  */
bool createEmptyHtml(QString fileName, QString title);

/**
  @function
  Create empty html file with text,
  @param file_path
  @param title
  @param text
  @return bool
  */
bool createEmptyHtml(QString fileName, QString title, QString text);
/**
  @function
  Create empty file with text,
  @param file_path
  @param text
  @return bool
  */
bool createEmpty(QString fileName, QString text);
/**
  @function
  Retrun text from <body> </body>
  @param file_path
  @return text
  */
QString getTextFromHtmlFile(QString fileName);
/**
  @function
  Retrurn description from <body> </body>
  @param file_path
  @return text
  */
QString getDescriptionFromHtmlFile(QString fileName);
/**
  @function
  Replace text in file
  @param file_path
  @param old_text
  @param new_text
  */
void replaceStrInFile(QString filepath, QString old, QString newstr);
/**
  @function
  Return info from dict input file
  Return list(QStringList)
  @param file_path
  @return info
  */
QStringList getInfoFromFile(QString file_path);
/**
  @function
  Return param from dict file
  Example:
  Input <meta name="Author" content="TEXT"> , Author
  Output TEXT
  @param str
  @param param
  @return param
  */
QString getParamInfo(QString *inputstr, QString param);
/**
  @function
  Hindi function for remove spaces
  dont use QString::simplified()
  used while :)
  @param text
  */
QString removeSpaces(QString str);
/**
  @function
  Delete word in file
  Delete <h4>word</h4> and description texts
  @param file_path
  @param word
  @param description
  */
void deleteWordFromDict(QString filePath, QString word, QString description);
/**
  @function
  Add word in file
  Add <h4>word</h4> and description texts
  @param file_path
  @param word
  @param description
  */
void addWordToDict(QString filePath, QString word, QString description);
/**
  @function
  Function for find string
  @param file
  @param text_to_find
  @return str_to_pos
  */
QString findPosWord(QString file, QString text);
/**
  \brief
  @function
  Create empty xml file.
  @param file_path
  @return bool
  */
bool createEmptyXML(QString fileName);
/**
 * @brief getParamModule
 * @param filename
 * @param param
 * @return
 */
QString getParamModule(QString filename, QString param); // возвращает параметр из файла. Вид файла    "PARAM = VALUE"
/**
 * @brief getBookList
 * @param filaPath
 * @return
 */
QStringList getBookList(QString filaPath);
/**
 * @brief getNumberOfChaptersInBook
 * @param filename
 * @return
 */
QHash<QString, int> getNumberOfChaptersInBook(QString filename);
/**
 * @brief removeEmptyQStringFromQStringList
 * @param list
 * @return
 */
QStringList removeEmptyQStringFromQStringList(QStringList *list);
/**
 * @brief getClearText
 * @param text
 * @return
 */
QString getClearText(QString *text);
/**
 * @brief getEndOfTag
 * @param tag
 * @return
 */
QString getEndOfTag(QString tag);
/**
 * @brief getListModulesFromPath
 * @param path
 * @param format
 * @return
 */
QStringList getListModulesFromPath(QString path, QString format=".ini");
/**
 * @brief recursiveFind
 * @param directory
 * @return
 */
QStringList recursiveFind(QString directory);

/**
 * @brief getNoteOfParams
 * @param curPath
 * @param curModule
 * @param curBook
 * @param curChapter
 * @param firstVerse
 * @return
 */
QHash<int, QString> getNoteOfParams(QString curPath,
                                    QString curModule,
                                    QString curBook,
                                    QString curChapter,
                                    QString firstVerse);
/**
 * @brief getVerseEndNumberFromNote
 * @param line
 * @return
 */
QString getVerseEndNumberFromNote(QString* line);
/**
 * @brief getVerseBeginNumberFromNote
 * @param line
 * @return
 */
QString getVerseBeginNumberFromNote(QString* line);
/**
 * @brief createListStrongs
 * @param path
 */
void createListStrongs(QString path);
/**
 * @brief getCoolLine
 * @param str
 * @return
 */
QString getCoolLine(QString str);
/**
 * @brief getNextWord
 * @param str
 * @param pos
 * @return
 */
QString getNextWord(QString str, int pos);
/**
 * @brief getShortLang
 * @param str
 * @return
 */
QString getShortLang(QString str);
/**
 * @brief getDescriptionForWordFromDict
 * @param pathToFile
 * @param word
 * @return
 */
QString getDescriptionForWordFromDict(QString pathToFile, QString word);

/**
 * @brief getBookmarks
 * return list of bookmarks from file
 * @param pathToFile
 * @return
 */
QStringList getBookmarks(QString pathToFile);



// this prog
QString getNameBook(const QString &m_str);
//QString getUrlChapter(const QString &url);
int removeFolder(QDir dir);
QString getTextChapter(const QString &m_text);
//QString getUrlChapter(const QString &url, const QString &bookName, const QString &chapterValue);

#endif // __FILECOMMON__H
