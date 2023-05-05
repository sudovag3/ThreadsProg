#ifndef READFILE_H
#define READFILE_H
#include <QThread>
#include <QFile>
#include <QProgressBar>
#include <QDebug>

class ReadFile : public QThread
{
    Q_OBJECT
    QString dir;

public:
    explicit ReadFile(QObject *pb = 0)
    {

    }

    void set_dir(QString directory)
    {
        dir = directory;

    }

    void run()
    {
        QFile file(dir);
        int coef = (file.size() / 4) / 100;
        if (file.open(QIODevice::ReadWrite))
        {
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_2_0);
            stream.setByteOrder(QDataStream::LittleEndian);
            int k = 0;

            while (!stream.atEnd())
            {
                int value;
                stream >> value;

                if (value < 0) {
                    value = 0;
                    file.seek(file.pos() - static_cast<qint64>(sizeof(int)));
                    stream << value;
                }

                emit progress_bar(1 + (k / coef));
                k++;
            }

            file.close();
        }
    }

signals:
    void progress_bar(int);

};

#endif // READFILE_H
