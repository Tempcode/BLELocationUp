#ifndef BASEDATA_H
#define BASEDATA_H

#include <QString>
#include <QByteArray>
#include <QVector>

#define		ADDRLENGTH                  (6)
#define		BLEMonitorLENGTH			(13)

#define     POINTCOUNT4LOCATING         (3)

/***** Structure of Under machine send ****/
typedef struct tagBLEMonitor
{
    QString     mAddr;
    QString     cAddr;
    qint8       cRssi;
}BLEMonitor;



/****************** DataBase ********************/
#define DBFilePath  ("./DATA")
#define DBFileName  ("./DATA/Data.db")

#define PersonnelInfoTableName  ("PersonnelInfo")
#define DutyTableName           ("Duty")
#define TitleTableName          ("Title")
#define AnchorTableName         ("Anchor")
#define CurrentPosViewName     ("CurrentPos")
#define PosRecordTableName      ("PosRecord")


#define FOREIGN_KEY_ON ("PRAGMA foreign_keys = ON;")

#define CREATE_ANCHOR       ("CREATE TABLE Anchor("\
                                "DevAddress	TEXT PRIMARY KEY,"\
                                "X	INTEGER,"\
                                "Y	INTEGER);")

#define CREATE_PERSONNELINFO ("CREATE TABLE PersonnelInfo("\
                                "CardAddress	TEXT PRIMARY KEY,"\
                                "Name       TEXT,"\
                                "Sex		TEXT,"\
                                "BirthDay	TEXT,"\
                                "TitleId    INTEGER,"\
                                "DutyId     INTEGER,"\
                                "TelePhone	TEXT,"\
                                "HomePhone	TEXT,"\
                                "FOREIGN KEY(TitleId) REFERENCES Title(Id),"\
                                "FOREIGN KEY(DutyId) REFERENCES Duty(Id));")

#define CREATE_POSRECORD    ("CREATE TABLE PosRecord("\
                                "Id	INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "RecordTime	TEXT,"\
                                "CardAddress	TEXT,"\
                                "X	INTEGER,"\
                                "Y	INTEGER,"\
                                "FOREIGN KEY(CardAddress) REFERENCES PersonnelInfo(CardAddress));")

#define CREATE_VIEW_CURRENTPOS  ("CREATE VIEW CurrentPos AS "\
                                    "SELECT Name, PosRecord.CardAddress, RecordTime, X, Y "\
                                    "FROM PosRecord INNER JOIN PersonnelInfo "\
                                    "ON PersonnelInfo.CardAddress = PosRecord.CardAddress "\
                                    "GROUP BY Name, PosRecord.CardAddress "\
                                    "ORDER BY RecordTime DESC;")

#define CREATE_DUTY         ("CREATE TABLE Duty("\
                                "Id	INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "DutyTimeStart 	TEXT,"\
                                "DutyTimeEnd	TEXT);")

#define CREATE_TITLE        ("CREATE TABLE Title("\
                                "Id	INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "Title TEXT);")

#endif // BASEDATA_H

