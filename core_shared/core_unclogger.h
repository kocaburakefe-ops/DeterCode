#ifndef CORE_UNCLOGGER_H
#define CORE_UNCLOGGER_H

// İşlemci üzerindeki gereksiz yükleri ve kısıtlamaları kaldıran ana fonksiyon
void core_unclog_limits();

// İşlemcinin o anki "serbestlik" durumunu raporlar
bool is_core_optimized();

#endif // CORE_UNCLOGGER_H

