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
  Return codec from string
  @param encoding(String)
  @return encoding(Codec)
   */
QTextCodec* getCodecOfEncoding(QString encoding); // получает строку с названием кодировки и возвращает кодес с этй кодировкой ( написана для уменьшения дублирования кода)
/**
  @function
  Retrun text from <body> </body>
  @param file_path
  @return text
  */
QString getTextFromHtmlFile(QString fileName);
/**
 * @brief removeEmptyQStringFromQStringList
 * @param list
 * @return
 */
QStringList removeEmptyQStringFromQStringList(QStringList *list);
/**
 * @brief recursiveFind
 * @param directory
 * @return
 */
QStringList recursiveFind(QString directory);

#endif // __FILECOMMON__H
