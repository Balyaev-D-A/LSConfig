#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <QString>
#include <QTextCodec>
#include <QTextEncoder>
#include <QTime>
#include <QApplication>

#define LoByte(x) (char)(x & 0xFF)
#define HiByte(x) (char)(x >> 8)
#define MakeWord(hi, lo) ((quint16)(hi & 0xFF) << 8) | (lo & 0xFF)
#define SwapBytes(x) ((quint16)LoByte(x) << 8) + HiByte(x)


quint16 CalculateCRC16(char* buffer, quint16 size);
QString cp1251_to_utf(char *text);
char* utf_to_cp1251(QString text);
void delay(int millisecondsToWait);

#endif // UTIL_H
