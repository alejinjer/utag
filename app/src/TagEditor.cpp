#include "TagEditor.h"

QVector<QString> TagEditor::getTagsVector(const QString &path)
{
    QVector<QString> result;
    TagLib::FileRef f(path.toStdString().c_str());

    if (f.isNull()) {
        throw std::invalid_argument("can't read file");
    }
    auto tags = f.tag();

    result.push_back(TStringToQString(tags->title()).trimmed());
    result.push_back(TStringToQString(tags->artist()).trimmed());
    result.push_back(TStringToQString(tags->album()).trimmed());
    result.push_back(TStringToQString(tags->genre()).trimmed());

    return result;
}

void TagEditor::modifyFileTags(const QVector<QTableWidgetItem *> &modified)
{
    TagLib::FileRef f(modified.back()->text().toStdString().c_str());

    if (f.isNull()) {
        throw std::invalid_argument("can't modify file");
    }

    auto tag = f.tag();

    tag->setTitle(modified[0]->text().toStdString());
    tag->setArtist(modified[1]->text().toStdString());
    tag->setAlbum(modified[2]->text().toStdString());
    tag->setGenre(modified[3]->text().toStdString());
    f.save();
}
