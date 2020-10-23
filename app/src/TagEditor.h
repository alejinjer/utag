#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include "../../3dparty/taglib/taglib/toolkit/tpropertymap.h"
#include "../../3dparty/taglib/taglib/fileref.h"
#include "../../3dparty/taglib/taglib/tag.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/id3v2frame.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
#include "../../3dparty/taglib/taglib/mpeg/mpegfile.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/id3v2tag.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
#include <QtCore>
#include <QTableWidgetItem>

#define TAG_COUNT 4

class TagEditor
{
public:
    TagEditor() = default;
    QVector<QString> getTagsVector(const QString& path);
    void modifyFileTags(const QVector<QTableWidgetItem *>& modified);

};

#endif // TAGEDITOR_H
