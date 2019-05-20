#include "blockcipher.h"
#include <QDir>
#include <QStandardPaths>

//File::File(const QString &filename)
//    : fileinfo_{filename}
//{
//    //TODO: Destination directory for encrypted files and dirs
//    //TODO: Checking Binary file. Encryption binary files using block ciphers

//    if (fileinfo_.isSymLink()) {
//        if (fileinfo_.exists())
//            fileinfo_.setFile(fileinfo_.symLinkTarget());
//        else
//            fileinfo_.setFile("");
//    }

//    if (fileinfo_.isDir())
//        isDirectory_ = true;
//}


//void base64Encoding(const QString& filename)
//{
//    const QString destfile = filename + ".b64";

//    CryptoPP::FileSource(filename.toUtf8().constData(), true,
//                         new CryptoPP::Base64Encoder(
//                             new CryptoPP::FileSink(destfile.toUtf8().constData())));
//}

//void base64Decoding(const QString& filename)
//{
//    QString only_filename = QFileInfo(filename).fileName();

//    const QString srcPath = filename.left(filename.lastIndexOf("/"));
//    int lastExtension = only_filename.lastIndexOf(".");

//    const QString destfile = srcPath + "/orig_" + only_filename.left(lastExtension);

//    CryptoPP::FileSource(filename.toUtf8().constData(), true,
//                         new CryptoPP::Base64Decoder(
//                             new CryptoPP::FileSink(destfile.toUtf8().constData())));
//}

//QString createDefaultSeedingDir(const QString& filepath)
//{
//    QString documents_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
//    qDebug() << "Standard Documents dir =" << documents_dir << "\n";

//    if (!documents_dir.contains("Documents")) {
//        documents_dir += "/Documents";
//        QDir().mkdir(documents_dir);
//        qDebug() << "Created '~/Documents' successfully!\n";
//    }

//    const QString seeding_dir = documents_dir + "/cryptoBT/Seeding/";
//    if (!QDir(seeding_dir).exists()) {
//        QDir().mkpath(seeding_dir);
//        qDebug() << "Created '~/Documents/cryptBT/Seeding' successfully!\n";
//    }

//    const QString outFile = seeding_dir + QFileInfo(filepath).fileName() + ".enf";
//    qDebug() << "Output file: " << outFile;

//    return outFile;
//}
